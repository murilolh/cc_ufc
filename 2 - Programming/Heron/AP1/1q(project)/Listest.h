#define MAX 10

typedef struct
{
     int t;
     void* vet[MAX];
}List_est;

List_est Empty_est();
List_est cons_est(void* inf, List_est l);
void* head_est(List_est l);
List_est tail_est(List_est l);
int isEmpty_est(List_est l);
