#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};
int Max(int a, int b)
{
    return a > b ? a : b;
}
int GetHeight(AVLTree T)
{ //树空，则高度为0
    int HL, HR, MaxH;
    if (T)
    {
        HL = GetHeight(T->Left);
        HR = GetHeight(T->Right);
        MaxH = (HL > HR) ? HL : HR;
        return (MaxH + 1);
    }
    else
        return 0;
}
AVLTree SingleLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
    return B;
}
AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;
    return B;
}
AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}
AVLTree Insert(AVLTree T, ElementType X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T)
    { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 1;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Data)
    {
        T->Left = Insert(T->Left, X);
        /* 如果需要左旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
            if (X < T->Left->Data)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
    }
    else if (X > T->Data)
    {
        T->Right = Insert(T->Right, X);
        /* 如果需要右旋 */
        if (GetHeight(T->Right) - GetHeight(T->Left) == 2)
            if (X > T->Right->Data)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
    }
    /* else X == T->Data，无须插入 */
    /* 别忘了更新树高 */
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
    return T;
}
int main()
{
    int i, N;
    int X;
    AVLTree T = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        T = Insert(T, X);
    }
    printf("%d\n", T->Data);
    system("pause");
    return 0;
}
