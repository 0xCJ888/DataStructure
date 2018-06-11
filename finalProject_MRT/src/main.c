#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataProcess.h"

int main(){
    FILE* pFILE = NULL;
    TwoDArray Distance[stationNum];
    TwoDArray Predecessor[stationNum];
    initTimeData(Distance);
    initInterData(Predecessor);
    readFile("docs/TaipeiMetroNumberTime.csv", &pFILE);
    setTimeField(&pFILE, Distance, Predecessor);
    printf("AdjMetrix:\n");
    printArrayData(Predecessor);
    return 0;
}