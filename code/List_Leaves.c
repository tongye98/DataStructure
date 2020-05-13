#include <stdio.h>
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1
struct TreeNode
{
    ElementType Element;
    Tree left;
    Tree right;
} T[MaxTree];
Tree BuildTree(struct TreeNode T[]);
void print_list_leaves(struct TreeNode T[], Tree R);
int main()
{
    Tree R;
    R = BuildTree(T);
    print_list_leaves(T, R);
    system("pause");
    return 0;
}
Tree BuildTree(struct TreeNode T[]) // 建树
{
    int N, i;
    int Root = Null;
    int cl, cr;
    scanf("%d\n", &N);
    int check[N];
    if (N)
    {
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            T[i].Element = i;
            scanf("%c %c\n", &cl, &cr);
            if (cl != '-')
            {
                T[i].left = cl - '0';
                int temp = T[i].left;
                check[temp] = 1;
            }
            else
                T[i].left = Null;
            if (cr != '-')
            {
                T[i].right = cr - '0';
                int temp = T[i].right;
                check[temp] = 1;
            }
            else
                T[i].right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i])
                break;
        Root = i;
    }
    return Root;
}
void print_list_leaves(struct TreeNode T[], Tree R)
{
    // printf("%d\n", T[R].Element);
    int a[MaxTree + 1];
    int i;
    for (i = 0; i < MaxTree + 1; i++)
        a[i] = -2;
    a[0] = T[R].Element;
    int top = 0;
    int temp = 1;
    int end = 0;
    while (a[top] != -2)
    {
        if (T[a[top]].left == -1 && T[a[top]].right == -1)
        {
            if (temp == 1)
                printf("%d", T[a[top]].Element);
            else
                printf(" %d", T[a[top]].Element);
            top++;
            temp = 0;
            continue;
        }
        if (T[a[top]].left != -1)
        {
            a[++end] = T[a[top]].left;
        }
        if (T[a[top]].right != -1)
        {
            a[++end] = T[a[top]].right;
        }
        top++;
    }
}
