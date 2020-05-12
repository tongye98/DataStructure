#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXTABLESIZE 1000000
#define PasswordDigit 17
#define AccountDigit 11
typedef int ElementType;
typedef int Position;
typedef int Index;
typedef enum
{
    Legitimate,
    Empty,
} EntryType;
typedef struct HashEntry Cell;
struct HashEntry
{
    ElementType Account;
    char *Password;
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
HashTable CreaTable(int TableSize)
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Cells = (Cell *)malloc(H->TableSize * sizeof(struct HashEntry));
    for (int i = 0; i < H->TableSize; i++)
    {
        H->Cells[i].Info = Empty;
        H->Cells[i].Password = (char *)malloc(PasswordDigit * sizeof(char));
        H->Cells[i].Password[0] = '\0';
    }
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
    while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Account != Key)
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

int main()
{
    int N;
    scanf("%d\n", &N);
    HashTable H = CreaTable(N);
    for (int i = 0; i < N; i++)
    {
        char c;
        char Account[AccountDigit];
        char Password[PasswordDigit];
        ElementType Key;
        scanf("%c", &c);
        scanf("%s", Account);
        scanf("%s", Password);
        if (c == 'L')
        {
            Key = atoi(Account);
            Index pos = Find(H, Key);
            if (H->Cells[pos].Info == Legitimate)
            {
                if (!strcmp(Password, H->Cells[pos].Password))
                    printf("Login: OK\n");
                else
                    printf("ERROR: Wrong PW\n");
            }
            else
                printf("ERROR: Not Exist\n");
        }
        else if (c == 'N')
        {
            Key = atoi(Account);
            Index pos = Find(H, Key);
            if (H->Cells[pos].Info != Legitimate)
            {
                H->Cells[pos].Info = Legitimate;
                H->Cells[pos].Account = Key;
                strcpy(H->Cells[pos].Password, Password);
                printf("New: OK\n");
            }
            else
                printf("ERROR: Exist\n");
        }
        else
            printf("input is illegal\n");
        getchar();
    }
    system("pause");
    return 0;
}