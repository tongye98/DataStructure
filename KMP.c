#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int Position;
#define NotFound -1
#define MAX 1000001
void BuildMatch(char *pattern, int *match)
{
    int i, j;
    int m = strlen(pattern);
    match[0] = -1;
    for (j = 1; j < m; j++)
    {
        i = match[j - 1];
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            i = match[i];
        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}
Position KMP(char *string, char *pattern)
{
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p, *match;
    if (n < m)
        return NotFound;
    match = (int *)malloc(m * sizeof(int));
    BuildMatch(pattern, match);
    s = p = 0;
    while (s < n && p < m)
    {
        if (string[s] == pattern[p])
        {
            s++;
            p++;
        }
        else if (p > 0)
            p = match[p - 1] + 1;
        else
            s++;
    }
    return (p == m) ? (s - m) : NotFound;
}
int main()
{
    char string[MAX];
    char pattern[MAX];
    scanf("%s", string);
    int N;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%s", pattern);
        Position p = KMP(string, pattern);
        if (p == NotFound)
            printf("Not Found\n");
        else
            printf("%s\n", string + p);
    }
    system("pause");
    return 0;
}