#ifndef VALORACIONLIST_H_
#define VALORACIONLIST_H_

#include"valoration.h"

typedef struct {
    Valoration *valorations;
    int numV;
    int tam;
}ValorationList;

//Coger lista de valoraciones de fichero
void takeValorationsFromFile(ValorationList *vl, char *fileName);

//Escribir lista de valoraciones en fichero
void writeValorationsInFile(ValorationList vl, char *fileName);

//Visualizar lista de valoraciones
void seeValorations(ValorationList vl);

//Añiadir valoracion a lista de valoraciones
void addToValorations(ValorationList *vl, Valoration val);

//Calcular valoración media
float calculateMeanValoration(ValorationList vl);

//manera del admin de ver la valoración media
void seeMeanValoration(float valoration);
#endif
