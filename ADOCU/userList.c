/*
 * userList.c
 *
 *  Created on: 4 mar 2024
 *      Author: apera
 */

#include "userList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Coge los usuarios de fichero y los almacena en array dinamico
void takeUsersFromFile(UserList *ul, char *fileName){
	User u;
	ul->tam = 100;
	FILE * pf;
	pf = fopen(fileName,"r");
	if(pf != (FILE*)NULL){
		ul->uList = (User *)malloc(ul->tam*sizeof(User));
		ul->numU = 0;
		while(fscanf(pf,"%s %s %s %s %c", u.name,u.age,u.username,u.password,&u.admin) != EOF){
			ul->uList[ul->numU] = u;
			ul->numU++;
		}
		fclose(pf);
	}
}

//Visualiza el array dinamico
void seeUserList(UserList ul){
	for(int i = 0; i<ul.numU; i++){
			printf("%s %s %s %s %c \n", ul.uList[i].name,ul.uList[i].age,ul.uList[i].username,ul.uList[i].password,ul.uList[i].admin);
		}
}

//Devuelve un int dependiendo si esta o no en la lista, si no esta devuelve (-1) (Inicio Sesion)
int findUserInList(UserList ul, User u){

	int pos = 0;
	int enc = 0;

	while(enc == 0 && pos<ul.numU){
		if (strcmp(ul.uList[pos].username,u.username) == 0 && strcmp(ul.uList[pos].password,u.password) == 0){
			enc = 1;
		}else if(strcmp(ul.uList[pos].username,u.username) == 0 && strcmp(ul.uList[pos].password,u.password) != 0){
			enc = 2;
		}else if(strcmp(u.username,"Admin") == 0 && strcmp(u.password,"Admin") == 0){
			enc = 3;
		}else{
			pos++;
		}
	}
	if (enc == 1){
		return 1;
	}else if (enc == 2){
		return -1;
	}else if(enc == 3){
		return 2;
	}else{
		return -2;
	}
}

//Mete un usuario a la lista
void addUserToList(UserList *ul, User u){
	if (ul->numU < ul->tam){
		ul->uList[ul->numU] = u;
		ul->numU++;
	}else{
		printf("Lo sentimos el limite de usuarios esta completo :( \n");
	}

}

//Inserta la lista de usuarios en fichero
void writeUsersInFile(UserList ul, char *fileName){
	FILE *pf;
	pf = fopen(fileName,"w");
	if (pf != (FILE*)NULL){
		for (int i = 0; i < ul.numU; i++){
			fprintf(pf, "%s %s %s %s %c\n", ul.uList[i].name,ul.uList[i].age,ul.uList[i].username, ul.uList[i].password, ul.uList[i].admin);
		}
	}
	fclose(pf);
}

//Ver si el usuario a registrar ya esta en la lista si esta devuelve(-1) (Registro)
int findUserInListRegis(UserList ul, User u){

	int pos = 0;
	int enc = 0;

	while(enc == 0 && pos<ul.numU){
		if (strcmp(ul.uList[pos].username,u.username) == 0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if (enc == 1){
		printf("Ese usuario ya esta registrado, pruebe otro :( \n");
		return -1;
	}else{
		printf("Usuario registrado correctamente :)\n");
		return pos;
	}
}

