/*
 * usuario.h
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#ifndef USER_H_
#define USER_H_

typedef struct{

	char name[20];
	char username[20];
	char password[20];
	char age[4];
	char admin;

}User;

//Pregunta al Usuario por su Usuario
User askForUser();

//Pregunta por el Usuario a Registrar
User userToIntroduce();

#endif /* USER_H_ */
