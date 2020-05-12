#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100005
typedef int ElementType;

typedef struct _node
{
    ElementType data;
    ElementType next;
} Node;

//反转链表函数，每rev_num 个节点，反转一下
int reverList(Node list[], int rev_num, int head, int N)
{
    int i;
    int flag = 1;

    int last_head; //用于记录上一次反转后，子链表的最后节点地址
        //待与下一次反转的子链表的头部相连
    int rev_head = head; //下一次待反转子链表的头节点地址
    int mid_head = head; //反转过程中的中间节点地址
    int mid_next;        //反转过程中的中间节点地址

    while (N - rev_num >= 0) //当剩余节点不够rev_num个时，则不再反转
    {
        N -= rev_num;

        //反转子链表
        for (i = 0; i < rev_num - 1; i++)
        {
            mid_next = list[rev_head].next;
            list[rev_head].next = list[mid_next].next;
            list[mid_next].next = mid_head;
            mid_head = mid_next;
        } //反转子链表

        //从第二次开始，需要把这次反转后的子链表的头节点连接到上一段的尾部
        if (flag == 0)
        {
            list[last_head].next = mid_head;
        }

        //记录第一次反转后的头结点，作为最终List的头节点并返回
        if (flag)
        {
            head = mid_head;
            flag = 0;
        }

        last_head = rev_head;
        rev_head = list[rev_head].next; //下次开始的头结点地址
        mid_head = rev_head;
    }
    return head;
}

printList(Node list[], int head)
{
    int next = head;
    while (list[next].next != -1)
    {
        printf("%05d %d %05d\n", next, list[next].data, list[next].next);
        next = list[next].next;
    }
    printf("%05d %d %d\n", next, list[next].data, list[next].next);
}

int main()
{
    int Head, N, rev_num;
    scanf("%d %d %d", &Head, &N, &rev_num);
    Node list[MAXSIZE];
    int i, add_front, add_next, number;

    for (i = 1; i <= N; i++)
    {
        scanf("%d %d %d", &add_front, &number, &add_next);
        list[add_front].data = number;
        list[add_front].next = add_next;
    }

    int next = Head;
    int num = 1; //所给数据节点并不都是链表中的节点，用于计数真正的节点个数
    while (list[next].next != -1)
    {
        num++;
        next = list[next].next;
    }

    if (rev_num > 1) //如果是1，则不需要反转，原序输出
        Head = reverList(list, rev_num, Head, num);
    printList(list, Head);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define MAX 100010
typedef int ElementType;
typedef int Position;
typedef struct Node *List;
struct Node
{
    ElementType data;
    int next;
} list[MAX];
void prinf_link(List list, int head);
int reserver_link(List list, int head, int K, int cnt);
int main()
{
    int head, N, K;
    scanf("%d %d %d", &head, &N, &K);
    int address, data, next_address;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &address, &data, &next_address);
        list[address].data = data;
        list[address].next = next_address;
    }
    //判断list上真正有多少个node
    int cnt = 1;
    address = head;
    while (list[address].next != -1)
    {
        cnt++;
        address = list[address].next;
    }
    if (K > 1)
        head = reserver_link(list, head, K, cnt);
    prinf_link(list, head);
    system("pause");
    return 0;
}
int reserver_link(List list, int head, int K, int cnt)
{
    int he = head;
    int new, old, temp;
    int first = 1;
    new = head;
    old = list[head].next;
    while (cnt - K >= 0)
    { // 说明需要反转
        if (first != 1)
        {
            new = old;
            old = list[old].next;
        }
        cnt -= K;
        int j = 1;
        while (j < K)
        {
            temp = list[old].next;
            list[old].next = new;
            new = old;
            old = temp;
            j++;
        }

        list[he].next = old;
        he = old;

        if (first == 1)
            head = new;
        first++;
    }
    return head;
}
void prinf_link(List list, int head)
{
    int address = head;
    while (1)
    {
        if (list[address].next != -1)
            printf("%05d %d %05d\n", address, list[address].data, list[address].next);
        else
            printf("%05d %d %d\n", address, list[address].data, list[address].next);
        address = list[address].next;
        if (address == -1)
            break;
    }
}

0 4 2 0 0 1 1 1 2 2 2 3 3 3 - 1 00001 1 00000 00000 0 00002 00002 2 - 1