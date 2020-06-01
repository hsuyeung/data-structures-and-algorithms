/* 静态查找 */
#include "../common.h"
#include <stdio.h>

/* 存储空间初始分配量 */
#define MAX_SIZE 100

/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/* 斐波那契数列 */
int F[100];

/* 无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a, int n, int key)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (a[i] == key)
        {
            return i;
        }
    }
    return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a, int n, int key)
{
    int i;
    a[0] = key;
    i = n;
    while (a[i] != key)
    {
        i--;
    }
    return i;
}

/* 折半查找 */
int Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    /* 定义最低下标为记录首位 */
    low = 1;
    /* 定义最高下标为记录末位 */
    high = n;
    while (low <= high)
    { /* 折半 */
        mid = (low + high) / 2;
        /* 若查找值比中值小 */
        if (key < a[mid])
        {
            /* 最高下标调整到中位下标小一位 */
            high = mid - 1;
        }
        /* 若查找值比中值大 */
        else if (key > a[mid])
        {
            /* 最低下标调整到中位下标大一位 */
            low = mid + 1;
        }
        else
        {
            /* 若相等则说明mid即为查找到的位置 */
            return mid;
        }
    }
    return 0;
}

/* 插值查找 */
int Interpolation_Search(int *a, int n, int key)
{
    int low, mid, high;
    low = 1;
    high = n;
    while (low <= high)
    {
        // 插值
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);
        if (key < a[mid])
        {
            high = mid - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
        }
        // 若相等则说明mid即为查找到的位置
        else
        {
            return mid;
        }
    }
    return 0;
}

/* 斐波那契查找 */
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k = 0;
    low = 1;
    high = n;
    while (n > F[k] - 1)
    {
        k++;
    }
    for (i = n; i < F[k] - 1; i++)
    {
        a[i] = a[n];
    }
    while (low <= high)
    {
        mid = low + F[k - 1] - 1;
        if (key < a[mid])
        {
            high = mid - 1;
            k = k - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            // 若相等则说明mid即为查找到的位置
            if (mid <= n)
            {
                return mid;
            }
            else
            {
                return n;
            }
        }
    }
    return 0;
}

int main(void)
{
    int a[MAX_SIZE + 1], i, result;
    int arr[MAX_SIZE] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};

    for (i = 0; i <= MAX_SIZE; i++)
    {
        a[i] = i;
    }
    result = Sequential_Search(a, 10, 99);
    printf("Sequential_Search:%d \n", result);
    result = Sequential_Search2(a, MAX_SIZE, 1);
    printf("Sequential_Search2:%d \n", result);

    result = Binary_Search(arr, 10, 62);
    printf("Binary_Search:%d \n", result);

    result = Interpolation_Search(arr, 10, 62);
    printf("Interpolation_Search:%d \n", result);

    F[0] = 0;
    F[1] = 1;
    for (i = 2; i < 100; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    result = Fibonacci_Search(arr, 10, 62);
    printf("Fibonacci_Search:%d \n", result);

    return 0;
}