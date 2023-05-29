#include<stdio.h>
#include<string.h>

void push(char);
char pop();
void display();
int isoperand(char);

//global variable declaration
char s[25] = {'\0'}; //declaring array with initializing with null value.
int top=-1;
char ch;

int main(){

    char prefix[25]={'\0'};
    char ele;
    int i,j;
    printf("\nEnter Prefix Expression: ");
    scanf("%s",prefix);
    i = strlen(prefix)-1;
    while(i>=0)
    {
        ele = prefix[i];
        if(isoperand(ele))
        {
            push(ele);
            push(' ');
            printf("\n element: %c Pushed to Stack",ele);
        }
        else
        {
            printf("\nOperator: %c",ele);
            for(int j = top-1; j>=0; j--)
            {
                if(s[j]==' ')
                {
                    s[j] = ele;
                    break;
                }
            }
        }
        i--;
        display();
        printf("\n________________________________");
    }
    printf("\n Entered Prefix Expression is : %s",prefix);
    printf("\n Infix Expression will be : %s",strrev(s));

    return 0;
}


void push(char ele){
    if(top==24)
    {
        printf("Stack is Full");
    }
    else
    {
        top++;
        s[top]=ele; 
    }
}

char pop()
{
    if(top==-1)
    {
        printf("Stack is Empty");
    }
    else
    {
        ch=s[top];
        top--;
    }
    return ch;
}

void display()
{
    for(int i=0;i<=top;i++)
    {
        printf("\ns[%d] : %c ",i,s[i]);
    }
}

int isoperand(char ele)
{
    if((ele>='A' && ele<='Z')||(ele>='a' && ele<='z'))
    {
        return 1;
    }
    else
    {
        return 0;
    } 
}