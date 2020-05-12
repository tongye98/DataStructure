#include <stdio.h>
struct PolyNode
{
    int coef;  //系数
    int expon; // 指数
    struct PolyNode *link;
};
typedef struct PolyNode *Polynomial;
Polynomial P1, P2;
Polynomial Add(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear; // 临时空节点作为多项式表头
    while (P1 && P2)
    {
        switch (Compare(P1->expon, P2->expon))
        {
        case 1:
            Attach(P1->coef, P1->expon, &rear);
            P1 = P1->link;
            break;
        case -1:
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
            break;
        case 0:
            sum = P1->coef + P2->coef;
            if (sum)
                Attach(sum, P1->expon, &rear);
            P1 = P1->link;
            P2 = P2->link;
            break;
        }
    }
    for (; P1; P1 = P1->link)
        Attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->link)
        Attach(P2->coef, P2->expon, &rear);
    rear->link = NULL;
    temp = front;
    front = front->link;
    free(temp);
    return front;
}
void Attach(int c, int e, Polynomial *pRear)
{ // 由于在本函数中需要改变当前结果表达式尾部指针的值
    // 所以函数传递进来的是节点指针的地址， *pRear指向尾项
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    // 将P指向的新节点插入到当前结果表达式尾项的后面
    (*pRear)->link = P;
    (*pRear) = P; // 修改pRear值
}
int Compare(int e1, int e2)
{
    if (e1 > e2)
        return 1;
    else if (e1 < e2)
        return -1;
    else
        return 0;
}
Polynomial ReadPoly()
{
    Polynomial P, Rear, t;
    int c, e, N;
    scanf("%d", &N);
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear);
    }
    t = P;
    P = P->link;
    free(t);
    return P;
}
Polynomial Mult(Polynomial P1, Polynomial P2)
{
    Polynomial P, Rear, t1, t2, t;
    int c, e;
    if (!P1 || !P2)
        return NULL;
    t1 = P1, t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (t2)
    {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while (t1)
    {
        t2 = P2;
        Rear = P;
        while (t2)
        {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon > e)
                Rear = Rear->link;
            if (Rear->link && Rear->link->expon == e)
            {
                if (Rear->link->coef + c)
                    Rear->link->coef += c;
                else
                {
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else
            {
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;
    P = P->link;
    free(t2);
    return P;
}
void PrintPoly(Polynomial P)
{
    int flag = 0;
    if (!P)
    {
        printf("0 0\n");
        return;
    }
    while (P)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}
int main()
{
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    PS = Add(P1, P2);
    PrintPoly(PS);
    system("pause");
    return 0;
}