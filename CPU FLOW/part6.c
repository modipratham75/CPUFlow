#include<stdio.h>

#define MAX 100

int main()
{
    int choice;

    int id[MAX];
    int arr_time[MAX];
    int bur_time[MAX];
    int priority[MAX];

    int PC[MAX];
    int accumulator[MAX];

    int state[MAX];

    int count = 0;
    int currentProcess = -1;

    int contextSwitches = 0;

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
        PC[count] = 0;
        accumulator[count] = 0;
        state[count] = 0;

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
        printf("\n========== CONTEXT SWITCHING ==========\n");
        printf("1. Display Processes\n");
        printf("2. Run Process\n");
        printf("3. Execute Process\n");
        printf("4. Context Switch\n");
        printf("5. Display CPU State\n");
        printf("6. Reset Process State\n");
        printf("7. Exit\n");
        printf("=======================================\n");

        printf("Enter Choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid Input.\n");

            while(getchar() != '\n');

            choice = 0;
        }

        switch(choice)
        {
            case 1:
            {
                printf("\nID\tPC\tAccumulator\tState\n");

                for(int i = 0; i < count; i++)
                {
                    if(state[i] == 1)
                    {
                        printf("P%d\t%d\t%d\t\tRunning\n",
                               id[i],
                               PC[i],
                               accumulator[i]);
                    }
                    else
                    {
                        printf("P%d\t%d\t%d\t\tReady\n",
                               id[i],
                               PC[i],
                               accumulator[i]);
                    }
                }
            }
            break;


            case 2:
            {
                int processID;
                int found = 0;

                printf("Enter Process ID to run: ");

                if(scanf("%d", &processID) != 1)
                {
                    printf("Invalid Input.\n");

                    while(getchar() != '\n');

                    break;
                }

                for(int i = 0; i < count; i++)
                {
                    if(id[i] == processID)
                    {
                        found = 1;

                        if(currentProcess != -1)
                        {
                            state[currentProcess] = 0;
                        }

                        currentProcess = i;

                        state[i] = 1;

                        printf("\nProcess P%d is now Running.\n",
                               id[i]);

                        printf("PC = %d\n",
                               PC[i]);

                        printf("Accumulator = %d\n",
                               accumulator[i]);

                        break;
                    }
                }

                if(found == 0)
                {
                    printf("Process Not Found.\n");
                }
            }
            break;


            case 3:
            {
                int steps;

                if(currentProcess == -1)
                {
                    printf("No Process is currently running.\n");
                }
                else
                {
                    printf("\n========== PROCESS EXECUTION ==========\n");

                    printf("Running Process = P%d\n",
                           id[currentProcess]);

                    printf("Current PC = %d\n",
                           PC[currentProcess]);

                    printf("Current Accumulator = %d\n",
                           accumulator[currentProcess]);

                    printf("\nEnter Number of Instructions to Execute: ");

                    if(scanf("%d", &steps) != 1)
                    {
                        printf("Invalid Input.\n");

                        while(getchar() != '\n');

                        break;
                    }

                    if(steps <= 0)
                    {
                        printf("Invalid Number of Instructions.\n");
                    }
                    else
                    {
                        for(int i = 0; i < steps; i++)
                        {
                            PC[currentProcess]++;

                            accumulator[currentProcess] =
                                accumulator[currentProcess] + 5;
                        }

                        printf("\nProcess P%d executed successfully.\n",
                               id[currentProcess]);

                        printf("Instructions Executed = %d\n",
                               steps);

                        printf("PC after execution = %d\n",
                               PC[currentProcess]);

                        printf("Accumulator after execution = %d\n",
                               accumulator[currentProcess]);
                    }
                }
            }
            break;


            case 4:
            {
                int processID;
                int nextProcess = -1;

                if(currentProcess == -1)
                {
                    printf("No Process is currently running.\n");
                }
                else
                {
                    printf("\n========== CONTEXT SWITCH ==========\n");

                    printf("Current Process: P%d\n",
                           id[currentProcess]);

                    printf("Current PC = %d\n",
                           PC[currentProcess]);

                    printf("Current Accumulator = %d\n",
                           accumulator[currentProcess]);

                    printf("\nEnter Process ID to switch to: ");

                    if(scanf("%d", &processID) != 1)
                    {
                        printf("Invalid Input.\n");

                        while(getchar() != '\n');

                        break;
                    }

                    for(int i = 0; i < count; i++)
                    {
                        if(id[i] == processID)
                        {
                            nextProcess = i;
                            break;
                        }
                    }

                    if(nextProcess == -1)
                    {
                        printf("Process Not Found.\n");
                    }
                    else if(nextProcess == currentProcess)
                    {
                        printf("Process is already running.\n");
                    }
                    else
                    {
                        printf("\nSaving state of P%d...\n",
                               id[currentProcess]);

                        state[currentProcess] = 0;

                        printf("PC saved = %d\n",
                               PC[currentProcess]);

                        printf("Accumulator saved = %d\n",
                               accumulator[currentProcess]);

                        printf("\nLoading state of P%d...\n",
                               id[nextProcess]);

                        currentProcess = nextProcess;

                        state[nextProcess] = 1;

                        printf("PC loaded = %d\n",
                               PC[nextProcess]);

                        printf("Accumulator loaded = %d\n",
                               accumulator[nextProcess]);

                        contextSwitches++;

                        FILE *fp;

                        fp = fopen("contextSwitches.txt", "w");

                        if(fp != NULL)
                        {
                            fprintf(fp, "%d\n",
                                    contextSwitches);

                            fclose(fp);
                        }

                        printf("\nContext Switch Completed.\n");

                        printf("Total Context Switches = %d\n",
                               contextSwitches);
                    }
                }
            }
            break;


            case 5:
            {
                if(currentProcess == -1)
                {
                    printf("\nNo Process is currently running.\n");
                }
                else
                {
                    printf("\n========== CPU STATE ==========\n");

                    printf("Running Process = P%d\n",
                           id[currentProcess]);

                    printf("Program Counter = %d\n",
                           PC[currentProcess]);

                    printf("Accumulator = %d\n",
                           accumulator[currentProcess]);

                    printf("Process State = Running\n");

                    printf("Context Switches = %d\n",
                           contextSwitches);
                }
            }
            break;


            case 6:
            {
                for(int i = 0; i < count; i++)
                {
                    PC[i] = 0;

                    accumulator[i] = 0;

                    state[i] = 0;
                }

                currentProcess = -1;

                contextSwitches = 0;

                FILE *fp;

                fp = fopen("contextSwitches.txt", "w");

                if(fp != NULL)
                {
                    fprintf(fp, "0\n");

                    fclose(fp);
                }

                printf("All Process States Reset Successfully.\n");
            }
            break;


            case 7:
                printf("Exiting....\n");
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 7);

    return 0;
}