#include <stdio.h>
#define bool int
int M;
int top = -1;
int local = 1;
bool push(int s[])
{
    if (top == M - 1)
        return -1;
    else
    {
        s[++top] = local;
        local++;
        return 1;
    }
}
int pop(int s[])
{
    if (top == -1)
        return -1;
    else
    {
        return s[top--];
    }
}
int main()
{
    int N, K;
    scanf("%d %d %d", &M, &N, &K);
    int temp;
    int s[M];
    while (K--)
    {
        top = -1;
        local = 1;
        bool flag = 1; // flag== ture ;flag == false;
        bool flag_push = 1;
        int a[N];
        int this = 0;
        for (int i = 0; i < N; i++)
            scanf("%d", &a[i]);
        for (this; this < N; this ++)
        {
            if (this == 0)
            {
                int z = a[this];
                while (z--)
                    flag_push = push(s);
                temp = pop(s);
                if (flag_push == -1 || temp != a[this])
                {
                    flag = -1;
                    break;
                }
            }
            else
            {
                if (a[this] > a[this - 1])
                {
                    int y = a[this] - local + 1;
                    while (y--)
                        flag_push = push(s);
                    temp = pop(s);
                    if (flag_push == -1 || temp != a[this])
                    {
                        flag = -1;
                        break;
                    }
                }
                else
                {
                    temp = pop(s);
                    if (temp != a[this])
                    {
                        flag = -1;
                        break;
                    }
                }
            }
        }
        if (flag == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    system("pause");
    return 0;
}