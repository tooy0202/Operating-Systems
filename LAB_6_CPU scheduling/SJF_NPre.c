#include <stdio.h>
#define NP 5 // number Process

typedef struct{
    int indexP;
    int startP;
}GanttChart;
typedef struct{
    int indexP;
    int BurtT;
}Queue;
typedef struct{
    int BurtT;
    int ArrivalT;
    int Priority;
}Process;
     //Process  burt time , Arrival time , Priority

Process P[NP+1]  =  {{0},
        /*P1*/ {    9     ,       1      ,      3},     // P1 = P[1]
        /*P2*/ {    3     ,       1      ,      5},     // P2 = P[2]
        /*P3*/ {    5     ,       3      ,      1},     // P3 = P[3]
        /*P4*/ {    4     ,       4      ,      4},     // P4 = P[4]
        /*P5*/ {    2     ,       7      ,      2}};    // P5 = P[5]

GanttChart Gantt[30];
Queue  Q[30];
int NT = 0;     //Time
int NG = 0;     //number GanttChart
int SP = 0;     //ตัวชี้ค่าในคิว

void push(int indexP){        //เก็บโปรเซสไว้ในคิว
    SP++;
    Q[SP].indexP = indexP;
    Q[SP].BurtT  = P[indexP].BurtT;
}
void pop(){                   //นำโปรเซสออกจากคิว
    if(SP == 0)
        printf("UNDER FLOW!!!\n");
    SP--;
}

Queue sortQ(){                //เรียงข้อมูลจากน้อยไปมาก
    Queue tempP;
    int i, j;
    for (i = 1; i <SP ; ++i) {
        j = i+1;
        if(Q[i].BurtT <= Q[j].BurtT){
            tempP = Q[i];
            Q[i]  = Q[j];
            Q[j]  = tempP;
        }
    }
    return Q[SP];
}

int minBurt(int indexP, int tempP[], int *countP) {  //ในกรณีที่มีโปรเซสเกิดในเวลาเดียวกัน หาค่าโปรเซสที่ใช้เวลาทำงานน้อยที่สุด
    int i;
    int minBurt = P[indexP].BurtT;
    int minPro = indexP;
    *countP = 0;
    for (i = 1; i <= NP; ++i)
        if (P[indexP].ArrivalT == P[i].ArrivalT) {
            tempP[*countP] = i;                     //เก็บโปรเซสที่เกิดในเวลาเดียวกัน
            *countP+=1;                             //จำนวนโปรเซสที่เกิดในเวลาเดียวกัน
            if(P[i].BurtT < minBurt ){
                minBurt = P[i].BurtT;
                minPro = i;
            }
        }
    return minPro;                                  //โปรเซสที่ใช้เวลาทำงานน้อยที่สุด
}

void pushSynchronous(int indexP, int tempP[], int countP) {//เก็บโปรเซสที่เกิดพร้อมกันไว้ในคิว(ในเวลาเดียวกัน)
    int i;
    for (i = 0; i < countP ; ++i)
        if(tempP[i] != indexP )                            //ยกเว้นโปรเซสที่ใช้เวลาทำงานน้อยที่สุด
            push(tempP[i]);

}
void getData(int indexP, int time_i){
    Gantt[NG].indexP = indexP;          //เก็บโปรเซสเพื่อทำ GanttChart
    Gantt[NG].startP = time_i;          //เก็บเวลาเริ่มทำงานโปรเซสเพื่อทำ GanttChart
    NG++;
}

void SJF_NP(){
    int i, j;
    int indexP = 0, ENDPro = 0;
    int tempP[NP], countP = 0;
    for (i = 0; i <= NT; ++i) {              //i แทนเวลา (Time)
        for (j = 1; j <= NP; ++j) {
            if(i == P[j].ArrivalT){              //ณ เวลาที่ i มีโปรเซส 1 2 3 ...N เกิดขึ้นใหม่
                indexP = minBurt(j,tempP,&countP);//ถ้ามีโปรเซสเกิดในเวลาเดียวกันให้หาโปรเซสที่ใช้เวลาทำงานน้อยที่สุด
                if(i >= ENDPro && SP == 0){      //ณ เวลาที่ i ถ้าไม่มีโปรเซสลกำลังทำงาน(ไม่มีการใช้ทรัพยากร) และ ไม่มีโปรเซสไหนรออยู่ในคิว
                    pushSynchronous(indexP,tempP,countP);//เก็บโปรเซสที่เหลือไว้ในคิวถ้ามีโปรเซสมีกิดขึ้นพร้อกัน(ในเวลาเดียวกัน)
                    ENDPro = i + P[indexP].BurtT;
                    getData(indexP,i);           //เก็บข้อมูลโปรเซส
                }else{                           //ณ เวลาที่ i ถ้ามีโปรเซสลกำลังทำงาน(มีการใช้ทรัพยากร) หรือ มีโปรเซสออยู่ในคิว
                    push(indexP);                //เก็บค่าโปรเซสที่เกิดใหม่ ณ เวลาที่ i ไว้ในคิว
                    pushSynchronous(indexP,tempP,countP);//เก็บโปรเซสที่เหลือไว้ในคิวถ้ามีโปรเซสมีกิดขึ้นพร้อกัน(ในเวลาเดียวกัน)
                }
                break;
            }
        }
        if (i >= ENDPro && SP != 0) {            //ณ เวลาที่ i ถ้าไม่มีโปรเซสไหนทำงาน(ทรัพยากรว่าง) แต่ ยังมีโปรเซสเหลืออยู่ในคิว
            Queue indexPQ;
            indexPQ = sortQ();                    //เรียงโปรเซสในคิว โดยดูจากโปรเซสที่ใช้เวลาการทำงานน้อยที่สุด
            pop();                               //นำโปรเซสออกจากคิว
            ENDPro = i + indexPQ.BurtT;
            getData(indexPQ.indexP,i);
        }
    }
}

float waitProcess(int indexP){                              // คำนวณหา เวลารอของโปรเซสที่ i
    int i;
    int count = 0;
    float waitT =0, end = 0;
    for (i = 0; i <NG ; i++) {
        if(Gantt[i].indexP == indexP){
            if(count == 0){                                 // เวลาโปรเซสได้เข้าทำงาน - เวลาเเกิดของโปรเซส
                waitT += (float)Gantt[i].startP - P[indexP].ArrivalT;
                end    = (float)Gantt[i+1].startP;
                count++;
            }else{
                waitT += (float)Gantt[i].startP - end;      // เวล่ที่โปรเซสได้เข้าทำงานอีกครั้ง - เวลาที่โปรเซสจบการทำงานครั้งก่อน
                end    = (float)Gantt[i+1].startP;
            }
        }
    }
    return waitT;
}

void calNT(){                                               //คำนวณหาผลรวมของ burt time
    int i;
    int sumBurt = 0;
    int minArrival = P[1].ArrivalT;
    for (i = 1; i <= NP; ++i) {
        if(P[i].ArrivalT < minArrival){
            minArrival = P[i].ArrivalT;
        }
        sumBurt += P[i].BurtT;
    }
    NT = minArrival + sumBurt;                             //เวลาที่เริ่มเกิดโปรเซสตัวแรก + ผลรวมเวลที่ใช้ในการทำงานของโปรเซส
}

int main(){
    int i;
    calNT();
     printf("# Weerawut Lukkanatorn ID:65543206078-9,\n");
    printf("# OUTPUT LAB6 CPU Scheduling\n");
    printf("# SJF Non Preemptive \n");
    printf("Sequence process is :");
    SJF_NP();
    for (i = 0; i <NG ; i++) {
        printf("P%d", Gantt[i]);
        if(i<NG-1)
            printf("->");
    }
    printf("\n------------------------------------------------------------\n");
    printf("Wait time of process (millisecond)\n");
    for (i = 1; i <= NP; i++) {
        printf("| P%-10d", i);
    }
    printf("\n");
    float sum = 0, avgTime;
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
