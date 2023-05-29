#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char st[100];
int top = -1;
void push(char x)
{
    st[++top] = x;
}
char pop()
{
    return st[top--];
}
int priority(char x)
{
    if (x == '^')
        return 3;
    if (x == '*' || x == '/')
        return 2;
    if (x == '+' || x == '-')
        return 1;
    return 0;
}
void convertToPostfix(char infix[])
{
    char postfix[20], *s, x;
    int i = -1;
    s = infix;
    while (*s != '\0')
    {
        if (isalnum(*s))
            postfix[++i] = *s;
        else if (*s == '(')
            push(*s);
        else if (*s == ')')
            while ((x = pop()) != '(')
                postfix[++i] = x;
        else
        {
            while (priority(st[top]) >= priority(*s))
                postfix[++i] = pop();
            push(*s);
        }
        s++;
    }
    while (top != -1)
        postfix[++i] = pop();
    postfix[++i] = '\0';
    printf("\nPostfix Expression is : %s", postfix);
}
void convertToPretfix(char infix[])
{
    char prefix[20], *s, x;
    int i = -1;
    s = infix;
    while (*s != '\0')
    {

        if (isalnum(*s))
            prefix[++i] = *s;
        else if (*s == ')')
            push(*s);
        else if (*s == '(')
            while ((x = pop()) != ')')
                prefix[++i] = x;

        else
        {
            while (priority(st[top]) >= priority(*s))
                prefix[++i] = pop();
            push(*s);
        }
        s++;
    }
    while (top != -1)
        prefix[++i] = pop();
    prefix[++i] = '\0';
    strrev(prefix);
    printf("\nPrefix Expression is : %s", prefix);
}
int operation(char ch, int a, int b)
{
    switch (ch)
    {
    case '+':
        return b + a;
    case '-':
        return b - a;
    case '*':
        return b * a;
    case '/':
        return b / a;
    case '^':
        return pow(b, a);
    }
    return 0;
}
void evaluatePostfix(char exp[])
{
    char *s;
    int x, a, b, c;
    s = exp;
    while (*s != '\0')
    {
        if (isalnum(*s))
        {
            x = *s - '0';
            push(x);
        }
        else
        {
            a = pop();
            b = pop();
            c = operation(*s, a, b);
            push(c);
        }
        s++;
    }
    printf("\n%d", pop());
}
void main()
{
    char infix[20], exp[20];
    int ch, c;
    do
    {
        printf("\n======================================");
        ;
        printf("\n1. Conversion\n2. Evaluation \n3. Exit ");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        printf("\n======================================");
        switch (ch)
        {
        case 1:
            printf("\n======================================");
            printf("\nEnter Infix Expression: ");
            scanf("%s", infix);
            do
            {
                printf("\n======================================");
                printf("\n1. Infix to postfix ");
                printf("\n2. Infix to prefix ");
                printf("\n3. Back");
                printf("\nEnter your choice: ");
                scanf("%d", &c);
                printf("\n======================================");
                switch (c)
                {
                case 1:
                    convertToPostfix(infix);
                    break;
                case 2:
                    convertToPretfix(infix);
                    break;
                case 3:
                    break;
                default:
                    printf("\nEnter Valid choice");
                    break;
                }
            } while (c != 3);
            break;
        case 2:
            do
            {
                printf("\n======================================");
                printf("\n1. Postfix Evaluation");
                printf("\n2. Prefix Evaluation");
                printf("\n3. Back");
                printf("\nEnter your choice: ");
                scanf("%d", &c);
                printf("\n======================================");
                switch (c)
                {
                case 1:
                    printf("\nEnter Postfix Expression: ");
                    scanf("%s", exp);
                    evaluatePostfix(exp);
                    break;
                case 2:
                    printf("\nEnter Prefix Expression: ");
                    scanf("%s", exp);
                    strrev(exp);
                    evaluatePostfix(exp);
                    break;
                case 3:
                    break;
                default:
                    printf("\nEnter Valid choice");
                }
            } while (c != 3);
        case 3:
            break;
        default:
            printf("\nEnter valid Choice");
            break;
        }
    } while (ch != 3);
}

