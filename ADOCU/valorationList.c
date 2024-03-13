#include<stdio.h>
#include"valorationList.h"
#include<stdlib.h>

void takeValorationsFromFile(ValorationList *vl, char *fileName){
    Valoration v;
    vl->tam = 100;
    FILE *pf;
    pf = fopen(fileName, "r");
    if (pf != (FILE*)NULL){
        vl->valorations = (Valoration*)malloc(vl->tam*sizeof(Valoration));
        vl->numV = 0;
        while (fscanf(pf, "%d", &v.val) != EOF){
            vl->valorations[vl->numV] = v;
            vl->numV++;
        }
    fclose(pf);  
    }
}
void writeValorationsInFile(ValorationList vl, char *fileName){
    FILE *pf;
    pf = fopen(fileName,"w");
    if (pf != (FILE*)NULL){
        for (int i = 0; i < vl.numV; i++){
            fprintf(pf,"%d\n",vl.valorations[i]);
        }
    }
    fclose(pf);
}

void seeValorations(ValorationList vl){
    
}