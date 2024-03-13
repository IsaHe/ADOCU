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

int main(){
	char option, optionVal;
	User u;
	UserList ul;
	Valoration v;

	takeUsersFromFile(&ul,FILE_NAME1);

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
				writeUsersInFile(ul,FILE_NAME1);
			}
		}else if(option == '3'){

			optionVal = menuValoracion();
			if(optionVal == '0'){

				option;
			}
			else if(optionVal == '1'){
				v = insertIntoValoration(1);
				printf("HAS VALORADO MUY MAL\n");
			}
			else if(optionVal == '2'){
				v = insertIntoValoration(2);
				printf("HAS VALORADO MAL\n");
			}
			else if(optionVal == '3'){
				v = insertIntoValoration(3);
				printf("HAS VALORADO REGULAR\n");
			}
			else if(optionVal == '4'){
				v = insertIntoValoration(4);
				printf("HAS VALORADO BIEN\n");
			}
			else if(optionVal == '5'){
				v = insertIntoValoration(5);
				printf("HAS VALORADO MUY BIEN\n");
			}
		}

	}while(option != '0');

	seeUserList(ul);
	//Comprobar si el usuario que va a introducir no se encuentra en la lista ya

	free(ul.uList);
	return 0;
}
