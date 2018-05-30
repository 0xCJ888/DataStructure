#ifndef _MUTILTIMER_H_
#define _MUTILTIMER_H_

#include "ev.h"
#include "setTime.h"
#include <time.h>

typedef struct timer{
    unsigned int timerName;
    TIME clock;
    REPEAT repeat;
    ev_timer timeout_watcher;
    struct timer *next;
}TIMER;


TIMER* insertTimer(TIME t);
void deleteTimer(EV_P_ int num);
void printList(void);

//extern TIMER *front;
//extern TIMER *rear;  
#endif