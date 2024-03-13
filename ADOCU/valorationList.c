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
        while (fscanf(pf, "%c", &v.val) != EOF){
        	vl->valorations[vl->numV] = v;
        	vl->numV++;
        }
    }
    fclose(pf);
}
void writeValorationsInFile(ValorationList vl, char *fileName){
    FILE *pf;
    pf = fopen(fileName,"w");
    if (pf != (FILE*)NULL){
        for (int i = 0; i < vl.numV; i++){
            fprintf(pf,"%c\n",vl.valorations[i].val);
        }
    }
    fclose(pf);
}

void seeValorations(ValorationList vl){
    for (int i = 0; i < vl.numV; i++){
    	printf("%c\n",vl.valorations[i].val);
    }
}

void addToValorations(ValorationList *vl, Valoration val){
	if (vl->numV < vl->tam){
		vl->valorations[vl->numV] = val;
		vl->numV++;
	}else{
		printf("La lista de valoraciones esta llena ;(\n");
	}
}
