#include <stdio.h>
#include <stdlib.h>
#include "valorationList.h"

void takeValorationsFromFile(ValorationList* valorationList, char* fileName) {
    Valoration valorationResult;
    char valoration[2];
    valorationList -> size = 100;
    FILE* file;
    file = fopen(fileName, "r");
    if (file != (FILE*) NULL) {
        valorationList -> valorations = (Valoration*) malloc(valorationList -> size * sizeof(Valoration));
        valorationList -> numValorations = 0;
        while (fscanf(file, "%s", valoration) != EOF) {
            valorationResult.valoration = valoration[0];
            valorationList -> valorations[valorationList -> numValorations] = valorationResult;
            valorationList -> numValorations++;
        }
    }
    fclose(file);
}

void writeValorationsInFile(ValorationList valorationList, char* fileName) {
    FILE* file;
    file = fopen(fileName, "w");
    if (file != (FILE*) NULL) {
        for (int i = 0; i < valorationList.numValorations; i++) {
            fprintf(file, "%c\n", valorationList.valorations[i].valoration);
        }
    }
    fclose(file);
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
