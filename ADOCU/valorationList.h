#ifndef VALORACIONLIST_H_
#define VALORACIONLIST_H_

#include"valoration.h"

typedef struct {
    Valoration *valorations;
    int numV;
    int tam;
}ValorationList;

void takeValorationsFromFile(ValorationList *vl, char *fileName);
void writeValorationsInFile(ValorationList vl, char *fileName);
void seeValorations(ValorationList vl);
#endif