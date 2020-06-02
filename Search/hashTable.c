/* 散列表(哈希表) */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAX_SIZE 100

#define SUCCESS 1
#define UNSUCCESS 0
/* 定义散列表长为数组的长度 */
#define HASH_SIZE 12
#define NULLKEY -32768

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

typedef struct
{
    // 数据元素存储基址，动态分配数组
    int *elem;
    // 当前数据元素个数
    int count;
} HashTable;

// /* 散列表表长，全局变量 */
int m = 0;

/* 初始化散列表 */
Status InitHashTable(HashTable *H)
{
    int i;
    m = HASH_SIZE;
    H->count = m;
    H->elem = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
    {
        H->elem[i] = NULLKEY;
    }
    return OK;
}

/* 散列函数 */
int Hash(int key)
{
    // 除留余数法
    return key % m;
}

/* 插入关键字进散列表 */
void InsertHash(HashTable *H, int key)
{
    // 求散列地址
    int addr = Hash(key);
    // 如果不为空，则冲突
    while (H->elem[addr] != NULLKEY)
    {
        //开放定址法的线性探测
        addr = (addr + 1) % m;
    }
    // 直到有空位后插入关键字
    H->elem[addr] = key;
}

/* 散列表查找关键字 */
Status SearchHash(HashTable H, int key, int *addr)
{
    // 求散列地址
    *addr = Hash(key);
    // 如果不为空，则冲突
    while (H.elem[*addr] != key)
    {
        // 开放定址法的线性探测
        *addr = (*addr + 1) % m;
        // 如果循环回到原点
        if (H.elem[*addr] == NULLKEY || *addr == Hash(key))
        {
            // 则说明关键字不存在
            return UNSUCCESS;
        }
    }
    return SUCCESS;
}

int main()
{
    int arr[HASH_SIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    int i, p, key, result;
    HashTable H;

    key = 39;

    InitHashTable(&H);
    for (i = 0; i < m; i++)
    {
        InsertHash(&H, arr[i]);
    }

    result = SearchHash(H, key, &p);
    if (result)
    {
        printf("查找 %d 的地址为：%d \n", key, p);
    }
    else
    {
        printf("查找 %d 失败。\n", key);
    }
    for (i = 0; i < m; i++)
    {
        key = arr[i];
        SearchHash(H, key, &p);
        printf("查找 %d 的地址为：%d \n", key, p);
    }

    return 0;
}
