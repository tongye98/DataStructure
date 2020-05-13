#include <stdio.h>
#define ERROR -1
#define ElementType int
#define bool int
struct Node
{ //队列中的节点
    ElementType Data;
    struct Node *Next;
};
struct QNode
{                       //链队列结构
    struct Node *rear;  // 指向队尾节点
    struct Node *front; // 指向队头节点
};
typedef struct QNode *Queue;
Queue PtrQ;
ElementType DeleteQ(Queue PtrQ)
{
    struct Node *FrontCell;
    ElementType FrontElem;
    if (PtrQ->front == NULL)
    {
        printf("the queue is empty");
        return ERROR;
    }
    FrontCell = PtrQ->front;
    if (PtrQ->front == PtrQ->rear) //队列只有一个元素
        PtrQ->front = PtrQ->rear = NULL;
    else
        PtrQ->front = PtrQ->front->Next;
    FrontElem = FrontCell->Data;
    free(FrontCell);
    return FrontElem;
}
bool IsEmpty(Queue Q)
{
    return (Q->front == NULL);
}
