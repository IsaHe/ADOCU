/*
 * main.c
 *
 *  Created on: 28 feb 2024
 *      Author: apera
 */

#define FILE_NAME "users.txt"
#include "menus.h"
#include "userList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	char option, optionVal;
	User u;
	UserList ul;

	takeUsersFromFile(&ul,FILE_NAME);

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
				writeUsersInFile(ul,FILE_NAME);
			}
		}else if(option == '3'){
			menuValoracion();
			optionVal = menuValoracion();
			if(optionVal == '0'){
				option;
			}
			else if(optionVal == '1'){
				printf("HAS VALORADO MUY MAL\n");
			}
			else if(optionVal == '2'){
				printf("HAS VALORADO MAL\n");
			}
			else if(optionVal == '3'){
				printf("HAS VALORADO REGULAR\n");
			}
			else if(optionVal == '4'){
				printf("HAS VALORADO BIEN\n");
			}
			else if(optionVal == '5'){
				printf("HAS VALORADO MUY BIEN\n");
			}
		}

	}while(option != '0');

	seeUserList(ul);
	//Comprobar si el usuario que va a introducir no se encuentra en la lista ya

	free(ul.uList);
	return 0;
}
