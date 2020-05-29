/* 关键路径算法 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAX_EDGE 30
#define MAX_VEX 30
#define INFINITY 65535

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/* 事件最早发生时间和最迟发生时间数组，全局变量 */
int *etv, *ltv;
/* 用于存储拓扑序列的栈 */
int *stack2;
/* 用于stack2的指针 */
int top2;

/* 邻接矩阵结构 */
typedef struct
{
    int vexs[MAX_VEX];
    int arc[MAX_VEX][MAX_VEX];
    int numVertexes, numEdges;
} MGraph;

/* 邻接表结构 */
/* 边表结点 */
typedef struct EdgeNode
{
    /* 邻接点域，存储该顶点对应的下标 */
    int adjvex;
    /* 用于存储权值，对于非网图可以不需要 */
    int weight;
    /* 链域，指向下一个邻接点 */
    struct EdgeNode *next;
} EdgeNode;

/* 顶点表结点 */
typedef struct VertexNode
{
    /* 顶点入度 */
    int in;
    /* 顶点域，存储顶点信息 */
    int data;
    /* 边表头指针，用来存所有与该顶点相连的顶点 */
    EdgeNode *firstedge;
} VertexNode, AdjList[MAX_VEX];

typedef struct
{
    /* 邻接表 */
    AdjList adjList;
    /* 图中当前顶点数和边数 */
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

/* 创建一个邻接矩阵 */
void CreateMGraph(MGraph *MG)
{
    int i, j;

    MG->numEdges = 13;
    MG->numVertexes = 10;
    /* 初始化图 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        MG->vexs[i] = i;
    }
    /* 初始化图 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = 0; j < MG->numVertexes; j++)
        {
            if (i == j)
                MG->arc[i][j] = 0;
            else
                MG->arc[i][j] = INFINITY;
        }
    }

    MG->arc[0][1] = 3;
    MG->arc[0][2] = 4;
    MG->arc[1][3] = 5;
    MG->arc[1][4] = 6;
    MG->arc[2][3] = 8;
    MG->arc[2][5] = 7;
    MG->arc[3][4] = 3;
    MG->arc[4][6] = 9;
    MG->arc[4][7] = 4;
    MG->arc[5][7] = 6;
    MG->arc[6][9] = 2;
    MG->arc[7][8] = 5;
    MG->arc[8][9] = 3;
}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph MG, GraphAdjList *ALG)
{
    int i, j;
    EdgeNode *e;

    *ALG = (GraphAdjList)malloc(sizeof(graphAdjList));
    (*ALG)->numVertexes = MG.numVertexes;
    (*ALG)->numEdges = MG.numEdges;
    // 读入顶点信息，建立顶点表
    for (i = 0; i < MG.numVertexes; i++)
    {
        (*ALG)->adjList[i].in = 0;
        (*ALG)->adjList[i].data = MG.vexs[i];
        // 将边表置为空
        (*ALG)->adjList[i].firstedge = NULL;
    }
    // 建立边表
    for (i = 0; i < MG.numVertexes; i++)
    {
        for (j = 0; j < MG.numVertexes; j++)
        {
            if ((MG.arc[i][j]!=0) && (MG.arc[i][j]<INFINITY))
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                // 与i点邻接的点序号为j
                e->adjvex = j;
                // 头插法
                e->weight = MG.arc[i][j];
                // 将当前顶点上的指向的结点指针赋值给e
                e->next = (*ALG)->adjList[i].firstedge;
                // 将当前顶点的指针指向e
                (*ALG)->adjList[i].firstedge = e;
                (*ALG)->adjList[j].in++;
            }
        }
    }
}

/* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0 */
Status TopologicalSort(GraphAdjList ALG)
{
    EdgeNode *e;
    int i, k, gettop;
    // 用于栈指针下标
    int top = 0;
    // 用于统计输出顶点的个数
    int count = 0;
    // 建栈将入度为0的顶点入栈
    int *stack;
    stack = (int *)malloc(ALG->numVertexes * sizeof(int));
    for (i = 0; i < ALG->numVertexes; i++)
    {
        if (0 == ALG->adjList[i].in)
        {
            stack[++top] = i;
        }
    }
    top2 = 0;
    // 事件最早发生事件数组
    etv = (int *)malloc(ALG->numVertexes * sizeof(int));
    for (i = 0; i < ALG->numVertexes; i++)
    {
        // 初始化
        etv[i] = 0;
    }
    // 初始化拓扑序列栈
    stack2 = (int *)malloc(ALG->numVertexes * sizeof(int));

    printf("TopologicalSort:\n");
    while (top != 0)
    {
        gettop = stack[top--];
        printf("%d -> ", ALG->adjList[gettop].data);
        // 输出i号顶点并计数
        count++;

        // 将弹出的顶点序号压入拓扑序列的栈
        stack2[++top2] = gettop;
        for (e = ALG->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            // 将i号顶点的邻接点的入度减1，如果减1后为0，则入栈
            if (!(--ALG->adjList[k].in))
            {
                stack[++top] = k;
            }
            // 求各顶点事件的最早发生时间etv值
            if ((etv[gettop] + e->weight) > etv[k])
            {
                etv[k] = etv[gettop] + e->weight;
            }
        }
    }
    printf("\n");
    if (count < ALG->numVertexes)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}

/* 求关键路径，ALG为邮箱网，输出ALG的各项关键活动 */
void CriticalPath(GraphAdjList ALG)
{
    EdgeNode *e;
    int i, gettop, k, j;
    // 声明活动最早发生时间和最迟发生时间变量
    int ete, lte;
    // 求拓扑序列，计算数组etv和stack2的值
    TopologicalSort(ALG);
    // 事件最早发生时间数组
    ltv = (int *)malloc(ALG->numVertexes * sizeof(int));
    for (i = 0; i < ALG->numVertexes; i++)
    {
        // 初始化
        ltv[i] = etv[ALG->numVertexes - 1];
    }
    printf("etv:\t");
    for (i = 0; i < ALG->numVertexes; i++)
    {
        printf("%d -> ", etv[i]);
    }
    printf("\n");

    // 出栈是求ltv
    while (top2 != 0)
    {
        gettop = stack2[top2--];
        for (e = ALG->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            if ((ltv[k] - e->weight) < ltv[gettop])
            {
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }
    printf("ltv:\t");
    for (i = 0; i < ALG->numVertexes; i++)
    {
        printf("%d -> ", ltv[i]);
    }
    printf("\n");

    // 求ete，lte和关键活动
    for (j = 0; j < ALG->numVertexes; j++)
    {
        for (e = ALG->adjList[j].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            // 活动最早发生时间
            ete = etv[j];
            // 活动最迟发生时间
            lte = ltv[k] - e->weight;
            if (ete == lte)
            {
                printf("<v%d - v%d> length: %d\n", ALG->adjList[j].data, ALG->adjList[k].data, e->weight);
            }
        }
    }
}

int main(void)
{
    MGraph G;
    GraphAdjList GL;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);
    CriticalPath(GL);

    return 0;
}