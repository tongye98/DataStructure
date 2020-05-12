#include <stdio.h>
typedef int ElementType;
typedef struct LNode *List;
struct LNode
{
    ElementType Data;
    List Next;
};
struct LNode L;
List PtrL;
int Length(List PtrL);                        //链表的长度
List Find(ElementType X, List PtrL);          //查找X元素,按值查找
List FindKth(int K, List PtrL);               //查找,按序号查找
List Insert(ElementType X, int i, List PtrL); //插入，插在第i个位置
List Delete(int i, List PtrL);                //删除第i个位置的节点
int main()
{

    system("pause");
    return 0;
}
int Length(List PtrL) //链表的长度
{
    List p = PtrL;
    int j = 0;
    while (p)
    {
        p = p->Next;
        j++;
    }
    return j;
}
List Find(ElementType X, List PtrL) //查找X元素,按值查找
{
    List p = PtrL;
    while (p != NULL && p->Data != X)
        p = p->Next;
    return p;
}
List FindKth(int K, List PtrL) //查找,按序号查找
{
    List p = PtrL;
    int i = 1;
    while (p != NULL && i < K)
    {
        p = p->Next;
        i++;
    }
    if (i == K)
        return p;
    else
        return NULL;
}
List Insert(ElementType X, int i, List PtrL) //插入，插在第i个位置
{
    List p, s;
    if (i == 1)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = PtrL;
        return s;
    }
    p = FindKth(i - 1, PtrL);
    if (p == NULL)
    {
        printf("参数i错");
        return NULL;
    }
    else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return PtrL; //返回新的链表的头指针
    }
}
List Delete(int i, List PtrL) //删除第i个位置的节点
{
    List p, s;
    if (i == 1)
    {
        s = PtrL;
        if (PtrL != NULL)
            PtrL = PtrL->Next;
        else
            return NULL;
        free(s);
        return PtrL;
    }
    p = FindKth(i - 1, PtrL);
    if (p == NULL)
    {
        printf("the %d node is not existing", i - 1);
        return NULL;
    }
    else if (p->Next == NULL)
    {
        printf("the %d node is not existing", i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}