#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100010
typedef int ElementType;
typedef int Position;
typedef struct Node *List;
struct Node
{
    ElementType Data;
    Position Next;
} list[MAX];
int Reserver_link(List list, int Head, int K, int Node_Number)
{
    bool IsFirst = true; // 判断是否是第一次反转
    Position new, old, temp;
    Position start, factor;
    old = Head;
    factor = old;
    while (Node_Number - K >= 0)
    {
        Node_Number -= K;
        start = old;
        new = list[old].Next;
        temp = list[new].Next;
        for (int i = 1; i < K; i++)
        {
            list[new].Next = old;
            old = new;
            new = temp;
            temp = list[new].Next;
        }
        Node_Number += K;
        if (Node_Number >= K)
        {
            if (!IsFirst)
            {
                list[factor].Next = old;
                factor = start;
            }
        }
        Node_Number -= K;
        if (Node_Number < K)
            list[start].Next = new;
        if (IsFirst)
            Head = old;
        IsFirst = false;
        old = new;
    }
    return Head;
}
void Print_link(List list, int Head)
{
    int Address = Head;
    while (1)
    {
        if (list[Address].Next != -1)
            printf("%05d %d %05d\n", Address, list[Address].Data, list[Address].Next);
        else
            printf("%05d %d %d\n", Address, list[Address].Data, list[Address].Next);
        Address = list[Address].Next;
        if (Address == -1)
            break;
    }
}
int main()
{
    int Head, N, K;
    scanf("%d %d %d", &Head, &N, &K);
    int Address, Data, Next_Address;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &Address, &Data, &Next_Address);
        list[Address].Data = Data;
        list[Address].Next = Next_Address;
    }
    //判断list上真正有多少个node
    int Node_Number = 1;
    Address = Head;
    while (list[Address].Next != -1)
    {
        Node_Number++;
        Address = list[Address].Next;
    }
    if (K > 1)
        Head = Reserver_link(list, Head, K, Node_Number);
    Print_link(list, Head);
    system("pause");
    return 0;
}
