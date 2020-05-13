#include <stdio.h>
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
//二叉树的遍历方法
void PreOrderTraversal(BinTree BT);   //先序---根、左子树、右子树
void InOrderTraversal(BinTree BT);    //中序---左子树、根、右子树
void PostOrderTraversal(BinTree BT);  //后序---左子树、右子树、根
void LevelOrderTraversal(BinTree BT); //层次遍历,从上到下,从左往右

void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PreOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Right);
    }
}
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }
}
void LevelOrderTraversal(BinTree BT)
{
    Queue Q;
    BinTree T;
    if (!BT)
        return;
    Q = CreatQueue(Maxsize);
    AddQ(Q, BT);
    while (!IsEmptyQ(Q))
    {
        T = Delete(Q);
        printf("%d\n", T->Data);
        if (T->Left)
            AddQ(Q, T->Left);
        if (T->Right)
            AddQ(Q, T->Right);
    }
}
int PostOrderGetHeight(BinTree BT) //树的深度
{
    int HL, HR, MaxH;
    if (BT)
    {
        HL = PostOrderGetHeight(BT->Left);
        HR = PostOrderGetHeight(BT->Right);
        MaxH = (HL > HR) ? HL : HR;
        return (MaxH + 1);
    }
    else
        return 0;
}
