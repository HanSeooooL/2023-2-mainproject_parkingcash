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
int checkMaxDayofMonth(int year, int month); //특정 년월의 일수 체크
int checkParkingdays(char *starttime);    //주차기간 체크
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
    
    int res = 0, days;
    
    days = checkParkingdays(selected.intime);
    
    
    
    return res;
}

int checkParkingdays(char *starttime) {
    int res = -1, year = 0, mon = 0, day = 0, hour = 0, min = 0, hourw = 0, dayw = 0, monw = 0, yearw = 0;
    char* now;
    now = returntimetomin();
    
    //연산
    //분
    if(Stringtoint(substring(starttime, MININTIME, TIMESECTORLEN)) > Stringtoint(substring(now, MININTIME,TIMESECTORLEN))) {
        hourw -= 1;
        min = (Stringtoint(substring(now, MININTIME, TIMESECTORLEN)) + 60) - Stringtoint(substring(starttime, MININTIME, TIMESECTORLEN));
    }
    else min = Stringtoint(substring(now, MININTIME, TIMESECTORLEN)) - Stringtoint(substring(starttime, MININTIME, TIMESECTORLEN));
    //시
    if(Stringtoint(substring(starttime, HOURINTIME, TIMESECTORLEN)) > (Stringtoint(substring(now, HOURINTIME, TIMESECTORLEN)) + hourw)) {
        dayw -= 1;
        hour = (Stringtoint(substring(now, HOURINTIME, TIMESECTORLEN)) + hourw + 24) -
        Stringtoint(substring(starttime, HOURINTIME, TIMESECTORLEN));
    }
    else hour = (Stringtoint(substring(now, HOURINTIME, TIMESECTORLEN)) + hourw) - Stringtoint(substring(starttime, HOURINTIME, TIMESECTORLEN));
    
    //일
    if(Stringtoint(substring(starttime, DAYINTIME, TIMESECTORLEN)) > Stringtoint(substring(now, DAYINTIME, TIMESECTORLEN)) + dayw) {
        int monthweight;
        monw -= 1;
        monthweight = checkMaxDayofMonth(Stringtoint(substring(now, YEARINTIME, TIMESECTORLEN)), Stringtoint(substring(now, MONINTIME, TIMESECTORLEN)) + monw);
        day = (Stringtoint(substring(now, DAYINTIME, TIMESECTORLEN)) + dayw + monthweight) -
        Stringtoint(substring(starttime, DAYINTIME, TIMESECTORLEN));
    }
    else day = (Stringtoint(substring(now, DAYINTIME, TIMESECTORLEN)) + dayw) - Stringtoint(substring(starttime, DAYINTIME, TIMESECTORLEN));
    
    //월
    if(Stringtoint(substring(starttime, MONINTIME, TIMESECTORLEN)) > Stringtoint(substring(now, MONINTIME, TIMESECTORLEN)) + monw) {
        yearw -= 1;
        
        
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

int checkMaxDayofMonth(int year, int month) {
    int res = 0;
    
    if (month < 8) {
        if(month % 2 == 1) {
            res = 31;
        }
        else {
            if(month == 2) {
                if(year % 4 == 0) res = 29;
                else res = 28;
            }
            else res = 30;
        }
    }
    else {
        if (month % 2 == 0) res = 30;
        else res = 31;
    }
    
    return res;
}
