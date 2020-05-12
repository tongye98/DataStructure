#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100000
typedef int ElementType;
int main()
{
    int N;
    scanf("%d", &N);
    ElementType A[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    int T[N]; // table
    for (int i = 0; i < N; i++)
        T[A[i]] = i;
    // 元素i 放在 A[T[i]] 中
    int flag = 0;   // 标识,指示环中是否有0;
    int cnt = 0;    // 计数
    int result = 0; // 记录最后结果
    for (int j = 0; j < N; j++)
    {
        cnt = 0;
        flag = 0;
        if (T[j] != j)
        {
            int i = j;
            int temp = A[i];
            if (temp == 0)
                flag = 1;
            while (1)
            {
                A[i] = A[T[i]];
                cnt++;
                if (A[i] == 0)
                    flag = 1;
                int next = T[i];
                T[i] = i;
                if (T[next] == next)
                    break;
                else
                    i = next;
            }
            A[i] = temp;
            if (flag)
                cnt--;
            else
                cnt++;
            result += cnt;
        }
    }
    printf("%d\n", result);
    system("pause");
    return 0;
}