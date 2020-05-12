#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int GetLeftLength(int n)
{
    int L;
    int H = log2(n + 1);
    int X = n + 1 - pow(2, H);
    if (X <= pow(2, H - 1))
        L = X + pow(2, H - 1) - 1;
    if (X > pow(2, H - 1))
        L = pow(2, H) - 1;
    return L;
}
void solve(int ALeft, int ARight, int TRoot, int *A, int *T)
{
    int n = ARight - ALeft + 1;
    if (n == 0)
        return;
    int L = GetLeftLength(n); //计算出n个结点的树其左子树有多少个结点
    T[TRoot] = A[ALeft + L];
    int LeftTRoot = 2 * TRoot + 1;
    int RightRoot = LeftTRoot + 1;
    solve(ALeft, ALeft + L - 1, LeftTRoot, A, T);
    solve(ALeft + L + 1, ARight, RightRoot, A, T);
}
int main()
{
    int N;
    scanf("%d", &N);
    int A[N]; //0到N-1
    int i;
    for (i = 0; i < N; i++)
        scanf("%d", &A[i]);
    qsort(A, N, sizeof(int), compare);
    int T[N];
    solve(0, N - 1, 0, A, T);
    for (i = 0; i < N; i++)
    {
        if (i == 0)
            printf("%d", T[i]);
        else
            printf(" %d", T[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}