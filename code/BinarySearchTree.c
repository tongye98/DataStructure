#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");
    system("pause");
    return 0;
}
void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        PreorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Right);
    }
}
/* 你的代码将被嵌在这里 */
Position Find(BinTree BST, ElementType X)
{
    // 函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
    while (BST)
    {
        if (X > BST->Data)
            BST = BST->Right;
        else if (X < BST->Data)
            BST = BST->Left;
        else
            return BST;
    }
    return NULL;
}
Position FindMin(BinTree BST)
{
    // 函数FindMin返回二叉搜索树BST中最小元结点的指针；
    if (BST)
        while (BST->Left)
            BST = BST->Left;
    return BST;
}
Position FindMax(BinTree BST)
{
    // 函数FindMax返回二叉搜索树BST中最大元结点的指针
    if (BST)
        while (BST->Right)
            BST = BST->Right;
    return BST;
}
BinTree Insert(BinTree BST, ElementType X)
{
    // 函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
    if (!BST)
    {
        BST = malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if (X < BST->Data)
            BST->Left = Insert(BST->Left, X);
        else if (X > BST->Data)
            BST->Right = Insert(BST->Right, X);
    }
    return BST;
}
BinTree Delete(BinTree BST, ElementType X)
{
    /* 函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
    如果X不在树中，则打印一行Not Found并返回原树的根结点指针；*/
    Position Tmp;
    if (!BST)
        printf("Not Found\n");
    else if (X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if (X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    else
    {
        if (BST->Left && BST->Right) //被删除节点有左右两个节点
        {
            Tmp = FindMin(BST->Right); //在右子树中找最小的元素填充删除结点
            BST->Data = Tmp->Data;
            BST->Right = Delete(BST->Right, BST->Data); //在删除结点的右子树中删除最小元素
        }
        else
        { // 被删除结点要么有一个子节点要么无子节点
            Tmp = BST;
            if (!BST->Left)
                BST = BST->Right;
            else if (!BST->Right)
                BST = BST->Left;
            free(Tmp);
        }
    }
    return BST;
}
