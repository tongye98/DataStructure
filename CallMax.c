#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define MAXTABLESIZE 100000
#define KEYLENGTH 11 /* 关键词字符串的最大长度 */
#define MAXD 5
typedef char ElementType[KEYLENGTH + 1]; /* 关键词类型用字符串 */
typedef int Index;                       /* 散列地址类型 */
/******** 以下是单链表的定义 ********/
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** 以上是单链表的定义 ********/

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode
{                  /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
};

int NextPrime(int N)
{                                       /* 返回大于N且不超过MAXTABLESIZE的最小素数 */
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

Index Hash(int Key, int TableSize)
{
    return Key % TableSize;
}

HashTable CreateTable(int TableSize)
{
    HashTable H;

    H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数 */
    H->TableSize = NextPrime(TableSize);

    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    /* 初始化表头结点 */
    for (int i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }

    return H;
}

Position Find(HashTable H, ElementType Key)
{
    Position P;
    Index Pos;

    Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize); /* 初始散列位置 */
    P = H->Heads[Pos].Next;                                 /* 从该链表的第1个结点开始 */
    /* 当未到表尾，并且Key未找到时 */
    while (P && strcmp(P->Data, Key))
        P = P->Next;

    return P; /* 此时P或者指向找到的结点，或者为NULL */
}

bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;

    P = Find(H, Key);
    if (!P)
    { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize); /* 初始散列位置 */
        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else
    { /* 关键词已存在 */
        P->Count++;
        return false;
    }
}

void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    /* 释放每个链表的结点 */
    for (i = 0; i < H->TableSize; i++)
    {
        P = H->Heads[i].Next;
        while (P)
        {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads); /* 释放头结点数组 */
    free(H);        /* 释放散列表结点 */
}

void ScanAndOutput(HashTable H)
{
    int MaxCnt = 0;
    int PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    for (int i = 0; i < H->TableSize; i++)
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {
            if (Ptr->Count > MaxCnt)
            {
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)
            {
                PCnt++;
                if (strcmp(MinPhone, Ptr->Data) > 0)
                    strcpy(MinPhone, Ptr->Data);
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if (PCnt > 1)
        printf(" %d", PCnt);
    printf("\n");
}

int main()
{
    int N;
    ElementType Key;
    HashTable H;
    scanf("%d", &N);
    H = CreateTable(N * 2);
    for (int i = 0; i < N; i++)
    {
        scanf("%s", Key);
        Insert(H, Key);
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);
    DestroyTable(H);
    system("pause");
    return 0;
}