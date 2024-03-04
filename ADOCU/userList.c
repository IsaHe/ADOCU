/*
 * userList.c
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#include "userList.h"
#include <stdlib.h>
#include <stdio.h>

//Coge los usuarios de fichero y los almacena en array dinamico
void takeUsersFromFile(UserList *ul, char *fileName){
	User u;
	ul->tam = 100;
	FILE * pf;
	pf = fopen(fileName,"r");
	if(pf != (FILE*)NULL){
		ul->uList = (User *)malloc(ul->tam*sizeof(User));
		ul->numU = 0;
		while(fscanf(pf,"%s %d %s %s %s", u.name,&u.age,u.username,u.password,&u.admin) != EOF){
			ul->uList[ul->numU] = u;
			ul->numU++;
		}
		fclose(pf);
	}
}

//Visualiza el array dinamico
void seeUserList(UserList ul){
	for(int i = 0; i<ul.numU; i++){
			printf("%s %d %s %s %c \n", ul.uList[i].name,ul.uList[i].age,ul.uList[i].username,ul.uList[i].password,ul.uList[i].admin);
		}
}
