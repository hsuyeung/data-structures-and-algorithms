/* 拓扑排序算法 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAX_EDGE 20
#define MAX_VEX 14
#define INFINITY 65535

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/* 邻接矩阵结构 */
typedef struct
{
    /* 顶点表 */
    int vexs[MAX_VEX];
    /* 邻接矩阵，可看作边表 */
    int arc[MAX_VEX][MAX_VEX];
    /* 图中当前的顶点数和边数 */
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

    MG->numEdges = MAX_EDGE;
    MG->numVertexes = MAX_VEX;
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
            MG->arc[i][j] = 0;
        }
    }

    MG->arc[0][4] = 1;
    MG->arc[0][5] = 1;
    MG->arc[0][11] = 1;
    MG->arc[1][2] = 1;
    MG->arc[1][4] = 1;
    MG->arc[1][8] = 1;
    MG->arc[2][5] = 1;
    MG->arc[2][6] = 1;
    MG->arc[2][9] = 1;
    MG->arc[3][2] = 1;
    MG->arc[3][13] = 1;
    MG->arc[4][7] = 1;
    MG->arc[5][8] = 1;
    MG->arc[5][12] = 1;
    MG->arc[6][5] = 1;
    MG->arc[8][7] = 1;
    MG->arc[9][10] = 1;
    MG->arc[9][11] = 1;
    MG->arc[10][13] = 1;
    MG->arc[12][9] = 1;
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
            if (MG.arc[i][j] == 1)
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                // 与i点邻接的点序号为j
                e->adjvex = j;
                // 头插法
                // 将当前顶点上的指向的结点指针赋值给e
                e->next = (*ALG)->adjList[i].firstedge;
                // 将当前顶点的指针指向e
                (*ALG)->adjList[i].firstedge = e;
                (*ALG)->adjList[j].in++;
            }
        }
    }
}

/* 拓扑排序，若ALG无回路，则输出拓扑排序序列并返回1，若有回路则返回0 */
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
            // 将入度为0的顶点入栈
            stack[++top] = i;
        }
    }
    while (top != 0)
    {
        gettop = stack[top--];
        printf("%d -> ", ALG->adjList[gettop].data);
        // 输出i号顶点并计数
        count++;
        for (e = ALG->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            // 将i号顶点的邻接点的入度减1，如果减1后为0，则入栈
            if (!(--ALG->adjList[k].in))
            {
                stack[++top] = k;
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

int main(void)
{
    MGraph MG;
    GraphAdjList ALG;
    int result;

    CreateMGraph(&MG);
    CreateALGraph(MG, &ALG);
    result = TopologicalSort(ALG);
    printf("result: %d\n", result);

    return 0;
}