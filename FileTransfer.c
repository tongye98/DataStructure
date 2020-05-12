#include <stdio.h>
#include <stdlib.h>
#define MAXN 10000
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXN];
void Union(SetType S, SetName Root1, SetName Root2)
{
    if (S[Root2] < S[Root1])
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    else
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}
SetName Find(SetType S, ElementType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]); //路径压缩
}
void Initialization(SetType S, int N)
{
    int i;
    for (i = 0; i < N; i++)
        S[i] = -1;
}
void Input_connection(SetType S)
{
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d", &u, &v);
    Root1 = Find(S, u - 1);
    Root2 = Find(S, v - 1);
    if (Root1 != Root2)
        Union(S, Root1, Root2);
}
void Check_connection(SetType S)
{
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d", &u, &v);
    Root1 = Find(S, u - 1);
    Root2 = Find(S, v - 1);
    if (Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
}
void Check_network(SetType S, int N)
{
    int i, counter = 0;
    for (i = 0; i < N; i++)
    {
        if (S[i] < 0)
            counter++;
    }
    if (counter == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", counter);
}
int main()
{
    int N;
    scanf("%d", &N);
    SetType S;
    Initialization(S, N);
    char symbol;
    do
    {
        scanf("%c", &symbol);
        switch (symbol)
        {
        case 'I':
            Input_connection(S);
            break;
        case 'C':
            Check_connection(S);
            break;
        case 'S':
            Check_network(S, N);
            break;
        }
    } while (symbol != 'S');
    system("pause");
    return 0;
}