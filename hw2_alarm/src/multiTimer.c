#include "ev.h"
#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

TIMER *front = NULL;
TIMER *rear = NULL;

/* insert */
TIMER* insertTimer(TIME t){
    TIMER *addNewTimer = (TIMER*) malloc(sizeof(TIMER));
    if(!addNewTimer){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        exit(1);
    }
    addNewTimer->clock = t;
    addNewTimer->next = NULL;

    TIMER *tmp = front;
    TIMER *prev = NULL;

    /* insertion sort */
    for(;tmp && (mktime(&tmp->clock) < mktime(&t));){
        prev = tmp;
        tmp = tmp->next;
    }

    /* insertfront */
    if(!prev){
        addNewTimer->next = front;
        front = addNewTimer;
    }
    /* insert */
    else{
        if(!tmp){   //append 
            prev->next = addNewTimer;
        }
        else{   //insertAfter
            addNewTimer->next = tmp;
            prev->next = addNewTimer;
        }
    }
    return addNewTimer;
}

/* delete */
void deleteTimer(EV_P_ int num){
    TIMER *addNewTimer;
    TIMER *previous = NULL;
    if(front == NULL)
        printf("Timer is empty\n");
    addNewTimer = front;

    while((addNewTimer != NULL) && addNewTimer->timerName != num){
        previous = addNewTimer;
        addNewTimer = addNewTimer->next;
    }

    if (addNewTimer == NULL)
        printf("There is no timer %d  can delete!\n", num);
    /* first node */
    else if(addNewTimer == front){
        front = addNewTimer->next;
        printf("Timer %hhd is deleted\n", addNewTimer->timerName);
        ev_timer_stop(EV_A_ &addNewTimer->timeout_watcher);
        free(addNewTimer);
    }
    else{
        previous->next = addNewTimer->next;
        printf("Timer %hhd is deleted\n", addNewTimer->timerName);
        ev_timer_stop(EV_A_ &addNewTimer->timeout_watcher);
        free(addNewTimer);
    }
}

void printList(void){
    TIMER* point;
    point = front;
    if(point == NULL)
        puts("No Timer now!\n");
    puts("--------------------------------------------");
    puts("Timer\t\trepeatTime(s)\t\ttime");
    for(; point != NULL; point = point->next){
        time_t t = mktime(&point->clock);
        printf("%d\t\t%d\t\t\t%s\n", point->timerName, point->repeat.RepeatTime, ctime(&t));
    }
}