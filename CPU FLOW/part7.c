#include<stdio.h>

#define MAX 100

int main()
{
    int choice;

    char algorithm[30];

    int id[MAX];
    int arr_time[MAX];
    int bur_time[MAX];
    int comp_time[MAX];
    int turnaround[MAX];
    int waiting[MAX];

    int count = 0;

    int cacheHits = 0;
    int cacheMisses = 0;

    int contextSwitches = 0;

    float avgWaitingTime = 0;
    float avgTurnaroundTime = 0;

    float cpuUtilization = 0;
    float throughput = 0;

    float hitRate = 0;
    float missRate = 0;

    do
    {
        printf("\n========== PERFORMANCE ANALYSIS ==========\n");
        printf("1. Calculate Performance\n");
        printf("2. Display Scheduling Results\n");
        printf("3. Display Cache Results\n");
        printf("4. Display Context Switch Results\n");
        printf("5. Exit\n");
        printf("==========================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                FILE *fp;

                fp = fopen("schedulingResults.txt", "r");

                if(fp == NULL)
                {
                    printf("\nschedulingResults.txt not found.\n");
                    printf("Run Part 3 first.\n");
                    break;
                }

                count = 0;

                fscanf(fp, "%s", algorithm);
                fscanf(fp, "%d", &count);

                for(int i = 0; i < count; i++)
                {
                    fscanf(fp, "%d %d %d %d %d %d",
                           &id[i],
                           &arr_time[i],
                           &bur_time[i],
                           &comp_time[i],
                           &turnaround[i],
                           &waiting[i]);
                }

                fclose(fp);


                /* Calculate Scheduling Performance */

                float totalWT = 0;
                float totalTAT = 0;

                int firstArrival = arr_time[0];
                int lastCompletion = comp_time[0];

                int totalBurstTime = 0;

                for(int i = 0; i < count; i++)
                {
                    totalWT =
                        totalWT + waiting[i];

                    totalTAT =
                        totalTAT + turnaround[i];

                    totalBurstTime =
                        totalBurstTime + bur_time[i];

                    if(arr_time[i] < firstArrival)
                    {
                        firstArrival = arr_time[i];
                    }

                    if(comp_time[i] > lastCompletion)
                    {
                        lastCompletion = comp_time[i];
                    }
                }

                avgWaitingTime =
                    totalWT / count;

                avgTurnaroundTime =
                    totalTAT / count;

                int totalTime =
                    lastCompletion - firstArrival;

                if(totalTime > 0)
                {
                    cpuUtilization =
                        (float)totalBurstTime /
                        totalTime * 100;

                    throughput =
                        (float)count /
                        totalTime;
                }


                /* Read Cache Results */

                fp = fopen("cacheResults.txt", "r");

                if(fp != NULL)
                {
                    fscanf(fp, "%d %d",
                           &cacheHits,
                           &cacheMisses);

                    fclose(fp);
                }
                else
                {
                    cacheHits = 0;
                    cacheMisses = 0;
                }


                /* Calculate Cache Performance */

                if(cacheHits + cacheMisses > 0)
                {
                    hitRate =
                        (float)cacheHits /
                        (cacheHits + cacheMisses) * 100;

                    missRate =
                        (float)cacheMisses /
                        (cacheHits + cacheMisses) * 100;
                }
                else
                {
                    hitRate = 0;
                    missRate = 0;
                }


                /* Read Context Switch Results */

                fp = fopen("contextSwitches.txt", "r");

                if(fp != NULL)
                {
                    fscanf(fp, "%d",
                           &contextSwitches);

                    fclose(fp);
                }
                else
                {
                    contextSwitches = 0;
                }


                /* Display Final Analysis */

                printf("\n========== FINAL PERFORMANCE ANALYSIS ==========\n");

                printf("\n----- CPU SCHEDULING -----\n");

                printf("Algorithm                = %s\n",
                       algorithm);

                printf("Number of Processes      = %d\n",
                       count);

                printf("Average Waiting Time     = %.2f\n",
                       avgWaitingTime);

                printf("Average Turnaround Time  = %.2f\n",
                       avgTurnaroundTime);

                printf("CPU Utilization          = %.2f%%\n",
                       cpuUtilization);

                printf("Throughput               = %.2f processes/unit time\n",
                       throughput);


                printf("\n----- CONTEXT SWITCHING -----\n");

                printf("Context Switches         = %d\n",
                       contextSwitches);


                printf("\n----- CACHE PERFORMANCE -----\n");

                printf("Cache Hits               = %d\n",
                       cacheHits);

                printf("Cache Misses             = %d\n",
                       cacheMisses);

                printf("Cache Hit Rate           = %.2f%%\n",
                       hitRate);

                printf("Cache Miss Rate          = %.2f%%\n",
                       missRate);


                printf("\n===============================================\n");
            }
            break;


            case 2:
            {
                FILE *fp;

                fp = fopen("schedulingResults.txt", "r");

                if(fp == NULL)
                {
                    printf("schedulingResults.txt not found.\n");
                }
                else
                {
                    fscanf(fp, "%s", algorithm);
                    fscanf(fp, "%d", &count);

                    printf("\n========== SCHEDULING RESULTS ==========\n");

                    printf("Algorithm: %s\n\n",
                           algorithm);

                    printf("ID\tAT\tBT\tCT\tTAT\tWT\n");

                    for(int i = 0; i < count; i++)
                    {
                        fscanf(fp, "%d %d %d %d %d %d",
                               &id[i],
                               &arr_time[i],
                               &bur_time[i],
                               &comp_time[i],
                               &turnaround[i],
                               &waiting[i]);

                        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                               id[i],
                               arr_time[i],
                               bur_time[i],
                               comp_time[i],
                               turnaround[i],
                               waiting[i]);
                    }

                    fclose(fp);
                }
            }
            break;


            case 3:
            {
                FILE *fp;

                fp = fopen("cacheResults.txt", "r");

                if(fp == NULL)
                {
                    printf("cacheResults.txt not found.\n");
                }
                else
                {
                    fscanf(fp, "%d %d",
                           &cacheHits,
                           &cacheMisses);

                    fclose(fp);

                    printf("\n========== CACHE RESULTS ==========\n");

                    printf("Cache Hits   = %d\n",
                           cacheHits);

                    printf("Cache Misses = %d\n",
                           cacheMisses);

                    if(cacheHits + cacheMisses > 0)
                    {
                        hitRate =
                            (float)cacheHits /
                            (cacheHits + cacheMisses) * 100;

                        missRate =
                            (float)cacheMisses /
                            (cacheHits + cacheMisses) * 100;
                    }

                    printf("Hit Rate     = %.2f%%\n",
                           hitRate);

                    printf("Miss Rate    = %.2f%%\n",
                           missRate);
                }
            }
            break;


            case 4:
            {
                FILE *fp;

                fp = fopen("contextSwitches.txt", "r");

                if(fp == NULL)
                {
                    printf("contextSwitches.txt not found.\n");
                }
                else
                {
                    fscanf(fp, "%d",
                           &contextSwitches);

                    fclose(fp);

                    printf("\n========== CONTEXT SWITCH RESULTS ==========\n");

                    printf("Total Context Switches = %d\n",
                           contextSwitches);
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