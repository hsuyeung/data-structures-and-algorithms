/*循环队列的顺序结构定义文件*/
#include "../../common.h"
#ifndef SQ_QUEUE
#define SQ_QUEUE

/*最大容量定义 start*/
#define MAX_SIZE 20
/*最大容量定义 end*/

/*循环队列的顺序结构定义 start*/

typedef struct
{
    QElemType data[MAX_SIZE];
    //头指针
    int front;
    //尾指针，若队列不空，指向队列尾元素的下一个位置
    int rear;
} SqQueue;

/*循环队列的顺序结构定义 end*/

/*循环队列的顺序结构具有的操作声明 start*/

/*初始化一个空队列Q*/
int InitQueue(SqQueue *Q);

/*将Q清为空队列*/
int ClearQueue(SqQueue *Q);

/*若队列Q为空队列,则返回TRUE,否则返回FALSE*/
int QueueEmpty(SqQueue Q);

/*返回Q的元素个数，也就是队列的当前长度*/
int QueueLength(SqQueue Q);

/*若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR*/
int GetHead(SqQueue Q, QElemType *e);

/*若队列未满，则插入元素e为Q新的队尾元素*/
int EnQueue(SqQueue *Q, QElemType e);

/*若队列不空，则删除Q中队头元素，用e返回其值*/
int DeQueue(SqQueue *Q, QElemType *e);

/*从队头到队尾依次对队列Q中每个元素输出*/
int QueueTraverse(SqQueue Q);

/*循环队列的顺序结构具有的操作声明 end*/

#endif