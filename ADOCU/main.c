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
	char option;
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
			addUserToList(&ul,u);
			writeUsersInFile(ul,FILE_NAME);
		}else if(option == '3'){

		}

	}while(option != '0');


	free(ul.uList);
	return 0;
}
