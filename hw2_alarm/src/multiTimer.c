#include "ev.h"
#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

TIMER *front = NULL;
TIMER *rear = NULL;

/* insert at the rear */
TIMER* insertTimer(TIME t){
    TIMER *current = (TIMER*) malloc(sizeof(TIMER));
    if(current == NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        exit(1);
    }
    current->clock = t;
    current->next = NULL;
    if(rear == NULL)
        front =current;
    else
        rear->next = current;
    rear = current;
    return current;
}

/* delete */
void deleteTimer(EV_P_ int num){
    TIMER *current;
    TIMER *previous = NULL;
    if(front == NULL)
        printf("Timer is empty\n");
    current = front;

    while((current != NULL) && current->timerName != num){
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        printf("There is no timer %d  can delete!\n", num);
    /* first node */
    else if(current == front){
        front = current->next;
        printf("Timer %hhd is deleted\n", current->timerName);
        ev_timer_stop(EV_A_ &current->timeout_watcher);
        free(current);
    }
    else{
        previous->next = current->next;
        printf("Timer %hhd is deleted\n", current->timerName);
        ev_timer_stop(EV_A_ &current->timeout_watcher);
        free(current);
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