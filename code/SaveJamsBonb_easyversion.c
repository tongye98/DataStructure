#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 1000
struct Node
{
    double x;
    double y;
} Position[MAX];
double D; //最大跳跃距离
const double r = 1.0 * 15 / 2;
bool Visited[MAX];
int N; //数目
void InputPosition(int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lf %lf", &Position[i].x, &Position[i].y);
        Visited[i] = false;
    }
}
bool FirstJump(int i) // 第一跳能跳到i吗
{
    return sqrt(pow(Position[i].x, 2) + pow(Position[i].y, 2)) <= r + D;
}
bool Jump(int i, int j) // 能从i 跳掉j 吗
{
    return sqrt(pow(Position[i].x - Position[j].x, 2) + pow(Position[i].y - Position[j].y, 2)) <= D;
}
bool IsSafe(int i)
{
    return (50 - abs(Position[i].x) <= D || 50 - abs(Position[i].y) <= D);
}
bool DFS(int v)
{
    bool IsJump = false;
    Visited[v] = true;
    if (IsSafe(v))
        return true;
    for (int i = 0; i < N; i++)
    {
        if (!Visited[i] && Jump(i, v))
        {
            IsJump = DFS(i);
            if (IsJump)
                return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d %lf", &N, &D);
    InputPosition(N);
    bool save = false;
    for (int i = 0; i < N; i++)
    {
        if (!Visited[i] && FirstJump(i))
        {
            save = DFS(i);
            if (save == true)
                break;
        }
    }
    if (save == true)
        printf("Yes\n");
    else
        printf("No\n");
    system("pause");
    return 0;
}
