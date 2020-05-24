/* 建立图的邻接表存储结构 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

 /* 最大顶点数,应由用户定义 */
#define MAX_VEX 100

/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef int Status;

/* 边表结点 */
typedef struct EdgeNode
{
    /* 邻接点域，存储该顶点对应的下标 */
    int adjvex;
    /* 用于存储权值，对于非网图可以不需要 */
    EdgeType info;
    /* 链域，指向下一个邻接点 */
    struct EdgeNode *next;
} EdgeNode;

/* 顶点表结点 */
typedef struct VertexNode
{
    /* 顶点域，存储顶点信息 */
    VertexType data;
    /* 边表头指针，用来存所有与该顶点相连的顶点 */
    EdgeNode *firstedge;
} VertexNode, AdjList[MAX_VEX];

/* 邻接表结构 */
typedef struct
{
    /* 邻接表 */
    AdjList adjList;
    /* 图中当前顶点数和边数 */
    int numNodes, numEdges;
} GraphAdjList;

/* 建立图的邻接表结构 */
void CreateALGraph(GraphAdjList *ALG)
{
    int i, j, k;
    EdgeNode *e;

    printf("输入顶点数和边数：\n");
    // 输入顶点数和边数
    scanf("%d %d", &ALG->numNodes, &ALG->numEdges);
    fflush(stdin);
    printf("输入顶点信息：\n");
    // 读入顶点信息,建立顶点表
    for (i = 0; i < ALG->numNodes; i++)
    {
        // 输入顶点信息
        scanf("%c", &ALG->adjList[i].data);
        // 将边表初始化为空表
        ALG->adjList[i].firstedge = NULL;
    }
    fflush(stdin);
    // 建立边表
    for (k = 0; k < ALG->numEdges; k++)
    {
        printf("输入边(vi, vj)上的顶点序号：\n");
        // 输入边(vi,vj)上的顶点序号
        scanf("%d %d", &i, &j);
        // 向内存申请空间，生成边表结点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        // 邻接点的序号为j
        e->adjvex = j;
        // 头插法
        // 将e的指针指向当前顶点上指向的结点
        e->next = ALG->adjList[i].firstedge;
        // 将当前顶点的指针指向e
        ALG->adjList[i].firstedge = e;

        // 无向图的邻接表结构中一条边都是对应两个点，所以i和j同时插入了
        // 向内存申请空间，生成边表结点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        // 邻接点的序号为i
        e->adjvex = i;
        // 头插
        // 将e的指针指向当前顶点上指向的结点
        e->next = ALG->adjList[j].firstedge;
        // 将当前顶点的指针指向e
        ALG->adjList[j].firstedge = e;
    }
}

int main(void)
{
    int i;
    EdgeNode *e;
    GraphAdjList ALG;

    CreateALGraph(&ALG);

    printf("无向网图的顶点数据：vex = ");
    for (i = 0; i < ALG.numNodes; i++)
    {
        printf("%c ", ALG.adjList[i].data);
    }
    printf("\n无向网图每个顶点的的边表数据：\n");
    for (i = 0; i < ALG.numNodes; i++)
    {
        printf("%c：", ALG.adjList[i].data);
        for (e = ALG.adjList[i].firstedge; e; e = e->next)
        {
            printf("%-d -> ", e->adjvex);
        }
        printf("NULL\n");
    }

    return 0;
}