#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAXNUM 100000 // the total number of users
typedef int ElementType;

// 初始数据定义
int N;                 // the total number of users
int K;                 // the total number of problems
int M;                 // the total number of submissions
ElementType p[MAXNUM]; // full mark of the i-th problem
ElementType A[MAXNUM];
struct Bucket
{ // for every student build a bucket
    ElementType total_score;
    int Submit_number;
    int perfectly_solved_number;
    ElementType *Score;
    int *ith_submission;
} bucket[MAXNUM];
void Judge_Isperfect(int user_id, int problem_id, ElementType partial_score_obtained)
{
    if (partial_score_obtained == p[problem_id])
        bucket[user_id].perfectly_solved_number += 1;
}
void Calculate_total_Score(int user_id)
{
    int total = 0;
    for (int i = 1; i <= K; i++)
        total += bucket[user_id].Score[i];
    bucket[user_id].total_score = total;
}
void Build_bucket(int user_id, int problem_id, ElementType partial_score_obtained)
{
    bucket[user_id].ith_submission[problem_id] += 1;
    if (partial_score_obtained >= 0)
        bucket[user_id].Submit_number += 1;
    if (partial_score_obtained > bucket[user_id].Score[problem_id])
    {
        Judge_Isperfect(user_id, problem_id, partial_score_obtained);
        bucket[user_id].Score[problem_id] = partial_score_obtained;
        Calculate_total_Score(user_id);
    }
}
void Initialize_bucket()
{
    for (int i = 1; i <= N; i++)
    {
        bucket[i].Submit_number = 0;
        bucket[i].Score = 0;
        bucket[i].perfectly_solved_number = 0;
        bucket[i].Score = malloc((K + 1) * sizeof(int));
        bucket[i].ith_submission = malloc((K + 1) * sizeof(int));
        for (int j = 1; j <= K; j++)
        {
            bucket[i].Score[j] = 0;
            bucket[i].ith_submission[j] = 0;
        }
    }
}
void Print(int user_id)
{
    printf(" %d", bucket[user_id].total_score);
    for (int j = 1; j <= K; j++)
        if (bucket[user_id].ith_submission[j] > 0)
            printf(" %d", bucket[user_id].Score[j]);
        else
            printf(" -");
    printf("\n");
}
void Bucket_Sort()
{
    int R = 0; //R is the number which will be linked finally
    for (int i = 1; i <= N; i++)
    {
        if (bucket[i].Submit_number)
            A[R++] = i;
    }
    //printf("%d\n", R);
    int table[R];
    for (int i = 0; i < R; i++)
        table[i] = i;
    for (int p = 1; p < R; p++)
    {
        int i;
        int tmp = table[p];
        for (i = p; i > 0 && (bucket[A[tmp]].total_score < bucket[A[table[i - 1]]].total_score || (bucket[A[tmp]].total_score == bucket[A[table[i - 1]]].total_score && bucket[A[tmp]].perfectly_solved_number < bucket[A[table[i - 1]]].perfectly_solved_number)) || (bucket[A[tmp]].total_score == bucket[A[table[i - 1]]].total_score && bucket[A[tmp]].perfectly_solved_number == bucket[A[table[i - 1]]].perfectly_solved_number && A[tmp] > A[table[i - 1]]); i--)
            table[i] = table[i - 1];
        table[i] = tmp;
        // for (int j = 0; j < R; j++)
        //     printf("%d ", table[j]);
        // printf("\n");
    }
    int rank = 1; // rank is the ranking
    for (int j = R - 1; j >= 0; j--)
    {
        if (j < R - 1 && bucket[A[table[j]]].total_score == bucket[A[table[j + 1]]].total_score)
            ;
        else
            rank = R - j;
        printf("%d %05d", rank, A[table[j]]);
        Print(A[table[j]]);
    }
}
int main()
{
    scanf("%d %d %d", &N, &K, &M);
    for (int i = 1; i <= K; i++)
        scanf("%d", &p[i]);
    Initialize_bucket(); // initialize every bucket for every users
    while (M--)
    { // input the submissions
        int user_id, problem_id;
        ElementType partial_score_obtained;
        scanf("%d %d %d", &user_id, &problem_id, &partial_score_obtained);
        Build_bucket(user_id, problem_id, partial_score_obtained);
    }
    Bucket_Sort();
    system("pause");
    return 0;
}