#include "dataProcess.h"

void splitField(char* line){
    const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",")){
        printf("%s\t", tok);
    }
}

void initalizeData(){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            AdjMatrix[i][j] = 0;
        }
    }
}