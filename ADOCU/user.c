/*
 * user.c
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#include <stdio.h>
#include "user.h"

//Pregunta al Usuario por su Usuario
User askForUser(){
	User u;

	printf("Introduce el usuario: \n");
	fflush(stdin);
	gets(u.username);

	printf("Introduce la contraseña: \n");
	fflush(stdin);
	gets(u.password);

	return u;

}
