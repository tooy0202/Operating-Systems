#include <stdio.h>
#define NUM_PAGE 19  //จำนวน page
#define NUM_PF  4  //จำนวนช่องของแต่ละ page frame

typedef struct {
    int time;
    int page;
}Pageframe;

Pageframe pageframe[NUM_PF];
int page[NUM_PAGE]={2,1,2,3,7,6,2,3,4,2,1,5,6,3,2,3,6,2,1};  // page All
int resultTable[NUM_PF][NUM_PAGE];                           // ใช้เก็บค่าเพจลงตารางดพื่อนำไปแสดงผลลัพธ์
int pagefaults[NUM_PAGE];                                    // page faults
int n_pagefaults;                                            // ใช้นับจำนวนเพจ page faults
int n_result = 0;                                            // ใช้นับจำนวน resultTable

void setPageframe(){                           // set ค่าเริ่มต้นของ pageframe ให้เป็น ์NULL
    for (int i = 0; i <NUM_PF ; ++i) {
        pageframe[i].page = -1;                // NULL,(-1)
    }
}

void Showresuult(){                         // แสดงผลลัพธ์จาก resultTable ตาราง
    for (int i = 0; i < NUM_PAGE; ++i) {
        printf("%2d  ", page[i]);
    }
    printf("\n-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < NUM_PF; ++i) {
        for (int j = 0; j < NUM_PAGE; ++j) {
            if(resultTable[i][j] == -1)
                printf("   |");
            else
                printf("%2d |",resultTable[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i <NUM_PAGE ; ++i) {     // แสดง page faualts
        printf("%2d |", pagefaults[i]);
    }
    printf("  page faults: %d\n", n_pagefaults);
}

void getResult(Pageframe pageframe[]){     //เก็บข้อมูลของแต่ละ pageframe เพื่อสร้างตารางแสดงผล
    for (int i = 0; i < NUM_PF; ++i) {
        resultTable[i][n_result] = pageframe[i].page;
    }
    n_result++;
}

int FIFO_LRU(Pageframe pageframe[]){         //หา page ที่อยู่นานที่สุด
    int min = pageframe[0].time;             // page ที่อยู่นานจะมีค่า i น้อย
    int indexmin = 0;
    for (int i = 0; i < NUM_PF; ++i) {
        if(pageframe[i].time < min){         // หา page อยู่นานที่สุด จาก pageframe
            min = pageframe[i].time;
            indexmin = i;
        }
    }
    return indexmin;                         //ที่อยู่ของ page นานที่สุด
}

int Optimal(Pageframe pageframe[],int start){  //แทนที่ page ทียังไม่ถูกเรียกใช้งาน มากที่สุด
    int temp[NUM_PF];
    int Long,index;
    for (int i = 0; i < NUM_PF; ++i) {        // วนลูปเพื่อหา page ที่ยังไม่ถูกเรียกใช้นานที่สุด
        for (int j = start+1; j < NUM_PAGE; ++j) {
            if(pageframe[i].page == page[j]) {
                temp[i] = j;                  // จะเก็บค่าเวลา ไว้ใน temp
                break;
            }else                             //ถ้าไม่เจอ page แปลว่าไม่มี page นี้ไม่มีอยู่ในอนาคต
                temp[i] = -1;                 //เก็บเป็น -1
        }
    }
    Long = temp[0];
    for (int i = 0; i < NUM_PF; ++i) {        //นำค่าจาก temp มาวนลูปว่า index ของ tempไหน
        if(temp[i] == -1) {                   //ที่ยังจะไม่เข้าทำงานอีกนาน
            index = i;                       // ถ้าเจอค่า -1 ในtemp แปลว่า page(index)
            break;                           // นี้จะไม่เข้ามาทำงานอีก ให้ break แล้วส่ง index กลับไป
        }
        if(temp[i] >= Long){
            Long = temp[i];
            index = i;
        }
    }
    return index;
}


void FIFO_Replacement(){
    printf("\nLeast Recently Used (FIFO) replacement\n\n");
    for (int i = 0; i < NUM_PAGE ; ++i) {       //วนลูปตามจพนวน page ทั้งหมด
        for (int j = 0; j < NUM_PF; ++j) {      //วนลูปตามจำนวนช่องของ page frame
            if(page[i] == pageframe[j].page){   //ถ้า page มีค่าเท่ากับ page ในช่องของ pageframe
                pagefaults[i] = 0;              //ไม่ต้องนับ page faults
                break;
            }else{
                if(pageframe[j].page == -1) {      //ถ้า pageframe ยังมีช่องที่ไม่ไก้ใช้งานอยู่
                    pageframe[j].page = page[i];   //เก็บ page ลงในช่อง
                    pageframe[j].time = i;        //บันทึก i (เวลา) ที่ page นี้เข้ามา
                    pagefaults[i] = 1;            //นับ pagefaults
                    n_pagefaults++;
                    break;
                }else{
                    if( j == NUM_PF-1){  //ถ้าวนจนครบ page frame ทั้งหมด ไม่มีช้องว่าง และไม่มี page ซ้ำเลย
                        int index = FIFO_LRU(pageframe);  // หาช่อง page มาก่อน (ออกก่อน)
                        pageframe[index].page = page[i];  // แทนที่ page ใหม่ตรงช่อง page มาก่อน
                        pageframe[index].time = i;        //บันทึกเวลา
                        pagefaults[i] = 1;                //นับ pagefaults
                        n_pagefaults++;
                        break;
                    }else
                        continue;
                }
            }
        }
        getResult(pageframe);                            //เก็บข้อมูล pageframe เพื่อไปทำตาางแสดงผล
    }
}

void Optimal_Replacement(){
    printf("\nOptimal replacement\n\n");
    for (int i = 0; i < NUM_PAGE ; ++i) {
        for (int j = 0; j < NUM_PF; ++j) {
            if(page[i] == pageframe[j].page){
                pagefaults[i] = 0;
                break;
            }else{
                if(pageframe[j].page == -1) {
                    pageframe[j].page = page[i];
                    pagefaults[i] = 1;
                    n_pagefaults++;
                    break;
                }else{
                    if( j == NUM_PF-1){
                        int index = Optimal(pageframe,i);  // หาช่อง page ที่ยังไม่ถูกเรียกใช้อีกนาน
                        pageframe[index].page = page[i];
                        pagefaults[i] = 1;
                        n_pagefaults++;
                        break;
                    }else
                        continue;
                }
            }
        }
        getResult(pageframe);
    }
}

void LRU_replacement(){
    printf("\nLeast Recently Used (LRU) replacement\n\n");
    for (int i = 0; i < NUM_PAGE ; ++i) {
        for (int j = 0; j < NUM_PF; ++j) {
            if(page[i] == pageframe[j].page){ //ถ้ามี page ค่าเท้ากับตรงช่อง page frame
                pagefaults[i] = 0;            //ไม่ต้องนับ pagefaults
                pageframe[j].time = i;        //แต่เปลี่ยนเวลา page ที่เข้ามาซ้ำใหม่
                break;
            }else{
                if(pageframe[j].page == -1) {
                    pageframe[j].page = page[i];
                    pageframe[j].time = i;
                    pagefaults[i] = 1;
                    n_pagefaults++;
                    break;
                }else{
                    if( j == NUM_PF-1){
                        int index = FIFO_LRU(pageframe); // หาช่อง page ที่ใช้มานานที่สุด (ออกก่อน)
                        pageframe[index].page = page[i];
                        pageframe[index].time = i;
                        pagefaults[i] = 1;
                        n_pagefaults++;
                        break;
                    }else
                        continue;
                }
            }
        }
        getResult(pageframe);
    }
}

int main(){
    int menu = 0;
    setPageframe();
    printf("ํ\nYOU num page...\n");
    for (int i = 0; i < NUM_PAGE; ++i) {
        if (i == NUM_PAGE-1)
        {
            printf("%2d", page[i]);
        }else
        {
            printf("%2d,", page[i]);
        }
    }
    printf("\n--------------------------------------\n");
    printf("**** |           menu           | ****\n");
    printf("**** | (1) FIFO_Replacement     | ****\n");
    printf("**** | (2) LRU_replacement      | ****\n");
    printf("**** | (3) Optimal_Replacement  | ****\n");
    printf("...Select the desired menu... : ");
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        FIFO_Replacement();
        break;
    case 2:
        LRU_replacement();
        break;
    case 3:
        Optimal_Replacement();
        break;
    default:
        printf("Invalid value\n");
        break;
    }
    if (menu > 0 && menu < 4)
    {
        Showresuult();
    }
    return 0;
}
