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
} T1[MaxTree], T2[MaxTree];
Tree BuildTree(struct TreeNode T[]);
int Isomorphic(Tree R1, Tree R2);
int main()
{
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if (Isomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");
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
            scanf("%c %c %c\n", &T[i].Element, &cl, &cr);
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
int Isomorphic(Tree R1, Tree R2) //判断是否同构
{
    if ((R1 == Null) && (R2 == Null))
        return 1; // both are empty
    if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))
        return 0; // one of them is empty
    if (T1[R1].Element != T2[R2].Element)
        return 0;                                       //root are different
    if ((T1[R1].left == Null) && (T2[R2].left == Null)) // both have no left subtree
        return Isomorphic(T1[R1].right, T2[R2].right);
    if (((T1[R1].left != Null) && (T2[R2].left != Null)) && ((T1[T1[R1].left].Element) == (T2[T2[R2].left].Element)))
        // no need to swap the left and the right
        return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
    else // need to swap the left and right
        return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
}