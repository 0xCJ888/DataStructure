#include "ev.h"
#include "setTime.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

INFO inputSec(void){
    INFO info;
    bool check = false;
    int ref;
    double seconds;
    time_t now;
    now = time(NULL);
    printf("Right now time is %s\n", ctime(&now));

    printf("Please input time which you want to set\n");
    /* set year */
    do{
        check = false;
        printf("year(began at 2018)=");
        ref = scanf("%d", &info.time.tm_year);
        getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        else if(info.time.tm_year < 2018){
            printf("Please input year starting from 2018\n");
            check = true;
        }
    }while(check);
    info.time.tm_year -= 1900;
    /* set month */
    do{
        check = false;
        printf("month(1~12)=");
        ref = scanf("%d", &info.time.tm_mon);
        getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        else if(info.time.tm_mon <= 0 || info.time.tm_mon > 12){
            printf("Please input 1~12 month\n");
            check = true;
        }
    }while(check);
    info.time.tm_mon -= 1;
    /* set day */
    do{
        check = false;
        printf("day(1~31)=");
        ref = scanf("%d", &info.time.tm_mday);
        getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        else if(info.time.tm_mday <= 0 || info.time.tm_mday > 31){
            printf("Please input 0~31 days\n");
            check = true;
        }
    }while(check);
    /* set hour */
    do{
        check = false;
        printf("hour(24H)=");
        ref = scanf("%d", &info.time.tm_hour);
        getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        else if(info.time.tm_hour < 0 || info.time.tm_hour >= 24){
            printf("Please input 0~23 hours\n");
            check = true;
        }
    }while(check);
    /* set min */
    do{
        check = false;
        printf("minute=");
        ref = scanf("%d", &info.time.tm_min);
        fflush(stdin);
        getchar();
        if(info.time.tm_min < 0 || info.time.tm_min >= 60){
            printf("Please input 0~59 min \n");
            check = true;
        }
    }while(check);
    /* set sec */
    do{
        check = false;
        printf("second=");
        ref = scanf("%d", &info.time.tm_sec);
        fflush(stdin);
        getchar();
        if(info.time.tm_sec < 0 || info.time.tm_sec >= 60){
            printf("Please input 0~59s\n");
            check = true;
        }
    }while(check);

    time_t set = mktime(&info.time);
    printf("setting time is %s\n", ctime(&set));
    info.seconds = difftime(mktime(&info.time), now);

    return info;
}

REPEAT isRepeat(void){
    char ref;
    int num;
    bool check = false;
    REPEAT Repeat;
    puts("Do you want to repeat alarm? [1] YES [2] NO");
    do{
        check = false;
        ref = scanf("%d", &num);
        getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        if(num!=1 && num !=2){
            puts("Please input number 1 or 2");
            check = true;
        }
    }while(check);
    
    if(num == 1)
        Repeat.isRepeat = true;
    else if (num == 2)
        Repeat.isRepeat = false;

    if(num == 1){
        puts("input how much time you want to repeat?");
        do{
            check = false;
            ref = scanf("%d", &num);
            getchar();
            if (ref == 0){
                puts("Plese input integer");
                check = true;
            }
        }while(check);
        Repeat.RepeatTime = num;
    }
    return Repeat;
}

int selectDel(void){
    char ref;
    int timerSelect;
    puts("Select which timer you want to delete");
    ref = scanf("%d", &timerSelect);
    getchar();
    if(ref == 0)
        printf("Please input a integer\n");
    return timerSelect;
}

int selectModify(void){
    char ref;
    int timerSelect;
    puts("Which timer you want to modify?");
    ref = scanf("%d", &timerSelect);
    getchar();
    if(ref == 0)
        printf("Please input a integer\n");
    return timerSelect;
}