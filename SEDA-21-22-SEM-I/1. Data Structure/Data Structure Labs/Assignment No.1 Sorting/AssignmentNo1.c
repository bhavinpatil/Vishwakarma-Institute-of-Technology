#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef struct
{
    int rollno;
    char name[20];
    float marks;
} stud;

void quickSort(stud[], int, int);
int partition(stud[], int, int);
void mergeSort(stud[], int, int);
void merge(stud[], int, int, int);


int main()
{
    int t[5], n, index = 1;
    printf("Enter the no. of Student: ");
    scanf("%d", &n);
    stud student[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Name of Student %d: ", index);
        scanf("\n");
        scanf("%[^\n]%*c", student[i].name);

        printf("Enter Roll No of Student %d: ", index);
        scanf("%d", &student[i].rollno);

        printf("Enter Marks of Student %d: ", index);
        scanf("%f", &student[i].marks);
        printf("\n");
        index++;
    }

    printf("\nData Before Sorting: \n"); //printing unsorted data

    printf("\n\tName\t|\tRoll No.|\tMarks\n");
    printf("\t----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t|\t%d\t|\t%f\n", student[i].name, student[i].rollno, student[i].marks);
    }

    int choice;
    do
    {
        printf("\nEnter the coice \n1.Quick Sort\t2.Merge Sort\t3.Exit\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nYour data is sorting using Qiuck Sort algorithm....\n");
            quickSort(student, 0, n - 1);
            for (int i = 0; i < n; i++)
            {
                printf("\nName : %s\tRoll No. : %d\tMarks : %f", student[i].name, student[i].rollno, student[i].marks);
            }
            break;
        case 2:
            printf("\nYour data is sorting using Merge Sort algorithm....\n");
            mergeSort(student, 0, n - 1);
            for (int i = 0; i < n; i++)
            {
                printf("\nName : %s\tRoll No. : %d\tMarks : %f", student[i].name, student[i].rollno, student[i].marks);
            }
            break;
        case 3:
            exit(1);
        default:
            printf("Enter a valid choice!");
            break;
        }
    } while (choice != 3);
    return 0;
}




// quick sort code
int partition(stud arr[], int low, int high)
{
    int pivot = arr[low].rollno;
    int i = low + 1;
    int j = high;
    stud temp[3];
    int k = 0;
    do
    {
        while (arr[i].rollno <= pivot)
        {
            i++;
        }

        while (arr[j].rollno > pivot)
        {
            j--;
        }

        if (i < j)
        {
            temp[k] = arr[i];
            arr[i] = arr[j];
            arr[j] = temp[k];
        }
    } while (i < j);

    temp[k] = arr[low];
    arr[low] = arr[j];
    arr[j] = temp[k];
    return j;
}
void quickSort(stud arr[], int low, int high)
{
    int partitionIndex;

    if (low < high)
    {
        partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// merge sort code
void merge(stud A[], int low, int mid, int high)
{
    int i, j, k;
    stud B[high + 1];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (A[i].rollno < A[j].rollno)
        {
            B[k] = A[i];
            k++;
            i++;
        }
        else
        {
            B[k] = A[j];
            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        B[k] = A[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        B[k] = A[j];
        k++;
        j++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
}
void mergeSort(stud A[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}

