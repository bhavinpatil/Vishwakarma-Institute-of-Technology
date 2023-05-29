#include <stdio.h>
#include <malloc.h>
struct node *st[100];
int top = -1;

// BST operation = create , insert ,traversing and search
struct node
{
    int data;
    struct node *left;
    struct node *right;
} * root;
// ---------------------------------------------
struct node *insert(struct node *temp, int data)
{
    struct node *r;
    r = malloc(sizeof(struct node));
    r->data = data;
    r->left = r->right = NULL;
    if (temp == NULL)
    {
        return r;
    }
    if (temp->data > data)
    {
        temp->left = insert(temp->left, data);
    }
    else
    {
        temp->right = insert(temp->right, data);
    }
    return temp;
}
// ---------------------------------------------
struct node *create(struct node *temp)
{
    struct node *r;
    int i, n, x;
    printf("\n How many nodes you want to insert: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter Data for Node: ");
        scanf("%d", &x);
        temp = insert(temp, x);
    }
    return temp;
}
// ---------------------------------------------
struct node *search(struct node *temp, int data)
{
    if (temp == NULL)
    {
        printf("\nData is not present");
        return NULL;
    }
    if (temp->data == data)
    {
        printf("\nData is present\n");
        return temp;
    }
    if (temp->data > data)
    {
        return search(temp->left, data);
    }
    else
    {
        return search(temp->right, data);
    }
}
// ---------------------------------------------
void inorder(struct node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        printf("\t%d", temp->data);
        inorder(temp->right);
    }
}
void preorder(struct node *temp)
{
    if (temp != NULL)
    {
        printf("\t%d", temp->data);
        preorder(temp->left);
        preorder(temp->right);
    }
}
void postorder(struct node *temp)
{
    if (temp != NULL)
    {
        postorder(temp->left);
        postorder(temp->right);
        printf("\t%d", temp->data);
    }
}
// ---------------------------------------------
void push(struct node *temp)
{
    st[++top] = temp;
}
struct node *pop()
{
    return st[top--];
}
void inordernr(struct node *temp)
{
    struct node *r;
    while (temp != NULL)
    {
        push(temp);
        temp = temp->left;
    }

    while (top != -1)
    {
        r = pop();
        printf("\t%d", r->data);
        r = r->right;
        while (r != NULL)
        {
            push(r);
            r = r->left;
        }
    }
}
void preordernr(struct node *temp)
{
    struct node *r;
    while (temp != NULL)
    {
        printf("\t%d", temp->data);
        push(temp);
        temp = temp->left;
    }

    while (top != -1)
    {
        r = pop();
        r = r->right;
        while (r != NULL)
        {
            printf("\t%d", r->data);
            push(r);
            r = r->left;
        }
    }
}

void main()
{
    int ch, choice, ele, ins;
    struct node *temp, *temp1;
    root = NULL;
    do
    {
        printf("\n1)Create\n2)Insert\n3)Inorder(recursive)\n4)Preorder(recursive)\n5)Postorder(recursive)\n6)Inorder(Non-recursive)\n7)Preorder(Non-recursive)\n8)Search\n0)Quit\n\nEnter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            temp = root;
            root = create(root);
            temp = root;
            break;
        case 2:
            printf("Enter the data you want to insert: ");
            scanf("%d", &ins);
            insert(temp, ins);
            break;
        case 3:
            printf("\n=====Inorder (Recursive)=====\n");
            inorder(temp);
            printf("\n================================\n");
            break;
        case 4:
            printf("\n=====Preorder (Recursive)=====\n");
            preorder(temp);
            printf("\n================================\n");
            break;
        case 5:
            printf("\n=====Postorder (Recursive)=====\n");
            postorder(temp);
            printf("\n================================\n");
            break;
        case 6:
            printf("\n=====Inorder (Non - Recursive)=====\n");
            inordernr(temp);
            printf("\n================================\n");
            break;
        case 7:
            printf("\n=====Preorder (Non - Recursive)=====\n");
            preordernr(temp);
            printf("\n================================\n");
            break;
        case 8:
            printf("\nEnter the data do you want to search: ");
            scanf("%d", &ele);
            printf("\n=====Search Result=====\n");
            search(root, ele);
            printf("\n================================\n");
            break;
        default:
            break;
        }
    } while (choice != 0);
}