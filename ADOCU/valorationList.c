#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valorationList.h"
#include "user.h"

int readValorationsFromDB(ValorationList* valorationList, sqlite3* db) {
    sqlite3_stmt* statement;

	char sql[] = "select * from valorations";

	int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	
    valorationList -> size = 100;
    valorationList -> valorations = (Valoration*) malloc(sizeof(Valoration) * valorationList -> size);
    valorationList -> numValorations = 0;

	do {
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW) {
			Valoration valoration;
			char valorationAux[2];
			strcpy(valorationAux, (char*) sqlite3_column_text(statement, 0));
			valoration.valoration = valorationAux[0];
			valorationList -> valorations[valorationList -> numValorations] = valoration;
			valorationList -> numValorations++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(statement);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int insertValorationsInDB(ValorationList valorationList, sqlite3* db) {
    deleteDB(db, "valorations");
	for (int i = 0; i < valorationList.numValorations; i++) {
		sqlite3_stmt* statement;

		char sql[] = "insert into valorations (valoration) values (?)";
		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparando el statement (INSERT).\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

        char valoration[2];
        valoration[0] = valorationList.valorations[i].valoration;
        valoration[1] = '\0';
		sqlite3_bind_text(statement, 1, valoration, strlen(valoration), SQLITE_STATIC);

		result = sqlite3_step(statement);
		if (result != SQLITE_DONE) {
			printf("Error insertando un usuario.\n");
			return result;
		}

		result = sqlite3_finalize(statement);
		if (result != SQLITE_OK) {
			printf("Error finalizando el statement (INSERT).\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	}

	return SQLITE_OK;
}

void seeValorations(ValorationList valorationList) {
    for (int i = 0; i < valorationList.numValorations; i++) {
        printf("%c\n", valorationList.valorations[i].valoration);
    }
}

void addToValorations(ValorationList* valorationList, Valoration valoration) {
    if (valorationList -> numValorations < valorationList -> size) {
        valorationList -> valorations[valorationList -> numValorations] = valoration;
        valorationList -> numValorations++;
        printf("Gracias por tu valoracion :)\n");
    } else {
        printf("La lista de valoraciones esta llena ;(\n");
    }
}

float calculateMeanValoration(ValorationList valorationList) {
    float result = 0, converted;
    for (int i = 0; i < valorationList.numValorations; i++) {
        char valoration[2] = {valorationList.valorations[i].valoration, '\0'};
        sscanf(valoration, "%f", &converted);
        result += converted;
    }
    return (result / valorationList.numValorations) * 2;
}

void seeMeanValoration(float valoration) {
    printf("VALORACIÓN MEDIA -> %.2f\n", valoration);
}
