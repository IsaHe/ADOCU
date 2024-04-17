#include "sqlite3.h"
#include "user.h"

#ifndef VALORATION_H_
#define VALORATION_H_

typedef struct {
    char valoration;
} Valoration;

Valoration insertIntoValoration(char valoration);
int insertUserValorationInDB(Valoration valoration, User user, sqlite3* db);
int readUserValorationsFromDB(sqlite3* db);

#endif
