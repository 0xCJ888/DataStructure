#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#include "hiredis.h"

#define stationNum 140


typedef struct _feildData FeildData;
typedef struct _twoDArray TwoDArray;
typedef struct _vertex Vertex;

struct _feildData{
    uint8_t from;
    uint8_t to;
    uint8_t intvTime;
};

struct _twoDArray{
    int colData[stationNum];
};

struct _vertex{
    int station;
    struct _vertex* nextVertex;
};

void readFile(const char* fileName, FILE** pFile);
void setTimeField(FILE** pFile, TwoDArray* Distance, TwoDArray* Predecessor);
void initTimeData(TwoDArray* twoDArray);
void initInterData(TwoDArray* twoDArray);
void printArrayData(TwoDArray* twoDArray);
void FloydWarshall(TwoDArray* Distance, TwoDArray* Predecessor);
void findShortestPath(TwoDArray* Predecessor, uint8_t from, uint8_t to, redisContext *c);
void pushVertex(Vertex** head, const int station);
void printVertex(Vertex* head, redisContext *c);

#endif //__DATAPROCESS_H__