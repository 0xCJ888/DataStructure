#include <stdio.h>
#include <stdlib.h>     /* atoi*/
#include <string.h>
#include <unistd.h>

#include "hiredis.h"
#include "card.h"
#include "player.h"

void checkConnection(redisContext *c);

int main(){
    pid_t pid;
    /* fork another porcess */
    pid = fork();
    if(pid < 0){ /* error occurred */
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid == 0){ /* child process */
        daemon(1, 0);
        execl("./redis-server", "redis-server", (char *)0);
    }
    else{ /* parent process */
        Player player[playerNum] = {[0] = { .playerName = "PlayerA"},
                                    [1] = { .playerName = "PlayerB"},
                                    [2] = { .playerName = "PlayerC"},
                                    [3] = { .playerName = "PlayerD"}};
        redisContext *c;
        c = redisConnect("127.0.0.1", 6379);
        checkConnection(c);

        createCards(c);
        checkDeck(c);

        for(int i = 0; i < playerNum; i++){
            deal(&player[i], c);
            cardInHand(&player[i], c);

            findPair(&player[i], c);
            findStraight(&player[i], c);
        }

        /* clean all */
        redisCommand(c, "flushall");
        redisFree(c);

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