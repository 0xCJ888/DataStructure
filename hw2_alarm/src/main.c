#include "ev.h"
#include "setTime.h"
#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef enum {insert=1, delete, view, update, quit}MODE;
INFO info;
unsigned char number = 0;
int alarmNum = 0;

static void timeout_cb (EV_P_ ev_timer *timer_w, int revents){
    printf("Tiemr %d is ring\n", *((int*)(timer_w->data)));
}

static void stdin_readable_cb (struct ev_loop *loop, ev_io *w, int revents){
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
            
        case insert:{
            alarmNum++;
            info = inputSec();
            TIMER* timer = insertTimer(info.time);
            timer->timerName = alarmNum;
            timer->timeout_watcher.data = &(timer->timerName);
            timer->repeat = isRepeat();

            if (timer->repeat.isRepeat){
                ev_timer_init(&timer->timeout_watcher, timeout_cb, info.seconds, timer->repeat.RepeatTime);
            }
            else{
                ev_timer_init(&timer->timeout_watcher, timeout_cb, info.seconds, 0.);
            }
            ev_timer_start(loop, &timer->timeout_watcher);
        }
            break;
        case delete:
            number = selectDel();
            printf("number = %hhd\n", number);
            deleteTimer(number);
            break;
        case view:
            printList();
            break;
        case quit:
            puts("Quit!\n");
            exit(1);
            break;
    }

    printf("[1]Insert alarm [2]Delete alarm [3]ViewAlarmList [4]Update [5]Quit\n");
}

int main(void){   
    
    struct ev_loop *loop = EV_DEFAULT;
    ev_io stdin_readable;

    printf("[1]Insert alarm [2]Delete alarm [3]ViewAlarmList [4]Update [5]Quit\n");
    ev_io_init (&stdin_readable, stdin_readable_cb, 0, EV_READ);
    ev_io_start (loop, &stdin_readable);
    
    ev_run(loop,0);

    return 0;
}
