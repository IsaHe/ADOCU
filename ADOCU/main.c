/*
 * main.c
 *
 *  Created on: 28 feb 2024
 *      Author: apera
 */

#define FILE_NAME1 "users.txt"
#define FILE_NAME2 "valorations.txt"
#include "menus.h"
#include "userList.h"
#include <stdio.h>
#include <stdlib.h>
#include"valoration.h"
#include "valorationList.h"

int main(){
	char option, optionVal;
	User u;
	UserList ul;
	Valoration v;
	ValorationList vl;

	takeUsersFromFile(&ul,FILE_NAME1);
	takeValorationsFromFile(&vl,FILE_NAME2);
	seeValorations(vl);
	do{
		option = mainMenu();
		if (option == '0'){
			printf("¡Gracias por usar ADOCU! \n");

		}else if(option == '1'){
			u = askForUser();
			if (findUserInList(ul,u) != -1){
				//Aqui va otro menu.
			}

		}else if(option == '2'){
			u = userToIntroduce();
			if (findUserInListRegis(ul,u) != -1){
				addUserToList(&ul,u);
			}
		}else if(option == '3'){
			optionVal = menuValoracion();
			if(optionVal == '0'){

			}else if(optionVal == '1'){
				printf("HAS VALORADO MUY MAL\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '2'){
				printf("HAS VALORADO MAL\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '3'){
				printf("HAS VALORADO REGULAR\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '4'){
				printf("HAS VALORADO BIEN\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '5'){
				printf("HAS VALORADO MUY BIEN\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}
		}

	}while(option != '0');

	writeUsersInFile(ul,FILE_NAME1);
	writeValorationsInFile(vl,FILE_NAME2);

	seeUserList(ul);
	seeValorations(vl);

	free(ul.uList);
	return 0;
}
