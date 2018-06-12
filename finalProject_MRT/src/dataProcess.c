#include "dataProcess.h"

void readFile(const char* fileName, FILE** pFILE){
    *pFILE = fopen(fileName, "r");
    if(!*pFILE){
        printf("%s open failed\n", fileName);
    }
}

void setTimeField(FILE** pFile, TwoDArray* Distance, TwoDArray* Predecessor){
    FeildData feildData;
    char line[1024];
    const char* tok;
    while(fgets(line, 1024, *pFile)){
        char* tmp = strdup(line);
        tok = strtok(line, ",");
        feildData.from = atoi(tok);
        tok = strtok(NULL, ",");
        feildData.to = atoi(tok);
        tok = strtok(NULL, ",");
        feildData.intvTime = atoi(tok);
        Distance[feildData.from].colData[feildData.to] = feildData.intvTime;
        Distance[feildData.to].colData[feildData.from] = feildData.intvTime;
        Predecessor[feildData.from].colData[feildData.to] = feildData.from;
        Predecessor[feildData.to].colData[feildData.from] = feildData.to;
        free(tmp);
    }
}

void initTimeData(TwoDArray* twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            if(i == j)
                twoDArray[i].colData[j] = 0;
            else
                twoDArray[i].colData[j] = USHRT_MAX;
        }
    }
}

void initInterData(TwoDArray* twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            twoDArray[i].colData[j] = -1;
        }
    }
}

void printArrayData(TwoDArray* twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            printf("%d\t", twoDArray[i].colData[j]);
        }
        getchar();
        puts("");
    }
}

void FloydWarshall(TwoDArray* Distance, TwoDArray* Predecessor){
    for(int k = 0; k < stationNum; k++){
        for(int i = 0; i < stationNum; i++){
            for(int j = 0; j < stationNum; j++){
                if(Distance[i].colData[j] > Distance[i].colData[k] + Distance[k].colData[j] && Distance[i].colData[k] != USHRT_MAX){
                    Distance[i].colData[j] = Distance[i].colData[k] + Distance[k].colData[j];
                    Predecessor[i].colData[j] = Predecessor[k].colData[j];
                }
            }
        }
    }
}

void findShortestPath(TwoDArray* Predecessor, uint8_t from, uint8_t to){
    int station;
    do{
        station = Predecessor[from].colData[to];
        printf("%d\n", station);
        getchar();
        to = station;
    }while(station != -1);
}