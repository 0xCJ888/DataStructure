#include "ev.h"
#include "setTime.h"
#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum {insert=1, delete, view, quit}MODE;
INFO info;
unsigned char number = 0;

static void timeout_cb (EV_P_ ev_timer *timer_w, int revents){
    printf("Tiemr %d is ring\n", (int)(timer_w->data));
    // this causes the innermost ev_run to stop iterating
    ev_break (EV_A_ EVBREAK_ONE);
}

static void stdin_readable_cb (struct ev_loop *loop, ev_io *w, int revents){
    ev_io_stop (loop, w); 
    /* read from stdin here and handle any I/O errors */
    bool check = false;
    char ref;

    do{
        check = false;
        ref = scanf("%hhd", &number);
        char c = getchar();
        if(ref == 0){
            printf("Please input a integer\n");
            check = true;
        }
        if(number == quit){
            check = false;
        }
        else if(number == view){
            check = false;
        }
        else if(number != insert && number != delete){
            printf("Please input 1 or 2\n");
            check = true;
        }
    }while(check);
     // this causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}

int main(void){   
    unsigned int alarmNum = 0;
    MODE mode = number;
    struct ev_loop *loop = EV_DEFAULT;
    ev_io stdin_readable;

    for( ;mode != quit; ){
        printf("[1]Insert alarm [2]Delete alarm [3]ViewAlarmList [4]Quit\n");
        ev_io_init (&stdin_readable, stdin_readable_cb, 0, EV_READ);
        ev_io_start (loop, &stdin_readable);
        ev_run(loop,0);

        mode = number;
        switch(mode){
            case insert:{
                alarmNum++;
                info = inputSec();
                TIMER* timer = insertTimer(info.time);
                timer->timeout_watcher.data = (void *) alarmNum;
                ev_timer_stop (loop, &timer->timeout_watcher);
                ev_timer_init(&timer->timeout_watcher, timeout_cb, info.seconds, 0.);
                ev_timer_start(loop, &timer->timeout_watcher);
            }
                break;
            case delete:
                deleteTimer(&info.time);
                break;
            case view:
                printList();
                break;
            case quit:
                puts("Quit!\n");
                exit(1);
                break;
        }
        ev_io_stop (loop, &stdin_readable);
    }
    return 0;
}
