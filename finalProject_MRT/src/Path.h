#ifndef __PATH_H__
#define __PATH_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#include "hiredis.h"
#include "Price.h"

#define stationNum 140


typedef struct _TimeData TimeData;
typedef struct _twoDArray TwoDArray;
typedef struct _vertex Vertex;

struct _TimeData{
    uint8_t from;
    uint8_t to;
    uint8_t intvTime;
};

struct _twoDArray{
    int colData[stationNum];
};

struct _vertex{
    int station;
    struct _vertex *nextVertex;
};

void readFile(const char *fileName, FILE **pFile);
void setPath(redisContext *c, FILE *pFILE);
void setTime(FILE **pFile, TwoDArray *Distance, TwoDArray *Predecessor);
void initTimeData(TwoDArray *twoDArray);
void initInterData(TwoDArray *twoDArray);
void printArrayData(TwoDArray *twoDArray);
void FloydWarshall(TwoDArray *Distance, TwoDArray *Predecessor);
void findShortestPath(TwoDArray *Predecessor, uint8_t from, uint8_t to, redisContext *c);
void pushVertex(Vertex **head, const int station);
void printVertex(Vertex *head, redisContext *c);
void printPathTime(redisContext *c, TwoDArray *Predecessor, TwoDArray *Time, StreamData streamData);

#endif //__PATH_H__