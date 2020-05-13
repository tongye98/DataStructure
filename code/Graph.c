/*---------------图的邻接矩阵表示法---------------------*/
#define MaxVertexNum 100 /* 最大顶点数设为100 */
#define INFINITY 65535   /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;   /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;     /* 有向边<V1, V2> */
    WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                   /* 顶点数 */
    int Ne;                                   /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
    DataType Data[MaxVertexNum];              /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    /* 插入边 <V1, V2> */
    Graph->G[E->V1][E->V2] = E->Weight;
    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);        /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

    scanf("%d", &(Graph->Ne)); /* 读入边数 */
    if (Graph->Ne != 0)
    {                                           /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
    }

    /* 如果顶点有数据的话，读入数据 */
    for (V = 0; V < Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));

    return Graph;
}

/*------------------图的邻接表表示法--------------------*/
#define MaxVertexNum 100 /* 最大顶点数设为100 */
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;   /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;     /* 有向边<V1, V2> */
    WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
    DataType Data;           /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum]; /* AdjList是邻接表类型 */

/* 图结点的定义 */
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
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    /* 若是无向图，还要插入边 <V2, V1> */
    /* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);        /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

    scanf("%d", &(Graph->Ne)); /* 读入边数 */
    if (Graph->Ne != 0)
    {                                           /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
    }

    /* 如果顶点有数据的话，读入数据 */
    for (V = 0; V < Graph->Nv; V++)
        scanf(" %c", &(Graph->G[V].Data));

    return Graph;
}

/* 邻接表存储的图 - DFS */
void Visit(Vertex V)
{
    printf("正在访问顶点%d\n", V);
}

/* Visited[]为全局变量，已经初始化为false */
void DFS(LGraph Graph, Vertex V, void (*Visit)(Vertex))
{ /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
    PtrToAdjVNode W;

    Visit(V);          /* 访问第V个顶点 */
    Visited[V] = true; /* 标记V已访问 */

    for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
        if (!Visited[W->AdjV])                      /* 若W->AdjV未被访问 */
            DFS(Graph, W->AdjV, Visit);             /* 则递归访问之 */
}

/* 邻接矩阵存储的图 - BFS */
/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
bool IsEdge(MGraph Graph, Vertex V, Vertex W)
{
    return Graph->G[V][W] < INFINITY ? true : false;
}

/* Visited[]为全局变量，已经初始化为false */
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{ /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;
    Vertex V, W;

    Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
    /* 访问顶点S：此处可根据具体访问需要改写 */
    Visit(S);
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Q, S);        /* S入队列 */

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);                 /* 弹出V */
        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if (!Visited[W] && IsEdge(Graph, V, W))
            {
                /* 访问顶点W */
                Visit(W);
                Visited[W] = true; /* 标记W已访问 */
                AddQ(Q, W);        /* W入队列 */
            }
    } /* while结束*/
}

/* 邻接表存储 - 无权图的单源最路径算法 */

/* dist[]和path[]全部初始化为-1 */
void Unweighted(LGraph Graph, int dist[], int path[], Vertex S)
{
    Queue Q;
    Vertex V;
    PtrToAdjVNode W;

    Q = CreateQueue(Graph->Nv); /* 创建空队列, MaxSize为外部定义的常数 */
    dist[S] = 0;                /* 初始化源点 */
    AddQ(Q, S);

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);
        for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
            if (dist[W->AdjV] == -1)
            {                                /* 若W->AdjV未被访问过 */
                dist[W->AdjV] = dist[V] + 1; /* W->AdjV到S的距离更新 */
                path[W->AdjV] = V;           /* 将V记录在S到W->AdjV的路径上 */
                AddQ(Q, W->AdjV);
            }
    } /* while结束*/
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; V++)
    {
        if (collected[V] == false && dist[V] < MinDist)
        {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V;          /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV;        /* 返回对应的顶点下标 */
    else
        return ERROR; /* 若这样的顶点不存在，返回错误标记 */
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V, W;

    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for (V = 0; V < Graph->Nv; V++)
    {
        dist[V] = Graph->G[S][V];
        if (dist[V] < INFINITY)
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    collected[S] = true;

    while (1)
    {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist(Graph, dist, collected);
        if (V == ERROR)                 /* 若这样的V不存在 */
            break;                      /* 算法结束 */
        collected[V] = true;            /* 收录V */
        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未被收录 */
            if (collected[W] == false && Graph->G[V][W] < INFINITY)
            {
                if (Graph->G[V][W] < 0) /* 若有负边 */
                    return false;       /* 不能正确解决，返回错误标记 */
                /* 若收录V使得dist[W]变小 */
                if (dist[V] + Graph->G[V][W] < dist[W])
                {
                    dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
                    path[W] = V;                        /* 更新S到W的路径 */
                }
            }
    }            /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}

/* 邻接矩阵存储 - 多源最短路算法 */

bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
    Vertex i, j, k;

    /* 初始化 */
    for (i = 0; i < Graph->Nv; i++)
        for (j = 0; j < Graph->Nv; j++)
        {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }

    for (k = 0; k < Graph->Nv; k++)
        for (i = 0; i < Graph->Nv; i++)
            for (j = 0; j < Graph->Nv; j++)
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    if (i == j && D[i][j] < 0) /* 若发现负值圈 */
                        return false;          /* 不能正确解决，返回错误标记 */
                    path[i][j] = k;
                }
    return true; /* 算法执行完毕，返回正确标记 */
}
