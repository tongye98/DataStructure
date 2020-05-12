#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 1001 /* 最大顶点数设为10000 */
typedef int Vertex;       /* 用顶点下标表示顶点,为整型 */
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2; /* 有向边<V1, V2> */
};
typedef PtrToENode Edge;
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
} AdjList[MaxVertexNum];     /* AdjList是邻接表类型 */
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    /* 顶点数 */
    int Ne;    /* 边数   */
    AdjList G; /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */
LGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    for (V = 1; V <= Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
    return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
bool Visited[MaxVertexNum];
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv);          /* 读入顶点个数 */
    Graph = CreateGraph(Nv);   /* 初始化有Nv个顶点但没有边的图 */
    scanf("%d", &(Graph->Ne)); /* 读入边数 */
    if (Graph->Ne != 0)
    {                                           /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
int Q[MaxVertexNum];
int head = -1;
int tail = -1;
void Initialization(int *Q)
{
    head = tail = -1;
}
void AddQ(int *Q, Vertex S)
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
Vertex Delete(int *Q)
{
    return Q[++head];
}
int BFS(LGraph Graph, Vertex S)
{
    int count = 1;
    int level = 0;
    Vertex last = S;
    Vertex tail;
    Initialization(Q); //初始化队列
    Vertex V, W;
    Visited[S] = true;
    AddQ(Q, S);
    while (!IsEmpty(Q))
    {
        V = Delete(Q);
        PtrToAdjVNode K;
        for (K = Graph->G[V].FirstEdge; K; K = K->Next)
            if (!Visited[K->AdjV])
            {
                Visited[K->AdjV] = true; /* 标记W已访问 */
                AddQ(Q, K->AdjV);        /* W入队列 */
                count++;
                tail = K->AdjV;
            }
        if (V == last)
        {
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return count;
}
void SDS(LGraph Graph)
{
    int count;
    Vertex V;
    for (V = 1; V <= Graph->Nv; V++)
    {
        for (int i = 1; i <= Graph->Nv; i++)
            Visited[i] = false;
        count = BFS(Graph, V);
        printf("%d: %.2lf%%\n", V, 100.0 * count / Graph->Nv);
    }
}
int main()
{
    LGraph Graph;
    Graph = BuildGraph();
    SDS(Graph); //对每个节点进行广度优先搜索
    system("pause");
    return 0;
}