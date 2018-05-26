#include <stdio.h>
#include <stdlib.h>     /* atoi*/
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "hiredis.h"
#include "card.h"
#include "player.h"

void checkConnection(redisContext *c);

int main(){
    pid_t child_pid;
    /* fork another porcess */
    child_pid = fork();
    if(child_pid < 0){ /* error occurred */
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(child_pid == 0){ /* child process */
        daemon(1, 0);
        execl("./redis-server", "redis-server", (char *)0);
    }
    else{ /* parent process */
        Player player[playerNum] = {[0] = { .playerName = "PlayerA"},
                                    [1] = { .playerName = "PlayerB"},
                                    [2] = { .playerName = "PlayerC"},
                                    [3] = { .playerName = "PlayerD"}};
        redisContext *c = redisConnect("127.0.0.1", 6379);
        checkConnection(c);

        createCards(c);
        checkDeck(c);

        for(int i = 0; i < playerNum; i++){
            deal(&player[i], c);
            cardInHand(&player[i], c);
                
            puts("find pair");
            findMultiCards(&player[i], c, PAIR);
            puts("RANGE");
            redisReply *replyLRANGE = redisCommand(c, "LRANGE %sPAIR %d %d", player[i].playerName, 0, -1);
            if(replyLRANGE->type == REDIS_REPLY_ARRAY){
                for(int j = 0; j < replyLRANGE->elements; j++){
                    printf("%s\n", replyLRANGE->element[j]->str);
                }
            }
            //findStraight(&player[i], c);
        }

        /* clean all */
        redisCommand(c, "flushall");
        redisFree(c);

        /* kill daemon */
        kill(child_pid+1, SIGKILL);
        return 0;
    }
}

void checkConnection(redisContext *c){
    if(c == NULL || c->err){
        if(c){
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        }else{
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}