#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();

    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    system("pause");
    return 0;
}
List Read()
{
    int K;
    scanf("%d", &K);
    int i;
    List head, temp;
    head = (List)malloc(sizeof(struct Node));
    temp = head;
    for (i = 0; i < K; i++)
    {
        head->Next = (List)malloc(sizeof(struct Node));
        scanf("%d", &head->Next->Data);
        head = head->Next;
    }
    head->Next = NULL;
    return temp;
}
void Print(List L)
{
    L = L->Next;
    while (L != NULL)
    {
        printf("%d ", L->Data);
        L = L->Next;
    }
    printf("\n");
}
List Merge(List L1, List L2)
{
    List L;
    L = (List)malloc(sizeof(struct Node));
    List l, l1, l2;
    l1 = L1->Next;
    l2 = L2->Next;
    l = L;
    while (l1 != NULL && l2 != NULL)
    {
        if (l1->Data < l2->Data)
        {
            l->Next = l1;
            l = l->Next;
            l1 = l1->Next;
        }
        else
        {
            l->Next = l2;
            l = l->Next;
            l2 = l2->Next;
        }
    }
    l->Next = l1 ? l1 : l2;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}