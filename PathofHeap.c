#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *Data; //存储元素的数组
    int Size;          //堆中当前元素个数
    int Capacity;      //堆中最大容量
};
typedef Heap MinHeap;
#define MINDATA -10001
MinHeap CreateHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最大堆 */
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MINDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/
    return H;
}
bool IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}
#define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
bool IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}
bool Insert(MinHeap H, ElementType X)
{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
    if (IsFull(H))
    {
        printf("MaxHeap is full");
        return false;
    }
    i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
    for (; H->Data[i / 2] > X; i /= 2)
        H->Data[i] = H->Data[i / 2];
    H->Data[i] = X;
    return true;
}
int main()
{
    int N, M;
    int X;
    int i;
    MinHeap H;
    scanf("%d %d", &N, &M);
    H = CreateHeap(N);
    while (N--)
    {
        scanf("%d", &X);
        Insert(H, X);
    }
    while (M--)
    {
        scanf("%d", &i);
        int flag = 0;
        for (i; i > 0; i /= 2)
        {
            if (flag == 0)
            {
                printf("%d", H->Data[i]);
                flag = 1;
            }
            else
            {
                printf(" %d", H->Data[i]);
            }
        }
        printf("\n");
    }
    system("pause");
    return 0;
}