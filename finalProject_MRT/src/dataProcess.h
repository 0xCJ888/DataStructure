#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define stationNum 108


typedef struct _feildData FeildData;
typedef struct _twoDArray TwoDArray;
struct _feildData{
    uint8_t from;
    uint8_t to;
    uint8_t intvTime;
};

struct _twoDArray{
    int colData[stationNum];
};

void readFile(const char* fileName, FILE** pFile);
void setTimeField(FILE** pFile, TwoDArray* Distance, TwoDArray* Predecessor);
void initTimeData(TwoDArray* twoDArray);
void initInterData(TwoDArray* twoDArray);
void printArrayData(TwoDArray* twoDArray);

#endif //__DATAPROCESS_H__