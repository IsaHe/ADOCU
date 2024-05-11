#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

void logAction(const char* action, const char* username, int status, ...)  {
    FILE* file = fopen("log.txt", "a");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    switch (status) {
        case 's':
            fprintf(file, "SUCCESS - ");
            break;
        case 'f':
            fprintf(file, "FAIL - ");
            break;
        default:
            break;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(file, "%d-%02d-%02d %02d:%02d:%02d - Accion: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    va_list args;
    va_start(args, status);
    vfprintf(file, action, args);
    va_end(args);

    fprintf(file, " - Realizada por: %s\n", username);
    fclose(file);
}
