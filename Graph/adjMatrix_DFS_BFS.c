/* 邻接矩阵的深度和广度优先遍历算法实现 */
#include "../common.h"
#include <stdio.h>

/* 存储空间初始分配量 */
#define MAX_SIZE 9
#define MAX_EDGE 15
#define MAX_VEX 9
#define INFINITY 65535

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;
/* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int Boolean;

typedef struct
{
    /* 顶点表 */
    VertexType vexs[MAX_VEX];
    /* 邻接矩阵，可看作边表 */
    EdgeType arc[MAX_VEX][MAX_VEX];
    /* 图中当前的顶点数和边数 */
    int numVertexes, numEdges;
} MGraph;

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

/* 创建一个无向图的邻接矩阵，这里为了方便直接给定数据，不让用户输入了 */
void CreateMGraph(MGraph *MG)
{
    int i, j;

    MG->numEdges = 15;
    MG->numVertexes = 9;

    /* 读入顶点信息，建立顶点表 */
    MG->vexs[0] = 'A';
    MG->vexs[1] = 'B';
    MG->vexs[2] = 'C';
    MG->vexs[3] = 'D';
    MG->vexs[4] = 'E';
    MG->vexs[5] = 'F';
    MG->vexs[6] = 'G';
    MG->vexs[7] = 'H';
    MG->vexs[8] = 'I';
    /* 初始化图 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = 0; j < MG->numVertexes; j++)
        {
            MG->arc[i][j] = 0;
        }
    }
    /* 给顶点表赋值 */
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
    /* 无向图的邻接矩阵是沿主对角线对称的 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = i; j < MG->numVertexes; j++)
        {
            MG->arc[j][i] = MG->arc[i][j];
        }
    }
}

/* 用来记录当前顶点是否访问过的数组 */
Boolean visited[MAX_VEX];

/* 邻接矩阵的深度优先递归算法(DFS) */
void DFS(MGraph MG, int i)
{
    int j;
    visited[i] = TRUE;
    //打印顶点，也可以是其他操作
    printf("%c ", MG.vexs[i]);
    for (j = 0; j < MG.numVertexes; j++)
    {
        if ((MG.arc[i][j] == 1) && !visited[j])
        {
            // 对未访问的邻接顶点递归调用
            DFS(MG, j);
        }
    }
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph MG)
{
    int i;
    for (i = 0; i < MG.numVertexes; i++)
    {
        // 初始所有顶点都是未访问过的状态
        visited[i] = FALSE;
    }
    for (i = 0; i < MG.numVertexes; i++)
    {
        // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
        if (!visited[i])
        {
            DFS(MG, i);
        }
    }
}

/* 邻接矩阵的广度遍历算法(BFS) */
void BFSTraverse(MGraph MG)
{
    int i, j;
    Queue Q;

    for (i = 0; i < MG.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    /* 初始化一辅助用的队列 */
    InitQueue(&Q);
    // 对每一个顶点做循环
    for (i = 0; i < MG.numVertexes; i++)
    {
        // 若是未访问过就做处理
        if (!visited[i])
        {
            // 设置当前顶点访问过
            visited[i] = TRUE;
            // 打印顶点，也可以是其他操作
            printf("%c ", MG.vexs[i]);
            // 将此顶点下标入队列
            EnQueue(&Q, i);
            // 若当前队列不为空
            while (!QueueEmpty(Q))
            {
                // 将队列元素出队列，赋值给i
                DeQueue(&Q, &i);
                for (j = 0; j < MG.numVertexes; j++)
                {
                    // 判断其它顶点，若与当前顶点存在边并且未访问过
                    if ((MG.arc[i][j] == 1) && !visited[j])
                    {
                        // 将找到的此顶点标记已访问
                        visited[j] = TRUE;
                        printf("%c ", MG.vexs[j]);
                        // 将找到的此顶点入队列
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}

int main(void)
{
    MGraph MG;

    CreateMGraph(&MG);
    printf("\n深度遍历：");
    DFSTraverse(MG);
    printf("\n广度遍历：");
    BFSTraverse(MG);

    return 0;
}