#include <stdio.h>
#define ElementType int
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    struct SNode *Next;
};
Stack CreateStack();
int IsEmpty(Stack S);
void Push(ElementType item, Stack S);
ElementType Pop(Stack S);
int main()
{
    system("pause");
    return 0;
}
Stack CreateStack()
{ // 构建一个堆栈的头结点，返回指针
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
int IsEmpty(Stack S)
{
    return (S->Next == NULL);
}
void Push(ElementType item, Stack S)
{ // 将元素item压入堆栈S
    struct SNode *TmpCell;
    TmpCell = (struct SNode *)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}
ElementType Pop(Stack S)
{ // 删除并返回堆栈S的栈顶元素
    struct SNode *FirstCell;
    ElementType TopElem;
    if (IsEmpty(S))
    {
        printf("the stock is empty");
        return NULL;
    }
    else
    {
        FirstCell = S->Next;
        S->Next = FirstCell->Next;
        TopElem = FirstCell->Data;
        free(FirstCell);
        return TopElem;
    }
}
