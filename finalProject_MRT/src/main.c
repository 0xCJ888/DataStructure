#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataProcess.h"

int main(){
    FILE* pFile;
    pFile = fopen("docs/TaipeiMetroTime.csv", "r");
    if(!pFile){
        fputs("fopen example", pFile);
        fclose(pFile);
    }
    char line[1024];
    while(fgets(line, 1024, pFile)){
        char* tmp = strdup(line);
        printf("tmp %s\n", tmp);
        splitField(tmp);
        free(tmp);
        getchar();
    }
    fclose(pFile);

    return 0;
}