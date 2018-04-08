#include "multiTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

TIMER *front = NULL;
TIMER *rear = NULL;

/* insert at the rear */
TIMER* insertTimer(TIME t){
    TIMER *tmp = (TIMER*) malloc(sizeof(TIMER));
    if(tmp == NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        exit(1);
    }
    tmp->clock = t;
    tmp->next = NULL;
    if(rear == NULL)
        front = tmp;
    else
        rear->next = tmp;
    rear = tmp;
    return tmp;
}

/* delete from front */
void deleteTimer(TIME *t){
    TIMER *tmp;
    if(front == NULL)
        printf("Timer is empty\n");
    tmp = front;
    front = front->next;
    /* only one node */
    if(front == NULL)
        rear = NULL;
    *t = tmp->clock;
    free(tmp);
}
