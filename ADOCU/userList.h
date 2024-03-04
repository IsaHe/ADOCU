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

#endif /* USERLIST_H_ */
