#ifndef _TIME_H_
#define _TIME_H_

#include "ev.h"
#include <stdbool.h>
#include <time.h>

typedef struct tm TIME;

typedef struct info{
    TIME time;
    double seconds;
}INFO;

typedef struct repeat{
    bool isRepeat;
    int RepeatTime;
}REPEAT;

INFO inputSec(void);
REPEAT isRepeat(void);
int selectDel(void);

#endif