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
        redisCommand(c, "flushall");

        createCards(c);
        checkDeck(c);

        for(int i = 0; i < playerNum; i++){
            deal(&player[i], c);
            cardInHand(&player[i], c);
                
            findPair(&player[i], c);
            puts("Pair");
            printList(&player[i], c, PAIR);
            findFullHouse(&player[i], c);
            puts("FULLHOUSE");
            printList(&player[i], c, FULLHOUSE);
            findFourOfAKind(&player[i], c);
            puts("FOUROFKIND");
            printList(&player[i], c, FOUROFKIND);
            //findStraight(&player[i], c);
        }

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