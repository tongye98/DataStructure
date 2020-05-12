#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 1000
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;
LGraph CreateGraph(int VertexNum)
{
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
    return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
/* 邻接表存储 - Kruskal最小生成树算法  稀疏图较优*/
typedef Vertex ElementType;
typedef Vertex SetName;
typedef ElementType SetType[MaxVertexNum];
void InitializeVSet(SetType S, int N)
{
    ElementType X;
    for (X = 0; X < N; X++)
        S[X] = -1;
}
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
        return S[X] = Find(S, S[X]);
}
bool CheckCycle(SetType VSet, Vertex V1, Vertex V2)
{
    Vertex Root1, Root2;
    Root1 = Find(VSet, V1);
    Root2 = Find(VSet, V2);
    if (Root1 == Root2)
        return false;
    else
    {
        Union(VSet, Root1, Root2);
        return true;
    }
}
void PercDown(Edge ESet, int p, int N)
{
    int Parent, Child;
    struct ENode X;
    X = ESet[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (ESet[Child].Weight) > ESet[Child + 1].Weight)
            Child++;
        if (X.Weight <= ESet[Child].Weight)
            break;
        else
            ESet[Parent] = ESet[Child];
    }
    ESet[Parent] = X;
}
void InitializeESet(LGraph Graph, Edge ESet)
{ // 将图的边存入数组ESet,初始化为最小堆
    // ESet是一个数组，每一个元素是一个边结构
    Vertex V;
    PtrToAdjVNode W;
    int ECount;
    ECount = 0;
    for (V = 0; V < Graph->Nv; V++)
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            if (V < W->AdjV)
            {
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->AdjV;
                ESet[ECount++].Weight = W->Weight;
            }
    for (ECount = Graph->Ne / 2; ECount >= 0; ECount--)
        PercDown(ESet, ECount, Graph->Ne);
}
void Swap(Edge E1, Edge E2)
{
    struct ENode temp;
    temp.V1 = (*E1).V1;
    temp.V2 = (*E1).V2;
    temp.Weight = (*E1).Weight;
    (*E1).V1 = (*E2).V1;
    (*E1).V2 = (*E2).V2;
    (*E1).Weight = (*E2).Weight;
    (*E2).V1 = temp.V1;
    (*E2).V2 = temp.V2;
    (*E2).Weight = temp.Weight;
}
int GetEdge(Edge ESet, int CurrentSize)
{
    Swap(&ESet[0], &ESet[CurrentSize - 1]);
    PercDown(ESet, 0, CurrentSize - 1);
    return CurrentSize - 1;
}
int Kruskal(LGraph Graph, LGraph MST)
{ //将最小生成树保存为邻接表存储的图MST,返回最小权重和
    WeightType TotalWeight;
    int ECount, NextEdge;
    SetType VSet;                    // 顶点数组
    Edge ESet;                       // 边数组
    InitializeVSet(VSet, Graph->Nv); //初始化顶点并查集
    ESet = (Edge)malloc(sizeof(struct ENode) * Graph->Ne);
    InitializeESet(Graph, ESet); //初始化边的最小堆
    MST = CreateGraph(Graph->Nv);
    TotalWeight = 0;
    ECount = 0;           // 初始化收录的边数
    NextEdge = Graph->Ne; // 原始边集的规模
    while (ECount < Graph->Nv - 1)
    {
        NextEdge = GetEdge(ESet, NextEdge);
        if (NextEdge < 0) //边集已空
            break;
        if (CheckCycle(VSet, ESet[NextEdge].V1, ESet[NextEdge].V2) == true)
        {
            InsertEdge(MST, ESet + NextEdge);
            TotalWeight += ESet[NextEdge].Weight;
            ECount++;
        }
    }
    if (ECount < Graph->Nv - 1)
        TotalWeight = -1; // 设置错误信号，表示生成树不存在
    return TotalWeight;
}
int main()
{
    LGraph Graph = BuildGraph();
    LGraph MST;
    WeightType TotalWeight = Kruskal(Graph, MST);
    printf("%d\n", TotalWeight);
    system("pause");
    return 0;
}