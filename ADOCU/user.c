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

	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s",u.username);

	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s",u.password);

	return u;

}

//Pregunta por el Usuario a Registrar
User userToIntroduce(){
	User u;

	printf("Introduce el nombre: ");
	fflush(stdin);
	scanf("%s",u.name);

	printf("Introduce la edad: ");
	fflush(stdin);
	scanf("%s",u.age);

	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s",u.username);

	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s",u.password);

	u.admin = 'U';

	return u;

}
