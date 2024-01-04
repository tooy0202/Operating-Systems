#include <stdio.h>
#define N 5         // จำนวนโปรเซส
#define T_SLICE 4   // Quantum time or Time Slice
#define NQ 20       // จำนวนช่องเก็บคิว

typedef struct{
    int BurtT;
    int ArrivalT;
    int Priority;
}Process;

typedef struct{
    int indexP;
    int BurtT;
}Queue;

typedef struct{
    int indexP;
    int startP;
}Gantt_C;

//Process  burt time , Arrival time , Priority
Process P[N+1]  =  {{0},
        /*P1*/ {    9     ,       1      ,      3},     // P1 = P[1]
        /*P2*/ {    3     ,       1      ,      5},     // P2 = P[2]
        /*P3*/ {    5     ,       3      ,      1},     // P3 = P[3]
        /*P4*/ {    4     ,       4      ,      4},     // P4 = P[4]
        /*P5*/ {    2     ,       7      ,      2}};    // P5 = P[5]


Gantt_C Gantt[20];
Queue   Q[NQ];   // คิว
int F = 0, R = 0;// ตัวชี้คิววงกลม Fชี้หน้า Rชี้หลัง
int NG = 0;      // number Gantt_chart
int NT = 0;      // number time
int NP = N;      // number process

void pushQ(int index, int BTimeLeft){
    if (R == F-1  || (F == 1 && R == NQ-1)) {
        printf("OVER FLOW!!\n");
    }else{
        if(R == NQ-1){
            R = 1;
        }else{
            R++;
            if(F == 0)
                F = 1;
        }
        Q[R].indexP = index;               // เก็บโปรเซสไว้ในคิว
        Q[R].BurtT  = BTimeLeft;           // เก็บเวลาการทำงานของโปรเซสที่เหลือไว้ในคิว
    }
}
Queue popQ() {
    Queue index;
    if (F == 0) {
        printf("UNDER FLOW!!\n");
    } else {
        index = Q[F];
        if (F == R) {
            F = 0; R = 0;
        } else {
            if (F == NQ-1)
                F = 1;
            else
                F++;
        }
        return index;
    }
}

int func_FCFS(int index){                 // โปรเซสเกิดพร้อมกัน ใช้ FCFS
    int i, j;
    int temp[20], n = 0;
    for (i = 1; i <= NP; i++) {
        if(P[index].ArrivalT == P[i].ArrivalT){
            temp[n++] = i;
        }
    }
    for (j = 0; j < n; j++) {      // นำโปรเตัวที่เหลือไปต่อคิว ยกเว้นโปรเซสที่เมาก่อน
        if(temp[j] != index){
            pushQ(temp[j],P[temp[j]].BurtT);
        }
    }
    return index;                     // return โปรเซสที่มาก่อน
}

int duplincate(int index){               // ตรวจดูว่ามีโปรเซสเเกิดในเวลาเดียวกันหรือไม่
    int i;
    int count = 0;
    for (i = 1; i <= NP; i++)
        if(P[index].ArrivalT == P[i].ArrivalT)
            count++;
    if (count > 1)                      // ถ้ามีโปรเซสเกิดในเวลาเดียวกัน
        return func_FCFS(index);        // หาโปรเซสที่ใช้เวลทำงานน้อยที่สุด
    else                                // ถ้าไม่มีโปรเซสเกิดในเวลาเดียวกัน
        return index;
}

void Round_Robin(){
    int i, j;
    int runingP = 0, timeleft, index, END_P = 0;
    for (i = 0; i <NT ; i++) {                      // i แทรเวลา time
        if(i == END_P && runingP != 0){                 // ถ้าครบเวลา Quantum time โปรเซสที่อยู่ในสถานะทำงานยังเหลือเวลาทำงานอยู่
            pushQ(runingP, timeleft);                   // ให้เก็บโปรเซสที่กำลังทำงาน และเวลาทำงานที่เหลือ ไว้ในคิวก่อน
        }
        for (j = 1; j <= NP; j++) {
            if (i == P[j].ArrivalT) {                   // ณ เวลาที่ i มี process[j] เกิดขึ้น
                index = j;
                if (i >= END_P && (F ==0 && R == 0 )) { // ถ้าจบQuantum time = โปรเซสสามารเข้าไปทำงานได้
                    index = duplincate(index);           // ตรวจสอบว่า มีโปรเซสเกิดขึ้นพร้อมกัน ใช่หรือไม่ (ถ้าใช่ก่ใช่ FCFS)
                    if(P[index].BurtT <= T_SLICE) {     // ถ้าเวลาทำงานของโปรเซสมีค่าน้อยกว่าเท่ากับ Quantum time
                        END_P = i + P[index].BurtT;     // ให้ Quantum time จบตามเวลาที่น้อยกว่า
                        runingP = 0;                    // ไม่มีโปรเซสอยู่ในสถานะทำงาน (เพราะจบในเวลา Quantum time )
                    }
                    else {                              // ถ้าเวลาทำงานของโปรเซสมีค่ามากกว่า Quantum time
                        END_P = i + T_SLICE;            // เวลาจบการทำงานของโปรเซส
                        runingP = index;                // โปรเซสที่กำลังทำงาน
                        timeleft = P[index].BurtT - T_SLICE; //เวลาที่เหลือของโปรเซส
                    }
                    Gantt[NG].indexP = index;
                    Gantt[NG].startP = i;               //เก็บค่าเวลาที่โปรเซสได้เริ่มทำงาน
                    NG++;
                    break;
                } else{                                 // ถ้า Quantum time ยังไม่จบ = โปรเซสจะไม่สามารเข้าไปทำงานได้
                    pushQ(index, P[index].BurtT);       // เก็บโปรเซสที่กำลังทำงานไว้ในคิวก่อน
                    duplincate(index);                 // ถ้ามีโปรเซสเกิดขึ้นพร้อมกันเก็บให้เก็บโปรเซสไว้ในคิว
                    break;
                }
            }
        }
        if (i >= END_P && (F != 0 && R != 0)) {         // ถ้าQuantum time จบแต่ไม่มีโปรเซสไหนเกิดขึ้น แต่ในคิวยังมีโปรเซสอยู่
            Queue indexQ;
            indexQ = popQ();                            // นำโปรเซสในคิวเข้าทำงาน

            if (indexQ.BurtT <= T_SLICE) {              // ถ้าเวลาทำงานของโปรเซสมีค่าน้อยกว่าเท่ากับ Quantum time
                END_P = i + indexQ.BurtT;
                runingP = 0;
            } else {                                    // ถ้าเวลาทำงานของโปรเซสมีค่ามากกว่า Quantum time
                END_P = i + T_SLICE;
                runingP = indexQ.indexP;;
                timeleft = indexQ.BurtT - T_SLICE;
            }
            Gantt[NG].indexP = indexQ.indexP;
            Gantt[NG].startP = i;
            NG++;
        }
    }
}

float waitProcess(int indexP){                                  // คำนวณหา เวลาที่โปรเซสรอ
    int i;
    int count = 0;
    float waitT =0, end = 0;
    for (i = 0; i <NG ; i++) {
        if(Gantt[i].indexP == indexP){
            if(count == 0){                                     // เวลาโปรเซสได้เข้าทำงาน - เวลาเเกิดของโปรเซส
                waitT += (float)Gantt[i].startP - P[indexP].ArrivalT;
                end    = (float)Gantt[i+1].startP;
                count++;
            }else{
                waitT += (float)Gantt[i].startP - end;          // เวล่ที่โปรเซสได้เข้าทำงานอีกครั้ง - เวลาที่โปรเซสจบการทำงานครั้งก่อน
                end    = (float)Gantt[i+1].startP;
            }
        }
    }
    return waitT;
}

void calNT(){
    int i;
    int sumBurt = 0;
    int minArrival = P[1].ArrivalT;
    for (i = 1; i <=NP; ++i) {
        if(P[i].ArrivalT < minArrival){
            minArrival = P[i].ArrivalT;
        }
        sumBurt += P[i].BurtT;
    }
    NT = minArrival + sumBurt;
}

int main(){
    int i;
    calNT();
     printf("# Weerawut Lukkanatorn ID:65543206078-9\n");
    printf("# OUTPUT LAB6 CPU Scheduling\n");
    printf("# Round Robin\n");
    printf("Sequence process is :");
    Round_Robin();
    for (i = 0; i <NG ; i++) {
        printf("P%d", Gantt[i].indexP);
        if(i<NG-1)
            printf("->");
    }
    printf("\n------------------------------------------------------------\n");
    printf("Wait time of process (millisecond)\n");
    for (i = 1; i <= NP; i++) {
        printf("| P%-10d", i);
    }
    printf("\n");
    float sum=0;
    float avgTime;
    for (i = 1; i <= NP; i++) {
        printf("| %-11.2f",waitProcess(i));
        sum += waitProcess(i);
    }
    avgTime = sum/NP;
    printf("\nAverage time is %.2f", avgTime);
    printf("\nTurnaround time\n");
    for (i = 1; i <= NP; i++) {
        printf("|P%d = %-6.2fms ", i, waitProcess(i) + P[i].BurtT);
    }
    printf("\n------------------------------------------------------------\n");
    return 0;
}
