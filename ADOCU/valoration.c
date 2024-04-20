#include "valoration.h"
#include <stdio.h>
#include <string.h>
#include "logger.h"

Valoration insertIntoValoration(char valoration) {
    Valoration valorationResult;
    valorationResult.valoration = valoration;
    logAction("Valoracion insertada", "sistema", 's');
    return valorationResult;
}

int insertUserValorationInDB(Valoration valoration, User user, sqlite3* db) {
    sqlite3_stmt* statement;

    char sql[] = "insert into uservaloration (username, valoration) values (?, ?)";
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement (INSERT).\n");
        printf("%s\n", sqlite3_errmsg(db));
        logAction(sqlite3_errmsg(db), "Preparar statment", 'f');
        return result;
    }

    sqlite3_bind_text(statement, 1, user.username, strlen(user.username), SQLITE_STATIC);
    char valorationAux[2];
    valorationAux[0] = valoration.valoration;
    valorationAux[1] = '\0';
    sqlite3_bind_text(statement, 2, valorationAux, strlen(valorationAux), SQLITE_STATIC);

    result = sqlite3_step(statement);
    if (result != SQLITE_DONE) {
        printf("Error insertando un usuario.\n");
        logAction(sqlite3_errmsg(db), "Ejecutar statment", 'f');
        return result;
    }

    result = sqlite3_finalize(statement);
    if (result != SQLITE_OK) {
        printf("Error finalizando el statement (INSERT).\n");
        printf("%s\n", sqlite3_errmsg(db));
        logAction(sqlite3_errmsg(db), "Finalizar statment", 'f');
        return result;
    }

  return SQLITE_OK;
}

int readUserValorationsFromDB(sqlite3* db) {
    sqlite3_stmt* statement;

	char sql[] = "select * from uservaloration";

	int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
        logAction(sqlite3_errmsg(db), "Preparar statment", 'f');
		return result;
	}
	
	int i = 0;
    printf("VALORACIONES (1 - 5):\n");
    printf("---------------------------------------------\n");
	do {
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW) {
            i++;
			printf("- %i. Usuario -> %s, Valoracion -> %s\n", i, sqlite3_column_text(statement, 0), sqlite3_column_text(statement, 1));
		}
	} while (result == SQLITE_ROW);
    printf("---------------------------------------------\n");

	result = sqlite3_finalize(statement);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
        logAction(sqlite3_errmsg(db), "Finalizar statment", 'f');
		return result;
	}

	return SQLITE_OK;
}