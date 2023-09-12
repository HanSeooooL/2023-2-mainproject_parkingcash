//
//  main.c
//  2023-2 mainproject_parkingcash
//
//  Created by 한설 on 2023/08/18.
//

#include <stdio.h>
#include "parkingcash.h"

extern char* substring(char *str, int start, int length); //문자열 부분 자르기


int main(int argc, const char * argv[]) {
    
    
    init_Parkingcarinfo();    //주차장 정보 초기화
    
    Parkcar a, b, c;
    strcpy(a.carnumber, "123가4567");
    strcpy(a.phonenumber, "010-2173-4577");
    Carin(a);
    strcpy(b.carnumber, "395나2039");
    strcpy(b.phonenumber, "010-3023-3050");
    Carin(b);
    strcpy(c.carnumber, "203피1029");
    strcpy(c.phonenumber, "010-2830-3030");
    Carin(c);
    Carout("123가4567");
    Carread();
    
    return 0;
}
