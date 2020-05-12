#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    fp = fopen("data.txt", "w");
    int N = 1000;
    int U = 1;
    int i, j;
    fprintf(fp, "%d %d\n", N, U * N);
    for (int K = 1; K <= U * N; K++)
    {
        i = rand() % 1001;
        j = rand() % 1001;
        if (i == 0 || j == 0)
        {
            i++;
            j++;
        }
        fprintf(fp, "%d %d\n", i, j);
    }
    fclose(fp);
    system("pause");
    return 0;
}