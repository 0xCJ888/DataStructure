#include "Price.h"

void setPrice(redisContext *c, FILE *pFILE){
    PriceData priceData;
    char line[1024];
    while (fgets(line, 1024, pFILE)){
        priceData.departure = strtok(line, ",");
        priceData.destination = strtok(NULL, ",");
        priceData.singleJourney = strtok(NULL, ",");
        priceData.easyCard = strtok(NULL, ",");
        priceData.senior = strtok(NULL, "\r\n");
        redisCommand(c, "RPUSH %s\t%s %s %s %s", priceData.departure, priceData.destination, priceData.singleJourney, priceData.easyCard, priceData.senior);
    }
    fclose(pFILE);
}

void printPrice(redisContext *c, const char *departure, const char *destination){
    redisReply *reply;
    reply = redisCommand(c, "LRANGE %s\t%s 0 -1", departure, destination);
    for(int i = 0; i < reply->elements; i++){
        if(i == 0)
            printf("Single-Journey Ticket : NT$%s\n", reply->element[i]->str);
        else if(i == 1)
            printf("EasyCard/iPASS : NT$%s\n", reply->element[i]->str);
        else if(i == 2)
            printf("Senior, Charity and Companion Cards : NT$%s\n", reply->element[i]->str);
    }
    puts("");
}