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
int dist[MAX]; // 记录层数
int path[MAX]; // 记录从哪里跳过来
int N;         //数目
void check_Position(int i, int x, int y)
{
    if (abs(x) >= 50 || abs(y) >= 50)
    {
        Position[i].x = 100;
        Position[i].y = 100;
    }
    if (sqrt(x * x + y * y) <= r)
    {
        Position[i].x = 100;
        Position[i].y = 100;
    }
}
void InputPosition(int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lf %lf", &Position[i].x, &Position[i].y);
        check_Position(i, Position[i].x, Position[i].y);
        dist[i] = -1;
        path[i] = -1;
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

// 队列的一些操作
int Q[MAX];
int head = -1;
int tail = -1;
void Initialization(int *Q)
{
    head = tail = -1;
}
void AddQ(int *Q, int S)
{
    Q[++tail] = S;
}
bool IsEmpty(int *Q)
{
    if (head == tail)
        return true;
    else
        return false;
}
int Delete(int *Q)
{
    return Q[++head];
}
int sucess_position[MAX]; // 上岸前的那个点
int cnt = -1;             //用于记录有几条逃生路径
bool cansave = false;
void UnWeighted()
{
    while (!IsEmpty(Q))
    {
        int V = Delete(Q);
        if (IsSafe(V))
        {
            cansave = true;
            sucess_position[++cnt] = V;
        }
        for (int W = 0; W < N; W++)
            if (dist[W] == -1 && Jump(V, W))
            {
                dist[W] = dist[V] + 1;
                path[W] = V;
                AddQ(Q, W);
            }
    }
}
// 建立一个堆栈存路径
int stock[MAX * 100];
int point = -1;
void Push(int i)
{
    stock[++point] = i;
}
int Pop()
{
    if (point != -1)
        return stock[point--];
    else
    {
        printf("the stock is empty\n");
        return;
    }
}
int fistjumpmin[MAX];
int minjump = 100;
int ct = -1;
int key;
int FindPath()
{
    int min = MAX;
    int j;
    int goal;
    for (j = 0; j <= cnt; j++)
    {
        if (dist[sucess_position[j]] < min)
        {
            min = dist[sucess_position[j]];
            goal = j;
        }
    }
    for (j = 0; j <= cnt; j++)
    { //要找到最小路径里第一条最小的
        if (dist[sucess_position[j]] == min)
            fistjumpmin[++ct] = sucess_position[j];
    }
    return goal;
}
void stock_operator()
{
    for (int k = 0; k <= ct; k++)
    {
        int u = fistjumpmin[k];
        while (path[u] != -1)
        {
            Push(u);
            u = path[u];
        }
        Push(u);
        if (sqrt(pow(Position[u].x, 2) + pow(Position[u].y, 2)) < minjump)
        {
            minjump = sqrt(pow(Position[u].x, 2) + pow(Position[u].y, 2));
            key = k;
        }
    }
}
void really()
{
    point = -1;
    int u = fistjumpmin[key];
    while (path[u] != -1)
    {
        Push(u);
        u = path[u];
    }
    Push(u);
}
void print()
{
    while (point >= 0)
    {
        int i = Pop();
        printf("%.0f %.0f\n", Position[i].x, Position[i].y);
    }
}
int main()
{
    scanf("%d %lf", &N, &D);
    InputPosition(N);
    Initialization(Q); //初始化队列
    if (D >= 50 - r)
    {
        printf("1\n");
        system("pause");
        return 0;
    }
    for (int K = 0; K < N; K++)
    {
        if (FirstJump(K))
        {
            if (!IsSafe(K))
            {
                dist[K] = 1;
                AddQ(Q, K);
            }
            else
            {
                dist[K] = 1;
                sucess_position[++cnt] = K;
            }
        }
    }
    UnWeighted();
    if (cnt != -1) //可能有多条路径
    {
        int goal = FindPath(); // 找到目标路径
        printf("%d\n", dist[sucess_position[goal]] + 1);
        stock_operator();
        really();
        print();
    }
    else
        printf("0\n");
    system("pause");
    return 0;
}
