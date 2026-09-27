#include<stdio.h>

#define MAX 100
#define MEMORY_SIZE 100
#define CACHE_SIZE 4

int id[MAX];
int arr_time[MAX];
int bur_time[MAX];
int priority[MAX];

int count = 0;

int readyQueue[MAX];
int front = 0;
int rear = -1;

int memory[MEMORY_SIZE];
int cache[CACHE_SIZE];

int memorySize = 0;
int cacheCount = 0;

int hits = 0;
int misses = 0;

int PC[MAX];
int accumulator[MAX];
int state[MAX];

int currentProcess = -1;
int contextSwitches = 0;


/* ================= FILE FUNCTIONS ================= */

void saveProcesses()
{
    FILE *fp;

    fp = fopen("processes.txt", "w");

    if(fp == NULL)
    {
        printf("Unable to save processes.\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %d %d %d\n",
                id[i],
                arr_time[i],
                bur_time[i],
                priority[i]);
    }

    fclose(fp);
}


void loadProcesses()
{
    FILE *fp;

    fp = fopen("processes.txt", "r");

    if(fp == NULL)
    {
        return;
    }

    count = 0;

    while(fscanf(fp, "%d %d %d %d",
                 &id[count],
                 &arr_time[count],
                 &bur_time[count],
                 &priority[count]) == 4)
    {
        count++;
    }

    fclose(fp);
}


void saveReadyQueue()
{
    FILE *fp;

    fp = fopen("readyQueue.txt", "w");

    if(fp == NULL)
    {
        return;
    }

    for(int i = front; i <= rear; i++)
    {
        int index = readyQueue[i];

        fprintf(fp, "%d %d %d %d\n",
                id[index],
                arr_time[index],
                bur_time[index],
                priority[index]);
    }

    fclose(fp);
}


/* ================= PART 1 ================= */

void processManagement()
{
    int choice;

    do
    {
        printf("\n========== PROCESS MANAGEMENT ==========\n");
        printf("1. Create Process\n");
        printf("2. Display Process\n");
        printf("3. Search Process\n");
        printf("4. Update Process\n");
        printf("5. Delete Process\n");
        printf("6. Back to Main Menu\n");
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
                    printf("Only %d processes can be added.\n",
                           MAX - count);

                    n = MAX - count;
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

                    PC[count] = 0;
                    accumulator[count] = 0;
                    state[count] = 0;

                    count++;
                }

                saveProcesses();

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
                int searchID;
                int found = 0;

                printf("Enter Process ID to be searched: ");
                scanf("%d", &searchID);

                for(int i = 0; i < count; i++)
                {
                    if(id[i] == searchID)
                    {
                        printf("\nProcess Found.\n");

                        printf("ID = P%d\n", id[i]);
                        printf("Arrival Time = %d\n",
                               arr_time[i]);
                        printf("Burst Time = %d\n",
                               bur_time[i]);
                        printf("Priority = %d\n",
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
            break;


            case 4:
            {
                int updateID;
                int found = 0;

                printf("Enter Process ID to be updated: ");
                scanf("%d", &updateID);

                for(int i = 0; i < count; i++)
                {
                    if(id[i] == updateID)
                    {
                        printf("Enter New Arrival Time: ");
                        scanf("%d", &arr_time[i]);

                        printf("Enter New Burst Time: ");
                        scanf("%d", &bur_time[i]);

                        printf("Enter New Priority: ");
                        scanf("%d", &priority[i]);

                        saveProcesses();

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
            break;


            case 5:
            {
                int deleteID;
                int found = 0;

                printf("Enter ID of Process to be deleted: ");
                scanf("%d", &deleteID);

                for(int i = 0; i < count; i++)
                {
                    if(id[i] == deleteID)
                    {
                        for(int j = i; j < count - 1; j++)
                        {
                            id[j] = id[j + 1];
                            arr_time[j] = arr_time[j + 1];
                            bur_time[j] = bur_time[j + 1];
                            priority[j] = priority[j + 1];
                        }

                        count--;

                        saveProcesses();

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
            break;


            case 6:
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);
}


/* ================= PART 2 ================= */

void readyQueueManagement()
{
    int choice;

    do
    {
        printf("\n========== READY QUEUE ==========\n");
        printf("1. Add Process to Queue\n");
        printf("2. Remove Process from Queue\n");
        printf("3. Display Ready Queue\n");
        printf("4. Peek\n");
        printf("5. Back to Main Menu\n");
        printf("=================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int processID;
                int found = 0;
                int alreadyAdded = 0;

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
                        if(id[i] == processID)
                        {
                            found = 1;

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

                                saveReadyQueue();
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

                    saveReadyQueue();
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

                    printf("\nFront Process = P%d\n",
                           id[index]);
                }
            }
            break;


            case 5:
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 5);
}


/* ================= PART 3 ================= */

void cpuScheduling()
{
    int choice;

    if(front > rear)
    {
        printf("\nReady Queue is Empty.\n");
        printf("Add processes to Ready Queue first.\n");
        return;
    }

    int tempCount = rear - front + 1;

    int pid[MAX];
    int at[MAX];
    int bt[MAX];
    int pri[MAX];

    for(int i = 0; i < tempCount; i++)
    {
        int index = readyQueue[front + i];

        pid[i] = id[index];
        at[i] = arr_time[index];
        bt[i] = bur_time[index];
        pri[i] = priority[index];
    }

    do
    {
        printf("\n========== CPU SCHEDULING ==========\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. SRTF\n");
        printf("4. Priority Scheduling\n");
        printf("5. Round Robin\n");
        printf("6. Back to Main Menu\n");
        printf("====================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int order[MAX];
                int ct[MAX];
                int tat[MAX];
                int wt[MAX];

                for(int i = 0; i < tempCount; i++)
                {
                    order[i] = i;
                }

                for(int i = 0; i < tempCount - 1; i++)
                {
                    for(int j = 0; j < tempCount - i - 1; j++)
                    {
                        if(at[order[j]] > at[order[j + 1]])
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

                for(int i = 0; i < tempCount; i++)
                {
                    int index = order[i];

                    if(currentTime < at[index])
                    {
                        currentTime = at[index];
                    }

                    printf("| P%d ", pid[index]);

                    currentTime = currentTime + bt[index];

                    ct[index] = currentTime;

                    tat[index] = ct[index] - at[index];

                    wt[index] = tat[index] - bt[index];
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < tempCount; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           pid[i],
                           at[i],
                           bt[i],
                           ct[i],
                           tat[i],
                           wt[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < tempCount; i++)
                {
                    totalWT += wt[i];
                    totalTAT += tat[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / tempCount);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / tempCount);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "FCFS\n");
                fprintf(fp, "%d\n", tempCount);

                for(int i = 0; i < tempCount; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            pid[i],
                            at[i],
                            bt[i],
                            ct[i],
                            tat[i],
                            wt[i]);
                }

                fclose(fp);
            }
            break;


            case 2:
            {
                int completed[MAX] = {0};

                int ct[MAX];
                int tat[MAX];
                int wt[MAX];

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== SJF ==========\n");

                while(completedCount < tempCount)
                {
                    int selected = -1;

                    for(int i = 0; i < tempCount; i++)
                    {
                        if(completed[i] == 0 &&
                           at[i] <= currentTime)
                        {
                            if(selected == -1 ||
                               bt[i] < bt[selected])
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
                        printf("| P%d ", pid[selected]);

                        currentTime += bt[selected];

                        ct[selected] = currentTime;

                        tat[selected] =
                            ct[selected] - at[selected];

                        wt[selected] =
                            tat[selected] - bt[selected];

                        completed[selected] = 1;

                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < tempCount; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           pid[i],
                           at[i],
                           bt[i],
                           ct[i],
                           tat[i],
                           wt[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < tempCount; i++)
                {
                    totalWT += wt[i];
                    totalTAT += tat[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / tempCount);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / tempCount);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "SJF\n");
                fprintf(fp, "%d\n", tempCount);

                for(int i = 0; i < tempCount; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            pid[i],
                            at[i],
                            bt[i],
                            ct[i],
                            tat[i],
                            wt[i]);
                }

                fclose(fp);
            }
            break;


            case 3:
            {
                int remaining[MAX];
                int ct[MAX];
                int tat[MAX];
                int wt[MAX];

                for(int i = 0; i < tempCount; i++)
                {
                    remaining[i] = bt[i];
                }

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== SRTF ==========\n");
                printf("Execution:\n");

                while(completedCount < tempCount)
                {
                    int selected = -1;

                    for(int i = 0; i < tempCount; i++)
                    {
                        if(at[i] <= currentTime &&
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
                        printf("P%d ", pid[selected]);

                        remaining[selected]--;

                        currentTime++;

                        if(remaining[selected] == 0)
                        {
                            ct[selected] = currentTime;

                            tat[selected] =
                                ct[selected] - at[selected];

                            wt[selected] =
                                tat[selected] - bt[selected];

                            completedCount++;
                        }
                    }
                }

                printf("\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < tempCount; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           pid[i],
                           at[i],
                           bt[i],
                           ct[i],
                           tat[i],
                           wt[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < tempCount; i++)
                {
                    totalWT += wt[i];
                    totalTAT += tat[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / tempCount);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / tempCount);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "SRTF\n");
                fprintf(fp, "%d\n", tempCount);

                for(int i = 0; i < tempCount; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            pid[i],
                            at[i],
                            bt[i],
                            ct[i],
                            tat[i],
                            wt[i]);
                }

                fclose(fp);
            }
            break;


            case 4:
            {
                int completed[MAX] = {0};

                int ct[MAX];
                int tat[MAX];
                int wt[MAX];

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== PRIORITY SCHEDULING ==========\n");

                while(completedCount < tempCount)
                {
                    int selected = -1;

                    for(int i = 0; i < tempCount; i++)
                    {
                        if(completed[i] == 0 &&
                           at[i] <= currentTime)
                        {
                            if(selected == -1 ||
                               pri[i] < pri[selected])
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
                        printf("| P%d ", pid[selected]);

                        currentTime += bt[selected];

                        ct[selected] = currentTime;

                        tat[selected] =
                            ct[selected] - at[selected];

                        wt[selected] =
                            tat[selected] - bt[selected];

                        completed[selected] = 1;

                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

                for(int i = 0; i < tempCount; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
                           pid[i],
                           at[i],
                           bt[i],
                           pri[i],
                           ct[i],
                           tat[i],
                           wt[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < tempCount; i++)
                {
                    totalWT += wt[i];
                    totalTAT += tat[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / tempCount);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / tempCount);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "Priority\n");
                fprintf(fp, "%d\n", tempCount);

                for(int i = 0; i < tempCount; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            pid[i],
                            at[i],
                            bt[i],
                            ct[i],
                            tat[i],
                            wt[i]);
                }

                fclose(fp);
            }
            break;


            case 5:
            {
                int remaining[MAX];
                int ct[MAX];
                int tat[MAX];
                int wt[MAX];

                int queue[MAX * 10];

                int qfront = 0;
                int qrear = 0;

                int added[MAX] = {0};

                int quantum;

                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);

                if(quantum <= 0)
                {
                    printf("Invalid Time Quantum.\n");
                    break;
                }

                for(int i = 0; i < tempCount; i++)
                {
                    remaining[i] = bt[i];
                }

                int currentTime = 0;
                int completedCount = 0;

                printf("\n========== ROUND ROBIN ==========\n");

                while(completedCount < tempCount)
                {
                    for(int i = 0; i < tempCount; i++)
                    {
                        if(at[i] <= currentTime &&
                           added[i] == 0)
                        {
                            queue[qrear] = i;

                            qrear++;

                            added[i] = 1;
                        }
                    }

                    if(qfront == qrear)
                    {
                        currentTime++;

                        continue;
                    }

                    int index = queue[qfront];

                    qfront++;

                    int executeTime;

                    if(remaining[index] > quantum)
                    {
                        executeTime = quantum;
                    }
                    else
                    {
                        executeTime = remaining[index];
                    }

                    printf("| P%d ", pid[index]);

                    remaining[index] -= executeTime;

                    currentTime += executeTime;

                    for(int i = 0; i < tempCount; i++)
                    {
                        if(at[i] <= currentTime &&
                           added[i] == 0)
                        {
                            queue[qrear] = i;

                            qrear++;

                            added[i] = 1;
                        }
                    }

                    if(remaining[index] > 0)
                    {
                        queue[qrear] = index;

                        qrear++;
                    }
                    else
                    {
                        ct[index] = currentTime;

                        tat[index] =
                            ct[index] - at[index];

                        wt[index] =
                            tat[index] - bt[index];

                        completedCount++;
                    }
                }

                printf("|\n");

                printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");

                for(int i = 0; i < tempCount; i++)
                {
                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           pid[i],
                           at[i],
                           bt[i],
                           ct[i],
                           tat[i],
                           wt[i]);
                }

                float totalWT = 0;
                float totalTAT = 0;

                for(int i = 0; i < tempCount; i++)
                {
                    totalWT += wt[i];
                    totalTAT += tat[i];
                }

                printf("\nAverage Waiting Time = %.2f\n",
                       totalWT / tempCount);

                printf("Average Turnaround Time = %.2f\n",
                       totalTAT / tempCount);

                FILE *fp;

                fp = fopen("schedulingResults.txt", "w");

                fprintf(fp, "Round Robin\n");
                fprintf(fp, "%d\n", tempCount);

                for(int i = 0; i < tempCount; i++)
                {
                    fprintf(fp, "%d %d %d %d %d %d\n",
                            pid[i],
                            at[i],
                            bt[i],
                            ct[i],
                            tat[i],
                            wt[i]);
                }

                fclose(fp);
            }
            break;


            case 6:
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);
}


/* ================= PART 5 ================= */

void cacheMemory()
{
    int choice;

    if(memorySize == 0)
    {
        printf("\nEnter Number of Memory Locations: ");
        scanf("%d", &memorySize);

        if(memorySize <= 0 || memorySize > MEMORY_SIZE)
        {
            printf("Invalid Memory Size.\n");

            memorySize = 0;

            return;
        }

        for(int i = 0; i < memorySize; i++)
        {
            printf("Enter value for Memory[%d]: ",
                   i);

            scanf("%d", &memory[i]);
        }
    }

    do
    {
        printf("\n========== CACHE & MEMORY ==========\n");
        printf("1. Display Main Memory\n");
        printf("2. Display Cache\n");
        printf("3. Access Memory\n");
        printf("4. Display Cache Statistics\n");
        printf("5. Reset Cache\n");
        printf("6. Back to Main Menu\n");
        printf("====================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                printf("\n========== MAIN MEMORY ==========\n");

                for(int i = 0; i < memorySize; i++)
                {
                    printf("Memory[%d] = %d\n",
                           i,
                           memory[i]);
                }
            }
            break;


            case 2:
            {
                printf("\n========== CACHE MEMORY ==========\n");

                if(cacheCount == 0)
                {
                    printf("Cache is Empty.\n");
                }
                else
                {
                    for(int i = 0; i < cacheCount; i++)
                    {
                        printf("Cache[%d] = Memory[%d]\n",
                               i,
                               cache[i]);
                    }
                }
            }
            break;


            case 3:
            {
                int address;
                int found = 0;

                printf("Enter Memory Address (0-%d): ",
                       memorySize - 1);

                scanf("%d", &address);

                if(address < 0 || address >= memorySize)
                {
                    printf("Invalid Memory Address.\n");
                }
                else
                {
                    for(int i = 0; i < cacheCount; i++)
                    {
                        if(cache[i] == address)
                        {
                            found = 1;
                            break;
                        }
                    }

                    if(found == 1)
                    {
                        hits++;

                        printf("\nCACHE HIT!\n");
                        printf("Value = %d\n",
                               memory[address]);
                    }
                    else
                    {
                        misses++;

                        printf("\nCACHE MISS!\n");
                        printf("Accessing Main Memory...\n");

                        printf("Value = %d\n",
                               memory[address]);

                        if(cacheCount < CACHE_SIZE)
                        {
                            cache[cacheCount] = address;

                            cacheCount++;
                        }
                        else
                        {
                            for(int i = 0; i < CACHE_SIZE - 1; i++)
                            {
                                cache[i] = cache[i + 1];
                            }

                            cache[CACHE_SIZE - 1] = address;
                        }

                        printf("Data loaded into Cache.\n");
                    }

                    FILE *fp;

                    fp = fopen("cacheResults.txt", "w");

                    if(fp != NULL)
                    {
                        fprintf(fp, "%d %d\n",
                                hits,
                                misses);

                        fclose(fp);
                    }
                }
            }
            break;


            case 4:
            {
                printf("\n========== CACHE STATISTICS ==========\n");

                printf("Cache Hits   = %d\n",
                       hits);

                printf("Cache Misses = %d\n",
                       misses);

                if(hits + misses > 0)
                {
                    float hitRate =
                        (float)hits /
                        (hits + misses) * 100;

                    float missRate =
                        (float)misses /
                        (hits + misses) * 100;

                    printf("Hit Rate     = %.2f%%\n",
                           hitRate);

                    printf("Miss Rate    = %.2f%%\n",
                           missRate);
                }
            }
            break;


            case 5:
            {
                for(int i = 0; i < CACHE_SIZE; i++)
                {
                    cache[i] = -1;
                }

                cacheCount = 0;

                hits = 0;
                misses = 0;

                FILE *fp;

                fp = fopen("cacheResults.txt", "w");

                if(fp != NULL)
                {
                    fprintf(fp, "0 0\n");

                    fclose(fp);
                }

                printf("Cache Reset Successfully.\n");
            }
            break;


            case 6:
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);
}


/* ================= PART 6 ================= */

void contextSwitching()
{
    int choice;

    if(count == 0)
    {
        printf("\nNo Processes Available.\n");
        return;
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
        printf("7. Back to Main Menu\n");
        printf("=======================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

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
                scanf("%d", &processID);

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

                        printf("Process P%d is now Running.\n",
                               id[i]);

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
                    printf("Enter Number of Instructions to Execute: ");
                    scanf("%d", &steps);

                    if(steps <= 0)
                    {
                        printf("Invalid Number of Instructions.\n");
                    }
                    else
                    {
                        for(int i = 0; i < steps; i++)
                        {
                            PC[currentProcess]++;

                            accumulator[currentProcess] += 5;
                        }

                        printf("Process P%d executed successfully.\n",
                               id[currentProcess]);

                        printf("PC = %d\n",
                               PC[currentProcess]);

                        printf("Accumulator = %d\n",
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
                    printf("Current Process = P%d\n",
                           id[currentProcess]);

                    printf("Enter Process ID to switch to: ");
                    scanf("%d", &processID);

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
                        printf("Saving state of P%d...\n",
                               id[currentProcess]);

                        state[currentProcess] = 0;

                        printf("PC saved = %d\n",
                               PC[currentProcess]);

                        printf("Accumulator saved = %d\n",
                               accumulator[currentProcess]);

                        currentProcess = nextProcess;

                        state[nextProcess] = 1;

                        printf("Loading state of P%d...\n",
                               id[nextProcess]);

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

                        printf("Context Switch Completed.\n");

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
                    printf("No Process is currently running.\n");
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
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 7);
}


/* ================= PART 7 ================= */

void performanceAnalysis()
{
    FILE *fp;

    char algorithm[30];

    int pid[MAX];
    int at[MAX];
    int bt[MAX];
    int ct[MAX];
    int tat[MAX];
    int wt[MAX];

    int n;

    fp = fopen("schedulingResults.txt", "r");

    if(fp == NULL)
    {
        printf("\nschedulingResults.txt not found.\n");
        printf("Run CPU Scheduling first.\n");

        return;
    }

    fscanf(fp, "%s", algorithm);

    fscanf(fp, "%d", &n);

    for(int i = 0; i < n; i++)
    {
        fscanf(fp, "%d %d %d %d %d %d",
               &pid[i],
               &at[i],
               &bt[i],
               &ct[i],
               &tat[i],
               &wt[i]);
    }

    fclose(fp);

    float totalWT = 0;
    float totalTAT = 0;

    int totalBurst = 0;

    int firstArrival = at[0];
    int lastCompletion = ct[0];

    for(int i = 0; i < n; i++)
    {
        totalWT += wt[i];

        totalTAT += tat[i];

        totalBurst += bt[i];

        if(at[i] < firstArrival)
        {
            firstArrival = at[i];
        }

        if(ct[i] > lastCompletion)
        {
            lastCompletion = ct[i];
        }
    }

    float avgWT =
        totalWT / n;

    float avgTAT =
        totalTAT / n;

    int totalTime =
        lastCompletion - firstArrival;

    float cpuUtilization = 0;
    float throughput = 0;

    if(totalTime > 0)
    {
        cpuUtilization =
            (float)totalBurst /
            totalTime * 100;

        throughput =
            (float)n /
            totalTime;
    }


    fp = fopen("cacheResults.txt", "r");

    if(fp != NULL)
    {
        fscanf(fp, "%d %d",
               &hits,
               &misses);

        fclose(fp);
    }

    float hitRate = 0;

    if(hits + misses > 0)
    {
        hitRate =
            (float)hits /
            (hits + misses) * 100;
    }


    fp = fopen("contextSwitches.txt", "r");

    if(fp != NULL)
    {
        fscanf(fp, "%d",
               &contextSwitches);

        fclose(fp);
    }


    printf("\n============================================\n");
    printf("        CPUFLOW PERFORMANCE ANALYSIS\n");
    printf("============================================\n");

    printf("\n----- CPU SCHEDULING -----\n");

    printf("Algorithm               = %s\n",
           algorithm);

    printf("Number of Processes     = %d\n",
           n);

    printf("Average Waiting Time    = %.2f\n",
           avgWT);

    printf("Average Turnaround Time = %.2f\n",
           avgTAT);

    printf("CPU Utilization         = %.2f%%\n",
           cpuUtilization);

    printf("Throughput              = %.2f processes/unit time\n",
           throughput);

    printf("\n----- CACHE -----\n");

    printf("Cache Hits              = %d\n",
           hits);

    printf("Cache Misses            = %d\n",
           misses);

    printf("Cache Hit Rate          = %.2f%%\n",
           hitRate);

    printf("\n----- CONTEXT SWITCHING -----\n");

    printf("Context Switches        = %d\n",
           contextSwitches);

    printf("\n============================================\n");
}


/* ================= MAIN ================= */

int main()
{
    int choice;

    for(int i = 0; i < CACHE_SIZE; i++)
    {
        cache[i] = -1;
    }

    loadProcesses();

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("              CPUFLOW SIMULATOR\n");
        printf("============================================\n");

        printf("1. Process Management\n");
        printf("2. Ready Queue\n");
        printf("3. CPU Scheduling\n");
        printf("4. Cache & Memory\n");
        printf("5. Context Switching\n");
        printf("6. Performance Analysis\n");
        printf("7. Exit\n");

        printf("============================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                processManagement();
                break;

            case 2:
                readyQueueManagement();
                break;

            case 3:
                cpuScheduling();
                break;

            case 4:
                cacheMemory();
                break;

            case 5:
                contextSwitching();
                break;

            case 6:
                performanceAnalysis();
                break;

            case 7:
                printf("\nExiting CPUFlow Simulator...\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 7);

    return 0;
}