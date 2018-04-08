#ifndef _TIME_H_
#define _TIME_H_

#include "ev.h"
#include <time.h>

typedef struct tm TIME;

typedef struct info{
    TIME time;
    double seconds;
}INFO;

INFO inputSec(void);

#endif