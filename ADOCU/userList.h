/*
 * userList.h
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#ifndef USERLIST_H_
#define USERLIST_H_

#include "user.h"

typedef struct {
	User * uList;
	int tam;
	int numU;
}UserList;

//Coge los usuarios de fichero y los almacena en array dinamico
void takeUsersFromFile(UserList *ul, char *fileName);

//Visualiza el array dinamico
void seeUserList(UserList ul);

//Devuelve un int dependiendo si esta o no en la lista, si no esta devuelve (-1)
int findUserInList(UserList ul, User u);

//Mete un usuario a la lista
void addUserToList(UserList *ul, User u);

//Inserta la lista de usuarios en fichero
void writeUsersInFile(UserList ul, char *fileName);

//Ver si el usuario a registrar ya esta en la lista si esta devuelve(-1)
int findUserInListRegis(UserList ul, User u);
#endif /* USERLIST_H_ */
