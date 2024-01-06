#include <stdio.h>
#define N 5         // จำนวนโปรเซส
#define T_SLICE 4   // Quantum time or Time Slice
#define NQ 24       // จำนวนช่องเก็บคิว

typedef struct{
    int BurtT;
    int ArrivalT;
}Process;

typedef struct{
    int indexP;
    int BurtT;
    int ArrivalT;
}Queue;

typedef struct{
    int indexP;
    int startP;
    int waitT;
}Gantt_C;

//Process  burt time , Arrival time , Priority
Process P[N+1]  =  {{0},
        /*P1*/ {9, 1},
        /*P2*/ {3, 1},
        /*P3*/ {5, 3},
        /*P4*/ {4, 4},
        /*P5*/ {2, 7}};

Gantt_C Gantt[24];
Queue   Q[NQ];   // คิว
int F = 0, R = 0;// ตัวชี้คิววงกลม Fชี้หน้า Rชี้หลัง
int NG = 0;      // number Gantt_chart
int NT = 0;      // number time
int NP = N;      // number process
int Q_Po = 0;
int G_Po = 0;
int Sum_P1,Sum_P2,Sum_P3,Sum_P4,Sum_P5;

void add_Q_P(int index, int BurtTL, int Arrival) {
    Q[Q_Po].indexP = index;
    Q[Q_Po].BurtT = BurtTL;
    Q[Q_Po].ArrivalT = Arrival;
    printf("add in %d : ", Q_Po);
    printf("P%d : B%d\n", Q[Q_Po].indexP, Q[Q_Po].BurtT);
    Q_Po++;
}

void calNT(){
    int i;
    int sumBurt = 0;
    int minArrival = P[1].ArrivalT;
    for (i = 1; i <= NP; ++i) {
        if(P[i].ArrivalT < minArrival){
            minArrival = P[i].ArrivalT;
        }
        sumBurt += P[i].BurtT;
    }
    NT = minArrival + sumBurt;
}

void outQ(int index) {
    Gantt[G_Po].startP = P[Q[index].indexP].ArrivalT;
    Gantt[G_Po].indexP = Q[index].indexP;
    Gantt[G_Po].waitT = Q[index].BurtT;
    printf("%d : P%d : WT%d \n", Gantt[G_Po].startP, Gantt[G_Po].indexP, Gantt[G_Po].waitT);
    R = G_Po;
    G_Po++;
}

int chk(int index, int Time) {
    int timeleft = 0;
    int END_P = 0;          // เวลาสิ้นสุดของโปรเซสที่กำลงทำงานั
    if (T_SLICE < P[index].BurtT) {
        timeleft = P[index].BurtT - T_SLICE;
        END_P = Time + T_SLICE;
        add_Q_P(index, timeleft, END_P);
    }
    if (T_SLICE >= P[index].BurtT) {
        timeleft = T_SLICE - P[index].BurtT;
    }
    return timeleft;
}
void Round_Robin() {
    int i, j, k;
    int index, timeleft = 0;
    int runingP = 0;        // ไอดีของโปรเซสที่กำลังทำงาน
    for (i = 0; i < NT; i++) {
        index = i;
        for (j = 1; j <= NP; j++) {
            if (i == P[j].ArrivalT) {
                if (Gantt[0].startP == 0 && Gantt[0].indexP == 0) {
                    timeleft = chk(j, i);
                    outQ(j - 1);
                } else {
                    timeleft = chk(j, i);
                    outQ(j - 1);
                }
            }
        }
        if(G_Po >= NP){
            if(Q[G_Po].indexP != NULL && Gantt[G_Po].indexP == NULL){
                if(Q[G_Po].indexP == NULL){
                    timeleft = chk(G_Po, i);
                    outQ(G_Po);
                }else{
                    timeleft = chk(G_Po, i);
                    outQ(G_Po);
                }
            }
        }
    }
}

int main() {
    int i;
    calNT();
    for (i = 1; i <= NP; i++) {
        add_Q_P(i, P[i].BurtT, P[i].ArrivalT);
    }
    Round_Robin();
    printf("# Weerawut Lukkanatorn ID:65543206078-9\n");
    printf("# OUTPUT LAB6 CPU Scheduling\n");
    printf("# Round Robin\n");
    printf("Sequence process is : \n");
    for (i = 0; i < NP; i++) {
        printf("P%d", Q[i].indexP == N+1 ? 1 : Q[i].indexP);  // Adjust index for P6
        printf(" : %d\n", Q[i].BurtT);
    }
    printf("------------------------------------------------------------\n");
    // แสดงผลข้อมูลทั้งหมดใน Gantt Chart
    printf("Gantt Chart:\n");
    for (i = 0; i < G_Po; i++) {
        printf("%d : P%d : WT%d\n", Gantt[i].startP, Gantt[i].indexP, Gantt[i].waitT);
    }
    printf("%d\n", NT);
    return 0;
}


