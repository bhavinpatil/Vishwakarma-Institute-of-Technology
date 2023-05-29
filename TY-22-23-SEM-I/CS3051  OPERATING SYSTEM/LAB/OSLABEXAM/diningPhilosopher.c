#include <stdio.h>
int p[5];
int chop[5];

void signal(int z)
{
    p[z] = 0;
    chop[z] = 0;
    chop[(z + 1) % 5] = 0;
}

void wait(int s)
{
    if ((chop[s] == 0) && (chop[(s + 1) % 5] == 0))
    {
        p[s] = 1;
        chop[s] = 1;
        chop[(s + 1) % 5] = 1;
    }
    else if (p[s] == 1)
    {
        int status;
        printf("Do Philosopher %d wants to stop eating ?(0/1) \n", s);
        scanf("%d", &status);
        if (status == 0)
            signal(s);
    }
    else
    {
        printf("Chopstick %d and %d are busy\n", s - 1, ((s - 1) + 1) % 5);
    }
}

int main()
{
    int status;

    for (int i = 1; i <= 5; i++)
    {
        p[i] = 0;
        chop[i] = 0;
    }
    do
    {
        for (int i = 1; i <= 5; i++)
        {
            if (p[i] == 0)
            {
                printf("Philosopher %d is thinking\n", i);
                printf("\n");
            }
            else
            {
                printf("Philosopher %d is Eating\n", i);
                printf("\n");
            }
        }
        int s;
        printf("Which Philosopher wants to eat ? \n");
        scanf("%d", &s);
        wait(s);
        printf("Do you want to continue(0/1) ? \n");
        scanf("%d", &status);
    } while (status == 0);
    return 0;
}