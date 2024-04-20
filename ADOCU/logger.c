//
// Created by PC on 20/04/2024.
//

#include "logger.h"
#include <stdio.h>
#include <time.h>

void logAction(const char* action, const char* username){
    FILE* file = fopen("log.txt", "a");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(file, "%d-%02d-%02d %02d:%02d:%02d - accion: %s realizada por: %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, action, username);
}
