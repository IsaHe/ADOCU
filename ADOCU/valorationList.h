#ifndef VALORATIONLIST_H_
#define VALORATIONLIST_H_

#include "valoration.h"

typedef struct {
    Valoration *valorations;
    int numValorations;
    int size;
} ValorationList;

void takeValorationsFromFile(ValorationList* valorationList, char* fileName);
void writeValorationsInFile(ValorationList valorationList, char* fileName);
void seeValorations(ValorationList valorationList);
void addToValorations(ValorationList* valorationList, Valoration valoration);
float calculateMeanValoration(ValorationList valorationList);
void seeMeanValoration(float valoration);

#endif
