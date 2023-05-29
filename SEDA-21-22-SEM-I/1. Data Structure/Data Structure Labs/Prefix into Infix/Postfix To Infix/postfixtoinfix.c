#include <stdio.h>
#include <stdlib.h>
int top = 10;
struct Node
{
    char ch;
    struct Node *next;
    struct Node *prev;
} * stack[11];
typedef struct Node Node;

void push(Node *str)
{
    if (top <= 0)
        printf("Stack is Full ");
    else
    {
        stack[top] = str;
        top--;
    }
}

Node *pop()
{
    Node *exp;
    if (top >= 10)
        printf("Stack is Empty ");
    else
        exp = stack[++top];
    return exp;
}

void convert(char exp[])
{
    Node *o1, *o2;
    Node *temp;
    int i;
    for (i = 0; exp[i] != '\0'; i++)
        if (exp[i] >= 'a' && exp[i] <= 'z' || exp[i] >= 'A' && exp[i] <= 'Z')
        {
            temp = (Node *)malloc(sizeof(Node));
            temp->ch = exp[i];
            temp->next = NULL;
            temp->prev = NULL;
            push(temp);
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' ||
                 exp[i] == '^')
        {
            o1 = pop();
            o2 = pop();
            temp = (Node *)malloc(sizeof(Node));
            temp->ch = exp[i];
            temp->next = o1;
            temp->prev = o2;
            push(temp);
        }
}

void display(Node *temp)
{
    if (temp != NULL)
    {
        display(temp->prev);
        printf("%c", temp->ch);
        display(temp->next);
    }
}

int main()
{
    char exp[50];
    printf("Enter Postfix expression :");
    scanf("%s", exp);
    convert(exp);
    printf("\nPostfix to Infix expression is:");
    display(pop());
    return 0;
}