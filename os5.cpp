#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 5
#define M 3
int safety(int available[], int max[][3], int allocation[][3], int need[][3]);
// ���������Դ�;���
void generateData(int *available, int max[][M], int allocation[][M], int need[][M]) {
    srand(time(NULL));

    // ���ɿ�����Դ��ȷ����Ϊ0
    for (int i = 0; i < M; i++) {
         //������Դ��Χ[1,10]
        available[i] = rand() % 10 + 1;
        printf("%d ", available[i]);
    }
    printf("\n\n");
    
    int sum[M]={0};
    // ��������������ȷ��С�ڿ�����Դ
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            //�����Դ��Χ[1,Available[j]]
            max[i][j] = rand() % available[j] + 1;
            if(rand()%2==0){
                allocation[i][j]=0;
            }else{
                int min=max[i][j];
                if(available[j]-sum[j]<min){
                    min=available[j]-sum[j];
                }
                if(min==0){
                    allocation[i][j]=0;
                }else{
                    allocation[i][j] = rand() % min + 1;
                }
            }
            sum[j]+=allocation[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for(int i=0;i<M;i++){
        available[i]-=sum[i];
    }
}

// ���㰲ȫ����
int safety(int available[M], int max[N][M], int allocation[N][M]) {
    int work[M];
    int finish[N]={0};
    int safe[N];
    int count = 0;

    // ��ʼ��work����Ϊ������Դ
    printf("work:\n");
    for (int i = 0; i < M; i++) {
        work[i] = available[i];
        printf("%d ", work[i]);
    }
    printf("\n");

    // ѭ�����ҿ����������Ľ���
    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < M; j++) {
                    if (max[i][j]-allocation[i][j] > work[j]) {
                        break;
                    }
                }
                //������Դ������
                if (j == M) {
                    for (int k = 0; k < M; k++) {
                        work[k] += allocation[i][k];
                    }
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        //û�ҵ�����ɵľ��ǽ�������״̬
        if (!found) {
            printf("Deadlock\n");
            return 0;
        }
    }
    // ��ӡ��ȫ����
    printf("Safe sequence:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", safe[i]+1);
    }
    printf("\n");
    return 1;
}

// ��ӡ����
void printMatix(int matix[N][M], const char *msg) {
    printf("%s:\n", msg);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    int available[M];
    int max[N][M];
    int allocation[N][M];
    int need[N][M];

    generateData(available, max, allocation, need);

    // ��ӡ����������
    printMatix(max, "Max Demand");
    // ��ӡ�������
    printMatix(allocation, "Allocation");
    // ��ӡ�������
    printMatix(need, "Need");
    // ��ӡ������Դ
    printf("Available:\n");
    for (int i = 0; i < M; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // ��ȫ�Լ��
    if (safety(available, max, allocation)) {
        printf("The system is in safe state.\n");
    } else {
        printf("The system is in unsafe state.\n");
    }

    return 0;
}