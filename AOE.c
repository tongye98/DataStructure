/*--------关键路径问题----------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType LastingTime;
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
    NewNode->Weight = E->LastingTime;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
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
            scanf("%d %d %d", &E->V1, &E->V2, &E->LastingTime);
            E->V1--;
            E->V2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
void TopSort(LGraph Graph)
{
    int Indegree[MaxVertexNum];
    int cnt = 0;
    int Earliest[MaxVertexNum];
    int Latest[MaxVertexNum];
    int Queue[MaxVertexNum]; //队列
    int head = -1;
    int tail = -1;
    int stock[MaxVertexNum]; // 堆栈
    int top = -1;            //栈顶位置
    int maxtime = -1;
    Vertex V;
    PtrToAdjVNode W;
    for (V = 0; V < Graph->Nv; V++)
    { // 初始化度和时间
        Indegree[V] = 0;
        Earliest[V] = 0;
        Latest[V] = INFINITY;
    }
    for (V = 0; V < Graph->Nv; V++) // 确定每个节点的入度
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->AdjV]++;
    for (V = 0; V < Graph->Nv; V++)
        if (Indegree[V] == 0) // 找到度为0的进队列 还要入栈
        {
            Queue[++tail] = V;
            stock[++top] = V;
        }
    while (head != tail)
    { //队列非空时
        V = Queue[++head];
        cnt++;
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (Earliest[V] + W->Weight > Earliest[W->AdjV])
                Earliest[W->AdjV] = Earliest[V] + W->Weight;
            if (--Indegree[W->AdjV] == 0)
            {
                Queue[++tail] = W->AdjV;
                stock[++top] = W->AdjV;
            }
        }
    }
    for (V = 0; V < Graph->Nv; V++)
        if (Earliest[V] > maxtime)
            maxtime = Earliest[V];
    if (cnt == Graph->Nv)
        printf("%d\n", maxtime);
    else
    {
        printf("0\n");
        return;
    }
    while (top != -1)
    {
        V = stock[top];
        if (Graph->G[V].FirstEdge == NULL)
        {
            if (Earliest[stock[top]] == maxtime) // 考虑到多起点多终点情形，参考自创样例三
            {
                Latest[stock[top]] = Earliest[stock[top]];
                top--;
                continue;
            }
            else
            {
                Latest[stock[top]] = Earliest[stock[top]] + 1;
                top--;
                continue;
            }
        }
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (Latest[V] > Latest[W->AdjV] - W->Weight)
                Latest[V] = Latest[W->AdjV] - W->Weight;
        }
        top--;
    }
    //for (V = 0; V < Graph->Nv; V++)
    //    printf("%d %d %d\n", V + 1, Earliest[V], Latest[V]);
    for (V = 0; V < Graph->Nv; V++)
    {
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            if (Latest[W->AdjV] - Earliest[V] - W->Weight == 0) //说明为关键路径
                printf("%d->%d\n", V + 1, W->AdjV + 1);
    }
}
int main()
{
    LGraph Graph = BuildGraph();
    TopSort(Graph);
    system("pause");
    return 0;
}