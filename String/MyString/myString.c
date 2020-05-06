#include "myString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i, j;
    char ch;
    String t, s1, s2;

    printf("给串s1赋值...");
    if (StrAssign(s1, "abcd") != OK)
    {
        exit(0);
    }
    printf("赋值成功。\n");
    printf("当前串s1为：");
    StrPrint(s1);
    printf("串长为%d，串空否？%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));
    // 将s1拷贝到s2
    StrCopy(s2, s1);
    printf("拷贝s1生成的串s2为：");
    StrPrint(s2);
    // 给s2赋值
    printf("给串s2赋值...");
    if (StrAssign(s2, "efghijk") != OK)
    {
        exit(0);
    }
    printf("赋值成功。\n");
    printf("当前串s2为：");
    StrPrint(s2);
    // 比较s1和s2
    i = StrCompare(s1, s2);
    if (i < 0)
    {
        ch = '<';
    }
    else if (i == 0)
    {
        ch = '=';
    }
    else
    {
        ch = '>';
    }
    printf("串s1%c串s2\n", ch);
    // 将s1和s2连接得到串t
    if (Concat(t, s1, s2) == FALSE)
    {
        printf("串t有截断\n");
    }
    printf("串s1连接串s2得到的串t为：");
    StrPrint(t);
    printf("t的长度：%d\n", StrLength(t));
    // 清空s1
    ClearString(s1);
    printf("清s1为空串后,串s1为: ");
    StrPrint(s1);
    printf("串长为%d，串空否？%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));
    // 截取子串
    printf("求串t的子串s2,请输入子串的起始位置,子串长度：");
    scanf("%d,%d", &i, &j);
    if (SubString(s2, t, i, j) == OK)
    {
        printf("子串s2为: ");
        StrPrint(s2);
        printf("串s2的长度为：%d\n", StrLength(s2));
    }
    // 删除子串
    printf("从串t的第pos个字符起,删除len个字符，请输入pos,len：");
    scanf("%d,%d", &i, &j);
    StrDelete(t, i, j);
    printf("删除后的串t为：");
    StrPrint(t);
    printf("串t的长度为：%d\n", StrLength(t));
    // 插入子串
    i = StrLength(s2) / 2;
    StrInsert(s2, i, t);
    printf("在串s2的第%d个字符之前插入串t后,串s2为：\n", i);
    StrPrint(s2);
    printf("串s2的长度为：%d\n", StrLength(s2));
    // 子串匹配
    printf("串t为：");
	StrPrint(t);
	printf("串s2为：");
	StrPrint(s2);
    printf("s2的第%d个字母起和t第一次匹配\n", Index(s2, t, 1));
    ClearString(t);
    ClearString(s1);
    StrAssign(t, "g");
    StrAssign(s1, "zz");
    Replace(s2, t, s1);
	printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
	StrPrint(s2);

    return 0;
}

/* 字符串的顺序结构具有的操作声明 start */

/* 生成一个其值等于chars的串T */
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

/* 由串S复制得串T */
int StrCopy(String T, String S)
{
    int i;
    // 如果S串长度大于了T串的最大容量则截断
    T[0] = S[0] >= MAX_SIZE ? MAX_SIZE - 1 : S[0];
    for (i = 1; i <= S[0]; i++)
    {
        T[i] = S[i];
    }
    return OK;
}

/* 若S为空串,则返回TRUE,否则返回FALSE */
int StrEmpty(String S)
{
    return S[0] == 0 ? TRUE : FALSE;
}

/* 初始条件: 串S和T存在 */
/* 操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
int StrCompare(String S, String T)
{
    int i;
    for (i = 1; i <= S[0] && i <= T[0]; i++)
    {
        if (S[i] != T[i])
        {
            return S[i] - T[i];
        }
    }
    return S[0] - T[0];
}

/* 返回串的元素个数 */
int StrLength(String S)
{
    return S[0];
}

/* 初始条件:串S存在。操作结果:将S清为空串 */
int ClearString(String S)
{
    S[0] = 0;
    return OK;
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
int Concat(String T, String S1, String S2)
{
    int i;
    // 未截断
    if (S1[0] + S2[0] < MAX_SIZE)
    {
        for (i = 1; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (i = 1; i <= S2[0]; i++)
        {
            T[S1[0] + i] = S2[i];
        }
        T[0] = S1[0] + S2[0];
        return TRUE;
    }
    // 截断S2
    else
    {
        for (i = 1; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (i = 1; i < MAX_SIZE - S1[0]; i++)
        {
            T[S1[0] + i] = S2[i];
        }
        T[0] = MAX_SIZE - 1;
        return FALSE;
    }
}

/* 用Sub返回串S的第pos个字符起长度为len的子串。 */
int SubString(String Sub, String S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
    {
        printf("不合法的参数。\n");
        return ERROR;
    }
    for (i = 0; i <= len; i++)
    {
        Sub[i] = S[pos + i];
    }
    Sub[0] = len;
    return OK;
}

/* 使用数组的方式完成暴力匹配,返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
    // i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配
    int i = pos;
    // j用于子串T中当前位置下标值
    int j = 1;
    // 若i小于等于S的长度并且j小于等于T的长度时循环继续
    while (i <= S[0] && j <= T[0])
    {
        // 若两字母相等则继续比较
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            // j退回到上次匹配首位的下一位
            // 因为下标为零的元素存储的是长度，所以这里是减2
            // 如果下标为零的元素也用来存储字符，就是减1
            i = i - j + 2;
            // j退回到子串T的首位
            j = 1;
        }
    }
    // 找到匹配的子串的条件
    if (j > T[0])
    {
        return i - T[0];
    }
    // 匹配失败
    else
    {
        return 0;
    }
}

/* 使用字符串的基本操作完成暴力匹配，T为非空串。若主串S中第pos个字符之后存在与T相等的子串， */
/* 则返回第一个这样的子串在S中的位置，否则返回0 */
int Index2(String S, String T, int pos)
{
    int n, m, i;
    String sub;
    if (pos > 0)
    {
        // 得到主串S的长度
        n = StrLength(S);
        // 得到子串T的长度
        m = StrLength(T);
        i = pos;
        while (i <= n - m + 1)
        {
            // 取主串中第i个位置长度于T相等的子串给sub
            SubString(sub, S, i, m);
            // 如果两串不相等
            if (StrCompare(sub, T) != 0)
            {
                i++;
            }
            // 如果两串相等
            else
            {
                // 则返回i值
                return i;
            }
        }
    }
    // 若无子串与T相等，返回0
    return 0;
}

/* 初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/* 操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
int StrInsert(String S, int pos, String T)
{
    int i;
    if (pos < 1 || pos > S[0] + 1)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    // 完全插入
    if (S[0] + T[0] < MAX_SIZE)
    {
        for (i = S[0]; i >= pos; i--)
        {
            S[i + T[0]] = S[i];
        }
        for (i = pos; i < pos + T[0]; i++)
        {
            S[i] = T[i - pos + 1];
        }
        S[0] = S[0] + T[0];
        return TRUE;
    }
    // 部分插入
    else
    {
        for (i = MAX_SIZE - 1; i > pos + T[0] - 1; i--)
        {
            S[i] = S[i - T[0]];
        }
        for (i = pos; i < pos + T[0]; i++)
        {
            S[i] = T[i - pos + 1];
        }
        S[0] = MAX_SIZE - 1;
        return FALSE;
    }
}

/* 初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/* 操作结果: 从串S中删除第pos个字符起长度为len的子串 */
int StrDelete(String S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S[0] - len + 1 || len < 0)
    {
        printf("删除位置不合理。\n");
        return ERROR;
    }
    for (i = pos + len; i <= S[0]; i++)
    {
        S[i - len] = S[i];
    }
    S[0] -= len;
    return OK;
}

/* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
int Replace(String S, String T, String V)
{
    // 从串S的第一个字符起查找串T
    int i = 1;
    // 若T是空串
    if (StrEmpty(T))
    {
        printf("T为空串。\n");
        return ERROR;
    }
    do
    {
        // 结果i为从上一个i之后找到的子串T的位置
        i = Index(S, T, i);
        // 如果串S中存在串T
        if (i)
        {
            // 删除该串T
            StrDelete(S, i, StrLength(T));
            // 在原串T的位置插入串V
            StrInsert(S, i, V);
            // 在插入的串V后面继续查找串T
            i += StrLength(V);
        }
    } while (i);
    return OK;
}

/* 输出字符串T */
void StrPrint(String T)
{
    int i;
    for (i = 1; i <= T[0]; i++)
    {
        printf("%c", T[i]);
    }
    printf("\n");
}

/* 字符串的顺序结构具有的操作声明 end */