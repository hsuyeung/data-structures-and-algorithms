#include "kmp_match.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int *p;
    String s1, s2;

    StrAssign(s1, "abcdex");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));

    StrAssign(s1, "abcabx");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));

    StrAssign(s1, "ababaaaba");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));

    StrAssign(s1, "aaaaaaaab");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));

    StrAssign(s1, "ababaaaba");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));
    get_nextval(s1, p); 
	printf("串s1的nextval数组为：");
	NextPrint(p, StrLength(s1));

    StrAssign(s1, "aaaaaaaab");
    printf("子串s1为：");
    StrPrint(s1);
    p = (int *)malloc((StrLength(s1) + 1) * sizeof(int));
    get_next(s1, p);
    printf("串s1的next数组为：");
    NextPrint(p, StrLength(s1));
    get_nextval(s1, p); 
	printf("串s1的nextval数组为：");
	NextPrint(p, StrLength(s1));

    StrAssign(s1,"00000000000000000000000000000000000000000000000001");
	printf("主串为：");
	StrPrint(s1);
	StrAssign(s2, "0000000001");
	printf("子串为：");
	StrPrint(s2);
	printf("\n");
	printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n", Index(s1, s2, 1));
	printf("主串和子串在第%d个字符处首次匹配（KMP算法） \n", Index_KMP(s1, s2, 1));
	printf("主串和子串在第%d个字符处首次匹配（KMP改良算法） \n", Index_KMP_improve(s1, s2, 1));

    return 0;
}

/*KMP算法具有的操作定义 start*/

/*生成一个其值等于chars的串T*/
int StrAssign(String T, char *chars)
{
    int i;
    if (strlen(chars) >= MAX_SIZE)
    {
        printf("串长超过MAXSIZE(=%d)\n", MAX_SIZE - 1);
        return ERROR;
    }
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
        {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}

/*初始条件:串S存在。操作结果:将S清为空串*/
int ClearString(String S)
{
    S[0] = 0;
    return OK;
}

/*输出字符串T*/
void StrPrint(String T)
{
    int i;
    for (i = 1; i <= T[0]; i++)
    {
        printf("%c", T[i]);
    }
    printf("\n");
}

/*返回串的元素个数*/
int StrLength(String S)
{
    return S[0];
}

/*使用数组的方式完成暴力匹配,返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。*/
/*其中,T非空,1≤pos≤StrLength(S)。*/
int Index(String S, String T, int pos)
{
    //i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配
    int i = pos;
    //j用于子串T中当前位置下标值
    int j = 1;
    //若i小于等于S的长度并且j小于等于T的长度时循环继续
    while (i <= S[0] && j <= T[0])
    {
        //若两字母相等则继续比较
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            //j退回到上次匹配首位的下一位
            //因为下标为零的元素存储的是长度，所以这里是减2
            //如果下标为零的元素也用来存储字符，就是减1
            i = i - j + 2;
            //j退回到子串T的首位
            j = 1;
        }
    }
    //找到匹配的子串的条件
    if (j > T[0])
    {
        return i - T[0];
    }
    //匹配失败
    else
    {
        return 0;
    }
}

/*输出Next数组值*/
void NextPrint(int next[], int length)
{
    int i;
    for (i = 1; i <= length; i++)
    {
        printf("->%d", next[i]);
    }
    printf("\n");
}

/*通过计算返回子串T的next数组*/
void get_next(String T, int *next)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;
    //T[0]表示串T的长度
    while (i < T[0])
    {
        //T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            //若字符不相同，则j值回溯
            j = next[j];
        }
    }
}

/*KMP算法，返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0*/
/*T非空，1≤pos≤StrLength(S)*/
int Index_KMP(String S, String T, int pos)
{
    //i用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配
    int i = pos;
    //j用于子串T中当前位置下标值
    int j = 1;
    //定义一个next数组
    int next[255];
    //对T作分析，得到next数组
    get_next(T, next);
    //若i小于S的长度且j小于T的长度时，循环继续
    while (i <= S[0] && j <= T[0])
    {
        //两字母相等则继续判断，与朴素算法相比增加了一个j==0的判断
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        //不相等则指针后退重新开始匹配
        else
        {
            //j退回到合适的位置，i值不变
            j = next[j];
        }
    }
    if (j > T[0])
    {
        return i - T[0];
    }
    else
    {
        return 0;
    }
}

/*求模式串T的next函数修正值并存入数组nextval*/
void get_nextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            //若当前字符与前缀字符不同，则当前的j为nextval在i位置的值
            if (T[i] != T[j])
            {
                nextval[i] = j;
            }
            //如果与前缀字符相同，则将前缀字符的nextval值赋给nextval在i位置的值
            else
            {
                nextval[i] = nextval[j];
            }
        }
        else
        {
            j = nextval[j];
        }
    }
}

/*改良版KMP算法*/
int Index_KMP_improve(String S, String T, int pos)
{
    //i用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配
    int i = pos;
    //j用于子串T中当前位置下标值
    int j = 1;
    //定义一个next数组
    int next[255];
    //对T作分析，得到next数组
    get_nextval(T, next);
    //若i小于S的长度且j小于T的长度时，循环继续
    while (i <= S[0] && j <= T[0])
    {
        //两字母相等则继续判断，与朴素算法相比增加了一个j==0的判断
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        //不相等则指针后退重新开始匹配
        else
        {
            //j退回到合适的位置，i值不变
            j = next[j];
        }
    }
    if (j > T[0])
    {
        return i - T[0];
    }
    else
    {
        return 0;
    }
}

/*KMP算法具有的操作定义 end*/