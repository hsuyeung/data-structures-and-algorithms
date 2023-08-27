/* 一些公共常量的定义 */
#ifndef COMMON
#define COMMON

/* 状态常量定义 start */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
/* 状态常量定义 end */

/* 数据元素类型定义 start */

// 顺序表结点的数据类型，目前暂定为整型
typedef int ElemType;
// 栈结点的数据类型，目前暂定为整型
typedef int SElemType;
// 队列结点的数据类型，目前暂定为整型
typedef int QElemType;
// 顺序存储树结点的数据类型，目前暂定为整型
typedef int TElemType;
// 链式存储树结点的数据类型，目前暂定为字符型
typedef char TLElemType;
// 图的顶点类型应由用户定义
typedef char VertexType;
// 图的边上的权值类型应由用户定义
typedef int EdgeType;

/* 数据元素类型定义 end */

#endif