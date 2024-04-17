#ifndef VALORATIONLIST_H_
#define VALORATIONLIST_H_

#include "valoration.h"

typedef struct {
    Valoration *valorations;
    int numValorations;
    int size;
} ValorationList;

int readValorationsFromDB(ValorationList* valorationList, sqlite3* db);
int insertValorationsInDB(ValorationList valorationList, sqlite3* db);
void seeValorations(ValorationList valorationList);
void addToValorations(ValorationList* valorationList, Valoration valoration);
float calculateMeanValoration(ValorationList valorationList);
void seeMeanValoration(float valoration);

#endif
