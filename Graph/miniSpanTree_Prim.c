/* Prim算法生成最小生成树代码实现 */
#include "../common.h"
#include <stdio.h>

#define MAX_EDGE 20
#define MAX_VEX 20
#define INFINITY 65535

typedef int Status;

typedef struct
{
    /* 邻接矩阵，可看作边表 */
    EdgeType arc[MAX_VEX][MAX_VEX];
    /* 图中当前的顶点数和边数 */
    int numVertexes, numEdges;
} MGraph;

/* 创建一个无向图的邻接矩阵，这里为了方便直接给定数据，不让用户输入了 */
void CreateMGraph(MGraph *MG)
{
    int i, j;

    MG->numEdges = 15;
    MG->numVertexes = 9;

    /* 初始化图 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = 0; j < MG->numVertexes; j++)
        {
            if (i == j)
            {
                MG->arc[i][j] = 0;
            }
            else
            {
                MG->arc[i][j] = MG->arc[j][i] = INFINITY;
            }
        }
    }

    MG->arc[0][1] = 10;
    MG->arc[0][5] = 11;
    MG->arc[1][2] = 18;
    MG->arc[1][8] = 12;
    MG->arc[1][6] = 16;
    MG->arc[2][8] = 8;
    MG->arc[2][3] = 22;
    MG->arc[3][8] = 21;
    MG->arc[3][6] = 24;
    MG->arc[3][7] = 16;
    MG->arc[3][4] = 20;
    MG->arc[4][7] = 7;
    MG->arc[4][5] = 26;
    MG->arc[5][6] = 17;
    MG->arc[6][7] = 19;

    /* 无向图的邻接矩阵是沿主对角线对称的 */
    for (i = 0; i < MG->numVertexes; i++)
    {
        for (j = i; j < MG->numVertexes; j++)
        {
            MG->arc[j][i] = MG->arc[i][j];
        }
    }
}

/* Prim算法生成最小生成树 */
void MiniSpanTree_Prim(MGraph MG)
{
    int min, i, j, k;
    // 保存相关顶点下标
    int adjvex[MAX_VEX];
    // 保存相关顶点间边的权值
    int lowcost[MAX_VEX];
    // lowcost的值为0，在这里就是此下标的顶点已经加入生成树
    // 初始化第一个顶点的下标为0
    adjvex[0] = 0;
    // 循环除下标为0外的所有顶点
    for (i = 1; i < MG.numVertexes; i++)
    {
        // 将v0顶点与之有边的权值存入数组
        lowcost[i] = MG.arc[0][i];
        // 初始化都为v0的下标
        adjvex[i] = 0;
    }
    for (i = 1; i < MG.numVertexes; i++)
    {
        // 初始化最小权值为∞，通常设置为不可能的大数字如32767、65535等
        min = INFINITY;
        j = 1;
        k = 0;
        // 循环全部顶点
        while (j < MG.numVertexes)
        {
            // 如果权值不为0且权值小于min
            if ((lowcost[j] != 0) && (lowcost[j] < min))
            {
                // 则让当前权值成为最小值
                min = lowcost[j];
                // 将当前最小值的下标存入k
                k = j;
            }
            j++;
        }
        // 打印当前顶点边中权值最小的边
        printf("(%d, %d)\n", adjvex[k], k);
        // 将当前顶点的权值设置为0,表示此顶点已经完成任务
        lowcost[k] = 0;
        // 循环所有顶点
        for (j = 1; j < MG.numVertexes; j++)
        {
            // 如果下标为k的顶点各边权值小于此前这些顶点未被加入生成树权值
            if ((lowcost[j] != 0) && (MG.arc[k][j] < lowcost[j]))
            {
                // 将较小的权值存入lowcost相应位置
                lowcost[j] = MG.arc[k][j];
                // 将下标为k的顶点存入adjvex
                adjvex[j] = k;
            }
        }
    }
}

int main(void)
{
    MGraph MG;

    CreateMGraph(&MG);
    MiniSpanTree_Prim(MG);

    return 0;
}