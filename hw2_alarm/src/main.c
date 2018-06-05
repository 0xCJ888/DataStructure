#include "ev.h"
#include "setTime.h"
#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct ev_loop* alarmLoop;
ev_io stdin_readable;
typedef enum {insert=1, delete, view, update, quit}MODE;
INFO info;
TIMER* timer;
unsigned char number = 0;
int alarmNum = 0;

static void timeout_cb (EV_P_ ev_timer *timer_w, int revents){
    printf("Tiemr %d is ring\n", *((int*)(timer_w->data)));
}

static void stdin_readable_cb (EV_P_ ev_io *w, int revents){
    bool check = false;
    char ref;
    
    /* io input */
    do{
        check = false;
        ref = scanf("%hhd", &number);
        char c = getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        switch(number){
            case insert: case delete: case view: case update: case quit:
                check = false;
                break;
            default:
                printf("Please input 1~5\n");
                break;
        }
    }while(check);

    /* mode control */
    switch(number){
        case update:
            number = selectDel();
            deleteTimer(alarmLoop, number);
        case insert:
            alarmNum++;
            info = inputSec();
            timer = insertTimer(info.time);
            timer->timerName = alarmNum;
            timer->timeout_watcher.data = &(timer->timerName);
            timer->repeat = isRepeat();

            if (timer->repeat.isRepeat){
                ev_timer_init(&timer->timeout_watcher, timeout_cb, info.seconds, timer->repeat.RepeatTime);
            }
            else{
                ev_timer_init(&timer->timeout_watcher, timeout_cb, info.seconds, 0.);
            }
            ev_timer_start(alarmLoop, &timer->timeout_watcher);
            break;
        case delete:
            number = selectDel();
            deleteTimer(alarmLoop, number);
            break;
        case view:
            printList();
            break;
        case quit:
            puts("Quit!\n");
            exit(1);
            break;
    }

    printf("[1]Insert alarm [2]Delete alarm [3]Dump [4]Update [5]Quit\n");
}

int main(void){   
    alarmLoop = EV_DEFAULT;

    printf("[1]Insert alarm [2]Delete alarm [3]Dump [4]Update [5]Quit\n");
    ev_io_init (&stdin_readable, stdin_readable_cb, 0, EV_READ);
    ev_io_start (alarmLoop, &stdin_readable);
    
    ev_run(alarmLoop,0);

    return 0;
}
