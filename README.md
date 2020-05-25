# DataStructuresAndAlgorithms
自学数据结构与算法的笔记

# 笔记
## 使用教材：《大话数据结构》
## 使用语言：C语言（C90标准）
## 代码编写工具：Visual Studio Code
## 使用编译器：gcc8.1.0
## 一、数据结构以及算法的定义  
    1、程序设计 = 数据结构 + 算法。
    2、数据结构：指相互之间存在一种或多种特定关系的数据元素的集合。
    3、算法：解决特定问题求解步骤的描述。
    4、算法的五个基本特性：输入、输出、有穷性、确定性、可行性。
    5、算法可以有零个或多个输入，至少有一个输出。
    6、用大O记法来表示算法时间复杂度。
    7、推导大O阶：
        (1)用常数1取代运行时间中的所有加法常数。
        (2)在修改后的运行次数函数中，只保留最高阶项。
        (3)如果最高阶项存在且不是1，则去除与这个项相乘的常数。
        最终得到的结果就是大O阶。
    8、常用时间复杂度分类：
        (1)常数阶：O(1)
        (2)线性阶：O(n)
        (3)对数阶：O(logn)
        (4)平方阶：O(n²)
        (5)nlogn阶：O(nlogn)
        (6)立方阶：O(n³)
        (7)指数阶：O(2^n)
    9、常用时间复杂度按照耗费时间从小到大排序：
        O(1) < O(logn) < O(n) < O(nlogn) < O(n²) < O(n³) < O(2^n) < O(n!) < O(n^n)
    10、一般情况下说的时间复杂度都是最坏情况下的时间复杂度。
    11、算法的设计要求：正确性、可读性、健壮性、高效率和低存储量需求。
    12、算法的度量方法：事后统计方法(不科学、不准确)、事前分析估算方法。
## 二、线性表
    1、线性表：零个或多个数据元素的有限序列。(序列表示线性表元素之间是有顺序的，若元素存在多个，则第一个元素无前驱，最后一个元素无后继，其他每个元素有且只有一个前驱和后继。)
    数据类型定义：
        ADT 线性表(List)
        Data
            线性表的数据对象集合为{a1,a2,...，an}，每个元素的类型均为DataType。
            其中，除第一个元素a1外，每一个元素有且只有一个直接前驱元素，除了最后一个元素an外，每一个元素有且只有一个直接后继元素。
            数据元素之间的关系是一对一的关系。
        Operation
            InitList()：初始化操作，建立一个空的线性表L并返回。
            ListEmpty(L)：若线性表为空，返回true；否则返回false。
            ClearList(*L)：将线性表清空。
            GetElem(L, i, *e)：将线性表L中的第i个位置元素值返回给e。
            LocationElem(L, e)：在线性表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功，否则返回-1。
        end ADT
    2、线性表的两种物理结构：
        (1)顺序存储结构：用一段地址连续的存储单元依次存储线性表的数据元素。
            (a)顺序线性表的结构代码：
                ```c
                    /* 存储空间初始分配量 */
                    #define MAX_SIZE 20
                    /* ElemType类型根据实际情况而定，这里假设为int */
                    typedef int ElemType;
                    typedef struct
                    {
                        /* 数组存储数据元素，最大容量为MAX_SIZE */
                        ElemType data[MAX_SIZE];
                        /* 线性表当前长度 */
                        int length;
                    } SqList;
                ```
            注意：在任意时刻，线性表长度应该小于等于数组的长度。
            (b)顺序线性表元素位置的计算：
                假设线性表中每一个元素占用c个存储单元，那么第i+1个数据元素与第i个数据元素的存储位置关系：
                LOC(ai + 1) = LOC(ai) + c
                因此：对于第i个数据元素ai的存储位置可以有a1推出：
                LOC(ai) = LOC(a1) + (i - 1) * c
                通过这个公式，可以得出该线性表的存取数据的时间复杂度为O(1)，通常把具有这一特点的存储结构成为随机存取结构。  
            (c)顺序线性表获取元素(GetElem)的操作：
                ```c
                    #define OK 1
                    #define ERROR 0
                    #define TRUE 1
                    #define FALSE 0
                    /* Status是函数的类型，其值是函数结果状态代码，如OK等 */
                    typedef int Status;
                    /* 初始条件：顺序线性表L已经存在，1 <= i <= ListLength(L) */
                    /* 操作结果：用e放回L中第i个数据元素的值 */
                    Status GetElem(SqList L, int i, ElemType *e) 
                    {
                        if (L.length == 0 || i < 1 || i > L.length) 
                        {
                            return ERROR;
                        }
                        *e = L.data[i - 1];
                        return OK;
                    }
                ```
            (d)顺序线性表的插入(ListInsert)操作：
                思路：
                    如果插入位置不合理，则抛出异常；
                    如果线性表长度大于等于数组长度，则抛出异常或者动态增加容量；
                    从最后一个元素开始向前遍历到第i个位置，分别将它们都向后移动一个位置；
                    将要插入元素填入位置i处；线性表长度+1。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在,1 <= i <= ListLength(L) */
                    /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
                    Status ListInsert(SqList *L, int i, ElemType e) {
                        int k;
                        /* 顺序线性表已满 */
                        if (L->length == MAX_SIZE) 
                        {
                            return ERROR;
                        }
                        /* 当i不在范围内时 */
                        if (i < 1 || i > L->length + 1) 
                        {
                            return ERROR;
                        }
                        /* 若插入数据位置不在表尾 */
                        if (i <= L->length) 
                        {
                            /* 将要插入位置后数据元素向后移动一位 */
                            for (k = L->length - 1; k >= i - 1; k--) 
                            {
                                L->data[k + 1] = L->data[k];
                            }
                        }
                        /* 将新元素插入 */
                        L->data[i - 1] = e;
                        L->length++;
                        return OK;
                    }
                ```
            (e)顺序线性表的删除(ListDelete)操作：
                思路：
                    如果删除位置不合理，抛出异常；
                    取出删除元素；
                    从删除元素位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置；
                    表长减一。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在,1 <= i <= ListLength(L) */
                    /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
                    Status ListDelete(SqList *L, int i, ElemType *e) {
                        int k;
                        /* 线性表为空 */
                        if (L->length == 0) 
                        {
                            return ERROR;
                        }
                        /* 删除位置不合理 */
                        if (i < 1 || i > L->length) 
                        {
                            return ERROR;
                        }
                        *e = L->data[i - 1];
                        /* 如果删除的不是最后一个位置 */
                        if (i < L->length) 
                        {
                            /* 将删除位置后继元素前移 */
                            for (k = i; k < L->length; k++) {
                                L->data[k - 1] = L->data[k];
                            }
                        }
                        L->length--;
                        return OK;
                    }
                ```
            (f)分析可得出，线性表的顺序存储结构在插入、删除操作时的时间复杂度为O(n)，说明它比较适合于元素个数不太变化，而更多的是存取数据的应用。
            (g)线性表顺序存储结构的优缺点：
                优点：
                    无须为表示表中元素之间的逻辑关系而增加额外的存储空间；
                    可以快速地存取表中任一位置的元素。
                缺点：
                    插入和删除操作需要移动大量元素；
                    当线性表长度变化较大时，难以确定存储空间的容量；
                    造成存储空间的“碎片”。
        (2)链式存储结构：用一组任意的存储单元存储线性表的数据元素，这组存储单元可以是连续的，也可以是不连续的。为了表示ai与其直接后继元素ai+1之间的逻辑关系，对数据元素ai来说，除了存储其本身的信息之外，还需存储一个指示其直接后继的信息（即直接后继的存储位置）。把存储数据元素信息的域成为数据域，把存储直接后继位置的域称为指针域。指针域中存储的信息称作指针或链。这两部分信息组成数据元素ai的存储映像，称为结点(Node)。n个结点链结成一个链表，即为线性表的链式存储结构，只有一个指针域的称为单链表。
            (a)头指针与头结点的区别：
                头指针：
                    头指针是指链表指向第一个结点的指针，若链表有头结点，则是指向头节点的指针；
                    头指针具有标识作用，所以常用头指针冠以链表的名字；
                    无论链表是否为空，头指针均不为空。头指针是链表的必要元素。
                头结点：
                    头结点是为了操作的统一和方便而设立的，放在第一元素的结点之前，其数据域一般无意义(也可以存放链表的长度);
                    有了头结点，对在第一元素结点前插入和删除第一结点，其操作与其它结点的操作就统一了；
                    头结点不一定是链表必须要素。
            (b)线性表的单链表存储结构代码描述：
            ```c
                /* 线性表的单链表存储结构 */
                typedef struct Node 
                {
                    ElemType data;
                    struct Node *next;
                } Node;
                /* 定义LinkList */
                typedef struct Node* LinkList;
            ```
            (c)单链表的读取：
                获取链表第i个数据的算法思路：
                    声明一个指针p指向链表第一个结点，初始化j从1开始；
                    当j < i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1；
                    弱到链表末尾p为空，则说明第i个结点不存在；
                    若查找成功，返回结点p的数据。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L) */
                    /* 操作结果：用e返回L中第i个数据元素的值 */
                    Status GetElem(LinkList L, int i, ElemType *e) 
                    {
                        int j;
                        /* 声明一个指针p */
                        LinkList p;
                        /* 让p指向链表L的第一个结点，因为假设L是带头结点的，所以L->next才是第一个结点 */
                        p = L->next;
                        /* j为计数器 */
                        j = 1;
                        /* p不为空且计数器j还没有等于i时，循环继续 */
                        while (p && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /* 第i个结点不存在 */
                        if (!p || j > i) 
                        {
                            return ERROR;
                        }
                        /* 取第i个结点的数据 */
                        *e = p->data;
                        return OK;
                    }
                ```
                分析可得，单链表的读取时间复杂度为O(n)。
            (d)单链表的插入操作：
                思路：
                    声明一指针p指向链表头结点，初始化j从1开始；
                    当j < i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1；
                    若到链表末尾p为空，则说明第i个结点不存在；
                    否则查找成功，在系统中生成一个空结点s；
                    将数据元素e赋值给s->data；
                    单链表的插入标准语句:s->next = p->next;p->next = s;(这两句话绝对不能交换顺序);
                    返回成功。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L) */
                    /* 操作结果：在L中第i个结点位置之前插入新的数据元素e，L长度加1 */
                    Status ListInsert(LinkList *L, int i, ElemType e) 
                    {
                        int j;
                        LinkList p, s;
                        p = *L;
                        j = 1;
                        /* 寻找第i - 1个结点 */
                        while (p && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /* 第i个结点不存在 */
                        if (!p || j > i) 
                        {
                            return ERROR;
                        }
                        /* 生成新结点 */
                        s = (LinkList)malloc(sizeof(Node));
                        s->data = e;
                        s->next = p->next;
                        p->next = s;
                        return OK;
                    }
                ```
            (e)单链表的删除操作：
                思路：
                    声明一指针p指向链表头结点，初始化j从1开始；
                    当j < i时，就遍历链表，让p得指针向后移动，不断指向下一个结点，j累加1；
                    若到链表末尾p为空，则说明第i个结点不存在；
                    否则查找成功，将欲删除的结点p->next赋值给q；
                    单链表的删除标准语句p->next = 1->next;
                    将q结点中的数据赋值给e，作为返回；
                    释放q结点；
                    返回成功。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L) */
                    /* 操作结果：删除L的第i个结点，并用e返回其值，L的长度减1 */
                    Status ListDelete(LinkList *L, int i, ElemType e) 
                    {
                        int j;
                        LinkList p, q;
                        p = *L;
                        j = 1;
                        /* 遍历寻找第i-1个结点 */
                        while (p->next && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /* 第i个结点不存在 */
                        if (!(p->next) || j > i) 
                        {
                            return ERROR;
                        }
                        q = p->next;
                        /* 将q的后继赋值给p的后继 */
                        p->next = q->next;
                        /* 将q结点中的数据给e */
                        *e = q->data;
                        /* 让系统回收此结点，释放内存 */
                        free(q);
                        return OK;
                    }
                ```
            (f)分析可以得出，单链表的插入与删除时间复杂的都也是O(n)，乍一看与顺序表没啥优势，但是如果当同时插入多个数据，那么单链表只有第一次需要遍历寻找第i个结点的位置，时间复杂度为O(n)，但是后面的几次就只需要简单的赋值移动指针完成了，时间复杂度为O(1)。所以，对于插入或删除数据越频繁的操作，单链表的效率优势就越明显。
            (g)单链表的整表创建：
                思路：
                    声明一指针p和计数变量i；
                    初始化一空链表L；
                    让L的头结点的指针指向NULL，即建立一个带头结点的单链表；
                    循环：
                        生成一新结点赋值给p；
                        随机生成一数字赋值给p的数据域p->data；
                        将p插入到头结点域前一新结点之间。
                实现代码：
                ```c
                    /* 随机产生n个元素的值，建立带表头结点的线性单链表L(头插法) */
                    void CreateListHead(LinkList *L, int n) 
                    {
                        LinkList p;
                        int i;
                        /* 初始化随机数种子 */
                        srand(time(0));
                        *L = (LinkList)malloc(sizeof(Node));
                        /* 先建立一个带头结点的单链表 */
                        (*L)->next = NULL;
                        for (i = 0; i < n; i++) 
                        {
                            /* 生成新节点 */
                            p = (LinkList)malloc(sizeof(Node));
                            /* 随机生成100以内的数字 */
                            P->data = rand() % 100 + 1;
                            p->next = (*L)->next;
                            /* 插入到表头 */
                            (*L)->next = p;
                        }
                    }
                ```
                ```c
                    /* 随机产生n个元素的值，建立带表头结点的线性单链表L(尾插法) */
                    void CreateListTail(LinkList *L, int n) 
                    {
                        LinkList p, r;
                        int i;
                        /* 初始化随机数种子 */
                        srand(time(0));
                        /* L指整个单链表 */
                        *L = (LinkList)malloc(sizeof(Node));
                        /* r为指向尾部的结点 */
                        r = *L;
                        for (i = 0; i < n; i++) 
                        {
                            /* 生成新节点 */
                            p = (LinkList)malloc(sizeof(Node));
                            /* 随机生成100以内的数字 */
                            P->data = rand() % 100 + 1;
                            /* 将表尾终端结点的指针指向新结点 */
                            r->next = p;
                            /* 将当前的新结点定义为表尾终端结点 */
                            r = p;
                        }
                        /* 表示当前链表结束 */
                        r->next = NULL;
                    }
                ```
            (h)单链表的整表删除：
                思路：
                    声明一个指针p和q；
                    将第一个结点赋值给p；
                    循环：
                        将下一结点赋值给q；
                        释放p；
                        将q赋值给p。
                实现代码：
                ```c
                    /* 初始条件：顺序线性表L已存在，操作结果：将L重置为空表 */
                    Status ClearList(LinkList *L) 
                    {
                        LinkList p, q;
                        /* p指向第一个结点 */
                        p = (*L)->next;
                        /* 没到表尾 */
                        while (p) 
                        {
                            q = p->next;
                            free(p);
                            p = q;
                        }
                        /* 将头结点的指针域设置为空 */
                        (*L)->next = NULL;
                        return OK;
                    }
                ```
        (3)单链表结构与顺序存储结构的对比：
            (a)存储分配方式：
                顺序存储结构用一段连续的存储单元依次存储线性表的数据元素；
                单链表采用链式存储结构，用一组任意的存储单元存放线性表的元素。
            (b)时间性能：
                查找：
                    顺序存储结构O(1)；
                    单链表O(n)。
                插入和删除：
                    顺序存储结构需要平均移动表长一半的元素，时间为O(n)；
                    单链表在找出某位置的指针后，插入和删除时间仅为O(1)。
            (c)空间性能：
                顺序存储结构徐涛预分配存储空间，分大了，浪费，分小了易发生上溢；
                单链表不需要分配存储空间，只要有就可以分配，元素个数也不受限制。
            通过上面的对比，可以得出一些经验性的总结：
                若线性表需要频繁查找，很少进行插入和删除操作时，宜采用顺序存储结构。若需要频繁插入和删除时，宜采用单链表结构；
                当线性表中的元素个数变化较大或者根本不知道有多大时，最好用单链表结构，如果事先知道线性表的大致长度，用顺序存储结构效率会高很多。
    3、静态链表：使用数组来代替指针，来描述单链表。首先，让数组的元素都是由两个数据域组成，data和cur。也就是说，数组的每一个下标都对应一个data和一个cur。数据域data用来存放数据元素；而游标cur相当于单链表中的next指针，存放该元素的后继在数组中的下标。就把这种用数组表述的链表叫静态链表，还有起名叫做游标实现法。主要用于不支持指针的程序设计语言中。
    4、线性表的静态链表的存储结构：
    ```c
        /* 线性表的静态链表存储结构 */
        /* 假设链表的最大长度为1000 */
        #define MAX_SIZE 1000
        typedef struct 
        {
            ElemType data;
            /* 游标，为0时表示无指向 */
            int cur;
        } Component, StaticLinkList[MAX_SIZE];
    ```
    另外对数组第一个和最后一个元素作为特殊元素处理，不存数据。
    通常把未被使用的数组元素称为备用链表。
    数组第一个元素，即下标为0的元素cur就存放备用链表的第一个结点的下标；而数组的最后一个元素的cur则存放第一个有数值元素的下标，相当于单链表中的头结点作用,当整个链表为空时，则为0。
    初始化的数组状态：
    ```c
        /* 将一维数组space中各分量链成一备用链表 */
        /* space[0].cur为头指针，"0"表示空指针 */
        Status InitList(StaticLinkList space) 
        {
            int i;
            for (i = 0; i < MAX_SIZE - 1; i++) 
            {
                space[i].cur = i + 1;
            }
            /* 目前静态链表为空，最后一个元素的cur为0 */
            space[MAX_SIZE - 1].cur = 0;
            return OK;
        }
    ```
    5、静态链表的插入操作：
        思路：为了辨明数组中哪些分量未被使用，解决办法是将所有未被使用过的及已被删除的分量用游标链成一个备用链表，每当进行插入时，便可以从备用链表上取得第一个结点作为待插入的新结点。
        ```c
            /* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
            int Malloc_SLL(StaticLinkList space) 
            {
                /* 当前数组第一个元素的cur存的值，就是要返回的第一个备用空闲的下标 */
                int i = space[0].cur;
                if (space[0].cur) 
                {
                    /* 由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用 */
                    space[0].cur = space[i].cur;
                }
                return i;
            }
        ```
        插入实现代码：
        ```c
            Status ListInsert(StaticLinkList L, int i, ElemType e) 
            {
                int j, k, l;
                /* 注意k首先是最后一个元素的下标 */
                k = MAX_SIZE - 1;
                if (i < 1 || i > ListLength(L) + 1) 
                {
                    return ERROR;
                }
                /* 获取空闲分量的下标 */
                j = Malloc_SSL(L);
                if (j) 
                {
                    /* 将数据赋值给此分量的data */
                    L[j].data = e;
                    /* 找到第i个元素的位置 */
                    for (l = 1; l <= i - 1; l++) 
                    {
                        k = L[k].cur;
                    }
                    /* 把第i个元素之前的cur赋值给新元素的cur */
                    L[j].cur = L[k].cur;
                    /* 把新元素的下标赋值给第i个元素之前元素的cur */
                    L[k].cur = j;
                    return OK;
                }
                return ERROR;
            }
        ```
    6、静态链表的删除操作：
        思路：和前面一样，删除元素使，原来使需要释放结点的函数free()。现在也得自己实现它。
        实现代码：
        ```c
            /* 删除在L中第i个数据元素e */
            Status LsitDelete(StaticLinkList L, int i) 
            {
                int j, k;
                if (i < 1 || i > ListLegth(L)) 
                {
                    return ERROR;
                }
                k = MAX_SIZE - 1;
                for (j = 1; j <= i - 1; j++) 
                {
                    k = L[k].cur;
                }
                j = L[k].cur;
                L[k].cur = L[j].cur;
                Free_SSL(L, j);
                return OK;
            }
            /* 将下标为k的空闲结点回收到备用链表 */
            void Free_SSL(StaticLinkList space, int k) 
            {
                /* 把第一个元素cur值赋给要删除的分量cur */
                space[k].cur = space[0].cur;
                /* 把要删除的分量下标赋值给第一个元素的cur */
                space[0].cur = k;
            }
            ```
    7、静态链表的一些其他操作，比如ListLength()：
    ```c
        /* 初始条件：静态链表L已存在。操作结果：返回L中数据元素个数 */
        int ListLength(StaticLinkList L) 
        {
            int j = 0;
            int i = L[MAX_SIZE - 1].cur;
            while (i) 
            {
                i = L[i].cur;
                j++;
            }
            return j;
        }
    ```
    8、静态链表的优缺点：
        优点：
            在插入和删除操作时，只需要修改游标，不需要移动元素，从而改进了在顺序存储结构中的插入和删除操作需要移动大量元素的缺点。
        缺点：
            没有解决连续存储分配带来的表长难以确定的问题；
            失去了顺序存储结构随机存取的特性。
    9、循环链表：将单链表中的终端结点的指针端由空指针改为指向头结点，就使整个单链表形成一个环，这种头尾相接的单链表称为单循环链表，简称循环链表。
    10、循环链表的判断条件不再是判断p->next是否为空，而是判断p->next是否等于头结点了。
    11、循环链表使用指向终端结点的尾指针而不使用头指针来表示循环链表，这样查找头结点和终端结点的时间复杂度都变为O(1)了，终端结点用尾指针rear指示，头结点就是rear->next，开始结点就是rear->next->next。
    12、要想将两个循环链表合并成一个表时，使用尾指针就很方便了，实现代码：
    ```c
        /* 保存A表的头结点 */
        p = rearA->next;
        /* 将本来是指向B表的第一个结点(不是头结点)赋值给rear->next */
        rearA->next = rearB->next->next;
        /* 将原A表的头结点赋值给rearB->next */
        rearB->next = p;
        /* 释放p */
        free(p);
    ```
    13、双向链表：在单链表的每个结点中，再设置一个指向其前驱结点的指针域。
    14、双向链表的存储结构:
    ```c
        /* 线性表的双向链表存储结构 */
        typedef struct DuLNode 
        {
            ElemType data;
            /* 直接前驱指针 */
            struct DuLNode *prior;
            /* 直接后继指针 */
            struct DuLNode *next;
        } DuLNode, *DulinkList;
    ```
    15、双向链表也有可以有循环链表。
    对于链表中的某一个结点p，它的后继的前驱、前驱的后继都是它自己：p->next->prior = p = p->prior->next。双向链表时单链表中扩展出来的结构，所以很多操作是相同的，比如求长度的ListLength，查找元素的GetElem，获得元素位置的LocationElem等，这些操作都只设计一个方向的指针即可，另一指针也不能提供任何帮助。但是双向链表再插入和删除时要麻烦一些，需要修改两个指针变量。
    16、双向链表的插入操作：并不复杂，但是顺序很重要，不能写反了！！
    假设存储元素e的结点s，现在要实现将结点s插入到结点p和p->next之间：
    实现代码：
    ```c
        /* 这四步的顺序千万不能换！ */
        /* 把p赋值给s的前驱 */
        s->prior = p;
        /* 把p->next赋值给s的后继 */
        s->next = p->next;
        /* 把s赋值给p->next的前驱 */
        p->next->prior = s;
        /* 把s赋值给p的后继 */
        p->next = s;
        /* 总结顺序就是：先搞定s的前驱和后继，再搞定后结点的前驱，最后解决前结点的后继 */
    ```
    17、双向链表的删除操作：若要删除结点p只需要两步。
    实现代码：
    ```c
        /* 这里的p代表的是当前要删除的结点，与代码中的p不相同 */
        /* 把p->next赋值给p->prior的后继 */
        p->prior->next = p->next;
        /* 把p->prior赋值给p->next的前驱 */
        p->next->prior = p->prior;
        /* 释放结点 */
        free(p);
    ```
## 三、栈与队列
    1、栈的定义：栈(Stack)是限定尽在表尾进行插入和删除操作的线性表。
    把允许插入和删除的一端称为栈顶(top)，另一端称为栈底(bottom)，不含任何数据元素的栈称为空栈。栈又称为后进先出(Last In First Out)的线性表，简称LIFO结构。
    2、理解栈的定义需要注意：
        首先它是一个线性表，也就是说栈元素具有线性关系，即前驱后继关系。只不过是一特殊的线性表而已。定义中说的线性表的表尾进行插入和删除操作，这里表尾是指栈顶，而不是栈底；
        栈底是固定的，最先进栈的只能再栈底；
        栈的插入操作，叫做进栈，也称压栈、入栈；
        栈的删除操作，叫做出栈，也有的叫作弹栈。
    3、栈的抽象数据类型定义：
        ADT 栈(Stack)
        Data
            栈的数据对象集合为{a1,a2,...，an}，每个元素的类型均为DataType。
            其中，除第一个元素a1外，每一个元素有且只有一个直接前驱元素，除了最后一个元素an外，每一个元素有且只有一个直接后继元素。
            数据元素之间的关系是一对一的关系。
        Operation
            InitStack()：初始化操作，建立并返回一个空栈S。
            DestroyStack(*S)：若栈存在，则销毁它。
            ClearStack(*S)：将栈清空。
            StackEmpty(S)：若栈为空，返回true，否则返回false。
            GetTop(S, *e)：若栈存在且非空，用e返回S的栈顶元素。
            Push(*S, e)：若栈S存在，插入新元素e到栈S中并成为栈顶元素。
            Pop(*S, *e)：删除栈S中栈顶元素，并用e返回其值。
            StackLength(S)：返回栈S中的元素个数。
        end ADT
    4、栈的顺序存储结构：栈的顺序存储其实也是线性表顺序存储的简化，我们简称为顺序栈。一般用数组下标为0的以端作为栈底比较好，因为首元素都在栈底，变化最小，所以让它作为栈底。当栈存在一个元素时，top为0，通常将空栈的判定条件定位top=-1。
    结构定义：
    ```c
        /* SElemType类型根据实际情况而定，这里假设为int */
        typedef int SElemType;
        typedef struct 
        {
            SElemType data[MAX_SIZE];
            /* 用于栈顶指针 */
            int top;
        } SqStack;
    ```
    5、栈的顺序存储结构的进栈操作：
    ```c
        Statuc Push(SqStack *S, SElemType e)
        {
            // 如果栈已经满了
            if (S->top == MAXSIZE - 1)
            {
                return ERROR;
            }
            // 栈顶指针加一
            S->top++;
            // 将新插入元素赋值给栈顶空间
            S->data[S->top] = e;
            return OK;
        }
    ```
    时间复杂度O(1)。
    6、栈的顺序存储结构的出栈操作：
    ```c
        Status Pop(SqStack *S, SElemType *e)
        {
            // 如果是空栈
            if (s->top == -1)
            {
                return ERROR;
            }
            // 将要删除的栈顶元素赋值给e
            *e = S->data[S->top];
            // 栈顶指针减一
            S->top--;
            return OK;
        }
    ```
    时间复杂度O(1)。
    7、两栈共享空间
    做法：数组有两个端点，两个栈有两个栈底，让一个栈的栈底为数组的始端，即下标为0处，另一个栈为数组的末端之后，即下标为数组长度n处。这样，两个栈如果增加元素，就是两端点向中间延伸。
    当top1 = -1， top2 = n的时候就是空栈，当top1 + 1 = top2的时候就是栈满。
    结构代码：
    ```c
        /* 两栈共享空间结构 */
        typedef struct
        {
            SElemType data[MAX_SIZE];
            // 栈1栈顶指针
            int top1;
            // 栈2栈顶指针
            int top2;
        } SqDoubleStack;
    ```
    8、两栈共享空间的push(入栈)操作：
    思路：除了要插入元素值参数歪，还需要有一个判断是栈1还是栈2的栈号参数stackNumber。
    实现代码：
    ```c
        /* 插入元素e为新的栈顶元素 */
        Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
        {
            // 栈已经满了，不能再push新元素了
            if (S->top1 + 1 == S->top2)
            {
                return ERROR;
            }
            // 如果是栈1有元素进栈
            if (stackNumber == 1)
            {
                // 若是栈1则先top1+1然后给数组元素赋值
                S->data[++S->top1] = e;
            }
            // 如果是栈2有元素进栈
            else if (stackNumber == 2)
            {
                // 若是栈2则先top2-1然后给数组元素赋值
                S->data[--S->top2] = e;
            }
            return OK;
        }
    ```
    9、两栈共享空间的pop(出栈)操作：
    ```c
        /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR */
        Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
        {
            if (stackNumber == 1)
            {
                // 栈1已经是空栈了
                if (S->top1 == -1)
                {
                    return ERROR;
                }
                // 将栈1的栈顶元素出栈
                *e = S->data[S->top1--];
            }
            else if (stackNumber == 2)
            {
                // 栈2已经是空栈了
                if (S->top2 == MAXSIZE)
                {
                    return ERROR;
                }
                // 将栈2的栈顶元素出栈
                *e = S->data[S->top2++];
            }
            return OK;
        }
    ```
    10、通常使用两栈共享空间这样的数据结构，通常都是当两个栈的空间需求有相反关系时，也就是一个栈在增长时另一个栈正在缩短的情况，就像买卖股票一样，你买入时，一定是有人卖出的。这样使用两栈共享空间存储方法才有比较大的意义。否则两个栈都在不停的增长，就很快会因栈满而溢出了。
    11、栈的链式存储结构，又简称为链栈，在链栈中，头结点已经不需要了。
    链栈的结构代码：
    ```c
        typedef struct StackNode
        {
            SElemType data;
            struct StackNode *next;
        } StackNode, *LinkStackPtr;
    
        typedef struct LinkStack
        {
            LinkStackPtr top;
            int count;
        } LinkStack;
        /* 链栈的操作绝大部分都和单链表类似，只是在插入和删除上特殊一些 */
    ```
    12、链栈的进栈(push)操作：
    假设元素值为e的新结点是s，top为栈顶指针。
    实现代码：
    ```c
        /* 插入元素为e的新的栈顶元素 */
        Status Push(LinkStack *S, SElemType e)
        {
            LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
            s->data = e;
            // 把当前的栈顶元素赋值给新结点的直接后继
            s->next = S->top;
            // 将新结点s赋值给栈顶指针
            S->top = s;
            S->count++;
            return OK;
        }
    ```
    时间复杂度O(1)。
    13、链栈的出栈(pop)操作：
    思路：假设变量p用来存储要删除的栈顶结点，将栈顶指针下移一位，最后释放p即可。
    实现代码：
    ```c
        /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR */
        Status Pop(LinkStack *S, SElemType *e)
        {
            LinkStackPtr p;
            // 如果栈为空
            if (StackEmpty(*S))
            {
                return ERROR;
            }
            *e = S->top->data;
            // 将栈顶结点赋值给p
            p = S->top;
            // 使栈顶指针下移一位，指向后一结点
            S->top = S->top->next;
            // 释放结点p
            free(p);
            S->count--;
            return OK;
        }
    ```
    时间复杂度O(1)。
    14、栈的应用：递归
        (1)递归函数：把一个直接调用自己或通过一系列的调用语句间接地调用自己的函数，称作递归函数。
        (2)每个递归定义必须至少有一个条件，满足时递归不再进行，即不再引用自身而是返回值退出。
    15、栈的应用：四则运算表达式求值
        (1)(后缀)逆波兰表达式(Reverse Polish Notation, RPN)：所有的符号都是在要运算数字的后面出现。
        例如：正常表达式：9+(3-1)*3+10/2
            其后缀表达式：9 3 1 - 3 * + 10 2 / +
        (2)后缀表达式的计算规则(以上面的表达式为例)：从左到右遍历表达式的每个数字和符号，遇到是数字就进栈，遇到是符号，就将处于栈顶两个数字出栈，进行运算，运算结果进栈，一直到最终获得结果。
            步骤：
                初始化一个空栈。此栈用来对要运算的数字进出使用；
                后缀表达式中前三个都是数字，所以9、3、1依次进栈；
                接下来是“-”，所以将栈中的1出栈作为减数，3出栈作为被减数，并运算3-1得到2，再将2进栈；
                接着是数字3进栈；
                后面是“*”，也就意味着栈中的3、2依次出栈，2与3相乘，得到6，并将6进栈；
                下面是“+”，所以栈中的6、9依次出栈，9与6相加，得到15，将15进栈；
                接着是10、2两数字依次进栈；
                接下来是符号“/”，因此，栈顶的2、10依次出栈，10与2相除，得到5，将5进栈；
                最后一个符号“+”，所以15、5依次出栈并相加，得到20，将20进栈；
                结果是20出栈，栈变为空。
        (3)中缀表达式转后缀表达式：
            我们把平时所用的标准四则运算表达式，叫做中缀表达式。
            规则：
                从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分；若是符号，则判断其与栈顶符号的优先级，是右括号或优先级低于栈顶符号(乘除优先于加减)则栈顶元素依次出栈并输出，并将当前符号进栈，一直到最终输出后缀表达式为止。
            步骤：
                初始化一空栈，用来对符号进出栈使用；
                第一个字符是数字9，输出9，后面是符号“+”，进栈；
                第三个字符是“（”，依然是符号，因其只是左括号，还未配对，故进栈；
                第四个字符是数字3，输出，总表达式为9 3，接着是“-”，进栈；
                接下来是数字1，输出，总表达式为9 3 1，后面是符号“）”，此时，我们需要去匹配之前的“（”，所以栈顶依次出栈，并输出，直到“）”出栈为止。此时左括号上方只有“-”，因此输出“-”。总的表达式为9 3 1 -；
                接着是数字3，输出，总的表达式为9 3 1 - 3.紧接着是符号“*”，因为此时的栈顶符号为“+”号，优先级低于“*”，因此不输出，“*”进栈；
                之后是符号“+”，此时当前栈顶元素“*”比这个“+”的优先级高，因此栈中元素出栈并输出(没有比“+”号更低的优先级，所以全部出栈)，总输出表达式为9 3 1 - 3 * +。然后将当前这个符号“+”进栈，也就是说，前面6步的栈底的“+”是指中缀表达式中开头的9后面那个“+”，而当前一步的“+”是指最后的一个“+”；
                紧接着数字10，输出，总表达式变为9 3 1 - 3 * + 10.后是符号“/”，所以“/”进栈；
                最后一个数字2，输出，总的表达式为9 3 1 - 3 * + 10 2；
                因为已经到最后，所以将栈中符号全部出栈并输出。最终结果即：9 3 1 - 3 * + 10 2 / +。
        (4)总结：要想让计算机处理具有我们通常的标准(中缀)表达式的能力，最重要的就是两步：
            将中缀表达式转化为后缀表达式(栈用来进出运算的符号)
            将后缀表达式进行运算得出结果(栈用来进出运算的数字)
    16、队列(queue)是只允许在一端进行插入操作，而在另一端进行删除操作的线性表。
    队列是一种先进先出(First In First Out)的线性表，简称FIFO。允许插入的一端称为队尾，允许删除的一端称为对头。
    17、队列的抽象数据类型定义：
        ADT 队列(Queue)
        Data
            同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
        Operation
            InitQueue(*Q)：初始化操作，建立一个空队列Q。
            DestroyQueue(*Q)：若队列Q存在，则销毁它。
            ClearQueue(*Q)：将队列Q清空。
            QueueEmpty(Q)：若队列为空，返回true，否则返回false。
            GetHead(Q, *e)：若队列Q存在且非空，用e返回队列Q的队头元素。
            EnQueue(*Q, e)：若队列Q存在，插入新元素e到队列Q中并1成为队尾元素。
            DeQueue(*Q, *e)：删除队列Q中队头元素，并用e返回其值。
            QueueLength(Q)：返回队列Q的元素个数。
        end ADT
    18、循环队列的顺序存储结构
        (1)把队列头尾相接的顺序存储结构称为循环队列。
        (2)队列为空的条件为：rear == front；队列为满的条件为：(rear + 1) % QueueSize == front
        (3)通用的计算队列长度公式为：
            (rear - front + QueueSize) % Queue
        (4)循环队列的顺序存储结构：
        ```c
            /* QElemType类型根据实际情况而定，这里假设为int */
            typedef int QElemType;
            /* 循环队列的顺序存储结构 */
            typedef struct
            {
                QElemType data[MAX_SIZE];
                // 头指针
                int front;
                // 尾指针，若队列不空，指向队列尾元素的下一个位置
                int rear;
            } SqQueue;
        ```
        (5)循环队列的初始化：
        ```c
            /* 初始化一个空队列Q */
            Status InitQueue(SqQueue *Q)
            {
                Q->front = 0;
                Q->rear = 0;
                return OK;
            }
        ```
        (6)循环队列求队列长度：
        ```c
            /* 返回Q中的元素个数，也就是队列的当前长度 */
            int QueueLength(SqQueue Q)
            {
                return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
            }
        ```
        (7)循环队列的入队列操作：
        ```c
            /* 若队列未满，则插入元素e为Q新的队尾元素 */
            Status EnQueue(SqQueue *Q, QElemType e)
            {
                // 队列满的判断
                if ((Q->rear + 1) % MAX_SIZE == Q->front)
                {
                    return ERROR;
                }
                // 将元素e赋值给队尾
                Q->data[Q->rear] = e;
                // rear指针向后移一位置，若到最后则转到数组头部
                Q->rear = (Q->rear + 1) % MAX_SIZE;
                return OK;
            }
        ```
        (8)循环队列的出队列操作：
        ```c
            /* 若队列不空，则删除Q中队头元素，用e返回其值 */
            Status DeQueue(SqQueue *Q, QElemType *e)
            {
                // 队列空的判断
                if (Q->front == Q->rear)
                {
                    return ERROR;
                }
                // 将队头元素赋值给e
                *e = Q->data[Q->front];
                // front指针向后移一位置，若到最后则转到数组头部
                Q->front = (Q->front + 1) % MAX_SIZE;
                return OK;
            }
    19、队列的链式存储结构
        (1)队列的链式存储结构，其实就是线性表的单链表，只不过它只能尾进头出而已，简称为链队列。为了操作的方便，将队头指针指向链队列的头结点，而队尾指针指向终端结点。空队列时，front和rear都指向头结点。
        (2)链队列的结构：
        ```c
            /* QElemType类型根据实际情况而定，这里假设为int */
            typedef int QElemType;
            /* 结点结构 */
            typedef struct QNode
            {
                QElemType data;
                struct QNode *next;
            } QNode, *QueuePtr;
            /* 队列的链表结构 */
            typedef struct
            {
                // 队头指针
                QueuePtr front;
                // 队尾指针
                QueuePtr rear;
            } LinkQueue;
        ```
        (3)链队列的入队操作：就是在链表尾部插入结点。
        ```c
            /* 插入元素e为Q的新的队尾元素 */
            Status EnQueue(LinkQueue *Q, QElemType e)
            {
                QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
                // 存储分配失败
                if (!s)
                {
                    exit(0);
                }
                s->data = e;
                s->next = NULL;
                // 把拥有元素e新结点s赋值给原队尾结点的后继
                Q->rear->next = s;
                // 把当前的s设置为队尾结点，rear指向s
                Q->rear = s;
                return OK;
            }
        ```
        (4)链队列的出队操作
            思路：出队操作时，就是头结点的后继结点出队，将头结点的后继改为它后面的结点，若链表除头结点外只剩一个元素时，则需将rear指向头结点。
            实现代码：
            ```c
                /* 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
                Status DeQueue(LinkQueue *Q, QElemType *e)
                {
                    QueuePtr p;
                    // 如果是空队列
                    if (Q->front == Q->rear)
                    {
                        return ERRROR;
                    }
                    // 将欲删除的对头结点暂存给p
                    p = Q->front->next;
                    // 将欲删除的队头结点的值赋值给e
                    *e = p->data;
                    // 将原队头结点后继p->next赋值给头结点后继
                    Q->front->next = p->next;
                    // 若对头是队尾，则删除后将rear指向头结点
                    if (Q->rear == p)
                    {
                        Q->rear = Q->front;
                    }
                    free(p);
                    return OK;
                }
            ```
        (5)总的来说，在可以确定那个队列长度最大值的情况下，建议用循环队列，如果你无法预估队列的长度时，则用链队列。
## 四、串
    1、串(string)是由零个或多个字符组成的有限序列，又名叫字符串。
        零个字符的串称为空串(null string),长度为零。所谓的序列，说明串的相邻字符之间具有前驱和后继的关系。
    2、对于两个串不相等时的大小判定：
        给定两个串：s = "a1a2...an"，t = "b1b2...bm",当满足以下条件之一时，s<t。
        (1)n < m，且ai = bi(i = 1, 2, ..., n)
        (2)存在某个k <= min(m, n)，使得ai = bi(i = 1, 2, ..., k-1)，ak < bk。
    3、串的抽象数据类型
        ADT 串(string)
        Data
            串中元素仅由一个字符组成，相邻元素具有前驱和后继关系。
        Operation
            StrAssign(T, *chars)：生成一个其值等于字符串常量chars的串T。
            StrCopy(T, S)：串S存在，由串S复制得串T。
            ClearString(S)：串S存在，将串清空。
            StringEmpty(S)：若串S为空，返回true，否则返回false。
            StrLength(S)：返回串S的元素个数，即串的长度。
            StrCompare(S, T)：若S > T，返回值>0，若S = T，返回0，若S < T，返回值<0。
            Concat(T, S1, S2)：用T返回由S1和S2联接而成的新串。
            SubString(Sub, S, pos, len)：串S存在，1<=pos<=StrLength(S)，且0<=len<=StrLength(S)-pos+1，用Sub返回串S的第pos个字符起长度为len的子串。
            Index(S, T, pos)：串S和T存在，T是非空串，1<=pos<=StrLength(S)。若主串S中存在和串T值相同的子串，则返回它在主串S中第pos个字符之后第一次出现的位置，否则返回0。
            Replace(S, T, V)：串S、T和V存在，T是非空串。用V替换主串S中出现的所有与T相等的不重叠的子串。
            StrInsert(S, pos, T)：串S和T存在，1<=pos<=StrLength(S)+1。在串S的第pos个字符之前插入串T。
            StrDelete(S, pos, len)：串S存在。1<=pos<=StrLength(S)-len+1。从串S中删除第pos个字符起长度为len的子串。
        end ADT
    4、Index的实现算法(暴力匹配)：
        ```c
            /* 若T为非空串。若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置，否则返回0 */
            int Index(String S, String T, int pos)
            {
                int n, m , i;
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
                        // 取主串第i个位置长度与T相等的子串给sub
                        SubString(sub, S, i, m);
                        // 如果两串不相等
                        if (StrCompare(sub, T) != 0)
                        {
                            i++;
                        }
                        // 如果两串相等，则返回i值
                        else
                        {
                            return i;
                        }
                    }
                }
                // 若无子串与T相等，返回0
                return 0;
            }
        ```
    5、串的顺序存储结构：直接看实现代码。
    6、串的链式存储结构：串的链式存储结构相对顺序存储结构来说不够灵活，性能也不如顺序存储结构好。
    7、朴素的模式匹配算法
        前面已经用串的其他操作实现了模式匹配的算法Index。现在考虑不用串的其他操作，而是只用基本的数组来实现同样的算法。注意，我们假设主串S和压迫匹配的子串T的长度存在S[0]和T[0]中。实现代码如下：
        ```c
            /* 返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0 */
            /* T非空，1<=pos<=StrLength(S)。 */
            int Index(String S, String T, int pos)
            {
                // i用于主串S中当前位置下标，若pos不为1，则从pos位置开始匹配
                int i = pos;
                // j用于子串T中当前位置的下标值
                int j = 1;
                // 若i小于等于S长度且j小于等于T的长度时循环
                while (i <= S[0] && j <= T[0])
                {
                    // 两字母相等则继续
                    if (S[i] == T[i])
                    {
                        i++;
                        j++;
                    }
                    // 指针后退重新开始匹配
                    else
                    {
                        // i退回到上次匹配首位的下一位
                        i = i - j + 2;
                        // j退回到子串T的首位
                        j = 1;
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
        ```
    8、KMP模式匹配算法
    ```c
        /* 通过计算返回子串T的next数组。 */
        void get_next(String T, int *next)
        {
            int i, j;
            i = 1;
            j = 0;
            // 注意：next[0]不存任何元素，当然也可以用来存长度
            next[1] = 0;
            // 此处T[0]表示串T的长度
            while (i < T[0])
            {
                // T[i]表示后缀的单个字符
                // T[j]表示前缀的单个字符
                if (j == 0 || T[i] == T[j])
                {
                    i++;
                    j++;
                    next[i] = j;
                }
                else
                {
                    // 若字符不相同，则j值回溯
                    j = next[j];
                }  
            }
        }
        /* 返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0。 */
        /* T非空，1<=pos<=StrLength(S) */
        int Index_KMP(String S, String T, int pos)
        {
            // i用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配
            int i = pos;
            // j用于子串T中当前位置下标值
            int j = 1;
            // 定义一个next数组
            int next[255];
            // 对T作分析，得到next数组
            get_next(T, next);
            // 若i小于S的长度且j小于T的长度时，循环继续
            while (i <= S[0] && j <= T[0])
            {
                // 两字母相等则继续判断，与朴素算法相比增加了一个j==0的判断
                if (j == 0 || S[i] == T[j])
                {
                    i++;
                    j++;
                }
                // 不相等则指针后退重新开始匹配
                else
                {
                    // j退回到合适的位置，i值不变
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
    ```
    注意：KMP算法仅当模式与主串之间存在许多“部分匹配”的情况下才体现出他的优势，否则两者差异并不明显。
    9、KMP模式匹配算法改进：将get_next函数进行改良，使用nextval来取代next
    改进代码：
    ```c
        /* 求模式串T的next函数修正值并存入数组nextval */
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
                    // 若当前字符与前缀字符不同，则当前的j为nextval在i位置的值
                    if (T[i] != T[j])
                    {
                        nextval[i] = j;
                    }
                    // 如果与前缀字符相同，则将前缀字符的nextval值赋给nextval在i位置的值
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
        实际匹配算法就只需要将"get_next(T, next);"改为"get_nextval(T, next);"即可。
        总结改进过的KMP算法，它是在计算出next值得同时，如果a位字符与它的next值指向的b位字符相等，则将该a位的nextval就指向b位的nextval值，如果不等，则该a位得nextval值就是它自己a位得next的值。
    ```
## 五、树
    1、树的定义：树(Tree)是n(n>=0)个结点的有限集。n=0时称为空树。在任意一棵非空树中：
        (1)有且仅有一个特定的称为根(Root)的结点；
        (2)当n>1时，其余结点可分为m(m>0)个互不相交的有限集T1、T2、...、Tm，其余每一个集合本身又是一棵树，并且称为根的子树(SubTree)。
    注意：(1)当n>0时根节点是唯一的，不可能存在多个根节点。
        (2)m>0时，子树的个数没有限制，但它们一定是互不相交的。
    2、结点分类：树的结点包含一个数据元素及若干指向其子树的分支。结点拥有的子树数称为结点的度(Degree)。度为0的结点称为叶结点(Leaf)或终端结点；度不为0的结点称为非终端结点或分支结点。除根节点外，分支结点也称为内部结点。树的度是树内各节点的度的最大值。
    3、结点间关系：结点的子树的根称为该结点的孩子(Child)，相应地，该结点称为孩子的双亲(Parent)。同一个双亲的孩子之间互称兄弟(Sibling)。结点的祖先是从根到该结点所经分支上的所有结点。反之，以某结点为根的子树中的任一结点都称为该结点的子孙。
    4、树的其他相关概念：
        (1)结点的层次(Level)从根开始定义起，根为第一层，根的孩子为第二层。若某一结点在第l层，则其子树的根就在第l+1层。其双亲在同一层的结点互为堂兄弟。树中结点的最大层次称为树的深度(Depth)或高度。
        (2)如果将树种结点的各子树看成从左至右是有次序的，不能互换的，则称该树为有序树，否则称为无序树。
        (3)森林(Forest)是m(m>=0)棵互不相交的树的集合。对树中每个结点而言，其子树的集合即为森林。
    5、线性结构和树结构的区别：
        线性结构：第一个数据元素：无前驱；
                最后一个数据元素：无后继；
                中间元素：一个前驱一个后继。
        树结构：根节点：无双亲，唯一；
                叶结点：无孩子，可以多个；
                中间结点：一个双亲多个孩子。
    6、树的抽象数据类型：
        ADT 树(tree)
        Data
            树是由一个根节点和若干棵子树构成。树中结点具有相同数据类型及层次关系。
        Operation
            InitTree(*T)：构造空树T。
            DestroyTree(*T)：销毁树T。
            CreateTree(*T, definnition)：按definition中给出树的定义来构造树。
            ClearTree(*T)：若树T存在，则将树T清为空树。
            TreeEmpty(T)：若T为空树，返回true，否则返回false。
            TreeDepth(T)：返回T的深度。
            Root(T)：返回T的根节点。
            Value(T, cur_e)：cur_e是树T中的一个结点，返回此结点的值。
            Assign(T, cur_e, value)：给树T的结点cur_e赋值为value。
            Parent(T, cur_e)：若cur_e是树T的非根节点，则返回它的双亲，否则返回空。
            LeftChild(T, cur_e)：若cur_e是树T的非叶结点，则返回它的最左孩子，否则返回空。
            RightSibling(T, cur_e)：若cur_e有有右兄弟，则返回它的右兄弟，否则返回空。
            InsertChild(*T, *p, i, c)：其中p指向树T的某个结点，i为所指结点p的度加上1，非空树c与T不相交，操作结果为插入c为树T中p指结点的第i棵子树。
            DeleteChild(*T, *p, i)：其中p指向树T的某个结点，i为所指结点p的度，操作结果为删除T中p所指结点的第i棵子树。
        end ADT
    7、树的存储结构：利用顺序存储结构和链式存储结构的特点实现树的存储结构表示。三种表示方法：双亲表示法、孩子表示法、孩子兄弟表示法。
    8、双亲表示法：假设以一组连续空间存储树的结点，同时在每个结点这种，附设一个指示器指示其双亲结点在链表中的位置。其中data是数据域，存储结点的数据信息。而parent是指针域，存储该结点的双亲在数组中的下标。
    ```c
        /* 树的双亲表示法结点结构定义 */
        #define MAX_TREE_SIZE 100
        // 树结点的数据类型，目前暂定为为整型
        typedef int TElemType;
        /* 结点结构 */
        typedef struct PTNode
        {
            // 结点数据
            TElemType data;
            // 双亲位置
            int parent;
        } PTNode;
        /* 树结构 */
        typedef struct
        {
            // 结点数组
            PTNode nodes[MAX_TREE_SIZE];
            // 根的位置
            int r;
            // 结点数
            int n;
        } PTree;
    ```
    由于根节点是没有双亲的，所以约定根节点的位置域设置为-1，也就意味着所有的结点都存有它双亲的位置。
    9、孩子表示法：把每个结点的孩子结点排列起来，以单链表作为存储结构，则n个结点有n个孩子链表，如果是叶子结点则此单链表为空。然后n个头指针又构成一个线性表，采用顺序存储结构，存放进一个一位数组中。
    因此设计两种结点结构，一个是孩子链表的孩子结点，其中data是数据域，用来存储某个结点在表头数组中的下标。next是指针域，用来存储指向某结点的下一个孩子结点的指针。另一个是表头数组的表头结点，其中data是数据域，存储某结点的数据信息。firstchild是头指针域，存储该结点的孩子链表的头指针。
    ```c
        /* 树的孩子表示法结构定义 */
        #define MAX_TREE_SIZE 100
        /* 孩子结点 */
        typedef struct CTNode
        {
            int child;
            struct CTNode *next;
        } *ChildPtr;
        /* 表头结构 */
        typedef struct
        {
            TElemType data;
            ChildPtr firstchild;
        } STBox;
        /* 树结构 */
        typedef struct
        {
            // 结点数组
            CTBox nodes[MAX_TREE_SIZE];
            // 根的位置
            int r;
            // 结点数
            int n;
        } CTree;
    ```
    10、孩子兄弟表示法：任意一棵树，它的结点的第一个孩子如果存在就是唯一的，它的右兄弟如果存在也是唯一的。因此，我们设置两个指针，分别指向该结点的第一个孩子和此结点的右兄弟。其中data是数据域，firstchild为指针域，存储该结点的第一个孩子结点的存储地址，rightsib是指针域，存储该结点的右兄弟结点的存储地址。
    ```c
        /* 树的孩子兄弟表示法结构定义 */
        typedef struct CSNode
        {
            TElemType data;
            struct CSNode *firstchild;
            struct CSNode *rightsib;
        } CSNode, *CSTree;
    ```
    这个表示法的最大好处是它把一棵复杂的树变成了一棵二叉树。这样就可以充分利用二叉树的特性和算法来处理这棵树了。
    11、二叉树的定义：二叉树(Binary Tree)是n(n>=0)个结点的有限集合，该集合或者为空集(称为空二叉树)，或者由一个根节点和两棵互不相交的、分别称为根节点的左子树和右子树的二叉树组成。
    12、二叉树的特点：
        (1)每个结点最多有两棵子树，所以二叉树中不存在度大于2的结点。注意不是只有两棵子树，而是最多有。没有子树或者有一棵子树也是可以的。
        (2)左子树和右子树是由顺序的，次序不能颠倒。
        (3)即使树中某结点只有一棵子树，也要区分它是左子树还是右子树。
    13、二叉树具有五种基本形态：
        (1)空二叉树。
        (2)只有一个根节点。
        (3)根节点只有左子树。
        (4)根节点只有右子树。
        (5)根节点既有左子树又有右子树。
    14、特殊二叉树：
        (1)斜树：顾名思义，斜树一定要是斜的。所有的结点都只有左子树的二叉树叫左斜树。所有结点都是只有右子树的二叉树叫右斜树。这两者统称为斜树。斜树很明显的特点就是每一层只有一个结点，结点的个数与二叉树的深度相同。
        线性表结构其实就可以理解为一种极其特殊的树的表现形式。
        (2)满二叉树：在一棵二叉树中，如果所有分支结点都存在左子树和右子树，并且所有叶子都在同一层上，这样的二叉树称为满二叉树。
        满二叉树的特点：
            叶子只能出现在最下一层。出现在其他层就不可能达成平衡；
            非叶子结点的度一定是2；
            在同样深度的二叉树中，满二叉树的结点个数最多，叶子数最多。
        (3)完全二叉树：对一棵具有n个结点的二叉树按层序编号，如果编号为i(1<=i<=n)的结点与同样深度的满二叉树中编号为i的结点在二叉树这种位置完全相同，则这棵二叉树称为完全二叉树。
        满二叉树一定是一棵完全二叉树，但完全二叉树不一定是满的。
        满二叉树的特点：
            叶子结点只能出现在最下两层；
            最下层的叶子一定集中在左部连续位置；
            倒数二层，若有叶子结点，一定都在右部连续位置；
            如果结点度为1，则该结点只有左孩子，即不存在只有右子树的情况；
            同样结点数的二叉树，完全二叉树的深度最小。
        判断某二叉树是否是完全二叉树的方法：就是看着树的示意图，心中默默给每个结点按照满二叉树的结构逐层顺序编号，如果编号出现空挡，则说明不是完全二叉树，否则就是。
    15、二叉树性质(需要理解并记住)：
        (1)在二叉树的第i层至多有2^(i-1)个结点(i>=1)。
        (2)深度为k的二叉树至多有2^k-1个结点(k>=1)。
        (3)对任何一棵二叉树T，如果其终端结点数为n0，度为2的结点数为n2，则n0=n2+1。
        (4)具有n个结点的完全二叉树的深度为[log2n(这里是log以2为底n的对数))]+1，这里的[x]表示不大于x的最大整数。
        (5)如果对一棵有n个结点的完全二叉树(其深度为[log2n]+1)的结点按层序编号(从第1层到第[log2n]+1层，每层从左到右)，对任一结点i(1<=i<=n)有：
            如果i=1，则结点i是二叉树的根，无双亲；如果i>1，则其双亲是结点[i/2]；
            如果2i>n，则结点i无左孩子(结点i为叶子结点)；否则其左孩子是结点2i；
            如果2i+1>n，则结点i无右孩子；否则其右孩子是结点2i。
    16、二叉树的顺序存储结构：一般只用于完全二叉树。
    17、二叉链表：二叉树每个结点最多有两个孩子，所以为它设计一个数据域和两个指针域，称这样的链表叫做二叉链表。其中data是数据域，lchild和rchild都是指针域，分别存放指向左孩子和右孩子的指针。
    ```c
        /* 二叉树的二叉链表结点结构定义 */
        /* 结点结构 */
        typedef struct BiTNode
        {
            // 结点数据
            TElemType data;
            // 左孩子指针
            struct BiTNode *lchild;
            // 右孩子指针
            struct BiTNode *rchild;
        } BiTNode, *BiTree;
    ```
    如果有需要还可以增加一个指向其双亲的指针域，那样就称为三叉链表。
    18、遍历二叉树：二叉树的遍历(traversing binary tree)是指从根节点出发，按照某种次序依次访问二叉树中所有结点，使得每个结点被访问一次且仅被访问一次。
    19、二叉树的遍历方法：
        (1)前序遍历：规则是若二叉树为空，则空操作返回，否则先访问根节点，然后前序遍历左子树，再前序遍历右子树。
        (2)中序遍历：规则是若二叉树为空，则空操作返回，否则从根节点开始(注意并不是先访问根节点)，中序遍历根节点的左子树，然后访问根节点，最后中序遍历右子树。
        (3)后续遍历：规则是若二叉树为空，则空操作返回，否则从左到右先叶子后结点的方式遍历访问左右子树，最后是访问根节点。
        (4)层序遍历：规则是若二叉树为空，则空操作返回，否则从树的第一层，也就是根节点开始访问，从上而下逐层遍历，在同一层中，按从左到右的顺序对结点逐个访问。
    20、前序遍历算法：
    ```c
        /* 二叉树的前序遍历递归算法 */
        void PreOrderTraverse(BiTree T)
        {
            if (T == NULL)
            {
                return;
            }
            // 显示结点数据，可以更改为其他对结点的操作
            printf("%c", T->data);
            // 再前序遍历左子树
            PreOrderTraverse(T->lchild);
            // 最后前序遍历右子树
            PreOrderTraverse(T->rchild);
        }
    ```
    21、中序遍历算法：
    ```c
        /* 二叉树的中序遍历递归算法 */
        void InOrderTraverse(BiTree T)
        {
            if (T == NULL)
            {
                return;
            }
            // 先中序遍历左子树
            InOrderTraverse(T->lchild);
            // 显示结点数据，可以更改为其他对结点的操作
            printf("%c", T->data);
            // 最后中序遍历右子树
            InOrderTraverse(T->rchild);
        }
    ```
    22、后序遍历算法：
    ```c
        /* 二叉树的后序遍历递归算法 */
        void PostOrderTraverse(BiTree T)
        {
            if (T == NULL)
            {
                return;
            }
            // 先后序遍历左子树
            PostOrderTraverse(T->lchild);
            // 然后后后序遍历右子树
            PostOrderTraverse(T->rchild);
            // 显示结点数据，可以更改为其他对结点的操作
            printf("%c", T->data);
        }
    ```
    23、已知前序遍历序列和中序遍历序列，可以唯一确定一棵二叉树；
        已知后序遍历序列和中序遍历序列，可以唯一确定一棵二叉树。
    24、二叉树的建立：将二叉树的每个结点的空指针引出一个虚结点，其值为一个特定值，比如“#”。我们称这种处理后的二叉树为原二叉树的扩展二叉树。这样扩展二叉树就可以做到一个遍历序列确定一棵二叉树了。
    ```c
        /* 按前序输入二叉树中结点的值(一个字符) */
        /* #表示空树，构造二叉链表表示二叉树T */
        void CreateBiTree(BiTree *T)
        {
            TElemType ch;
            scanf("%c", &ch);
            if (ch == '#')
            {
                *T = NULL;
            }
            else
            {
                *T = (BiTree)malloc(sizeof(BiTNode));
                if (!*T)
                {
                    printf("内存分配失败。\n");
                    exit(0);
                }
                // 生成根节点
                (*T)->data = ch;
                // 构造左子树
                CreateBiTree(&(*T)->lchild);
                // 构造右子树
                CreateBiTree(&(*T)->rchild);
            }
        }
    ```
    当然也可以用中序或者后序遍历的方式实现二叉树的建立，只不过代码里生成结点和构造左右子树的代码顺序交换一下。另外，输入的字符也要做相应的更改。
    25、(1)线索二叉树：利用那些空的指针域来存放指向结点在某种遍历次序下的前驱和后继结点的地址。把指向前驱和后继的指针称为线索，加上线索的二叉链表称为线索链表，相应的二叉树就称为线索二叉树(Threaded Binary Tree)。
        将所有空指针域中的rchild改为指向当前结点的后继。
        将所有空指针域中的lchild改为指向当前结点的前驱。
        其实线索二叉树等于是把一棵二叉树转变成了一个双向链表。
        (2)线索化：对二叉树以某种次序遍历使其变为线索二叉树的过程称做是线索化。
        (3)为了知道某一结点的lchild和rchild是指向它们的左右孩子还是指向前驱或者后继呢。需要再增设两个标志域LTag和rtag。
            其中：LTag为0时指向该结点的左孩子，为1时指向该结点的前驱；
                rtag为0时指向该结点的右孩子，为1时指向该结点的后继。
        (4)线索二叉树的结构实现：
        ```c
            /* 二叉树的二叉线索存储结构定义 */
            // Link==0，表示指向左右孩子指针
            // Thread==1，表示指向前驱或后继的线索
            typedef enum {Link, Thread} PointerTag;
            typedef struct BiThrNode
            {
                // 结点数据
                TElemType data;
                // 左右孩子指针
                struct BiThrNode *lchild, *rchild;
                // 左右标志
                PointerTag LTag, RTag;
            } BiThrNode, *BiThrTree;
        ```
        由于前驱和后继的信息只有在遍历该二叉树的时候才能得到，所以线索化的过程就是在遍历的过程中修改空指针的过程。
        (5)中序遍历线索化：
        注意：这段代码其实是不完整的，运行会因为pre未初始化数据会报错。正确的应该是将树的头结点赋值给pre。详细看实现代码。
        ```c
            // 全局变量，始终指向刚刚访问过的结点
            BiThrTree pre;
            /* 中序遍历进行中序线索化 */
            void InThreading(BiThrTree p)
            {
                if (p)
                {
                    // 递归左子树线索化
                    InThreading(p->lchild);
                    // 没有左孩子
                    if (!p->lchild)
                    {
                        // 前驱线索
                        p->LTag = Thread;
                        // 左孩子指针指向前驱
                        p->lchild = pre;
                    }
                    // 前驱没有右孩子
                    if (!pre->rchild)
                    {
                        // 后继线索
                        pre->RTag = Thread;
                        // 前驱右孩子指针指向后继(当前结点p)
                        pre->rchild = p;
                    }
                    // 保持pre指向p的前驱
                    pre = p;
                    // 递归右子树线索化
                    InThreading(p->rchild);
                }
            }
        ```
        和双向链表一样，在二叉树线索链表上添加一个头结点，并令其lchild域的指针指向二叉树的根节点，其rchild域的指针指向中序遍历时访问的最后一个结点。令二叉树的中序序列中的第一个结点的lchild域指针和最后一个结点的rchild域指针均指向头结点。这样既可以从第一个结点其顺后继进行遍历，也可以从最后一个结点起顺前驱进行遍历。
        (6)遍历的代码实现：
        ```c
            /* T指向头结点，头结点左链lchild指向根节点，头结点右链rchild指向中序遍历的最后一个结点。 */
            /* 中序遍历二叉线索链表表示的二叉树T */
            int InOrderTraverse_Thr(BiThrTree T)
            {
                BiThrTree p;
                // p指向根结点
                p = T->lchild;
                // 空树或遍历结束时，p==T
                while (p != T)
                {
                    // 当LTag==0时循环到中序序列的第一个结点
                    while (p->LTag == Link)
                    {
                        p = p->lchild;
                    }
                    // 显示结点数据，可以更改为其他对结点的操作
                    printf("%c", p->data);
                    while (p->RTag == Thread && p->rchild != T)
                    {
                        p = p->rchild;
                        printf("%c", p->data);
                    }
                    // p进至其右子树根
                    p = p->rchild;
                }
                return OK;
            }
        ```
        从代码可以看出，等于时一个链表的扫描，所以时间复杂度为O(n)。
        在实际问题中，如果所用的二叉树需要经常遍历或者查找结点时需要某种遍历序列中的前驱和后继，那么采用线索二叉树的存储结构就是非常不错的选择。
    26、树、森林与二叉树的转换：
        (1)将树转换为二叉树的步骤：
            a.加线。在所有兄弟结点之间加一条连线；
            b.去线。对树中每个结点，只保留与它第一个孩子结点的连线，删除它与其他孩子结点之间的连线。
            c.层次调整。以树的根节点为轴心，将整棵树顺时针旋转一定的角度，使之结构层次分明。注意第一个孩子是二叉树结点的左孩子，兄弟转换过来的孩子是结点的右孩子。
        (2)森林转换为二叉树：森林是由若干棵树组成的，完全可以理解为，森林中每一棵树都是兄弟，可以按照兄弟的处理办法来操作：
            a.把每棵树转换为二叉树。
            b.第一棵二叉树不动，从第二棵二叉树开始，依次把后一棵二叉树的根节点作为前一棵二叉树根节点的右孩子，用线连起来，当所有二叉树连接起来后就得到了由森林转换来的二叉树。
        (3)二叉树转换为树：就是树转换为二叉树的逆过程：
            a.加线。若某结点的左孩子结点存在，则将这个左孩子的右孩子结点、右孩子的右孩子结点、右孩子的右孩子的右孩子结点...，反正就是左孩子的n个右孩子结点都作为此结点的孩子。将该结点与这些右孩子结点用线连接起来。
            b.去线。删除原二叉树中所有结点与其右孩子结点的连线。
            c.层次调整。使之结构层次分明。
        (4)二叉树转换为森林：判断一棵二叉树能够转换成一棵树还是森林，标准很简单，就是只要看这颗二叉树的根节点有没有右孩子，有就是森林，没有就是一棵树。步骤如下：
            a.从根结点开始，若右孩子存在，则把与右孩子结点的连线删除，再查看分离后的二叉树，若右孩子存在，则重复上面的过程，直到把所有右孩子连线都删除为止，得到分离的二叉树。
            b.再将每棵分离后的二叉树转换为树即可。
    27、树与森林的遍历：
        (1)树的遍历分为两种：
            a.先根遍历，即先访问树的根节点，然后依次先根遍历根的每棵子树。
            b.后根遍历：即先依次后根遍历每棵子树，然后再访问根节点。
        (2)森林的遍历分为两种：
            a.前序遍历：先访问森林中第一棵树的根节点，然后再依次先根遍历根的每棵子树，再依次用同样的方法遍历除去第一棵树的剩余树构成的森林。
            b.后序遍历：先访问森林中第一棵树，后根遍历的方式遍历每棵子树，然后再访问根节点，再依次同样方式遍历除去第一棵树的剩余树构成的1森林。
            结论：森林的前序遍历和二叉树的前序遍历结果相同，森林的后序遍历和二叉树的中序遍历结果相同。
    28、赫夫曼树：
        (1)赫夫曼大叔说，从树中一个结点到另一个结点之间的分支构成两个结点之间的路径，路径上的分支数目称作路径长度。
        (2)树的路径长度就是从树根到每一结点的路径长度之和。
        (3)如果考虑带权的结点，结点的带权的路径长度就是从该结点到树根之间的路径长度与结点上权的乘积。树的带权路径长度为树中所有叶子结点的带权路径长度之和。
        (4)将带权路径长度WPL最小的二叉树就称作赫夫曼树(也叫最优二叉树)。
        (5)构造赫夫曼树的算法描述：
            a.根据给定的n个权值{w1,w2,...,wn}构成n棵二叉树的集合F={T1,T2,...,Tn}，其中每棵二叉树Ti中只有一个带权为wi根节点，其左右子树均为空。
            b.在F中选取两棵根节点的权值最小的树作为左右子树构造一棵新的二叉树，且置新的二叉树的根节点的权值为其左右子树上根节点的权值之和。
            c.在F中删除这两棵树，同时将新得到的二叉树加入F中。
            d.重复bc步骤，直到F只含一棵树为止。这棵树便是赫夫曼树。
    29、赫夫曼编码：一般地，设需要编码的字符集为{d1,d2,...,dn}，各个字符在电文中出现的次数或频率集合为{w1,w2,w3...,wn}，以d1,d2,...,dn作为叶子结点，以w1,w2,...,wn作为相应叶子结点的权值来构造一棵赫夫曼树。规定赫夫曼树的左分支代表0，右分支代表1，则从根节点到叶子结点所经过的路径分支组成的0和1的序列便为该结点对应字符的编码，这就是赫夫曼编码。
## 六、图
    1、图的定义：图(Graph)是由顶点的有穷非空集合和顶点之间边的集合组成，通常表示为：G(V, E)，其中，G表示一个图，V是图G中顶点的集合，E是图G中边的集合。
    2、关于图的定义需要注意的地方：
        (1)线性表中我们把数据元素叫元素，树中将数据元素叫结点，载图中数据元素，我们则称之为顶点(Vertex)。
        (2)线性表中可以没有数据元素，称为空表。树中可以没有结点，叫做空树。而在图结构中，不允许没有顶点。在定义中，若V是顶点的集合，则强调了顶点集合V有穷非空。
        (3)线性表中,相邻的数据元素之间具有线性关系，树结构中，相邻两层的结点具有层次关系，而图中，任意两个顶点之间都可能有关系，顶点之间的逻辑关系用边来表示，边集可以是空的。
    3、各种图的定义：
        (1)无向边：若顶点vi到vj之间的边没有方向，则称这条边为无向边(Edge)，用无序偶对(vi, vj)来表示(由于无序反过来写也行)。如果图中任意两个顶点之间的边都是无向边，则称该图为无向图(Undirevted graphs)。
        (2)有向边：若从顶点vi到vj的边有方向，则称这条边为有向边，也成为弧(Arc)。用有序偶对<Vi, vj>来表示，vi称为弧尾(Tail)，vj称为弧头(Head)。如果图中任意两个顶点之间的边都是有向边，则称该图为有向图(Directed graphs)。
        看清楚了，无向边用小括号表示，有向边用尖括号表示。
        (3)在图中，若不存在顶点到其自身的边，且同一条边不重复出现，则称这样的图为简单图。(接下来学习讨论的都是简单图)
        (4)在无向图中，如果任意两个顶点之间都存在边，则称该图为无向完全图。含有n个顶点的无向完全图有n*(n-1)/2条边。
        (5)在有向图中，如果任意两个顶点之间都存在方向互为相反的两条弧，则称该图为有向完全图。含有n个顶点的有向完全图有n*(n-1)条边。
        因此可以得出结论：对于具有n个顶点和e条边数的图，无向图0<=e<=n*(n-1)/2，有向图0<=e<=n*(n-1)。
        (6)有很少条边或弧的图称为稀疏图，反之称为稠密图。这里的稀疏和稠密是模糊的概念，都是相对而言的。
        (7)有些图的边或弧具有与它相关的数字，这种与图的边或弧相关的数叫做权(Weight)。这些权可以表示从一个顶点到另一个顶点的距离或耗费。这种带权的图通常称为网(Network)。
        (8)假设有两个图G=(V, {E})和G'=(V', {E'})，如果V'包含于于V且E'包含于E，则称G'为G的子图(Subgraph)。
    4、图的顶点与边之间的关系：
        (1)对于无向图G=(V, {E})，如果边(v, v')属于E，则称顶点v和v'互为邻接点(Adjacent)，即v和v'相邻接。边(v, v')依附(incident)于顶点v和v'，或者说(v, v')与顶点v和v'相关联。顶点v的度(Degree)是和v相关联的边的数目，记为TD(v)。
        观察可得出结论：无向图中的边数e其实就是各顶点度数和的一半，多出的一半是因为重复两次计数。
        (2)对于有向图G=(V, {E})，如果弧<v, v'>属于E，则称顶点v邻接到顶点v'，顶点v'邻接自顶点v。弧<v, v'>和顶点v, v'相关连。以顶点v为头的弧的数目称为v的入度(InDegree)，记为ID(v)；以v为尾的弧的数目称为v的出度(OutDegree)，记为OD(v)；顶点v的度尾TD(v)=ID(v)+OD(v)。
        结论：有向图中的边数e等于各顶点的出度和，也等于各顶点的入读和。
    5、路径的长度是路径上的边或弧的数目。第一个顶点到最后一个顶点相同的路径称为回路或环(Cycle)。序列中顶点不重复出现的路径称为简单路径。除了第一个顶点和最后一个顶点之外，其余顶点不重复出现的回路，称之为简单回路或简单环。
    6、连通图：在无向图G中，如果从顶点v到顶点v'有路径，则称v和v'是连通的。如果对于图中任意两个顶点vi、vj属于E，vi和vj都是连通的，则称G是连通图(Connected Graph)。
        (1)无向图中的极大连通子图称为连通分量。注意连通分量的概念，它强调：
            a.要是子图；
            b.子图要是连通的；
            c.连通子图含有极大顶点数；
            d.具有极大顶点数的连通子图包含依附于这些顶点的所有边。
        (2)在有向图G中，如果对于每一对vi、vj属于V，vi≠vj，从vi到vj和从vj到vi都存在路径，则称G是强连通图。有向图中的极大强连通子图称作有向图的强连通分量。(注意抄写这个概念时教材的图是有错的，220页图1和图2的AB之间的箭头指向画反了)
    7、连通图的生成树：所谓的一个连通图的生成树是一个极小的连通子图，它含有图中全部的n个顶点，但只有足以构成一颗树的n-1条边。
    8、如果一个有向图恰有一个顶点的入度为0，其余顶点的入度均为1，则是一棵有向树。所谓入度为0其实就像相当于树中的根结点，其余顶点入度为1就是说树的非根结点的双亲只有一个。一个有向图的生成森林由若干棵有向树组成，含有图中全部顶点，但只有足以构成若干棵互不相交的有向树的弧。
    9、图的抽象数据类型：
        ADT 图(Graph)
        Data
            顶点的有穷非空集合和边的集合
        Operation
            CreateGraph(*G, V, VR)：按照顶点集V和边弧集VR的定义构造图G。
            DestroyGraph(*G)：图G存在则销毁。
            LocateVex(G, u)：若G中存在顶点u则返回在图中的位置。
            GetVex(G, v)：返回图G中顶点v的值。
            PutVex(G, v, value)：将图G中顶点v赋值value。
            FirstAdjVex(G, *v)：返回顶点v的一个邻接顶点，若顶点在G中无邻接顶点返回空。
            NextAdjVex(G, v, *w)：返回顶点v相对于顶点w的下一个邻接顶点，若w是v的最后一个邻接点则返回“空”。
            InsertVex(*G, v)：在图G中增添新顶点v。
            DeleteVex(*G, v)：删除图G中顶点v及其相关的弧。
            InsertArc(*G, v, w)：在图G中增添弧<v, w>，若图G是无向图，还需要增添对称弧<w, v>。
            DeleteArc(*G, v, w)：在图G中删除弧<v, w>，若G是无向图，泽海删除对称弧<w, v>。
            DFSTraverse(G)：对图G中进行深度优先遍历，在遍历过程中对每个顶点调用。
            HFSTraverse(G)：对图G中进行广度优先遍历，在遍历过程中对每个顶点调用。
        end ADT
    10、图的存储结构：
        (1)邻接矩阵：图的邻接矩阵(Adjacency Matrix)存储方式是用两个数组来表示图。一个一维数组存储图中顶点信息，一个二维数组(称为邻接矩阵)存储图中的边或弧的信息。
            a.设图G有n个顶点，则邻接矩阵是一个n*n的方阵，定义为：
                arc[i][j] = 
                    1(若(vi, vj)∈E或<vi, vj>∈E)
                    0(反之)。
            b.无向图的边数组是一个对称矩阵。所谓对称矩阵就是n阶矩阵的元满足a(ij)=a(ji)，(0<=i,j<=n)。即从矩阵的左上角到右下角的主对角线为轴，右上角的元与左下角相对应的元全都是相等的。
            c.有了这个矩阵，
                要判定任意两顶点是否有边就很容易了；
                要知道某个顶点的度，其实就是这个顶点vi在邻接矩阵第i行(或第i列的元素之和)；
                求顶点vi的所有邻接点就是将矩阵中第i行元素扫描一遍，arc[i][j]为1就是邻接点。
            d.有向图讲究入度与出度，
                顶点vi的入度正好是第vi列各数之和。顶点vi的出度即第vi行的各数之和；
                判断顶点vi到vj是否存在弧，只需要查找矩阵中arc[i][j]是否为1即可；
                要求vi的所有邻接点就是将矩阵第i行元素扫描一遍，查找arc[i][j]为1的顶点。
            e.网(每条边上带有权的图叫做网)的处理：
                设图G是网图，有n个顶点，则邻接矩阵是一个n*n的方阵，定义为：
                    arc[i][j] = 
                        W(ij)，若(vi, vj)∈E或<vi, vj>∈E
                        0，若i = j
                        ∞，反之
                这里W(ij)表示(vi, vj)或<vi, vj>上的权值。∞表示一个计算机允许的、大于所有边上权值的值，也就是一个不可能的极限值。
            f.图的邻接矩阵存储的结构：
            ```c
                /* 顶点类型应有用户定义 */
                typedef char VertexType;
                /* 边上的权值类型应由用户定义 */
                typedef int EdgeType;
                /* 最大顶点数，应由用户定义 */
                #define MAX_VEX 100
                /* 用65535来表示∞ */
                #define INFINITY 65535
                typedef struct
                {
                    /* 顶点表 */
                    VerTexType vexs[MAX_VEX];
                    /* 邻接矩阵，可看作边表 */
                    EdgeType arc[MAX_VEX][MAX_VEX];
                    /* 图中当前的顶点数和边数 */
                    int numVertexex, numEdges;
                } MGraph;
            ```
            有了结构定义，构造一个图其实就是给顶点表和边表输入数据的过程。下面是无向网图的构建代码。
            ```c
                /* 建立无向网图的邻接矩阵表示 */
                void CreateMGraph(MGraph *G)
                {
                    int i, j, k, w;
                    printf("输入顶点数和边数：\n");
                    // 输入顶点数和边数
                    scanf("%d,%d", &G->numVertexes, &G->numEdges);
                    for (i = 0; i < G->numVertexes; i++)
                    {
                        scanf("%d", &G->vexs[i]);
                    }
                    for (i = 0; i < G->numVertexes; i++)
                    {
                        for (j = 0; j < G->numVertexes; j++)
                        {
                            // 邻接矩阵初始化
                            G->arc[i][j] = INFINITY;
                        }
                    }
                    // 读入numEdges条边，建立邻接矩阵
                    for (k = 0; k < G->numEdges; k++)
                    {
                        printf("输入边(vi, vj)的下标i，下标j和权w：\n");
                        输入边(vi, vj)上的权w
                        scanf("%d,%d,%d", &i, &j, &w);
                        G->arc[i][j] = w;
                        // 因为是无向图，矩阵对称
                        G->arc[j][i] = G->arc[i][j];
                    }
                }
            ```
            从代码中可以得到，n个顶点和e条边的无向网图的创建，时间复杂度为O(n+n²+e)，其中对邻接矩阵G.arc的初始化耗费了O(n²)的时间。
        (2)邻接表：
            a.邻接矩阵对于边数相对顶点较少图，这种结构就存在对存储空间的极大浪费。
            b.类似于树的孩子表示法，将结点存入数组，并对结点的孩子进行链式存储，这同样适用于图的存储。把这种数组与链表相结合的存储方法称为邻接表(Adjacency List)。
            c.邻接表的处理方法：
                图中顶点用一个一维数组存储，当然，顶点也可以用单链表存储，不过数组可以较容易地读取顶点信息，更加方便。另外，对于顶点数组中，每个数据元素还需要存储指向第一个邻接点的指针，以便于查找该顶点的边信息；
                图中每个顶点vi的所有邻接点构成一个线性表，由于邻接点的个数不定，所以用单链表存储，无向图称为顶点vi的边表，有向图则成为顶点vi作为弧尾的出边表。
            d.顶点表中的各个结点由data和firstedge两个域表示，data是数据域，存储顶点的信息，firstedge是指针域，指向边表的第一个结点，即此顶点的第一个邻接点。边表结点由adjvex和next两个域组成。adjvex是邻接点域，存储某结点的邻接点在顶点表中的下标，next则存储指向边表中下一个结点的指针。
            e.根据邻接表的结构，
                要想知道某个顶点的度，就去查找这个顶点的边表中结点的个数；
                若要判断vi到vj是否存在边，只需要测试顶点vi边表中的adjvex是否存在结点vj的下标j就行了；
                若求顶点的所有邻接点，其实就是对此顶点的边表进行遍历，得到的adjvex域对应的顶点就是邻接点。
            f.对于有向图，邻接表结构是类似的。由于有向图有方向，我们是以顶点为弧尾来存储边表的，这样很容易得到每个顶点的出度。但有时为了方便确定顶点的入度或以顶点为弧头的弧，我们可以建立一个有向图的逆邻接矩阵，即对每个顶点vi都建立一个链接为vi为弧头的表。(比如a->b，那么a是弧尾，b是弧头，参考上方有向边中的定义)
            g.对于有权值得网图，可以在边表结点定义中再增加一个weight得数据域，存储权值信息即可。
            h.关于结点定义的代码：
            ```c
                /* 顶点类型应由用户定义 */
                typedef char VertexType;
                /* 边上的权值类型应由用户定义 */
                typedef int EdgeType;
                /* 边表结点 */
                typedef struct EdgeNode
                {
                    /* 邻接点域，存储该顶点对应下的下标 */
                    int adjvex;
                    /* 用于存储权值，对于非网图可以不需要 */
                    EdgeType weight;
                    /* 链域，指向下一个邻接点 */
                    struct EdgeNode *next;
                } EdgeNode;
                /* 顶点表结点 */
                typedef struct VertexNode
                {
                    /* 顶点域，存储顶点信息 */
                    VertexType data;
                    /* 边表头指针 */
                    EdgeNode *firstedge;
                } VertexNode, AdjList[MAX_VEX];
                /* 邻接表结构 */
                typedef struct
                {
                    /* 邻接表 */
                    AdjList adjList;
                    /* 图中当前顶点数和边数 */
                    int numVertexes, numEdges;
                } GraphAdjList;
            ```
            i.邻接表的创建代码：
            ```c
                /* 建立图的邻接表结构 */
                void CreateALGraph(GraphAdjList *G)
                {
                    int i, j, k;
                    EdgeNode *e;
                    printf("输入顶点数和边数：\n");
                    // 输入顶点数和边数
                    scanf("%d,%d", &G->numVertexes, &G->numEdges);
                    // 输入顶点信息，建立顶点表
                    for (i = 0; i < G->numVertexes; i++)
                    {
                        // 输入顶点信息
                        scanf("%d", &G->adjList[i].data);
                        // 将边表置为空表
                        G->adjList[i].firstedge = NULL;
                    }
                    // 建立边表
                    for (k = 0; k < G->numEdges; k++)
                    {
                        printf("输入边(vi, vj)上的顶点序号：\n");
                        scanf("%d,%d", &i, &j);

                        // ****************
                        // 以下代码采用头插法
                        // ****************

                        // 向内存申请空间，生成边表结点
                        e = (EdgeNode *) malloc(sizeof(EdgeNode));
                        // 邻接序号为j
                        e->adjvex = j;
                        // 将e指针指向当前顶点指向的结点
                        e->next = G->adjList[i].firstedge;
                        // 将当前顶点的指针指向e
                        G->adjList[i].firstedge = e;
                        // 向内存申请空间，生成边表结点
                        e = (EdgeNode *) malloc(sizeof(EdgeNode));
                        // 邻接序号为i
                        e->adjvex = i;
                        // 将e指针指向当前顶点指向的结点
                        e->next = G->adjList[j].firstedge;
                        // 将当前顶点的指针指向e
                        G->adjList[j].firstedge = e;
                    }
                }
            ```
            由于对于无向图，一条边对应都是两个顶点，所以在循环中，一次就针对i和j分别进行了插入。本算法的时间复杂度，对于n个顶点e条边来说，是O(n+e)。
            j.十字链表：对于有向图来说，邻接表是有缺陷的，关心了出度问题，想了解入度就必须要遍历整个图才能知道，反之，逆邻接表解决了入度却不了解出度的情况，于是将邻接表与逆邻接表结合起来组成了狮子链表(Orthogonal List)。
                重新定义顶点表结点结构：
                    其中firstin表示入边表头指针，指向该顶点的入边表中第一个结点，firstout表示出边表头指针，指向该顶点的出边表战中的第一个结点。
                重新定义边表结点结构：
                    其中tailvex是指弧起点在顶点表的下标，headvex是指弧重点在定点表中的下标，headlink是指入边表指针域，指向终点相同的下一条边，taillink是指边表指针域，指向起点相同的下一条边。如果是网，还可以再增加一个weight域来存储权值。
            k.邻接多重表：当更多的关注于边的操作时可以用这个结构。
                重新定义边表结点结构：其中ivex和jvex是与某条边依附的两个顶点在顶点表中下标。ilink指向依附顶点ivex的下一条边，jlink指向依附顶点jvex的下一条边。这就是邻接多重表结构。
            l.边集数组：边集数组是由两个一维数组构成。一个存储顶点的信息；另一个是存储边的信息，这个边数组每个数据元素由一条边的起点下标(begin)、终点下标(end)和权(weight)组成。
            这种结构更适合对边依次进行处理的操作，而不适合对顶点相关的操作。相关介绍在后面的克鲁苏卡尔(Kruskal)算法中介绍。
        (3)图的遍历：从图中某一顶点出发访遍图中其余顶点，且使每一个顶点仅被访问一次，这一过程就叫做图的遍历。
            a.深度优先遍历(Depth_First_Search)，也有称为深度优先搜索，简称为DFS。它从图中某个顶点v出发，访问此顶点，然后从v未被访问得邻接点出发深度优先遍历图，直至图中所有和v有路径相通的顶点都被访问到。事实上，我们这里讲到得使连通图，对于非连通图，只需要对他的连通分量分别进行深度优先遍历，即在先前一个顶点进行一次深度优先遍历后，若图中尚有顶点未被访问，则另选图中一个未曾被访问的顶点作为起始点，重复上述过程，直至图中所有顶点都被访问到为止。
            b.邻接矩阵的深度优先遍历算法：
            ```c
                /* Boolean是布尔类型，其值是TRUE或FALSE */
                typedef int Boolean;
                // 访问标志的数组
                Boolean visited[MAX];
                /* 邻接矩阵的深度优先递归算法 */
                void DFS(MGraph G, int i)
                {
                    int j;
                    visited[i] = TRUE;
                    // 打印顶点，也可以其他操作
                    printf("%c ", G.vexs[i]);
                    for (j = 0; j < G.numVertexes; j++)
                    {
                        if (G.arc[i][j] == 1 && !visited[j])
                        {
                            // 对未访问的邻接顶点递归调用
                            DFS(G, j);
                        }
                    }
                }
                /* 邻接矩阵的深度遍历操作 */
                void DFSTraverse(MGraph G)
                {
                    int i;
                    for (i = 0; i < G.numVertexes; i++)
                    {
                        // 初始所有顶点状态都是未访问过状态
                        visited[i] = FALSE;
                    }
                    for (i = 0; i < G.numVertexes; i++)
                    {
                        // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
                        if (!visited(i))
                        {
                            DFS(G, i);
                        }
                    }
                }
            ```
            c.邻接表的深度遍历算法：
            ```c
                /* 邻接表的深度优先递归算法 */
                void DFS(GraphAdjList GL, int i)
                {
                    EdgeNode *p;
                    visited[i] = TRUE;
                    printf("%c ", GL->adjList[i].data);
                    p = GL->adjList[i].firstedge;
                    while (p)
                    {
                        if (!visited[p->adjvex])
                        {
                            DFS(GL, p->adjvex);
                        }
                        p = p->next;
                    }
                }
                /* 邻接表的深度遍历操作 */
                void DFSTraverse(GraphAdjList GL)
                {
                    int i;
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        viisted[i] = FALSE;
                    }
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
                        if (!visited[i])
                        {
                            DFS(GL, i);
                        }
                    }
                }
            ```
            d.比较上述两种结构，邻接矩阵要查找每个顶点的邻接点需要访问矩阵中所有元素，需要O(n²)时间，邻接表所需时间取决于顶点和边的数量，所以是O(n+e)。显然对于点多边少的稀疏图来说，邻接表结构使得算法在时间效率上大大提高。
            对于有向图而言，由于它只是对铜到存在可行或不可行的判断，算法上没有任何变化，完全可以通用的。
            e.广度优先遍历(Breadth_First_Search)，又称为广度优先搜索，简称BFS。
            如果说图的深度优先遍历类似于树的前序遍历，那么图的广度优先遍历就类似于树的层序遍历了。
            f.邻接矩阵结构的广度优先遍历算法：
            ```c
                /* 邻接矩阵的广度遍历算法 */
                void BFSTraverse(MGraph G)
                {
                    int i, j;
                    Queue Q;
                    for (i = 0; i < G.numVertexes; i++)
                    {
                        visited[i] = FALSE;
                    }
                    // 初始化以辅助用的队列
                    InitQueue(&Q);
                    // 对每一个顶点做循环
                    for (i = 0; i < G.numVertexes; i++)
                    {
                        // 若是未访问过就处理
                        if (!visited[i])
                        {
                            // 设置当前顶点访问过
                            visited[i] = TRUE;
                            // 打印顶点，也可以其他操作
                            printf("%c ", G.vexes[i]);
                            // 将此顶点入队列
                            EnQueue(&Q, i);
                            // 若当前队列不为空
                            while (!QueueEmpty(Q))
                            {
                                // 将队中元素出队列，赋值给i
                                DeQueue(&Q, &i);
                                for (j = 0; j < G.numVertexes; j++)
                                {
                                    // 判断其他顶点若与当前顶点存在边且未访问过
                                    if (G.arc[i][j] == 1 && !visited[j])
                                    {
                                        // 将找到的此顶点标记为已访问
                                        vivited[j] = TRUE;
                                        // 打印顶点
                                        printf("%c ", G.vexes[j]);
                                        // 将找到的此顶点入队列
                                        EnQueue(&Q, j);
                                    }
                                }
                            }
                        }
                    }
                }
            ```
            g.邻接表的广度优先遍历算法：
            ```c
                /* 邻接表的广度遍历算法 */
                void BFSTraverse(GraphAdjList GL)
                {
                    int i;
                    EdgeNode *p;
                    Queue Q;
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        visited[i] = FALSE;
                    }
                    INitQueue(&Q);
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        if (!visited[i])
                        {
                            visited[i] = TRUE;
                            printf("%c ", GL->adjList[i].data);
                            EnQueue(&Q, i);
                            while (!QueueEmpty(Q))
                            {
                                DeQueue(&Q, &i);
                                // 找到当前顶点边表链表头指针
                                p = GL->adjList[i].firstedge;
                                while (p)
                                {
                                    // 若此顶点未被访问
                                    if (!visited[p->adjvex])
                                    {
                                        visited[p->adjvex] = TRUE;
                                        printf("%c ", GL->adjList[p->adjvex].data);
                                        // 将此顶点入队列
                                        EnQueue(&Q, p->adjvex);
                                    }
                                    // 指针指向下一个邻接点
                                    p = p->next;
                                }
                            }
                        }
                    }
                }
            ```
            h.DFS和BFS的时间复杂度是一样的，不同之处仅在于对顶点访问的顺序不同。深度优先更适合目标比较明确，以找到目标为主要目的的情况，而广度优先更适合在不断扩大遍历范围时找到相对最优解的情况。
        (4)最小生成树：把构造连通网的最小代价生成树称为最小生成树(Minimum Cost Spanning Tree)。找连通网的最小生成树，经典的有两种算法，普里姆算法和克鲁斯卡尔算法。
            a.普里姆(Prim)算法(数学描述看百科)：
            ```c
                /* Prim算法生成最小生成树 */
                void MiniSpanTree_Prim(MGraph G)
                {
                    int min, i, j, k;
                    // 保存相关顶点下标
                    int adjvex[MAX_VEX];
                    // 保存相关顶点间边的权值
                    int lowcost[MAX_VEX];
                    // 初始化第一个权值为0，即v0加入生成树
                    // lowcost的值为0，在这里就是此下标的顶点已经加入生成树
                    lowcost[0] = 0;
                    // 初始化第一个顶点下标为0
                    adjvex[0] = 0;
                    for (i = 1; i < G.numVertexes; i++)
                    {
                        // 将v0顶点与之有边的权值存入数组
                        lowcost[i] = G.arc[0][i];
                        // 初始化都为v0的下标
                        adjvex[i] = 0;
                    }
                    for (i = 1; i < G.numVertexes; i++)
                    {
                        // 初始化最小权值为∞
                        // 通常设置为不可能的大数字，如32767、65535等
                        min = INFINITY;
                        // j用来做顶点下标循环的变量
                        j = 1;
                        // k用来保存最小权值的顶点下标
                        k = 0;
                        // 循环全部顶点，找到与当前顶点相连权值最小的那条边
                        while (j < G.numVertexes)
                        {
                            // 如果权值不为0并且权值小于min
                            // lowcost[j]!=0表示已经是生成树的顶点不参与最小权值的查找
                            if ((lowcost[j] != 0) && (lowcost[j] < min))
                            {
                                // 则让当前权值成为最小值
                                min = lowcost[j];
                                // 将当前最小值的小标存入k
                                k = j;
                            }
                            j++;
                        }
                        // 打印当前顶点边中权值最小的边
                        printf("(%d, %d)", adjvex[k], k);
                        // 将当前顶点的权值设置为0，表示此顶点已经完成任务
                        lowcost[k] = 0;
                        // 循环所有顶点
                        for (j = 1; j < G.numVertexes; j++)
                        {
                            // 若下标为k顶点各边权值小于此前这些顶点未被加入生成树时的权值
                            if ((lowcost[j] != 0) && (G.arc[k][j] < lowcost[j]))
                            {
                                // 将较小权值存入lowcost
                                low[j] = G.arc[k][j];
                                // 将下标为k的顶点存入adjvex
                                adjvex[j] = k;
                            }
                        }
                    }
                }
            ```
            由代码中的循环嵌套可知此算法的时间复杂度为O(n²)(这个其实只是基本实现最小生成树的构建，还可以优化)。
            b.克鲁斯卡尔(Kruskal)算法(数学描述看百科)：直接以边为目标去构建，只不过构建时要考虑是否会形成环路。此时需要使用图的存储结构中的边集数组结构。
            edge边集数据结构定义:
            ```c
                /* 对边集数组Edge结构的定义 */
                typedef struct
                {
                    int begin;
                    int end;
                    int weight;
                }
            ```
            于是算法代码如下：
            ```c
                /* Kruskal算法生成最小生成树 */
                void MiniSpanTree_Kruskal(MGraph G)
                {
                    int i, n, m;
                    // 定义边集数组
                    Edge edges[MAX_EDE];
                    // 定义一个数组用来判断边与边是否形成环路
                    int parent[MAX_VEX];
                    // ...
                    // 此处省略了将邻接矩阵G转化为边集数组edges并按权由小到大排序的代码(实现见后面具体的代码文件)
                    // ...、
                    for (i = 0; i < G.numVertexes; i++)
                    {
                        // 初始化数组为0
                        parent[i] = 0;
                    }
                    // 循环每一条边
                    for (i = 0; i < G.numEdges; i++)
                    {
                        n = Find(parent, edges[i].begin);
                        m = Find(parent, edges[i].end);
                        // 加入n和m不等，说明此边没有与现有生成树形成环路
                        if (n != m)
                        {
                            // 就此边的结尾顶点放入下标为起点的parent中，表示此顶点已经在生成树集合中
                            parent[n] = m;
                            printf("(%d, %d) %d", edges[i].begin, edges[i].end, edges[i].weight);
                        }
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
            ```
            对比两个算法，Kruskal算法主要针对边来展开，边数少时效率会非常高，所以对于稀疏图有很多优势；而Prim算法对于稠密图，即边数很多的情况会更好一些。
        (5)最短路径：在网图和非网图中，最短路径的含义是不同的。由于非网图没有边上的权值，所谓的最短路径，其实就是两顶点之间经过的边数最少的路径；而对于网图来说，最短路径，是指两顶点之间经过的边上权值之和最少的路径，并且我们成路径上的第一个顶点是源点，最后一个顶点是终点。显然，研究网图更有实际意义，就地图而言，距离就是两顶点之间的权值之和。而非网图可以理解为所有边的权值都为1的网。
        (6)第一种求最短路径的算法：从某个源点到其余各顶点的最短路径问题。
            迪杰斯特拉(Dijkstra)算法：
            ```c
                #define MAX_VEX 9
                #define INFINITY 65535
                /* 用于存储最短路径下标的数组 */
                typedef int Pathmatrix[MAX_VEX];
                /* 用于存储到各点最短路径的权值和 */
                typedef int ShortPathTable[MAX_VEX];
                /* Dijkstra算法，求有向网G的v0顶点到其余各顶点v最短路径P[v]及带权长度D[v] */
                /* P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和 */
                void ShortestPath_Dijkstra(MGraph G, int v0, Pathmatrix *P, ShortPathTable *D)
                {
                    int v, w, k, min;
                    // final[w] = 1表示求得顶点v0至vw的最短路径
                    int final[MAX_VEX];
                    // 初始化数据
                    for (v = 0; v < G.numVertexes; v++)
                    {
                        // 全部顶点初始化为未知最短路径的状态
                        final[v] = 0;
                        // 将与v0点(v0=0)有连线的顶点加上权值
                        (*D)[v] = G.matrix[v0][v];
                        // 初始化路径数组P为0
                        (*P)[v] = 0;
                    }
                    // v0至v0路径为0
                    (*D)[v0] = 0;
                    // v0至v0不需要求路径
                    final[v0] = 1;
                    // 开始主循环，每次求得v0到某个v顶点的最短路径
                    for (v = 1; v < G.numVertexes; v++)
                    {
                        // 当前所知离v0顶点的最近距离
                        min = INFINITY;
                        // 寻找离v0最近的顶点
                        for (w = 0; w < G.numVertexes; w++)
                        {
                            if (!final[w] && ((*D)[w] < min))
                            {
                                k = w;
                                // w顶点离v0顶点更近
                                min = (*D)[w];
                            }
                        }
                        // 将目前找到的最近的顶点置为1
                        final[k] = 1;
                        // 修正当前最短路径及距离
                        for (w = 0; w < G.numVertexes; w++)
                        {
                            // 如果经过v顶点的路径比现在这条路径的长度短的话
                            if (!final[w] && (min + G.matrix[k][w] < (*D)[w]))
                            {
                                // 说明找到了更短的路径，修改D[w]和P[w]
                                // 修改当前路径长度
                                (*D)[w] = min + G.matrix[k][w];
                                (*P)[w] = k;
                            }
                        }
                    }
                }
            ```
            该算法可以求得v0到其余任何一个顶点得最短路径，时间复杂度为O(n²)，若要求任意两点之间得最短路径，相当于就是把每个点都当作源点v0来进行一次Dijkstra算法，时间复杂度为O(n³)。
        (7)另一种求最短路径的算法：弗洛伊德(Floyd)算法，该算法求所有顶点到所有顶点的时间复杂度也是O(n³)，但是该算法非常简洁优雅。
        注意：因为是求所有顶点到所有顶点的最短路径，因此Pathmatrix和ShortPathTable都是二维数组。
        ```c
            typedef int Pathmatrix[MAX_VEX][MAX_VEX];
            typedef int ShortPathTable[MAX_VEX][MAX_VEX];
            /* Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w] */
            void ShortestPath_Floyd(MGraph G, Pathmatrix *p, ShortPathTable *D)
            {
                int v, w, k;
                // 初始化D和P
                for (v = 0; v < G.numVertexes; v++)
                {
                    for (w = 0; w < G.numVertexes; w++)
                    {
                        // D[v][w]值即为对应点间的权值
                        (*D)[v][w] = G.matrix[v][w];
                        // 初始化P
                        (*P)[v][w] = w;
                    }
                }
                // k代表中转顶点的下标
                // 比如，k=0就是说所有顶点都进过v0中专计算是否有最短路径的变化
                for (k = 0; k < G.numVertexes; k++)
                {
                    // v代表起始顶点
                    for (v = 0; v < G.nunmVertexes; v++)
                    {
                        // w代表结束顶点
                        for (w = 0; w < G.numVertexes; w++)
                        {
                            // 如果经过下标为k的顶点的路径比原两点间的路径更短
                            if ((*D)[v][w] > ((*D)[v][k] + (*D)[k][w]))
                            {
                                // 将当前两点间权值设为更小的一个
                                (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                                // 路径设置经过下标为k的顶点
                                (*P)[v][w] = (*P)[v][k];
                            }
                        }
                    }
                }
            }
            /* 利用上述算法将求得的最短路径打印出来 */
            for (v = 0; v < G.numVertexes; v++)
            {
                for (w = v + 1; w < G.numVertexes; w++)
                {
                    printf("v%d->v%d weight：%d ", v, w, D[v][w]);
                    // 获得第一个路径顶点下标
                    k = P[v][w];
                    // 打印源点
                    printf(" path：%d", v);
                    // 如果路径顶点下标不是终点
                    while (k != w)
                    {
                        // 打印路径顶点
                        printf(" -> %d", k);
                        // 获得下一个路径顶点下标
                        k = P[k][w];
                    }
                    // 打印终点
                    printf(" -> %d\n", w);
                }
                printf("\n);
            }
        ```
        (8)拓扑排序：研究没有环的图
            a.在一个表示工程的有向图中，用顶点表示活动，用弧表示活动之间的优先关系，这样的有向图为顶点表示活动的网，我们称为AOV网(Activity On Vertex Network)。
            b.设G = {V, E}是一个具有n个顶点的有向图，V中的顶点序列v1，v2，...，vn，满足若从顶点vi到vj有一条路径，则在顶点序列中顶点vi必在顶点vj之前。则我们称这样的顶点序列为一个拓扑序列。
            c.所谓拓扑排序，其实就是对一个有向图构造拓扑序列的过程。
                构造时会有两个结果：
                    如果此网的全部顶点被输出，则说明它是不存在环(回路)的AOV网；
                    如果输出顶点数少了，哪怕是少了一个，也说明这个网存在环(回路)，不是AOV网。
            d.拓扑排序算法：
                主要是为了解决一个工程问题能否顺利进行的问题。
                基本思路：从AOV网中选择一个入度为0的顶点输出，然后删去此顶点，并删除以此顶点为尾的弧，继续重复此步骤，直到输出全部顶点或者AOV网中不存在入度为0的顶点为止。
                涉及的结构代码：
                ```c
                    /* 边表结点 */
                    typedef struct EdgeNode
                    {
                        /* 邻接点域，存储该顶点对应的下标 */
                        int adjvex;
                        /* 用于存储权值，对于非网图可以不需要 */
                        int weight;
                        /* 链域，指向下一个邻接点 */
                        struct EdgeNode *next;
                    } EdgeNode;

                    /* 顶点表结构 */
                    typedef struct VertexNode
                    {
                        /* 顶点入度 */
                        int in;
                        /* 顶点域，存储顶点信息 */
                        int data;
                        /* 边表头指针 */
                        EdgeNode *firstedge;
                    } VertexesNode, AdjList[MAX_VEX];

                    typedef struct
                    {
                        AdjList adjList;
                        /* 图中当前顶点数和边数 */
                        int numVertexes, numEdges;
                    } graphAdjList, *GraphAdjList;
                ```
                在算法中，还需要一个辅助数据结构--栈，用来存储处理过程中入度为0的顶点，目的是为了避免每个查找时都要去遍历顶点表找有没有入度为0的顶点。
                实现代码：
                ```c
                    /* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回OK，若有回路返回ERROR */
                    Status ToplogicalSort(GraphAdjList GL)
                    {
                        EdgeNode *e;
                        int i, k, gettop;
                        // 用于栈指针下标
                        int top = -1;
                        // 用于统计输出顶点的个数
                        int count = 0;
                        // 建栈存储入度为0的顶点
                        int *stack;
                        stack = (int *)malloc(GL->numVertexs * sizeof(int));
                        for (i = 0; i < GL->numVertexes; i++)
                        {
                            if (GL->adjList[i].in == 0)
                            {
                                // 将入度为0的顶点入栈
                                // 这里从1开始存起走是因为下面while的结束条件是为0，如果从0开始存，那下面的while条件就改为-1
                                stack[++top] = i;
                            }
                        }
                        while (top != 0)
                        {
                            // 出栈
                            gettop = stack[top--];
                            // 打印此顶点
                            printf("%d -> ", GL->adjList[i].data);
                            // 统计输出顶点数
                            count++;
                            // 对此顶点弧表遍历
                            for (e = GL->adjList[gettop].firstedge; e; e = e->next)
                            {
                                k = e->adjvex;
                                // 将k号顶点邻接点的入度减一
                                if (!(--GL->adjList[k].in))
                                {
                                    // 若为0则入栈，以便于下次循环输出
                                    stack[++top] = k;
                                }
                            }
                        }
                        // 如果count小于顶点数，说明存在环
                        if (vount < GL->numVertexes)
                        {
                            return ERROR;
                        }
                        else
                        {
                            return OK;
                        }
                    }
                ```
                对一个具有n个顶点e条弧的AOV网来说，算法时间复杂度为O(n+e)。
            e.关键路径：
                解决工程完成需要的最短时间问题。
                在一个表示工程的带权有向图中，用顶点表示事件，用有向边表示活动，用边上的权值表示活动的持续时间，这种有向图的边表示活动的网，我们称之为AOE网(Activity On Edge Network)。
                把AOE网中没有入边的顶点称为始点或源点，没有出边的顶点称为终点或汇点。一个工程，总有一个开始和结束，所以正常情况下，AOE网只有一个源点和一个汇点。
                把路径上各个活动所持续的时间之和称为路径长度，从源点到汇点具有最大长度的路径叫关键路径，在关键路径上的活动称为关键活动。
            f.关键路径算法原理：只需要找到所有活动的最早开始时间和最晚开始时间，并且比较它们，如果相等就意味着此活动是关键活动，活动间的路径为关键路径。如果不等，则就不是。
            为此，我们需要定义如下几个参数：
                I.事件的最早发生时间etv(earliest time of vertex)：即顶点vk鞥都最早发生时间；
                II.事件的最晚发生时间ltv(latest time of vertex)：即顶点vk的最晚发生时间，也就是每个顶点对应的事件最晚需要开始的时间，超出此事件将会延误整个工期；
                III.活动的最早开工时间ete(earliest time of edge)：即弧ak的最早发生时间
                IV.活动的最晚开工时间lte(latest time of edge)：即弧ak的最晚发生时间，也就是不推迟工期的最晚开工时间。
            我们是由I和II可以求得III和IV，然后再根据ete[k]是否与lte[k]相等来判断ak是否是关键活动。
            g.关键路径算法：
            求事件的最早发生时间etv的过程，就是我们从头至尾找拓扑序列的过程，因此，在求关键路径之前，需要先调用一次拓扑序列算法的代码来计算etv和拓扑序列列表。
            首先定义几个全局变量：
            ```c
                /* 事件最早发生时间和最迟发生时间数组 */
                int *etv, *ltv;
                /* 用于存储拓扑序列的栈，以便后面求关键路径时使用 */
                int *stack2;
                int top2;
            ```
            以下是改进过的求拓扑序列算法：
            ```c
                /* 拓扑排序，用于关键路径计算 */
                Status TopologicSort(GraphAdjList GL)
                {
                    EdgeNode *e;
                    int i, k, gettop;
                    /* 用于栈指针下标 */
                    int top = -1;
                    /* 用于统计输出顶点的个数 */
                    int count = 0;
                    /* 建栈将入度为0的顶点入栈 */
                    int *stack;
                    stack = (int *) malloc(GL->numVertexes * sizeof(int));
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        if (0 == GL->adjList[i].in)
                        {
                            stack[++top] = i;
                        }
                    }
                    // 初始化为0 
                    top2 = 0;
                    // 事件最早发生事件
                    etv = (int *) malloc(GL->numVertexes * sizeof(int));
                    for (i= 0; i < GL->numVertexes; i++)
                    {
                        // 初始化为0
                        etv[i] = 0;
                    }
                    stack2 = (int *) malloc(GL->numVertexes * sizeof(int));
                    while (top != 0)
                    {
                        gettop = stack[top--];
                        count++;
                        // 将弹出的顶点序号压入拓扑序列的栈
                        stack2[++top2] = gettop;
                        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
                        {
                            k = e->adjvex;
                            if (!(--GL->adjList[k].in))
                            {
                                stack[++top] = k;
                            }
                            // 求各顶点事件最早发生时间值
                            if ((etv[gettop] + e->weight) > etv[k])
                            {
                                etv[k] = etv[gettop] + e->weight;
                            }
                        }
                    }
                    if (count < GL->numVertexes)
                    {
                        return ERROR;
                    }
                    else
                    {
                        return OK;
                    }
                }
            ```
            可以得出计算顶点vk即求etv[k]的最早发生时间公式：
            etv[k] = 
                0，当k=0时
                max{etv[k] + len<vi, vk>}，当k≠0且<vi, vk>∈P[k]时，其中P[k]表示所有到达顶点vk的弧的集合，len<vi, vk>是弧<vi, vk>上的权值
            下面是求关键路径的算法代码：
            ```c
                /* 求关键路径，GL为有向网，输出GL的各项关键活动 */
                void CriticalPath(GraphAdjList GL)
                {
                    EdgeNode *e;
                    int i, gettop, k, j;
                    // 声明活动最早发生时间和最迟发生时间变量
                    int ete, lte;
                    // 求拓扑序列，计算数组etv和stack2的值
                    TopologicalSort(GL);
                    // 事件最晚发生时间
                    ltv = (int *) malloc(GL->numVertexes * sizeof(int));
                    for (i = 0; i < GL->numVertexes; i++)
                    {
                        // 初始化ltv
                        ltv[i] = etv[GL->numVertexes - 1];
                    }
                    // 计算ltv
                    while (top2 != 0)
                    {
                        // 将拓扑序列出栈，后进先出
                        gettop = stack2[top2--];
                        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
                        {
                            // 求各顶点时间的最迟发生时间ltv值
                            k = e->adjvex;
                            if ((ltv[k] - e->weight) < ltv[gettop])
                            {
                                ltv[gettop] = ltv - e->weight;
                            }
                        }
                    }
                    // 求ete，lte和关键活动
                    for (j = 0; j < GL->numVertexes; j++)
                    {
                        for (e = GL->adjList[j].firstedge; e; e = e->next)
                        {
                            k = e->adjvex;
                            // 活动最早发生时间
                            ete = etv[j];
                            // 活动最迟发生时间
                            lte = ltv[k] - e->weight;
                            // 如果两者相等即在关键路径上
                            if (ete == lte)
                            {
                                printf("<v%d, v%d> length：%d , ", GL->adjList[j].data, GL->adjList[k].data, e->weight);
                            }
                        }
                    }
                }
            ```
            在计算ltv时，其实是把拓扑序列倒过来进行的。计算顶点vk即求ltv[k]的最晚发生时间的公式是：
            ltv[k] = 
                etv[k]，当k=n-1时
                min{ltv[j] + len<vk, vj>}，当k < n-1且<vk, vj>∈S[k]时，其中S[k]表示所有从顶点vk出发的弧的集合，len<vk, vj>是弧<vk, vj>上的权值
## 七、查找
    1、
    2、
    3、
    4、
    5、
## 八、拍序