/*
 * menus.c
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#include"menus.h"
#include <stdio.h>

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
    char a;
    printf("1. MUY MAL\n");
	printf("2. MAL\n");
	printf("3. REGULAR\n");
	printf("4. BIEN\n");
	printf("5. MUY BIEN\n");
	printf("0. VOLVER\n");

	printf("Introduce opción: ");
	scanf("%c", &a);
	return a;
}
