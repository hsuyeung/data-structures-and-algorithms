/* 邻接表的深度和广度优先遍历算法实现 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAX_SIZE 9
#define MAX_EDGE 15
#define MAX_VEX 9
#define INFINITY 65535

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;
/* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int Boolean;

/* 邻接矩阵结构 */
typedef struct
{
    /* 顶点表 */
    VertexType vexs[MAX_VEX];
    /* 邻接矩阵，可看作边表 */
    EdgeType arc[MAX_VEX][MAX_VEX];
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
    EdgeType weight;
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

typedef struct
{
    /* 邻接表 */
    AdjList adjList;
    /* 图中当前顶点数和边数 */
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

/* 用到的队列结构与函数 */
/* 循环队列的顺序存储结构 */
typedef struct
{
    int data[MAX_SIZE];
    /* 头指针 */
    int front;
    /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
    int rear;
} Queue;

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
    return (Q.front == Q.rear) ? TRUE : FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
int EnQueue(Queue *Q, QElemType e)
{
    // 队列满的判断
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        printf("队列满了。\n");
        return ERROR;
    }
    // 将元素e赋值给队尾
    Q->data[Q->rear] = e;
    // rear指针向后移一位，若到最后则转到数组头部
    Q->rear = (Q->rear + 1) % MAX_SIZE;
    return OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
int DeQueue(Queue *Q, QElemType *e)
{
    // 队列空的判断
    if (Q->front == Q->rear)
    {
        printf("队列为空。\n");
        return ERROR;
    }
    // 将队头元素赋值给e
    *e = Q->data[Q->front];
    // front指针向后移一位置，若到最后则转到数组头部
    Q->front = (Q->front + 1) % MAX_SIZE;
    return OK;
}

/* 创建一个邻接矩阵 */
void CreateMGraph(MGraph *MG)
{
    int i, j;

    MG->numEdges = 15;
    MG->numVertexes = 9;

    /* 读入顶点信息,建立顶点表 */
    MG->vexs[0] = 'A';
    MG->vexs[1] = 'B';
    MG->vexs[2] = 'C';
    MG->vexs[3] = 'D';
    MG->vexs[4] = 'E';
    MG->vexs[5] = 'F';
    MG->vexs[6] = 'G';
    MG->vexs[7] = 'H';
    MG->vexs[8] = 'I';

    for (i = 0; i < MG->numVertexes; i++) /* 初始化图 */
    {
        for (j = 0; j < MG->numVertexes; j++)
        {
            MG->arc[i][j] = 0;
        }
    }

    MG->arc[0][1] = 1;
    MG->arc[0][5] = 1;

    MG->arc[1][2] = 1;
    MG->arc[1][8] = 1;
    MG->arc[1][6] = 1;

    MG->arc[2][3] = 1;
    MG->arc[2][8] = 1;

    MG->arc[3][4] = 1;
    MG->arc[3][7] = 1;
    MG->arc[3][6] = 1;
    MG->arc[3][8] = 1;

    MG->arc[4][5] = 1;
    MG->arc[4][7] = 1;

    MG->arc[5][6] = 1;

    MG->arc[6][7] = 1;

    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = i; j < MG->numVertexes; j++)
        {
            MG->arc[j][i] = MG->arc[i][j];
        }
    }
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
            }
        }
    }
}

/* 访问标志的数组 */
Boolean visited[MAX_SIZE];

/* 邻接表的深度优先递归算法 */
void DFS(GraphAdjList ALG, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c ", ALG->adjList[i].data);
    p = ALG->adjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            // 对未访问的邻接顶点递归调用
            DFS(ALG, p->adjvex);
        }
        p = p->next;
    }
}

/* 邻接表的深度遍历操作 */
void DFSTraverse(GraphAdjList ALG)
{
    int i;
    for (i = 0; i < ALG->numVertexes; i++)
    {
        // 初始所有顶点状态都是未访问过状态
        visited[i] = FALSE;
    }
    for (i = 0; i < ALG->numVertexes; i++)
    {
        // 对未访问过的顶点调用DFS,若是连通图,只会执行一次
        if (!visited[i])
        {
            DFS(ALG, i);
        }
    }
}

/* 邻接表的广度遍历算法 */
void BFSTraverse(GraphAdjList ALG)
{
    int i;
    EdgeNode *p;
    Queue Q;

    for (i = 0; i < ALG->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    InitQueue(&Q);
    for (i = 0; i < ALG->numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", ALG->adjList[i].data);
            EnQueue(&Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);
                // 找到当前顶点的边表
                p = ALG->adjList[i].firstedge;
                while (p)
                {
                    // 若此顶点未被访问
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", ALG->adjList[p->adjvex].data);
                        EnQueue(&Q, p->adjvex);
                    }
                    // 指针指向下一个邻接点
                    p = p->next;
                }
            }
        }
    }
}

int main(void)
{
    MGraph MG;
    GraphAdjList ALG;

    CreateMGraph(&MG);
    CreateALGraph(MG, &ALG);

    printf("\n深度遍历：");
    DFSTraverse(ALG);
    printf("\n广度遍历：");
    BFSTraverse(ALG);

    return 0;
}