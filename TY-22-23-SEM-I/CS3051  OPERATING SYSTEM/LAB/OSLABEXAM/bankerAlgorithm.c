#include <stdio.h>
int max[10][10], allocation[10][10], need[10][10];
int available[10];
int no_of_process, no_of_resource;

void readMatrix(int matrix[no_of_process][no_of_resource])
{
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_resource; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[no_of_process][no_of_resource])
{
    for (int i = 0; i < no_of_process; i++)
    {
        printf("\n P%d", i);
        for (int j = 0; j < no_of_resource; j++)
        {
            printf(" %d", matrix[i][j]);
        }
    }
}

void calculateNeed()
{
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_resource; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void banker()
{
    int k, flag, finish[10], safe_seq[10];
    for (int i = 0; i < no_of_process; i++)
    {
        finish[i] = 0; // all process are incomplete i.e. 0
    }

    for (int i = 0; i < no_of_process; i++)
    {
        flag = 0;
        if (finish[i] == 0) // then execute the process
        {
            for (int j = 0; j < no_of_resource; j++) // checkin need of each process
            {
                if (need[i][j] > available[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                finish[i] = 1;
                safe_seq[k] = i;
                k++;
                for (int j = 0; j < no_of_resource; j++)
                {
                    available[j] += allocation[i][j]; // adding already allocated resource to available resource
                    i = -1;
                }
            }
        }
    }

    flag = 0;
    for (int i = 0; i < no_of_process; i++)
    {
        if (finish[i] == 0)
        {
            printf("\n\nThe System is in Deadlock !!!\n\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("The System is in safe State! Safe Sequence is : ");
        for (int i = 0; i < no_of_process; i++)
        {
            printf("P%d->", safe_seq[i]);
        }
    }
}

int main()
{
    printf("Enter number of process: ");
    scanf("%d", &no_of_process);
    printf("Enter number of resources: ");
    scanf("%d", &no_of_resource);

    // Allocation Column
    printf("Enter initial Allocation for each Process: \n");
    readMatrix(allocation);

    // Maximum Need Column
    printf("Enter Max need for each process: \n");
    readMatrix(max);

    // Available Column (First Row)
    printf("Enter available resources: \n");
    for (int i = 0; i < no_of_resource; i++)
    {
        scanf("%d", &available[i]);
    }

    //============Display========================

    printf("\n\tInitial Allocation\n\t");
    displayMatrix(allocation);
    printf("\n\n\tMaximum Need\n\t");
    displayMatrix(max);
    printf("\n\n\tAvailable Resources\n\t");
    for (int i = 0; i < no_of_resource; i++)
    {
        printf(" %d", available[i]);
    }

    //==============Calculate Need=================
    calculateNeed();
    printf("\n\n\tRemaining Need\n\t");
    displayMatrix(need);

    //============execution=====================
    banker();
    printf("\n\n\n");

    return 0;
}