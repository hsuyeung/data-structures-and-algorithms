/* 最短路径的Floyd算法实现 */
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
    int vexs[MAX_VEX];
    /* 邻接矩阵，可看作边表 */
    int arc[MAX_VEX][MAX_VEX];
    /* 图中当前的顶点数和边数 */
    int numVertexes, numEdges;
} MGraph;

/* 用于存储最短路径下标的数组 */
typedef int Patharc[MAX_VEX][MAX_VEX];
/* 用于存储到各点最短路径的权值和 */
typedef int ShortPathTable[MAX_VEX][MAX_VEX];

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

/* Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]以及带权长度D[v] */
void ShortestPath_Floyd(MGraph MG, Patharc *P, ShortPathTable *D)
{
    int v, w, k;
    // 初始化P与D
    for (v = 0; v < MG.numVertexes; v++)
    {
        for (w = 0; w < MG.numVertexes; w++)
        {
            // D[v][w]值即为对应点间的权值
            (*D)[v][w] = MG.arc[v][w];
            // 初始化P
            (*P)[v][w] = w;
        }
    }
    for (k = 0; k < MG.numVertexes; k++)
    {
        for (v = 0; v < MG.numVertexes; v++)
        {
            for (w = 0; w < MG.numVertexes; w++)
            {
                // 如果经过下标为k的顶点路径比原两点间路径更短
                if ((*D)[v][w] > ((*D)[v][k] + (*D)[k][w]))
                {
                    // 将当前两点间权值设为更小的一个
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    // 路径设置为经过下标为k的顶点
                    (*P)[v][w] = (*P)[v][k];
                }
            }
        }
    }
}

int main(void)
{
    int v, w, k;
    MGraph MG;
    Patharc P;
    // 求某点到其余各点的最短路径
    ShortPathTable D;

    CreateMGraph(&MG);
    ShortestPath_Floyd(MG, &P, &D);

    printf("各顶点间最短路径如下：\n");
    for (v = 0; v < MG.numVertexes; v++)
    {
        for (w = v + 1; w < MG.numVertexes; w++)
        {
            printf("v%d-v%d weight: %d ", v, w, D[v][w]);
            // 获得第一个路径顶点的下标
            k = P[v][w];
            // 打印源点
            printf(" path: %d", v);
            while (k != w)
            {
                // 打印路径顶点
                printf(" -> %d", k);
                // 获得下一个路径顶点下标
                k = P[k][w];
            }
            printf(" -> %d\n", w);
        }
    }

    printf("最短路径D\n");
    for (v = 0; v < MG.numVertexes; v++)
    {
        for (w = 0; w < MG.numVertexes; w++)
        {
            printf("%-d\t", D[v][w]);
        }
        printf("\n");
    }
    printf("最短路径P\n");
    for (v = 0; v < MG.numVertexes; v++)
    {
        for (w = 0; w < MG.numVertexes; w++)
        {
            printf("%-d\t", P[v][w]);
        }
        printf("\n");
    }

    return 0;
}