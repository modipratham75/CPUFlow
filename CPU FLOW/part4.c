#include<stdio.h>

#define MAX 100

int main()
{
    int choice;

    int memory[MAX];

    int PC = 0;
    int IR = 0;
    int accumulator = 0;

    int memorySize;

    printf("Enter Memory Size: ");
    scanf("%d", &memorySize);

    if(memorySize > MAX)
    {
        printf("Memory size cannot be greater than %d.\n", MAX);
        return 0;
    }

    printf("\nEnter values into Memory:\n");

    for(int i = 0; i < memorySize; i++)
    {
        printf("Memory[%d] = ", i);
        scanf("%d", &memory[i]);
    }

    do
    {
        printf("\n========== CPU ARCHITECTURE ==========\n");
        printf("1. Display Memory\n");
        printf("2. Fetch Instruction\n");
        printf("3. Decode Instruction\n");
        printf("4. Execute Instruction\n");
        printf("5. Display CPU Registers\n");
        printf("6. Reset CPU\n");
        printf("7. Exit\n");
        printf("======================================\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                printf("\n========== MEMORY ==========\n");

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
                if(PC >= memorySize)
                {
                    printf("Program Counter is outside Memory.\n");
                }
                else
                {
                    printf("\n========== FETCH ==========\n");

                    IR = memory[PC];

                    printf("PC = %d\n", PC);
                    printf("Instruction fetched = %d\n", IR);

                    PC++;

                    printf("PC updated to = %d\n", PC);
                }
            }
            break;


            case 3:
            {
                printf("\n========== DECODE ==========\n");

                printf("Instruction in IR = %d\n", IR);

                printf("Control Unit is decoding the instruction.\n");

                printf("Instruction decoded successfully.\n");
            }
            break;


            case 4:
{
    printf("\n========== EXECUTE ==========\n");

    printf("Instruction = %d\n", IR);

    printf("Accumulator before execution = %d\n",
           accumulator);

    printf("Control Unit sent instruction for execution.\n");

    printf("ALU is executing the instruction.\n");

    accumulator = accumulator + IR;

    printf("Instruction executed successfully.\n");

    printf("Accumulator after execution = %d\n",
           accumulator);
}
break;


            case 5:
            {
                printf("\n========== CPU REGISTERS ==========\n");

                printf("Program Counter (PC) = %d\n", PC);

                printf("Instruction Register (IR) = %d\n", IR);

                printf("Accumulator = %d\n", accumulator);
            }
            break;


            case 6:
            {
                PC = 0;
                IR = 0;
                accumulator = 0;

                printf("\nCPU Reset Successfully.\n");

                printf("PC = %d\n", PC);
                printf("IR = %d\n", IR);
                printf("Accumulator = %d\n", accumulator);
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