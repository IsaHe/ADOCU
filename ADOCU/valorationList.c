#include<stdio.h>
#include"valorationList.h"
#include<stdlib.h>

//Coger lista de valoraciones de fichero
void takeValorationsFromFile(ValorationList *vl, char *fileName){
    Valoration v;
    char val[2];
    vl->tam = 100;
    FILE *pf;
    pf = fopen(fileName, "r");
    if (pf != (FILE*)NULL){
        vl->valorations = (Valoration*)malloc(vl->tam*sizeof(Valoration));
        vl->numV = 0;
        while (fscanf(pf, "%s", val) != EOF){
        	v.val = val[0];
        	vl->valorations[vl->numV] = v;
        	vl->numV++;
        }
    }
    fclose(pf);
}

//Escribir lista de valoraciones en fichero
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

//Visualizar lista de valoraciones
void seeValorations(ValorationList vl){
    for (int i = 0; i < vl.numV; i++){
    	printf("%c\n",vl.valorations[i].val);
    }
}

//Añiadir valoracion a lista de valoraciones
void addToValorations(ValorationList *vl, Valoration val){
	if (vl->numV < vl->tam){
		vl->valorations[vl->numV] = val;
		vl->numV++;
		printf("Gracias por tu valoracion :) \n");
	}else{
		printf("La lista de valoraciones esta llena ;(\n");
	}
}

//Calcular valoración media
float calculateMeanValoration(ValorationList vl){
    float result = 0, convertido;
    

    for(int i = 0; i<vl.numV; i++){
        char valoracion[2] = {vl.valorations[i].val, '\0'};
        sscanf(valoracion, "%f", &convertido);
        result += convertido;
    }

    return (result / vl.numV) * 2;
}


//manera del admin de ver la valoración media
void seeMeanValoration(float valoration){
    printf("VALORACIÓN MEDIA -> %.2f\n", valoration);
}
