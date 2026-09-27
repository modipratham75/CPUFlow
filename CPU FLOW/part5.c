#include<stdio.h>

#define MEMORY_SIZE 100
#define CACHE_SIZE 4

int main()
{
    int memory[MEMORY_SIZE];
    int cache[CACHE_SIZE];

    int choice;

    int memorySize;
    int cacheCount = 0;

    int hits = 0;
    int misses = 0;

    for(int i = 0; i < CACHE_SIZE; i++)
    {
        cache[i] = -1;
    }

    FILE *fp;

    fp = fopen("cacheResults.txt", "w");

    if(fp != NULL)
    {
        fprintf(fp, "0 0\n");
        fclose(fp);
    }

    printf("========== MAIN MEMORY SETUP ==========\n");

    printf("Enter Number of Memory Locations: ");
    scanf("%d", &memorySize);

    if(memorySize <= 0 || memorySize > MEMORY_SIZE)
    {
        printf("Invalid Memory Size.\n");
        return 0;
    }

    for(int i = 0; i < memorySize; i++)
    {
        printf("Enter value for Memory[%d]: ", i);
        scanf("%d", &memory[i]);
    }

    do
    {
        printf("\n========== CACHE & MEMORY ==========\n");
        printf("1. Display Main Memory\n");
        printf("2. Display Cache\n");
        printf("3. Access Memory\n");
        printf("4. Display Cache Statistics\n");
        printf("5. Reset Cache\n");
        printf("6. Exit\n");
        printf("====================================\n");

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

                if(scanf("%d", &address) != 1)
                {
                    printf("Invalid Input.\n");

                    while(getchar() != '\n');

                    break;
                }

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
                        printf("Data found in Cache.\n");

                        printf("Memory Address = %d\n",
                               address);

                        printf("Value = %d\n",
                               memory[address]);
                    }
                    else
                    {
                        misses++;

                        printf("\nCACHE MISS!\n");
                        printf("Data not found in Cache.\n");
                        printf("Accessing Main Memory...\n");

                        printf("Memory Address = %d\n",
                               address);

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
                else
                {
                    printf("No memory access has been performed yet.\n");
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
                printf("Exiting....\n");
                break;


            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);

    return 0;
}