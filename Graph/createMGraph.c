/* 创建无向图的邻接邻接矩阵存储结构 */
#include "../common.h"
#include <stdio.h>

/* 最大顶点数，应由用户定义 */
#define MAX_VEX 100
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
    int numNodes, numEdges;
} MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *MG)
{
    int i, j, k, w;
    printf("输入顶点数和边数：\n");
    // 输入顶点数和边数
    scanf("%d %d", &MG->numNodes, &MG->numEdges);
    fflush(stdin);
    printf("输入顶点信息：\n");
    // 读入顶点信息,建立顶点表
    for (i = 0; i < MG->numNodes; i++)
    {
        scanf("%c", &MG->vexs[i]);
    }
    fflush(stdin);
    // 建立邻接矩阵
    for (i = 0; i < MG->numNodes; i++)
    {
        for (j = 0; j < MG->numNodes; j++)
        {
            // 邻接矩阵初始化
            MG->arc[i][j] = (i == j ? 0: INFINITY);
        }
    }
    // 读入numEdges条边，给邻接矩阵赋值
    for (k = 0; k < MG->numEdges; k++)
    {
        printf("输入边(vi, vj)上的下标i，下标j和权w：\n");
        scanf("%d %d %d", &i, &j, &w);
        MG->arc[i][j] = w;
        // 因为时无向图，矩阵延主对角线对称
        MG->arc[j][i] = MG->arc[i][j];
    }
}

int main(void)
{
    int i, j;
    MGraph MG;

    CreateMGraph(&MG);
    printf("无向网图的顶点表数据：vex = ");
    for (i = 0; i < MG.numNodes; i++)
    {
        printf("%c ", MG.vexs[i]);
    }
    printf("\n无向网图的边表数据：arc[%d][%d] = \n", MG.numEdges, MG.numEdges);
    for (i = 0; i < MG.numNodes; i++)
    {
        for (j = 0; j < MG.numNodes; j++)
        {
            printf("%-d\t", MG.arc[i][j]);
        }
        printf("\n");
    }

    return 0;
}
