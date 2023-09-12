//
//  programinside.c
//  2023-2 mainproject_parkingcash
//
//  Created by 한설 on 2023/08/18.
//

#include "parkingcash.h"
#include <time.h>

extern void savethecar(Parkcar newone);
extern void readParkinginfo(void);
extern Parkcar searchtheCar(char *targetcarnumber, int *count);
extern void deletetheCar(int count);

extern void print_queue(char *msg);

char* returntimetoday(void);
char* returntimetomin(void);
int Stringtoint(char *str); //문자열 -> 정수변환
char* substring(char *str, int start, int length); //문자열 부분 자르기(자를 문자열, 시작지점, 길이)
int checkBill(Parkcar selected); //요금 체크


void Carin(Parkcar newone) {    //작동
    strcpy(newone.intime, returntimetomin());
    savethecar(newone);
}

void Carread(void) {    //작동
    readParkinginfo();
    print_queue("");
}

void Carout(char *carnumber) {  //작동
    int count = 0;
    searchtheCar(carnumber, &count);
    if(count == FAIL) {printf("찾지 못했습니다\n");}
    else deletetheCar(count);
}

void addCommuter(char *addcar) {
    
}

char* returntimetomin(void) {
    //분단위까지 문자열 형태로 반환
    time_t currtime;
    time(&currtime);
    char *res = NULL;
    res = (char*)malloc(sizeof(char) * INTIMESIZE);
    
    struct tm nowtime;
    nowtime = *localtime(&currtime);
    res[0] = ((nowtime.tm_year + 1900) % 100) / 10 + 48;
    res[1] = ((nowtime.tm_year + 1900) % 10) + 48;
    res[2] = ((nowtime.tm_mon + 1) / 10) + 48;
    res[3] = ((nowtime.tm_mon + 1) % 10) + 48;
    res[4] = ((nowtime.tm_mday) / 10) + 48;
    res[5] = ((nowtime.tm_mday) % 10) + 48;
    res[6] = ((nowtime.tm_hour) / 10) + 48;
    res[7] = ((nowtime.tm_hour) % 10) + 48;
    res[8] = ((nowtime.tm_min) / 10) + 48;
    res[9] = ((nowtime.tm_min) % 10) + 48;
    res[10] = '\0';
    
    return res;
}

char* returntimetoday(void) {
    //오늘 날짜까지 문자열 형태로 반환
    time_t currtime;
    time(&currtime);
    char *res = NULL;
    res = (char*)malloc(sizeof(char) * LIMITTIMESIZE);
    
    struct tm nowtime;
    nowtime = *localtime(&currtime);
    res[0] = ((nowtime.tm_year + 1900) % 100) / 10 + 48;
    res[1] = ((nowtime.tm_year + 1900) % 10) + 48;
    res[2] = ((nowtime.tm_mon + 1) / 10) + 48;
    res[3] = ((nowtime.tm_mon + 1) % 10) + 48;
    res[4] = ((nowtime.tm_mday) / 10) + 48;
    res[5] = ((nowtime.tm_mday) % 10) + 48;
    res[6] = '\0';
    
    return res;
}

int checkBill(Parkcar selected) {
    int res = 0, year, *mon, hour, min;
    char* now;
    now = returntimetomin();
    //년 계산
    year = Stringtoint(substring(now, YEARINTIME, TIMESECTORLEN)) - Stringtoint(substring(selected.intime, YEARINTIME, TIMESECTORLEN));
    //월 계산
    //시작월이 현재 월보다 클 경우
    if(Stringtoint(substring(now, MONINTIME, TIMESECTORLEN)) < Stringtoint(substring(selected.intime, MONINTIME, TIMESECTORLEN))) {
        if(Stringtoint(substring(now, YEARINTIME, TIMESECTORLEN)) >
           Stringtoint(substring(selected.intime, YEARINTIME, TIMESECTORLEN))) {
            year -= 1;
            mon = (int*)malloc(sizeof(int) *
                               (12 - ((Stringtoint(substring(selected.intime, MONINTIME, TIMESECTORLEN)) - Stringtoint(substring(now, MONINTIME, TIMESECTORLEN))))));
            int j = 0;
            for(int i = Stringtoint(substring(selected.intime, MONINTIME, TIMESECTORLEN)); i != Stringtoint(substring(now, MONINTIME, TIMESECTORLEN)); i++) {
                mon[j] = i;
                j += 1;
                if(i == 12) i = 0;
            }
        }
        else {
            printf("잘못된 입력입니다.");
            exit(1);
        }
        
    }
    //시작 월이 현재 월보다 작을 경우
    else {
        if(Stringtoint(substring(now, YEARINTIME, TIMESECTORLEN)) >= Stringtoint(substring(selected.intime, YEARINTIME, TIMESECTORLEN))) {
            
        }
    }
    
    
    
    return res;
}

int Stringtoint(char *str) {
    int res = 0, w = 1;
    unsigned long length;
    length = strlen(str);
    for (int i = (int)length - 1; i >= 0; i--) {
        res += (str[i] - 48) * w;
        w *= 10;
    }
    return res;
}

char* substring(char *str, int start, int length) {
    char *res;
    res = (char*)malloc(sizeof(char) * length + 1);
    strncpy(res, &str[start], length);
    res[length] = '\0';
    return res;
}
