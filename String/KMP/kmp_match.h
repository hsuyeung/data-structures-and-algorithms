/* KMP模式匹配算法及其改良版定义文件 */
#include "../../common.h"
#include "../MyString/myString.h"
#ifndef KMP_MATCH
#define KMP_MATCH

/* KMP算法具有的操作声明 start */

/* 输出Next数组值 */
void NextPrint(int next[], int length);

/* 通过计算返回子串T的next数组 */
void get_next(String T, int *next);

/* KMP算法，返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0 */
/* T非空，1≤pos≤StrLength(S) */
int Index_KMP(String S, String T, int pos);

/* 求模式串T的next函数修正值并存入数组nextval */
void get_nextval(String T, int *nextval);

/* 改良版KMP算法 */
int Index_KMP_improve(String S, String T, int pos);

/* KMP算法具有的操作声明 end */

#endif