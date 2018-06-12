#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "hiredis.h"
#include "dataProcess.h"

int main(){
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
        char line[1024];
        const char* tok;
        uint8_t count = 0;
        uint8_t from, to;
        char* fromNode, toNode;
        FILE* pFILE = NULL;
        redisReply *reply;

        redisContext *c = redisConnect("127.0.0.1", 6379);
        redisCommand(c, "flushall");

        readFile("docs/stationLineNum_121.csv", &pFILE);
        while(fgets(line, 1024, pFILE)){
            tok = strtok(line, "\n");
            redisCommand(c, "set %s %d", tok, count);
            count++;
        }
        
        reply = redisCommand(c, "keys *");
        
        TwoDArray Distance[stationNum];
        TwoDArray Predecessor[stationNum];
        initTimeData(Distance);
        initInterData(Predecessor);
        readFile("docs/TaipeiMetroNumberTime.csv", &pFILE);
        setTimeField(&pFILE, Distance, Predecessor);
        FloydWarshall(Distance, Predecessor);
        
        while(1){
            printf("from:");
            scanf("%s", &from);
            printf("to:");
            scanf("%s", &to);
            findShortestPath(Predecessor, from, to); 
        }
        
    }
    return 0;
}