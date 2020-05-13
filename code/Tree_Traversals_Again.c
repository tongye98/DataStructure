#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50
int stack[max];
int top = -1;
int Post;
void Push(int num)
{
    stack[++top] = num;
}
int Pop()
{
    if (top > -1)
        return stack[top--];
    else
        printf("error");
}
void Pre_and_In_to_Post(int PreL, int InL, int PostL, int n, int *Preorder, int *Inorder, int *Postorder);
void Print_Post(int *Postorder, int N);
int main()
{
    int N;
    scanf("%d", &N);
    int Preorder[max];
    int Inorder[max];
    int Postorder[max];
    int i;
    char str[5];
    int x;
    int k = 0;
    int t = 0;
    for (i = 0; i < 2 * N; i++)
    {
        scanf("%s", str);
        if (str[1] == 'u')
        {
            scanf("%d", &x);
            Push(x);
            Preorder[t++] = x;
        }
        if (str[1] == 'o')
            Inorder[k++] = Pop();
    }
    Pre_and_In_to_Post(0, 0, 0, N, Preorder, Inorder, Postorder);
    Print_Post(Postorder, N);
    system("pause");
    return 0;
}
void Pre_and_In_to_Post(int PreL, int InL, int PostL, int n, int *Preorder, int *Inorder, int *Postorder)
{
    if (n == 0)
        return;
    if (n == 1)
    {
        Postorder[PostL] = Preorder[PreL];
        return;
    }
    int root = Preorder[PreL];
    Postorder[PostL + n - 1] = root;
    int i;
    for (i = 0; i < n; i++)
        if (Inorder[InL + i] == root)
            break;
    int L = i;
    int R = n - L - 1;
    Pre_and_In_to_Post(PreL + 1, InL, PostL, L, Preorder, Inorder, Postorder);
    Pre_and_In_to_Post(PreL + L + 1, InL + L + 1, PostL + L, R, Preorder, Inorder, Postorder);
}
void Print_Post(int *Postorder, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (i == 0)
            printf("%d", Postorder[i]);
        else
            printf(" %d", Postorder[i]);
    }
    printf("\n");
}
