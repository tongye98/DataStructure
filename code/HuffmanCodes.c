#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    char symbol;
    int Weight;
    HuffmanTree Left, Right;
};
typedef struct Tree *PtrTree;
struct Tree
{
    int weight;
    char symbol;
    PtrTree Left;
    PtrTree Right;
};
typedef struct HNode *Heap;
struct HNode
{
    HuffmanTree *Data; //存储元素的数组
    int Size;          //堆中当前元素个数
    int Capacity;      //堆中最大容量
};
typedef Heap MinHeap;
#define MAXDATA -1000 /* 该值应根据具体情况定义为小于堆中所有可能元素的值 */
MinHeap CreateHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最小堆 */
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (HuffmanTree *)malloc((MaxSize + 1) * sizeof(HuffmanTree));
    H->Size = 0;
    H->Capacity = MaxSize;
    //H->Data[0]->Weight = MAXDATA; /* 定义"哨兵"为小于堆中所有可能元素的值*/
    return H;
}
bool IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}
bool IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}
bool Insert(MinHeap H, HuffmanTree X)
{ /* 将元素X插入最小堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
    if (IsFull(H))
    {
        printf("MinHeap is full");
        return false;
    }
    i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
    if (i > 1)
    {
        for (; H->Data[i / 2]->Weight > X->Weight; i /= 2)
            H->Data[i] = H->Data[i / 2];
        H->Data[i] = X;
        return true;
    }
    else
    {
        H->Data[i] = X;
        return true;
    }
}
#define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
HuffmanTree DeleteMin(MinHeap H)
{ /* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
    int parent, child;
    HuffmanTree MinItem, X;
    if (IsEmpty(H))
    {
        printf("MinHeap is empty");
        return NULL;
    }
    MinItem = H->Data[1]; /* 取出根结点存放的最小值 */
    X = H->Data[H->Size--];
    for (parent = 1; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if ((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight))
            child++; /* child指向左右子结点的较小者 */
        if (X->Weight <= H->Data[child]->Weight)
            break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
    return MinItem;
}
MinHeap ReadData(MinHeap H, int N)
{
    int i;
    for (i = 1; i <= N; i++)
    {
        H->Data[i] = malloc(sizeof(struct TreeNode));
        H->Data[i]->Left = H->Data[i]->Right = NULL;
        scanf("%c %d", &H->Data[i]->symbol, &H->Data[i]->Weight);
        getchar();
        H->Size++;
    }
    return H;
}
void PercDown(MinHeap H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
    int parent, child;
    HuffmanTree X;
    X = H->Data[p];
    for (parent = p; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if ((child != H->Size) && H->Data[child]->Weight > H->Data[child + 1]->Weight)
            child++;
        if (X->Weight < H->Data[child]->Weight)
            break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
}
void BuildMinHeap(MinHeap H)
{
    int i;
    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
}
HuffmanTree Huffman(MinHeap H)
{
    int i;
    HuffmanTree T;
    int cont = H->Size;
    BuildMinHeap(H);
    for (i = 1; i < cont; i++)
    {
        T = malloc(sizeof(struct TreeNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}
int WPL(HuffmanTree T, int Depth)
{
    if (!T->Left && !T->Right)
        return (Depth * T->Weight);
    else
        return (WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1));
}
HuffmanTree node;
void getWeight(HuffmanTree T, char sym)
{
    if (T)
    {
        if (T->symbol == sym)
            node = T;
        getWeight(T->Left, sym);
        getWeight(T->Right, sym);
    }
}
int everyline(HuffmanTree T, PtrTree V, int *Student_CodeLen, int N)
{ //对每一行而言
    PtrTree t = V;
    int flag = 1;
    char *p;
    p = (char *)malloc(sizeof(char));
    char sym;
    getchar();
    scanf("%c %s", &sym, p);
    int len = strlen(p);
    if (len > N - 1)
        flag = 0;
    getWeight(T, sym);
    int Weight = node->Weight;
    Student_CodeLen[0] += Weight * len;
    int i;
    for (i = 0; i < len; i++)
    {
        if (flag == 0)
            break;
        if (*(p + i) == '0') //往左走
        {
            if (t->Left == NULL)
            { //无左儿子，创建一个节点
                t->Left = (PtrTree)malloc(sizeof(struct Tree));
                t = t->Left;
                t->weight = 0;
                t->Left = t->Right = NULL;
                if (i == len - 1)
                {
                    if (!t->Left && !t->Right)
                        t->weight = Weight;
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            { //有左儿子
                t = t->Left;
                if (t->weight != 0) //判断有无权重
                {
                    flag = 0;
                    break;
                }
                if (i == len - 1)
                {
                    if (!t->Left && !t->Right)
                        t->weight = Weight;
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        else
        { //往右走
            if (t->Right == NULL)
            { //无右儿子，创建一个节点
                t->Right = (PtrTree)malloc(sizeof(struct Tree));
                t = t->Right;
                t->weight = 0;
                t->Left = t->Right = NULL;
                if (i == len - 1)
                {
                    if (!t->Left && !t->Right)
                        t->weight = Weight;
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            { //有右儿子
                t = t->Right;
                if (t->weight != 0) //判断有无权重，如有
                {
                    flag = 0;
                    break;
                }
                if (i == len - 1)
                {
                    if (!t->Left && !t->Right)
                        t->weight = Weight;
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
    if (flag == 1)
        return 1;
    else
        return 0;
}
int IsHuffmanCode(HuffmanTree T, int CodeLen, int N)
{ //对每一位学生的编码而言
    PtrTree V;
    V = (PtrTree)malloc(sizeof(struct Tree));
    V->Left = V->Right = NULL;
    int Student_CodeLen[1];
    Student_CodeLen[0] = 0;
    int flag = 1;
    int final_flag = 1;
    int n = N;
    while (N--)
    { //对每一行编码而言
        flag = everyline(T, V, Student_CodeLen, n);
        if (flag == 0)
            final_flag = 0;
    }
    if (final_flag == 0)
        return 0;
    else
    {
        if (Student_CodeLen[0] == CodeLen)
            return 1;
        else
            return 0;
    }
}
int main()
{
    int N;
    scanf("%d\n", &N);
    MinHeap H = CreateHeap(N);
    H = ReadData(H, N);
    HuffmanTree T = Huffman(H);
    int CodeLen = WPL(T, 0);
    //printf("%d\n", CodeLen);
    int M;
    scanf("%d", &M);
    while (M--)
    {
        if (IsHuffmanCode(T, CodeLen, N))
            printf("Yes\n");
        else
            printf("No\n");
    }
    system("pause");
    return 0;
}
