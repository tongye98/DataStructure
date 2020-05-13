#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 1000
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType1;
typedef int WeightType2;
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType1 distance;
    WeightType2 cost;
};
typedef PtrToENode Edge;
typedef struct Node
{
    WeightType1 distance;
    WeightType2 cost;
} node;
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    node G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;
MGraph CreateGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
        {
            Graph->G[V][W].distance = 0; //距离为0代表V,W不连通
            Graph->G[V][W].cost = INFINITY;
        }
    return Graph;
}
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2].distance = E->distance;
    Graph->G[E->V1][E->V2].cost = E->cost;
    Graph->G[E->V2][E->V1].distance = E->distance;
    Graph->G[E->V2][E->V1].cost = E->cost;
}
const Vertex Source, Destination; // 出发地和目的地
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    scanf("%d %d", &Source, &Destination);
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->distance, &E->cost);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
bool collected[MaxVertexNum];
WeightType1 dist[MaxVertexNum]; // source 到目前节点的距离
WeightType2 cost[MaxVertexNum]; // source 到目前节点的收费
Vertex path[MaxVertexNum];      // 记录当前节点的上一个节点
void Initialize(MGraph Graph, Vertex Source)
{
    int i;
    for (i = 0; i < Graph->Nv; i++)
    {
        collected[i] = false;
        dist[i] = INFINITY;
        cost[i] = 0;
        path[i] = -1;
    }
    // 接下来对source 源进行预处理
    collected[Source] = true;
    for (i = 0; i < Graph->Nv; i++)
    {
        if (Graph->G[Source][i].distance != 0)
        {
            dist[i] = Graph->G[Source][i].distance;
            cost[i] = Graph->G[Source][i].cost;
            path[i] = Source;
        }
    }
}
Vertex FindMindist(MGraph Graph)
{
    int i;
    WeightType1 min = INFINITY;
    Vertex result = -1;
    for (i = 0; i < Graph->Nv; i++)
        if (collected[i] == false)
        {
            if (dist[i] < min)
            {
                min = dist[i];
                result = i;
            }
        }
    return result;
}
void Dijkstra(MGraph Graph, Vertex S)
{
    Vertex V, W;
    int i;
    while (1)
    {
        // V = 未收入节点中的dist最小者
        V = FindMindist(Graph);
        if (V == -1) // 代表这样的节点不存在
            break;
        collected[V] = true;
        for (W = 0; W < Graph->Nv; W++) /* V的每个临接点W*/
            if (Graph->G[V][W].distance != 0)
            {
                if (collected[W] == false)
                    if (dist[V] + Graph->G[V][W].distance < dist[W])
                    {
                        dist[W] = dist[V] + Graph->G[V][W].distance;
                        path[W] = V;
                        cost[W] = cost[V] + Graph->G[V][W].cost;
                    }
                    else if ((dist[V] + Graph->G[V][W].distance == dist[W]) && (cost[W] > cost[V] + Graph->G[V][W].cost))
                    {
                        cost[W] = cost[V] + Graph->G[V][W].cost;
                        path[W] = V;
                    }
            }
    }
}
void print()
{
    printf("%d %d\n", dist[Destination], cost[Destination]);
}
int main()
{
    MGraph Graph;
    Graph = BuildGraph();
    Initialize(Graph, Source);
    Dijkstra(Graph, Source);
    print();
    system("pause");
    return 0;
}
