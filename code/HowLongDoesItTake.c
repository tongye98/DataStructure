#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100
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
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
void TopSort(LGraph Graph)
{
    int Indegree[MaxVertexNum];
    int Time[MaxVertexNum];
    int cnt = 0;
    int Queue[MaxVertexNum];
    int head = -1;
    int tail = -1;
    int maxtime = -1;
    Vertex V;
    PtrToAdjVNode W;
    for (V = 0; V < Graph->Nv; V++)
    { // 初始化度和时间
        Indegree[V] = 0;
        Time[V] = 0;
    }
    for (V = 0; V < Graph->Nv; V++)
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            Indegree[W->AdjV]++;
    for (V = 0; V < Graph->Nv; V++)
        if (Indegree[V] == 0)
            Queue[++tail] = V;
    while (head != tail)
    { //队列非空时
        V = Queue[++head];
        cnt++;
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (Time[V] + W->Weight > Time[W->AdjV])
                Time[W->AdjV] = Time[V] + W->Weight;
            if (--Indegree[W->AdjV] == 0)
                Queue[++tail] = W->AdjV;
        }
    }
    if (cnt == Graph->Nv)
    {
        for (V = 0; V < Graph->Nv; V++)
            if (Time[V] > maxtime)
                maxtime = Time[V];
        printf("%d\n", maxtime);
    }
    else
        printf("Impossible\n");
}
int main()
{
    LGraph Graph = BuildGraph();
    TopSort(Graph);
    system("pause");
    return 0;
}
