#ifndef _MUTILTIMER_H_
#define _MUTILTIMER_H_

#include "ev.h"
#include "setTime.h"
#include <time.h>

typedef struct timer{
    int timerName;
    TIME clock;
    ev_timer timeout_watcher;
    struct timer *pnext;
}TIMER;


TIMER* insertTimer(TIME t);
void deleteTimer(int num);
void sort();
void printList(void);

extern TIMER *front;
extern TIMER *rear;  
#endif