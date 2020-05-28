/* 最短路径的Dijkstra算法实现 */
#include "../common.h"
#include <stdio.h>

/* 存储空间初始分配量 */
#define MAX_EDGE 20
#define MAX_VEX 20
#define INFINITY 65535

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

typedef struct
{
    /* 顶点表 */
    VertexType vexs[MAX_VEX];
    /* 邻接矩阵，可看作边表 */
    EdgeType arc[MAX_VEX][MAX_VEX];
    /* 图中当前的顶点数和边数 */
    int numVertexes, numEdges;
} MGraph;

/* 用于存储最短路径下标的数组 */
typedef int Patharc[MAX_VEX];
/* 用于存储到各点最短路径的权值和 */
typedef int ShortPathTable[MAX_VEX];

/* 构建图 */
void CreateMGraph(MGraph *MG)
{
    int i, j;

    /* printf("请输入边数和顶点数:"); */
    MG->numEdges = 16;
    MG->numVertexes = 9;
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
                MG->arc[i][j] = MG->arc[j][i] = INFINITY;
        }
    }

    MG->arc[0][1] = 1;
    MG->arc[0][2] = 5;
    MG->arc[1][2] = 3;
    MG->arc[1][3] = 7;
    MG->arc[1][4] = 5;

    MG->arc[2][4] = 1;
    MG->arc[2][5] = 7;
    MG->arc[3][4] = 2;
    MG->arc[3][6] = 3;
    MG->arc[4][5] = 3;

    MG->arc[4][6] = 6;
    MG->arc[4][7] = 9;
    MG->arc[5][7] = 5;
    MG->arc[6][7] = 2;
    MG->arc[6][8] = 7;

    MG->arc[7][8] = 4;

    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = i; j < MG->numVertexes; j++)
        {
            MG->arc[j][i] = MG->arc[i][j];
        }
    }
}

/* Dijkstra算法，求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */
/* P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */
void ShortestPath_Dijkstra(MGraph MG, int v0, Patharc *P, ShortPathTable *D)
{
    int v, w, k, min;
    // final[w]=1表示求得顶点v0至vw的最短路径
    int final[MAX_VEX];
    // 初始化数据
    for (v = 0; v < MG.numVertexes; v++)
    {
        // 全部顶点初始化为未知最短路径状态
        final[v] = 0;
        // 将与v0点有连线的顶点加上权值
        (*D)[v] = MG.arc[v0][v];
        // 初始化路径数组P为-1
        (*P)[v] = -1;
    }
    // v0至v0的路径为0
    (*D)[v0] = 0;
    // v0至v0不需要求路径
    final[v0] = 1;
    // 开始主循环，每次求得v0到某个v顶点的最短路径
    for (v = 1; v < MG.numVertexes; v++)
    {
        // 当前所知离v0顶点的最近距离
        min = INFINITY;
        // 寻找离v0最近的顶点
        for (w = 0; w < MG.numVertexes; w++)
        {
            if (!final[w] && ((*D)[w] < min))
            {
                k = w;
                // w顶点离v0顶点更近
                min = (*D)[w];
            }
        }
        // 将目前找到的最近的顶点置为1
        final[k] = 1;
        // 修正当前最短路径及距离
        for (w = 0; w < MG.numVertexes; w++)
        {
            // 如果经过v顶点的路径比现在这条路径的长度短的话
            if (!final[w] && (min + MG.arc[k][w] < (*D)[w]))
            {
                // 说明找到了更短的路径，就修改D[w]和P[w]
                (*D)[w] = min + MG.arc[k][w];
                (*P)[w] = k;
            }
        }
    }
}

int main(void)
{
    int i, j, v0;
    MGraph MG;
    Patharc P;
    // 求某点到其余各点的最短路径
    ShortPathTable D;
    v0 = 0;

    CreateMGraph(&MG);
    ShortestPath_Dijkstra(MG, v0, &P, &D);

    printf("最短路径倒序如下：\n");
    for (i = 1; i < MG.numVertexes; i++)
    {
        printf("v%d - v%d : ", v0, i);
        j = i;
        while (P[j] != -1)
        {
            printf("%d ", P[j]);
            j = P[j];
        }
        printf("\n");
    }
    printf("\n源点到各顶点的最短路径长度为：\n");
    for (i = 1; i < MG.numVertexes; i++)
    {
        printf("v%d - v%d : %d \n", MG.vexs[0], MG.vexs[i], D[i]);
    }

    return 0;
}