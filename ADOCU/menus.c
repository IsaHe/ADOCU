/*
 * menus.c
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#include"menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grupo.h"

//Menu Principal
char mainMenu(){
	char option;
	printf("1. Iniciar Sesión \n");
	printf("2. Registrarse \n");
	printf("3. Valorar la aplicacion \n");
	printf("0. Salir \n");
	fflush(stdin);
	printf("Introduce opción: ");
	scanf("%c",&option);
	return option;
}

char menuValoracion(){
    char option;
    printf("1. MUY MAL\n");
	printf("2. MAL\n");
	printf("3. REGULAR\n");
	printf("4. BIEN\n");
	printf("5. MUY BIEN\n");
	printf("0. VOLVER\n");
	fflush(stdin);
	printf("Introduce opción: ");
	scanf("%c", &option);
	return option;
}

char menuAdmin(){
	char option;
	printf("1. Eliminar Usuarios\n");
	printf("2. Eliminar Grupo\n");
	printf("3. Eliminar Actividades\n");
	printf("4. Ver Valoracion Media\n");
	printf("5. Volver\n");
	printf("Introduce una opción: ");
	fflush(stdin);
	scanf("%c",&option);
	return option;
}

char menuLogIn(){
	char option;
		printf("1. Crear Grupo\n");
		printf("2. Unirse a Grupo\n");
		printf("3. Volver\n");
		printf("Introduce una opción: ");
		fflush(stdin);
		scanf("%c",&option);
		return option;
}

char* menuCrearGrupo() {
    char* nomGrupo = NULL;
    char* numParticipantes = NULL;

    do {
        printf("Nombre del Grupo: ");
        fflush(stdin);
        scanf("%s", nomGrupo);
    } while (validateNombreGrupo(nomGrupo));

    do {
        printf("Numero de participantes: ");
        fflush(stdin);
        scanf("%s", numParticipantes);
    } while (validateNumUsuariosMax(numParticipantes));

    char* result = (char*) malloc(sizeof(char) * (strlen(nomGrupo) + strlen(numParticipantes) + 2));
    strcpy(result, nomGrupo);
    strcat(result, ";");
    strcat(result, numParticipantes);

    return result;

}

char* menuUnirseGrupo() {
    char *codInvitacion = NULL;

    printf("Introduce el código de invitación: ");
    fflush(stdin);
    scanf("%s", codInvitacion);

    return codInvitacion;
}
