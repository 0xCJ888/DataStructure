#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define stationNum 108

uint8_t AdjMatrix[stationNum][stationNum];

void splitField(char* line);
void initializeData();


#endif