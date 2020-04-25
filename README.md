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
                    /*存储空间初始分配量*/
                    #define MAX_SIZE 20
                    /*ElemType类型根据实际情况而定，这里假设为int*/
                    typedef int ElemType;
                    typedef struct
                    {
                        /*数组存储数据元素，最大容量为MAX_SIZE*/
                        ElemType data[MAX_SIZE];
                        /*线性表当前长度*/
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
                    /*Status是函数的类型，其值是函数结果状态代码，如OK等*/
                    typedef int Status;
                    /*初始条件：顺序线性表L已经存在，1 <= i <= ListLength(L)*/
                    /*操作结果：用e放回L中第i个数据元素的值*/
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
                    /*初始条件：顺序线性表L已存在,1 <= i <= ListLength(L)*/
                    /*操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1*/
                    Status ListInsert(SqList *L, int i, ElemType e) {
                        int k;
                        /*顺序线性表已满*/
                        if (L->length == MAX_SIZE) 
                        {
                            return ERROR;
                        }
                        /*当i不在范围内时*/
                        if (i < 1 || i > L->length + 1) 
                        {
                            return ERROR;
                        }
                        /*若插入数据位置不在表尾*/
                        if (i <= L->length) 
                        {
                            /*将要插入位置后数据元素向后移动一位*/
                            for (k = L->length - 1; k >= i - 1; k--) 
                            {
                                L->data[k + 1] = L->data[k];
                            }
                        }
                        /*将新元素插入*/
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
                    /*初始条件：顺序线性表L已存在,1 <= i <= ListLength(L)*/
                    /*操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1*/
                    Status ListDelete(SqList *L, int i, ElemType *e) {
                        int k;
                        /*线性表为空*/
                        if (L->length == 0) 
                        {
                            return ERROR;
                        }
                        /*删除位置不合理*/
                        if (i < 1 || i > L->length) 
                        {
                            return ERROR;
                        }
                        *e = L->data[i - 1];
                        /*如果删除的不是最后一个位置*/
                        if (i < L->length) 
                        {
                            /*将删除位置后继元素前移*/
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
                /*线性表的单链表存储结构*/
                typedef struct Node 
                {
                    ElemType data;
                    struct Node *next;
                } Node;
                /*定义LinkList*/
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
                    /*初始条件：顺序线性表L已存在，1 <= i <= ListLength(L)*/
                    /*操作结果：用e返回L中第i个数据元素的值*/
                    Status GetElem(LinkList L, int i, ElemType *e) 
                    {
                        int j;
                        /*声明一个指针p*/
                        LinkList p;
                        /*让p指向链表L的第一个结点，因为假设L是带头结点的，所以L->next才是第一个结点*/
                        p = L->next;
                        /*j为计数器*/
                        j = 1;
                        /*p不为空且计数器j还没有等于i时，循环继续*/
                        while (p && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /*第i个结点不存在*/
                        if (!p || j > i) 
                        {
                            return ERROR;
                        }
                        /*取第i个结点的数据*/
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
                    /*初始条件：顺序线性表L已存在，1 <= i <= ListLength(L)*/
                    /*操作结果：在L中第i个结点位置之前插入新的数据元素e，L长度加1*/
                    Status ListInsert(LinkList *L, int i, ElemType e) 
                    {
                        int j;
                        LinkList p, s;
                        p = *L;
                        j = 1;
                        /*寻找第i - 1个结点*/
                        while (p && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /*第i个结点不存在*/
                        if (!p || j > i) 
                        {
                            return ERROR;
                        }
                        /*生成新结点*/
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
                    /*初始条件：顺序线性表L已存在，1 <= i <= ListLength(L)*/
                    /*操作结果：删除L的第i个结点，并用e返回其值，L的长度减1*/
                    Status ListDelete(LinkList *L, int i, ElemType e) 
                    {
                        int j;
                        LinkList p, q;
                        p = *L;
                        j = 1;
                        /*遍历寻找第i-1个结点*/
                        while (p->next && j < i) 
                        {
                            p = p->next;
                            ++j;
                        }
                        /*第i个结点不存在*/
                        if (!(p->next) || j > i) 
                        {
                            return ERROR;
                        }
                        q = p->next;
                        /*将q的后继赋值给p的后继*/
                        p->next = q->next;
                        /*将q结点中的数据给e*/
                        *e = q->data;
                        /*让系统回收此结点，释放内存*/
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
                    /*随机产生n个元素的值，建立带表头结点的线性单链表L(头插法)*/
                    void CreateListHead(LinkList *L, int n) 
                    {
                        LinkList p;
                        int i;
                        /*初始化随机数种子*/
                        srand(time(0));
                        *L = (LinkList)malloc(sizeof(Node));
                        /*先建立一个带头结点的单链表*/
                        (*L)->next = NULL;
                        for (i = 0; i < n; i++) 
                        {
                            /*生成新节点*/
                            p = (LinkList)malloc(sizeof(Node));
                            /*随机生成100以内的数字*/
                            P->data = rand() % 100 + 1;
                            p->next = (*L)->next;
                            /*插入到表头*/
                            (*L)->next = p;
                        }
                    }
                ```
                ```c
                    /*随机产生n个元素的值，建立带表头结点的线性单链表L(尾插法)*/
                    void CreateListTail(LinkList *L, int n) 
                    {
                        LinkList p, r;
                        int i;
                        /*初始化随机数种子*/
                        srand(time(0));
                        /*L指整个单链表*/
                        *L = (LinkList)malloc(sizeof(Node));
                        /*r为指向尾部的结点*/
                        r = *L;
                        for (i = 0; i < n; i++) 
                        {
                            /*生成新节点*/
                            p = (LinkList)malloc(sizeof(Node));
                            /*随机生成100以内的数字*/
                            P->data = rand() % 100 + 1;
                            /*将表尾终端结点的指针指向新结点*/
                            r->next = p;
                            /*将当前的新结点定义为表尾终端结点*/
                            r = p;
                        }
                        /*表示当前链表结束*/
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
                    /*初始条件：顺序线性表L已存在，操作结果：将L重置为空表*/
                    Status ClearList(LinkList *L) 
                    {
                        LinkList p, q;
                        /*p指向第一个结点*/
                        p = (*L)->next;
                        /*没到表尾*/
                        while (p) 
                        {
                            q = p->next;
                            free(p);
                            p = q;
                        }
                        /*将头结点的指针域设置为空*/
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
        /*线性表的静态链表存储结构*/
        /*假设链表的最大长度为1000*/
        #define MAX_SIZE 1000
        typedef struct 
        {
            ElemType data;
            /*游标，为0时表示无指向*/
            int cur;
        } Component, StaticLinkList[MAX_SIZE];
    ```
    另外对数组第一个和最后一个元素作为特殊元素处理，不存数据。
    通常把未被使用的数组元素称为备用链表。
    数组第一个元素，即下标为0的元素cur就存放备用链表的第一个结点的下标；而数组的最后一个元素的cur则存放第一个有数值元素的下标，相当于单链表中的头结点作用,当整个链表为空时，则为0。
    初始化的数组状态：
    ```c
        /*将一维数组space中各分量链成一备用链表*/
        /*space[0].cur为头指针，"0"表示空指针*/
        Status InitList(StaticLinkList space) 
        {
            int i;
            for (i = 0; i < MAX_SIZE - 1; i++) 
            {
                space[i].cur = i + 1;
            }
            /*目前静态链表为空，最后一个元素的cur为0*/
            space[MAX_SIZE - 1].cur = 0;
            return OK;
        }
    ```
    5、静态链表的插入操作：
        思路：为了辨明数组中哪些分量未被使用，解决办法是将所有未被使用过的及已被删除的分量用游标链成一个备用链表，每当进行插入时，便可以从备用链表上取得第一个结点作为待插入的新结点。
        ```c
            /*若备用空间链表非空，则返回分配的结点下标，否则返回0*/
            int Malloc_SLL(StaticLinkList space) 
            {
                /*当前数组第一个元素的cur存的值，就是要返回的第一个备用空闲的下标*/
                int i = space[0].cur;
                if (space[0].cur) 
                {
                    /*由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用*/
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
                /*注意k首先是最后一个元素的下标*/
                k = MAX_SIZE - 1;
                if (i < 1 || i > ListLength(L) + 1) 
                {
                    return ERROR;
                }
                /*获取空闲分量的下标*/
                j = Malloc_SSL(L);
                if (j) 
                {
                    /*将数据赋值给此分量的data*/
                    L[j].data = e;
                    /*找到第i个元素的位置*/
                    for (l = 1; l <= i - 1; l++) 
                    {
                        k = L[k].cur;
                    }
                    /*把第i个元素之前的cur赋值给新元素的cur*/
                    L[j].cur = L[k].cur;
                    /*把新元素的下标赋值给第i个元素之前元素的cur*/
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
            /*删除在L中第i个数据元素e*/
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
            /*将下标为k的空闲结点回收到备用链表*/
            void Free_SSL(StaticLinkList space, int k) 
            {
                /*把第一个元素cur值赋给要删除的分量cur*/
                space[k].cur = space[0].cur;
                /*把要删除的分量下标赋值给第一个元素的cur*/
                space[0].cur = k;
            }
            ```
    7、静态链表的一些其他操作，比如ListLength()：
    ```c
        /*初始条件：静态链表L已存在。操作结果：返回L中数据元素个数*/
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
        /*保存A表的头结点*/
        p = rearA->next;
        /*将本来是指向B表的第一个结点(不是头结点)赋值给rear->next*/
        rearA->next = rearB->next->next;
        /*将原A表的头结点赋值给rearB->next*/
        rearB->next = p;
        /*释放p*/
        free(p);
    ```
    13、双向链表：在单链表的每个结点中，再设置一个指向其前驱结点的指针域。
    14、双向链表的存储结构:
    ```c
        /*线性表的双向链表存储结构*/
        typedef struct DuLNode 
        {
            ElemType data;
            /*直接前驱指针*/
            struct DuLNode *prior;
            /*直接后继指针*/
            struct DuLNode *next;
        } DuLNode, *DulinkList;
    ```
    15、双向链表也有可以有循环链表。
    对于链表中的某一个结点p，它的后继的前驱、前驱的后继都是它自己：p->next->prior = p = p->prior->next。双向链表时单链表中扩展出来的结构，所以很多操作是相同的，比如求长度的ListLength，查找元素的GetElem，获得元素位置的LocationElem等，这些操作都只设计一个方向的指针即可，另一指针也不能提供任何帮助。但是双向链表再插入和删除时要麻烦一些，需要修改两个指针变量。
    16、双向链表的插入操作：并不复杂，但是顺序很重要，不能写反了！！
    假设存储元素e的结点s，现在要实现将结点s插入到结点p和p->next之间：
    实现代码：
    ```c
        /*这四步的顺序千万不能换！*/
        /*把p赋值给s的前驱*/
        s->prior = p;
        /*把p->next赋值给s的后继*/
        s->next = p->next;
        /*把s赋值给p->next的前驱*/
        p->next->prior = s;
        /*把s赋值给p的后继*/
        p->next = s;
        /*总结顺序就是：先搞定s的前驱和后继，再搞定后结点的前驱，最后解决前结点的后继*/
    ```
    17、双向链表的删除操作：若要删除结点p只需要两步。
    实现代码：
    ```c
        /*这里的p代表的是当前要删除的结点，与代码中的p不相同*/
        /*把p->next赋值给p->prior的后继*/
        p->prior->next = p->next;
        /*把p->prior赋值给p->next的前驱*/
        p->next->prior = p->prior;
        /*释放结点*/
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
    4、栈的顺序存储结构：栈的顺序存储其实也是线性表顺序存储的简化，我们简称为顺序栈。一般用数组下标为0的以端作为栈底比较好，因为首元素都在栈底，变化最小，所以让它作为栈底。当栈存在一个元素时，top位0，通常将空栈的判定条件定位top=-1。
    结构定义：
    ```c
        /*SElemType类型根据实际情况而定，这里假设为int*/
        typedef int SElemType;
        typedef struct 
        {
            SElemType data[MAX_SIZE];
            /*用于栈顶指针*/
            int top;
        } SqStack;
    ```
    5、栈的顺序存储结构的进栈操作：
    ```c
        Statuc Push(SqStack *S, SElemType e)
        {
            //如果栈已经满了
            if (S->top == MAXSIZE - 1)
            {
                return ERROR;
            }
            //栈顶指针加一
            S->top++;
            //将新插入元素赋值给栈顶空间
            S->data[S->top] = e;
            return OK;
        }
    ```
    时间复杂度O(1)。
    6、栈的顺序存储结构的出栈操作：
    ```c
        Status Pop(SqStack *S, SElemType *e)
        {
            //如果是空栈
            if (s->top == -1)
            {
                return ERROR;
            }
            //将要删除的栈顶元素赋值给e
            *e = S->data[S->top];
            //栈顶指针减一
            S->top--;
            return OK;
        }
    ```
    时间复杂度O(1)。
    7、两栈共享空间
    做法：数组有两个端点，两个栈有两个栈底，让一个栈的栈底为数组的始端，即下标为0处，另一个栈为数组的末端，即下标为数组长度n-1处。这样，两个栈如果增加元素，就是两端点向中间延伸。
    当top1 = -1， top2 = n-1的时候就是空栈，当top1 + 1 = top2的时候就是栈满。
    结构代码：
    ```c
        /*两栈共享空间结构*/
        typedef struct
        {
            SElemType data[MAX_SIZE];
            //栈1栈顶指针
            int top1;
            //栈2栈顶指针
            int top2;
        } SqDoubleStack;
    ```
    8、两栈共享空间的push(入栈)操作：
    思路：除了要插入元素值参数歪，还需要有一个判断是栈1还是栈2的栈号参数stackNumber。
    实现代码：
    ```c
        /*插入元素e为新的栈顶元素*/
        Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
        {
            //栈已经满了，不能再push新元素了
            if (S->top1 + 1 == S->top2)
            {
                return ERROR;
            }
            //如果是栈1有元素进栈
            if (stackNumber == 1)
            {
                //若是栈1则先top1+1然后给数组元素赋值
                S->data[++S->top1] = e;
            }
            //如果是栈2有元素进栈
            else if (stackNumber == 2)
            {
                //若是栈2则先top2-1然后给数组元素赋值
                S->data[--S->top2] = e;
            }
            return OK;
        }
    ```
    9、两栈共享空间的pop(出栈)操作：
    ```c
        /*若栈不空，则删除S的栈顶元素，用e放回其值，并返回OK，否则返回ERROR*/
        Status Pop(SqDoubleStack *S. SElemType *e, int stackNumber)
        {
            if (stackNumber == 1)
            {
                //栈1已经是空栈了
                if (S->top1 == -1)
                {
                    return ERROR;
                }
                //将栈1的栈顶元素出栈
                *e = S->data[S->top1--];
            }
            else if (stackNumber == 2)
            {
                //栈2已经是空栈了
                if (S->top2 == MAXSIZE)
                {
                    return ERROR;
                }
                //将栈2的栈顶元素出栈
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
        /*链栈的操作绝大部分都和单链表类似，只是在插入和删除上特殊一些*/
    ```
    12、链栈的进栈(push)操作：
    假设元素值为e的新结点是s，top为栈顶指针。
    实现代码：
    ```c
        /*插入元素为e的新的栈顶元素*/
        Status Push(LinkStack *S, SElemType e)
        {
            LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
            s->data = e;
            //把当前的栈顶元素赋值给新结点的直接后继
            s->next = S->top;
            //将新结点s赋值给栈顶指针
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
        /*若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR*/
        Status Pop(LinkStack *S, SElemType *e)
        {
            LinkStackPtr p;
            //如果栈为空
            if (StackEmpty(*S))
            {
                return ERROR;
            }
            *e = S->top->data;
            //将栈顶结点赋值给p
            p = S->top;
            //使栈顶指针下移一位，指向后一结点
            S->top = S->top->next;
            //释放结点p
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
            /*QElemType类型根据实际情况而定，这里假设为int*/
            typedef int QElemType;
            /*循环队列的顺序存储结构*/
            typedef struct
            {
                QElemType data[MAX_SIZE];
                //头指针
                int front;
                //尾指针，若队列不空，指向队列尾元素的下一个位置
                int reat;
            } SqQueue;
        ```
        (5)循环队列的初始化：
        ```c
            /*初始化一个空队列Q*/
            Status InitQueue(SqQueue *Q)
            {
                Q->front = 0;
                Q->rear = 0;
                return OK;
            }
        ```
        (6)循环队列求队列长度：
        ```c
            /*返回Q中的元素个数，也就是队列的当前长度*/
            int QueueLength(SqQueue Q)
            {
                return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
            }
        ```
        (7)循环队列的入队列操作：
        ```c
            /*若队列未满，则插入元素e为Q新的队尾元素*/
            Status EnQueue(SqQueue *Q, QElemType e)
            {
                //队列满的判断
                if ((Q->rear + 1) % MAX_SIZE == Q->front)
                {
                    return ERROR;
                }
                //将元素e赋值给队尾
                Q->data[Q->rear] = e;
                //rear指针向后移一位置，若到最后则转到数组头部
                Q->rear = (Q->rear + 1) % MAX_SIZE;
                return OK;
            }
        ```
        (8)循环队列的出队列操作：
        ```c
            /*若队列不空，则删除Q中队头元素，用e返回其值*/
            Status DeQueue(SqQueue *Q, QElemType *e)
            {
                //队列空的判断
                if (Q->front == Q->rear)
                {
                    return ERROR;
                }
                //将队头元素赋值给e
                *e = Q->data[Q->front];
                //front指针向后移一位置，若到最后则转到数组头部
                Q->front = (Q->front + 1) % MAX_SIZE;
                return OK;
            }
    19、队列的链式存储结构
        (1)队列的链式存储结构，其实就是线性表的单链表，只不过它只能尾进头出而已，简称为链队列。为了操作的方便，将队头指针指向链队列的头结点，而队尾指针指向终端结点。空队列时，front和rear都指向头结点。
        (2)链队列的结构：
        ```c
            /*QElemType类型根据实际情况而定，这里假设为int*/
            typedef int QElemType;
            /*结点结构*/
            typedef struct QNode
            {
                QElemType data;
                struct QNode *next;
            } QNode, *QueuePtr;
            /*队列的链表结构*/
            typedef struct
            {
                //队头指针
                QueuePtr front;
                //队尾指针
                QueuePtr rear;
            } LinkQueue;
        ```
        (3)链队列的入队操作：就是在链表尾部插入结点。
        ```c
            /*插入元素e为Q的新的队尾元素*/
            Status EnQueue(LinkQueue *Q, QElemType e)
            {
                QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
                //存储分配失败
                if (!s)
                {
                    exit(0);
                }
                s->data = e;
                s->next = NULL;
                //把拥有元素e新结点s赋值给原队尾结点的后继
                Q->rear->next = s;
                //把当前的s设置为队尾结点，rear指向s
                Q->rear = s;
                return OK;
            }
        ```
        (4)链队列的出队操作
            思路：出队操作时，就是头结点的后继结点出队，将头结点的后继改为它后面的结点，若链表除头结点外只剩一个元素时，则需将rear指向头结点。
            实现代码：
            ```c
                /*若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR*/
                Status DeQueue(LinkQueue *Q, QElemType *e)
                {
                    QueuePtr p;
                    //如果是空队列
                    if (Q->front == Q->rear)
                    {
                        return ERRROR;
                    }
                    //将欲删除的对头结点暂存给p
                    p = Q->front->next;
                    //将欲删除的队头结点的值赋值给e
                    *e = p->data;
                    //将原队头结点后继p->next赋值给头结点后继
                    Q->front->next = p->next;
                    //若对头是队尾，则删除后将rear指向头结点
                    if (Q->rear == p)
                    {
                        Q->rear = Q->front;
                    }
                    free(p);
                    return OK;
                }
            ```
        (5)总的来说，在可以去欸的那个队列长度最大值的情况下，建议用循环队列，如果你无法预估队列的长度时，则用链队列。
## 四、串
        