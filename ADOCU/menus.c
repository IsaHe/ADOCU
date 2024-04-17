#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mainMenu() {
	char option;
	printf("1. Iniciar Sesión\n");
	printf("2. Registrarse\n");
	printf("0. Salir\n");
	printf("Introduce opción: ");
	fflush(stdin);
	scanf(" %c", &option);
	return option;
}

char menuValoration(){
    char option;
    printf("1. MUY MAL\n");
	printf("2. MAL\n");
	printf("3. REGULAR\n");
	printf("4. BIEN\n");
	printf("5. MUY BIEN\n");
	printf("0. Volver\n");
	fflush(stdin);
	printf("Introduce opción: ");
	scanf(" %c", &option);
	return option;
}

char menuAdmin() {
	char option;
	printf("1. Eliminar Usuarios\n");
	printf("2. Añadir Actividades\n");
	printf("3. Eliminar Actividades\n");
	printf("4. Ver Valoracion Media\n");
	printf("5. Ver Valoracion Por Usuario\n");
	printf("6. Volver\n");
	printf("Introduce una opción: ");
	fflush(stdin);
	scanf(" %c", &option);
	return option;
}

char menuLogIn() {
	char option;
	printf("1. Crear Grupo\n");
	printf("2. Unirse a Grupo\n");
	printf("3. Valorar Aplicacion\n");
	printf("4. Volver\n");
	printf("Introduce una opción: ");
	fflush(stdin);
	scanf(" %c", &option);
	return option;
}

char menuActivity() {
	char option;
	printf("1. Añadir actividades\n");
	printf("2. Ver actividades\n");
	printf("3. Volver\n");
	printf("Introduce una opción: ");
	fflush(stdin);
	scanf(" %c", &option);
	return option;
}
