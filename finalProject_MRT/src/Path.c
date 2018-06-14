#include "Path.h"

void readFile(const char *fileName, FILE **pFILE){
    *pFILE = fopen(fileName, "r");
    if(!*pFILE){
        perror ("Error opening file");
    }
}

void setPath(redisContext *c, FILE *pFILE){
    uint8_t count = 0;
    char line[1024];
    const char *tok;
    while(fgets(line, 1024, pFILE)){
        tok = strtok(line, "\r\n");
        redisCommand(c, "SET %s %d", tok, count);
        redisCommand(c, "SET %d %s", count, tok);
        count++;
    }
    fclose(pFILE);
}

void setTime(FILE *pFILE, TwoDArray *Distance, TwoDArray *Predecessor){
    TimeData timeData;
    char line[1024];
    const char* tok;
    while(fgets(line, 1024, pFILE)){
        tok = strtok(line, ",");
        timeData.from = atoi(tok);
        tok = strtok(NULL, ",");
        timeData.to = atoi(tok);
        tok = strtok(NULL, ",");
        timeData.intvTime = atoi(tok);
        Distance[timeData.from].colData[timeData.to] = timeData.intvTime;
        Distance[timeData.to].colData[timeData.from] = timeData.intvTime;
        Predecessor[timeData.from].colData[timeData.to] = timeData.from;
        Predecessor[timeData.to].colData[timeData.from] = timeData.to;
    }
    fclose(pFILE);
}

void initTimeData(TwoDArray *twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            if(i == j)
                twoDArray[i].colData[j] = 0;
            else
                twoDArray[i].colData[j] = USHRT_MAX;
        }
    }
}

void initInterData(TwoDArray *twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            twoDArray[i].colData[j] = -1;
        }
    }
}

void printArrayData(TwoDArray *twoDArray){
    for(int i = 0; i < stationNum; i++){
        for(int j = 0; j < stationNum; j++){
            printf("%d\t", twoDArray[i].colData[j]);
        }
        getchar();
        puts("");
    }
}

void FloydWarshall(TwoDArray *Distance, TwoDArray *Predecessor){
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

void findShortestPath(TwoDArray *Predecessor, uint8_t from, uint8_t to, redisContext *c){
    int station;
    Vertex *head = NULL;
    pushVertex(&head, to);
    do{
        station = Predecessor[from].colData[to];
        if(station != -1)
            pushVertex(&head, station);
        to = station;
    }while(station != -1);

    printVertex(head, c);
}

void pushVertex(Vertex **head, const int station){
    Vertex *tmp = (Vertex*)malloc(sizeof(Vertex));
    tmp->station = station;
    tmp->nextVertex = *head;
    *head = tmp;
}

void printVertex(Vertex *head, redisContext *c){
    redisReply *reply;
    Vertex *current = head;
    puts("Travel path");
    while(current){
        reply = redisCommand(c, "GET %d", current->station);
        printf("%s\n", reply->str);
        current = current->nextVertex;
    }
    puts("");
}

void printPathTime(redisContext *c, TwoDArray *Predecessor, TwoDArray *Time, StreamData streamData){
    uint8_t from, to;
    redisReply *reply;
    reply = redisCommand(c, "GET %s\t%s", streamData.fromMark, streamData.fromNode);
    if(!reply->str)
        goto EXIT;    
    from = atoi(reply->str);
    reply = redisCommand(c, "GET %s\t%s", streamData.toMark, streamData.toNode);
    if(!reply->str)
        goto EXIT;
    to = atoi(reply->str);
    findShortestPath(Predecessor, from, to, c);
    printf("Travel time : %.1f min\n\n", Time[from].colData[to] / 60.0f);
    return;
    EXIT:
        perror("Wrong input!!");
        exit(0);
}