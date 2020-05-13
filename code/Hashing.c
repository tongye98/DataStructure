#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MAXTABLESIZE 100000
int Num;        /* 全局变量，记录输入个数*/
int PrintTimes; /* 全局变量，记录print 次数*/
typedef int ElementType;
typedef int Index;
typedef int Position;
typedef enum
{
    Legitimate,
    Empty,
    Deleted
} EntryType;
typedef struct HashEntry Cell;
struct HashEntry
{
    ElementType Data;
    EntryType Info;
};
typedef struct TblNode *HashTable;
struct TblNode
{
    int TableSize;
    Cell *Cells;
};
int NextPrime(int N)
{ /* 返回大于N且不超过MAXTABLESIZE的最小素数 */
    if (N == 1)
        return N + 1;
    int i, p = (N % 2) ? N + 2 : N + 1; /*从大于N的下一个奇数开始 */
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) /* p不是素数 */
                break;
        if (i == 2)
            break; /* for正常结束，说明p是素数 */
        else
            p += 2; /* 否则试探下一个奇数 */
    }
    return p;
}
HashTable CreatTable(int TabelSize)
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TabelSize);
    H->Cells = (Cell *)malloc(H->TableSize * sizeof(struct HashEntry));
    for (int i = 0; i < H->TableSize; i++)
        H->Cells[i].Info = Empty;
    return H;
}
Position Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
}
Position Find(HashTable H, ElementType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0;                                  /* 记录冲突次数 */
    NewPos = CurrentPos = Hash(Key, H->TableSize); /* 初始散列位置 */
    /* 当该位置的单元非空，并且不是要找的元素时，发生冲突 */
    while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key)
    { /* 字符串类型的关键词需要 strcmp 函数!! */
        if (CNum > H->TableSize)
            return -1;
        /* 统计1次冲突，并判断奇偶次 */
        if ((++CNum % 2))
        {                                                      /* 奇数次冲突 */
            NewPos = CurrentPos + (CNum + 1) * (CNum + 1) / 4; /* 增量为+[(CNum+1)/2]^2 */
            if (NewPos >= H->TableSize)
                NewPos = NewPos % H->TableSize; /* 调整为合法地址 */
        }
        else
        {                                          /* 偶数次冲突 */
            NewPos = CurrentPos + CNum * CNum / 4; /* 增量为-(CNum/2)^2 */
            if (NewPos >= H->TableSize)
                NewPos = NewPos % H->TableSize; /* 调整为合法地址 */
        }
    }
    return NewPos; /* 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）*/
}
bool Insert(HashTable H, ElementType Key)
{
    Position Pos = Find(H, Key); /* 先检查Key是否已经存在 */
    if (Pos == -1)
    {
        printf("-");
        PrintTimes++;
        if (PrintTimes != Num)
            printf(" ");
        return false;
    }
    if (H->Cells[Pos].Info != Legitimate)
    { /* 如果这个单元没有被占，说明Key可以插入在此 */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        /*字符串类型的关键词需要 strcpy 函数!! */
        printf("%d", Pos);
        PrintTimes++;
        if (PrintTimes != Num)
            printf(" ");
        return true;
    }
    else
    {
        printf("键值已存在");
        return false;
    }
}
int main()
{
    int MSize, N;
    scanf("%d %d", &MSize, &N);
    Num = N;
    HashTable H = CreatTable(MSize);
    ElementType Key;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &Key);
        Insert(H, Key);
    }
    system("pause");
    return 0;
}
