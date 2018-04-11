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
    current->pnext = NULL;
    if(rear == NULL)
        front = current;
    else
        rear->pnext = current;
    rear = current;
    return current;
}

void deleteTimer(int num){
    TIMER *current;
    TIMER *previous = NULL;
    if(front == NULL)
        printf("Timer is empty\n");
    current = front;

    while((current != NULL) && current->timerName != num){
        previous = current;
        current = current->pnext;
    }

    if (current == NULL)
        printf("There is no timer %d  can delete!\n", num);
    /*TIMER */
    else if(current == front){
        front = current->pnext;
        printf("Timer %hhd is deleted\n", current->timerName);
        free(current);
    }
    else{
        previous->pnext = current->pnext;
        printf("Timer %hhd is deleted\n", current->timerName);
        free(current);
    }
    
}

void sort(void){
    TIMER *tail = front;
    TIMER *tmp = front;
    TIMER *current = front;
    TIMER *prev = front;

    int size = 0;
    while(tail){
        tail = tail->pnext;
        size++; 
    }
    printf("size = %d\n", size);

    for (int i = size; i > 0; i--){
        current = front;
        prev = front;
        for(int j = 0; j < i - 1 && current->pnext; j++){
            if(difftime(mktime(&current->pnext->clock), mktime(&current->clock)) > 0.){
                tmp = current->pnext;
                current->pnext = tmp->pnext;
                tmp->pnext = current;
                if(current == front){
                    front = tmp;
                    prev = tmp;
                }
                else{
                    prev->pnext=tmp;
                    prev = prev->pnext;
                }
            }
            else{
                current = current->pnext;
                if(j!=0) prev = prev->pnext;
            }   
        }
    }
}

/* sort by time */
void printList(void){
    TIMER* point;
    point = front;
    if(point == NULL)
        puts("No Timer now!\n");
    sort();
    /* print timer */
    for(; point != NULL; point = point->pnext){
        time_t t = mktime(&point->clock);
        printf("Timer %d set time is %s\n", point->timerName, ctime(&t));
    }
}