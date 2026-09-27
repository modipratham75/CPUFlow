#include<stdio.h>

#define MAX 100

int main()
{
    int choice;
    int count = 0;

    int id[MAX];
    int arr_time[MAX];
    int bur_time[MAX];
    int priority[MAX];

    do
    {
        printf("\n========== PROCESS MANAGEMENT ==========\n");
        printf("1. Create Process\n");
        printf("2. Display Process\n");
        printf("3. Search Process\n");
        printf("4. Update Process\n");
        printf("5. Delete Process\n");
        printf("6. Exit\n");
        printf("=========================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int n;

                printf("Enter Number of Process: ");
                scanf("%d", &n);

                if(n > MAX - count)
                {
                    printf("Number of processes exceeds the limit.\n");

                    n = MAX - count;

                    printf("Only %d processes can be added.\n", n);
                }

                for(int i = 0; i < n; i++)
                {
                    printf("\nProcess %d\n", count + 1);

                    printf("Enter Process ID: ");
                    scanf("%d", &id[count]);

                    printf("Enter Arrival Time: ");
                    scanf("%d", &arr_time[count]);

                    printf("Enter Burst Time: ");
                    scanf("%d", &bur_time[count]);

                    printf("Enter Priority: ");
                    scanf("%d", &priority[count]);

                    count++;
                }

                FILE *fp;

                fp = fopen("processes.txt", "w");

                for(int i = 0; i < count; i++)
                {
                    fprintf(fp, "%d %d %d %d\n",
                            id[i],
                            arr_time[i],
                            bur_time[i],
                            priority[i]);
                }

                fclose(fp);

                printf("Processes saved successfully.\n");
            }
            break;


            case 2:
            {
                if(count == 0)
                {
                    printf("No Process Available.\n");
                }
                else
                {
                    printf("\nID\tArrival Time\tBurst Time\tPriority\n");

                    for(int i = 0; i < count; i++)
                    {
                        printf("P%d\t%d\t\t%d\t\t%d\n",
                               id[i],
                               arr_time[i],
                               bur_time[i],
                               priority[i]);
                    }
                }
            }
            break;


            case 3:
            {
                int item;
                int found = 0;

                if(count == 0)
                {
                    printf("No Process Available.\n");
                }
                else
                {
                    printf("Enter Process ID to be searched: ");
                    scanf("%d", &item);

                    for(int i = 0; i < count; i++)
                    {
                        if(item == id[i])
                        {
                            printf("Process Found.\n");

                            printf("\nID\tArrival Time\tBurst Time\tPriority\n");

                            printf("P%d\t%d\t\t%d\t\t%d\n",
                                   id[i],
                                   arr_time[i],
                                   bur_time[i],
                                   priority[i]);

                            found = 1;

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


            case 4:
            {
                int updateID;
                int found = 0;

                if(count == 0)
                {
                    printf("No Process Available.\n");
                }
                else
                {
                    printf("Enter Process ID to be updated: ");
                    scanf("%d", &updateID);

                    for(int i = 0; i < count; i++)
                    {
                        if(updateID == id[i])
                        {
                            printf("\nProcess Found.\n");

                            printf("Enter New Arrival Time: ");
                            scanf("%d", &arr_time[i]);

                            printf("Enter New Burst Time: ");
                            scanf("%d", &bur_time[i]);

                            printf("Enter New Priority: ");
                            scanf("%d", &priority[i]);

                            FILE *fp;

                            fp = fopen("processes.txt", "w");

                            for(int j = 0; j < count; j++)
                            {
                                fprintf(fp, "%d %d %d %d\n",
                                        id[j],
                                        arr_time[j],
                                        bur_time[j],
                                        priority[j]);
                            }

                            fclose(fp);

                            printf("Process Updated Successfully.\n");

                            found = 1;

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


            case 5:
            {
                int delid;
                int found = 0;

                if(count == 0)
                {
                    printf("No Process Available.\n");
                }
                else
                {
                    printf("Enter ID of the Process to be deleted: ");
                    scanf("%d", &delid);

                    for(int i = 0; i < count; i++)
                    {
                        if(delid == id[i])
                        {
                            for(int j = i; j < count - 1; j++)
                            {
                                id[j] = id[j + 1];

                                arr_time[j] = arr_time[j + 1];

                                bur_time[j] = bur_time[j + 1];

                                priority[j] = priority[j + 1];
                            }

                            count--;

                            FILE *fp;

                            fp = fopen("processes.txt", "w");

                            for(int j = 0; j < count; j++)
                            {
                                fprintf(fp, "%d %d %d %d\n",
                                        id[j],
                                        arr_time[j],
                                        bur_time[j],
                                        priority[j]);
                            }

                            fclose(fp);

                            printf("Process Deleted.\n");

                            found = 1;

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


            case 6:
                printf("Exiting....\n");
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);

    return 0;
}