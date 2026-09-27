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

    int front = 0;
    int rear = -1;

    FILE *file;

    file = fopen("processes.txt", "r");

    if(file == NULL)
    {
        printf("File not found.\n");
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

    int readyQueue[MAX];

    do
    {
        printf("\n========== READY QUEUE ==========\n");
        printf("1. Add Process to Queue\n");
        printf("2. Remove Process from Queue\n");
        printf("3. Display Ready Queue\n");
        printf("4. Peek\n");
        printf("5. Exit\n");
        printf("=================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int processID;
                int found = 0;

                if(rear == MAX - 1)
                {
                    printf("Ready Queue is Full.\n");
                }
                else
                {
                    printf("Enter Process ID: ");
                    scanf("%d", &processID);

                    for(int i = 0; i < count; i++)
                    {
                        if(processID == id[i])
                        {
                            found = 1;

                            int alreadyAdded = 0;

                            for(int j = front; j <= rear; j++)
                            {
                                if(readyQueue[j] == i)
                                {
                                    alreadyAdded = 1;
                                    break;
                                }
                            }

                            if(alreadyAdded == 1)
                            {
                                printf("Process P%d is already in Ready Queue.\n",
                                       id[i]);
                            }
                            else
                            {
                                rear++;
                                readyQueue[rear] = i;

                                printf("Process P%d added to Ready Queue.\n",
                                       id[i]);

                                /* Update readyQueue.txt */

                                FILE *fp;

                                fp = fopen("readyQueue.txt", "w");

                                for(int j = front; j <= rear; j++)
                                {
                                    int index = readyQueue[j];

                                    fprintf(fp, "%d %d %d %d\n",
                                            id[index],
                                            arr_time[index],
                                            bur_time[index],
                                            priority[index]);
                                }

                                fclose(fp);

                                printf("Ready Queue saved successfully.\n");
                            }

                            break;
                        }
                    }

                    if(found == 0)
                    {
                        printf("Process Not Found.\n");
                    }
                }
            }
            break;


            case 2:
            {
                if(front > rear)
                {
                    printf("Ready Queue is Empty.\n");
                }
                else
                {
                    int index = readyQueue[front];

                    printf("Process P%d removed from Ready Queue.\n",
                           id[index]);

                    front++;

                    if(front > rear)
                    {
                        front = 0;
                        rear = -1;
                    }

                    /* Update readyQueue.txt */

                    FILE *fp;

                    fp = fopen("readyQueue.txt", "w");

                    for(int j = front; j <= rear; j++)
                    {
                        int index = readyQueue[j];

                        fprintf(fp, "%d %d %d %d\n",
                                id[index],
                                arr_time[index],
                                bur_time[index],
                                priority[index]);
                    }

                    fclose(fp);

                    printf("Ready Queue saved successfully.\n");
                }
            }
            break;


            case 3:
            {
                if(front > rear)
                {
                    printf("Ready Queue is Empty.\n");
                }
                else
                {
                    printf("\nID\tArrival Time\tBurst Time\tPriority\n");

                    for(int i = front; i <= rear; i++)
                    {
                        int index = readyQueue[i];

                        printf("P%d\t%d\t\t%d\t\t%d\n",
                               id[index],
                               arr_time[index],
                               bur_time[index],
                               priority[index]);
                    }
                }
            }
            break;


            case 4:
            {
                if(front > rear)
                {
                    printf("Ready Queue is Empty.\n");
                }
                else
                {
                    int index = readyQueue[front];

                    printf("\nFront Process:\n");
                    printf("ID\tArrival Time\tBurst Time\tPriority\n");

                    printf("P%d\t%d\t\t%d\t\t%d\n",
                           id[index],
                           arr_time[index],
                           bur_time[index],
                           priority[index]);
                }
            }
            break;


            case 5:
                printf("Exiting....\n");
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 5);

    return 0;
}