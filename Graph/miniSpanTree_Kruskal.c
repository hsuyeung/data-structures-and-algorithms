/* Kruskal算法生成最小生成树代码实现 */
#include "../common.h"
#include <stdio.h>

#define MAX_EDGE 20
#define MAX_VEX 20
#define INFINITY 65535

typedef int Status;

typedef struct
{
    int arc[MAX_VEX][MAX_VEX];
    int numVertexes, numEdges;
} MGraph;

/* 对边集数组Edge结构的定义 */
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;

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

/* 交换权值以及头和尾 */
void Swapn(Edge *edges, int i, int j)
{
    int temp;
    temp = edges[i].begin;
    edges[i].begin = edges[j].begin;
    edges[j].begin = temp;

    temp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = temp;

    temp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = temp;
}

/* 对权值进行排序 */
void sort(Edge edges[], MGraph *MG)
{
    int i, j;
    for (i = 0; i < MG->numEdges - 1; i++)
    {
        for (j = i + 1; j < MG->numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                Swapn(edges, i, j);
            }
        }
    }
    printf("权排序之后的为：\n");
    for (i = 0; i < MG->numEdges; i++)
    {
        printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
    }
}

/* 查找连线顶点的尾部下标 */
int Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

/* Kuskal算法生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph MG)
{
    int i, j, n, m;
    int k = 0;
    // 定义一数组用来判断边与边是否形成环路
    int parent[MAX_VEX];
    // 定义边集数组,edge的结构为begin,end,weight,均为整型
    Edge edges[MAX_EDGE];
    // 用来构建边集数组并排序
    for (i = 0; i < MG.numVertexes - 1; i++)
    {
        for (j = i + 1; j < MG.numVertexes; j++)
        {
            if (MG.arc[i][j] < INFINITY)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = MG.arc[i][j];
                k++;
            }
        }
    }
    sort(edges, &MG);

    for (i = 0; i < MG.numVertexes; i++)
    {
        // 初始化数组为0
        parent[i] = 0;
    }

    printf("打印最小生成树：\n");
    // 循环每一条边
    for (i = 0; i < MG.numEdges; i++)
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        // printf("当前的n = %d, m = %d\n", n, m);
        // 假如n与m不等，说明此边没有与现有的生成树形成环路
        if (n != m)
        {
            // 将此边的结尾顶点放入下标为起点的parent中。表示此顶点已经在生成树集合中
            parent[n] = m;
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
    
}

int main(void)
{
    MGraph MG;

    CreateMGraph(&MG);
    MiniSpanTree_Kruskal(MG);

    return 0;
}