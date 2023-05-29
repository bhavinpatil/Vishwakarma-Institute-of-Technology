#include <stdio.h>
int main()
{
    int i, j, k, nofPages, nofFrames, frames[10], pageNum[50], flag, fcount = 0;

    printf("Enter Number of Pages: ");
    scanf("%d", &nofPages);

    printf("Enter Page Numbers: ");
    for (i = 1; i <= nofPages; i++)
    {
        scanf("%d", &pageNum[i]);
    }

    printf("Enter Number of Frames: ");
    scanf("%d", &nofFrames);

    for (i = 0; i < nofFrames; i++)
    {
        frames[i] = -1;
    }

    j = 0;

    printf("\n\nPage Numbers \t Page Frames \t Hit/Fault\n");
    for (i = 1; i <= nofPages; i++)
    {
        printf("%d\t\t", pageNum[i]);
        flag = 0;

        for (k = 0; k < nofFrames; k++)
            if (frames[k] == pageNum[i])
            {
                flag = 1;
                for (k = 0; k < nofFrames; k++)
                {
                    printf("%d\t", frames[k]);
                }
                printf("H");
            }
        if (flag == 0)
        {
            frames[j] = pageNum[i];
            j = (j + 1) % nofFrames;
            fcount++;
            for (k = 0; k < nofFrames; k++)
            {
                printf("%d\t", frames[k]);
            }
            printf("F");
        }
        printf("\n");
    }
    printf("Page Fault is %d\n\n", fcount);
    return 0;
}

/*
7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
*/