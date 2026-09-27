#include<stdio.h>

#define MAX 100

int main()
{
    int choice;

    int id[MAX];
    int arr_time[MAX];
    int bur_time[MAX];
    int priority[MAX];

    int count = 0;

    FILE *file;

    file = fopen("readyQueue.txt", "r");

    if(file == NULL)
    {
        printf("readyQueue.txt not found.\n");
        printf("Run Part 2 first.\n");

        return 0;
    }

    while(fscanf(file, "%d %d %d %d",
                 &id[count],
                 &arr_time[count],
                 &bur_time[count],
                 &priority[count]) == 4)
    {
        count++;
    }

    fclose(file);

    if(count == 0)
    {
        printf("No Process Available in Ready Queue.\n");
        return 0;
    }

    do
    {
        printf("\n========== CPU SCHEDULING ==========\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. SRTF\n");
        printf("4. Priority Scheduling\n");
        printf("5. Round Robin\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            /* ================= FCFS ================= */

            case 1:
            {
                int order[MAX];
                int completion[MAX];
                int turnaround[MAX];
                int waiting[MAX];

                for(int i = 0; i < count; i++)
                {
                    order[i] = i;
                }

                for(int i = 0; i < count - 1; i++)
                {
                    for(int j = 0; j < count - i - 1; j++)
                    {
                        if(arr_time[order[j]] > arr_time[order[j + 1]])
                        {
                            int temp = order[j];

                            order[j] = order[j + 1];
                            order[j + 1] = temp;
                        }
                    }
                }

                int currentTime = 0;

                printf("\n========== FCFS ==========\n");

                printf("Gantt Chart:\n");

                for(int i = 0; i < count; i++)
                {
                    int index = order[i];

                    if(currentTime < arr_time[index])
                    {
                        currentTime = arr_time[index];
                    }

                    printf("| P%d ", id[index]);

                    currentTime =
                        currentTime + bur_time[index];

                    completion[index] = currentTime;

                    turnaround[index] =
                        completion[index] - arr_time[index];

                    waiting[index] =
                        turnaround[index] - bur_time[index];
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < count; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           id[i],
                           arr_time[i],
                           bur_time[i],
                           completion[i],
                           turnaround[i],
                           waiting[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT += waiting[i];
                    totalTAT += turnaround[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / count);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / count);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "FCFS\n");
                fprintf(fp, "%d\n", count);

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            completion[i],
                            turnaround[i],
                            waiting[i]);
                }

                fclose(fp);

                printf("\nScheduling results saved successfully.\n");
            }
            break;


            /* ================= SJF ================= */

            case 2:
            {
                int completed[MAX] = {0};
                int completion[MAX];
                int turnaround[MAX];
                int waiting[MAX];

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== SJF ==========\n");

                printf("Gantt Chart:\n");

                while(completedCount < count)
                {
                    int selected = -1;

                    for(int i = 0; i < count; i++)
                    {
                        if(completed[i] == 0 &&
                           arr_time[i] <= currentTime)
                        {
                            if(selected == -1 ||
                               bur_time[i] < bur_time[selected])
                            {
                                selected = i;
                            }
                        }
                    }

                    if(selected == -1)
                    {
                        currentTime++;
                    }
                    else
                    {
                        printf("| P%d ", id[selected]);

                        currentTime =
                            currentTime + bur_time[selected];

                        completion[selected] = currentTime;

                        turnaround[selected] =
                            completion[selected] - arr_time[selected];

                        waiting[selected] =
                            turnaround[selected] - bur_time[selected];

                        completed[selected] = 1;
                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < count; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           id[i],
                           arr_time[i],
                           bur_time[i],
                           completion[i],
                           turnaround[i],
                           waiting[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT += waiting[i];
                    totalTAT += turnaround[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / count);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / count);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "SJF\n");
                fprintf(fp, "%d\n", count);

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            completion[i],
                            turnaround[i],
                            waiting[i]);
                }

                fclose(fp);

                printf("\nScheduling results saved successfully.\n");
            }
            break;


            /* ================= SRTF ================= */

            case 3:
            {
                int remaining[MAX];

                int completion[MAX];
                int turnaround[MAX];
                int waiting[MAX];

                for(int i = 0; i < count; i++)
                {
                    remaining[i] = bur_time[i];
                }

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== SRTF ==========\n");

                printf("Execution:\n");

                while(completedCount < count)
                {
                    int selected = -1;

                    for(int i = 0; i < count; i++)
                    {
                        if(arr_time[i] <= currentTime &&
                           remaining[i] > 0)
                        {
                            if(selected == -1 ||
                               remaining[i] < remaining[selected])
                            {
                                selected = i;
                            }
                        }
                    }

                    if(selected == -1)
                    {
                        currentTime++;
                    }
                    else
                    {
                        printf("P%d ",
                               id[selected]);

                        remaining[selected]--;

                        currentTime++;

                        if(remaining[selected] == 0)
                        {
                            completion[selected] = currentTime;

                            turnaround[selected] =
                                completion[selected] - arr_time[selected];

                            waiting[selected] =
                                turnaround[selected] - bur_time[selected];

                            completedCount++;
                        }
                    }
                }

                printf("\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < count; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           id[i],
                           arr_time[i],
                           bur_time[i],
                           completion[i],
                           turnaround[i],
                           waiting[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT += waiting[i];
                    totalTAT += turnaround[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / count);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / count);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "SRTF\n");
                fprintf(fp, "%d\n", count);

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            completion[i],
                            turnaround[i],
                            waiting[i]);
                }

                fclose(fp);

                printf("\nScheduling results saved successfully.\n");
            }
            break;


            /* ================= PRIORITY ================= */

            case 4:
            {
                int completed[MAX] = {0};

                int completion[MAX];
                int turnaround[MAX];
                int waiting[MAX];

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== PRIORITY SCHEDULING ==========\n");

                printf("Gantt Chart:\n");

                while(completedCount < count)
                {
                    int selected = -1;

                    for(int i = 0; i < count; i++)
                    {
                        if(completed[i] == 0 &&
                           arr_time[i] <= currentTime)
                        {
                            if(selected == -1 ||
                               priority[i] < priority[selected])
                            {
                                selected = i;
                            }
                        }
                    }

                    if(selected == -1)
                    {
                        currentTime++;
                    }
                    else
                    {
                        printf("| P%d ", id[selected]);

                        currentTime =
                            currentTime + bur_time[selected];

                        completion[selected] = currentTime;

                        turnaround[selected] =
                            completion[selected] - arr_time[selected];

                        waiting[selected] =
                            turnaround[selected] - bur_time[selected];

                        completed[selected] = 1;

                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

                for(int i = 0; i < count; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
                           id[i],
                           arr_time[i],
                           bur_time[i],
                           priority[i],
                           completion[i],
                           turnaround[i],
                           waiting[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT += waiting[i];
                    totalTAT += turnaround[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / count);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / count);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "Priority\n");
                fprintf(fp, "%d\n", count);

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            completion[i],
                            turnaround[i],
                            waiting[i]);
                }

                fclose(fp);

                printf("\nScheduling results saved successfully.\n");
            }
            break;


            /* ================= ROUND ROBIN ================= */

            case 5:
            {
                int remaining[MAX];

                int completion[MAX];
                int turnaround[MAX];
                int waiting[MAX];

                int queue[MAX * 10];

                int front = 0;
                int rear = 0;

                int added[MAX] = {0};

                int quantum;

                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);

                for(int i = 0; i < count; i++)
                {
                    remaining[i] = bur_time[i];
                }

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== ROUND ROBIN ==========\n");

                printf("Execution:\n");

                while(completedCount < count)
                {
                    for(int i = 0; i < count; i++)
                    {
                        if(arr_time[i] <= currentTime &&
                           added[i] == 0)
                        {
                            queue[rear] = i;
                            rear++;

                            added[i] = 1;
                        }
                    }

                    if(front == rear)
                    {
                        currentTime++;
                        continue;
                    }

                    int index = queue[front];
                    front++;

                    int executeTime;

                    if(remaining[index] > quantum)
                    {
                        executeTime = quantum;
                    }
                    else
                    {
                        executeTime = remaining[index];
                    }

                    printf("| P%d ",
                           id[index]);

                    remaining[index] =
                        remaining[index] - executeTime;

                    currentTime =
                        currentTime + executeTime;

                    for(int i = 0; i < count; i++)
                    {
                        if(arr_time[i] <= currentTime &&
                           added[i] == 0)
                        {
                            queue[rear] = i;
                            rear++;

                            added[i] = 1;
                        }
                    }

                    if(remaining[index] > 0)
                    {
                        queue[rear] = index;
                        rear++;
                    }
                    else
                    {
                        completion[index] = currentTime;

                        turnaround[index] =
                            completion[index] - arr_time[index];

                        waiting[index] =
                            turnaround[index] - bur_time[index];

                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < count; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           id[i],
                           arr_time[i],
                           bur_time[i],
                           completion[i],
                           turnaround[i],
                           waiting[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT += waiting[i];
                    totalTAT += turnaround[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / count);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / count);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "Round Robin\n");
                fprintf(fp, "%d\n", count);

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            completion[i],
                            turnaround[i],
                            waiting[i]);
                }

                fclose(fp);

                printf("\nScheduling results saved successfully.\n");
            }
            break;


            case 6:
                printf("Exiting....\n");
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);

    return 0;
}