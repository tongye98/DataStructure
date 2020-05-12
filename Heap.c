#include <stdio.h>

typedef int ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *Data; //存储元素的数组
    int Size;          //堆中当前元素个数
    int Capacity;      //堆中最大容量
};
typedef Heap MaxHeap;
typedef Heap MinHeap;
#define MAXDATA 1000 /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */
MaxHeap CreateHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最大堆 */
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/
    return H;
}
bool IsFull(MaxHeap H)
{
    return (H->Size == H->Capacity);
}
bool Insert(MaxHeap H, ElementType X)
{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
    if (IsFull(H))
    {
        printf("MaxHeap is full");
        return false;
    }
    i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
    for (; H->Data[i / 2] < X; i /= 2)
        H->Data[i] = H->Data[i / 2];
    H->Data[i] = X;
    return true;
}
#define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
bool IsEmpty(MaxHeap H)
{
    return (H->Size == 0);
}
ElementType DeleteMax(MaxHeap H)
{ /* 从最大堆H中取出键值为最大的元素，并删除一个结点 */
    int parent, child;
    ElementType MaxItem, X;
    if (IsEmpty(H))
    {
        printf("MaxHeap is empty");
        return ERROR;
    }
    MaxItem = H->Data[1]; /* 取出根结点存放的最大值 */
    X = H->Data[H->Size--];
    for (parent = 1; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if ((child != H->Size) && (H->Data[child] < H->Data[child + 1]))
            child++; /* child指向左右子结点的较大者 */
        if (X >= H->Data[child])
            break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
    return MaxItem;
}
/*----------- 建造最大堆 -----------*/
void PercDown(MaxHeap H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
    int parent, child;
    ElementType X;
    X = H->Data[p];
    for (parent = p; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if ((child != H->Size) && H->Data[child] < H->Data[child + 1])
            child++;
        if (X > H->Data[child])
            break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
}
void BuildHeap(MaxHeap H)
{   /* 调整H->Data[]中的元素，使满足最大堆的有序性  */
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
    int i;
    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
}