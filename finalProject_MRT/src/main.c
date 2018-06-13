#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "hiredis.h"
#include "Path.h"
#include "Price.h"

int main(int argc, char **argv){
    pid_t child_pid;
    child_pid = fork();
    if(child_pid < 0){
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(child_pid == 0){
        daemon(1, 0);
        execl("./redis-server", "redis-server", (char*)0);
    }
    else{
        FILE *pFILE = NULL;

        redisContext *c = redisConnect("127.0.0.1", 6379);
        redisCommand(c, "flushall");

        readFile("docs/TaipeiMetroPrice.csv", &pFILE);
        setPrice(c, pFILE);

        readFile("docs/station.txt", &pFILE);
        setPath(c, pFILE);

        TwoDArray Time[stationNum];
        TwoDArray Predecessor[stationNum];
        initTimeData(Time);
        initInterData(Predecessor);
        
        readFile("docs/TaipeiMetroNumberTime.csv", &pFILE);
        setTime(&pFILE, Time, Predecessor);
        FloydWarshall(Time, Predecessor);
        
        StreamData streamData = {
            .fromMark = malloc(sizeof(char) * 1024),
            .fromNode = malloc(sizeof(char) * 1024),
            .toMark = malloc(sizeof(char) * 1024),
            .toNode = malloc(sizeof(char) * 1024),
        };

        streamData.fromMark = argv[1];
        streamData.fromNode = argv[2];
        streamData.toMark = argv[3];
        streamData.toNode = argv[4];

        printPathTime(c, Predecessor, Time, streamData);
        printPrice(c, streamData.fromNode, streamData.toNode);
        
        kill(child_pid+1, SIGKILL);  
    }
    return 0;
}