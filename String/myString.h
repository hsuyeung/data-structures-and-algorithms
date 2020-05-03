/*字符串的定义文件*/
#include "../common.h"
#ifndef STRING
#define STRING

/*最大容量定义 start*/
#define MAX_SIZE 40
/*最大容量定义 end*/

/*字符串的顺序结构定义 start*/

//char[0]用来存放串的实际长度
typedef char String[MAX_SIZE];

/*字符串的顺序结构定义 end*/

/*字符串的顺序结构具有的操作声明 start*/

/*生成一个其值等于chars的串T*/
int StrAssign(String T, char *chars);

/*由串S复制得串T*/
int StrCopy(String T, String S);

/*若S为空串,则返回TRUE,否则返回FALSE*/
int StrEmpty(String S);

/*初始条件: 串S和T存在*/
/*操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0*/
int StrCompare(String S, String T);

/*返回串的元素个数*/
int StrLength(String S);

/*初始条件:串S存在。操作结果:将S清为空串*/
int ClearString(String S);

/*用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE*/
int Concat(String T, String S1, String S2);

/*用Sub返回串S的第pos个字符起长度为len的子串。*/
int SubString(String Sub, String S, int pos, int len);

/*返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。*/
/*其中,T非空,1≤pos≤StrLength(S)。*/
int Index(String S, String T, int pos);

/*T为非空串。若主串S中第pos个字符之后存在与T相等的子串，*/
/*则返回第一个这样的子串在S中的位置，否则返回0*/
int Index2(String S, String T, int pos);

/*初始条件: 串S和T存在,1≤pos≤StrLength(S)+1*/
/*操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE*/
int StrInsert(String S, int pos, String T);

/*初始条件: 串S存在,1≤pos≤StrLength(S)-len+1*/
/*操作结果: 从串S中删除第pos个字符起长度为len的子串*/
int StrDelete(String S, int pos, int len);

/*初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关）*/
/*操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串*/
int Replace(String S, String T, String V);

/*输出字符串T*/
void StrPrint(String T);

/*字符串的顺序结构具有的操作声明 end*/

#endif
