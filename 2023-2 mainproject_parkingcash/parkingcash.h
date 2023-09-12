//
//  parkingcash.h
//  2023-2 mainproject_parkingcash
//
//  Created by 한설 on 2023/08/18.
//

#ifndef parkingcash_h
#define parkingcash_h

#define FAIL -1

#define CARNUMBERSIZE 11        //차량번호크기
#define PHONENUMBERSIZE 14      //전화번호크기
#define INTIMESIZE 11           //입차시간크기
#define LIMITTIMESIZE 7         //만료날짜크기
#define YEARINTIME 0            //시간 데이터에서의 연도 위치
#define MONINTIME 2             //시간 데이터에서의 월 위치
#define DAYINTIME 4             //시간 데이터에서의 일 위치
#define HOURINTIME 6            //시간 데이터에서의 시간 위치
#define MININTIME 8             //시간 데이터에서의 분 위치
#define TIMESECTORLEN 2         //시간 데이터에서의 각 구간 길이


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef struct _parkcar {
    char carnumber[CARNUMBERSIZE];  //차량번호
    char phonenumber[PHONENUMBERSIZE];  //전화번호
    char intime[INTIMESIZE];        //입차시간
} Parkcar;

typedef struct _commuterinfo {
    char carnumber[CARNUMBERSIZE];  //차량번호
    char limittimesize[LIMITTIMESIZE];  //만료날짜
} Commuterinfo;

//programinside
void init_Parkingcarinfo(void);
void init_Commuterinfo(void);
void Carin(Parkcar newone);
void Carread(void);
void Carout(char *carnumber);
void addCommuter(char *addcar);



#endif /* parkingcash_h */
