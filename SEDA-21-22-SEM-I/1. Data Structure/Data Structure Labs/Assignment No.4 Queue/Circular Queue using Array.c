#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int queue[10], f = -1, r = -1;
void display();
void enqueue(int x)
{
    if ((f == 0 && r == 10 - 1) ||
        (r == (f - 1) % (10 - 1)))
    {
        printf("\nQueue is Full!");
        return;
    }
    if (f == -1)
    {
        f = 0;
        r = 0;
        queue[r] = x;
    }
    else if (r == 10 - 1 && f != 0)
    {
        r = 0;
        queue[r] = x;
    }
    else
    {
        r++;
        queue[r] = x;
    }
    display();
}
void dequeue()
{
    int x;

    if (f == -1)
    {
        printf("\nQueue is empty!");
        return;
    }
    x = queue[f];
    queue[f] = -1;
    if (f == r)
    {
        f = r = -1;
    }
    else if (f == 10 - 1)
    {
        f = 0;
    }
    else
    {
        f++;
        printf("\n%d is deleted from the queue.\n", x);
    }
    display();
}
void display()
{
    if (r == -1)
    {
        printf("\nQueue is empty");
    }
    else
    {
        printf("\nCircular Queue: ");
        if (r >= f)
        {
            for (int i = f; i <= r; i++)
                printf("%d ", queue[i]);
        }
        else
        {
            for (int i = f; i < 10; i++)
                printf("%d ", queue[i]);

            for (int i = 0; i <= r; i++)
                printf("%d ", queue[i]);
        }
    }
}

void main()
{
    int ch, x;
    do
    {
        printf("\n===================================");
        printf("\n1. Enqueue\t2. Dequeue \t3. Exit ");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        printf("\n===================================");
        switch (ch)
        {
        case 1:
            printf("\nEnter Element: ");
            scanf("%d", &x);
            enqueue(x);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            exit(0);
        default:
            printf("\nEnter valid choice!");
        }
    } while (ch != 3);
}
