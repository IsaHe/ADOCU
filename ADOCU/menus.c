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
