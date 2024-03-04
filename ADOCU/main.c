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

	do{
		option = mainMenu();
		if (option == '0'){
			printf("¡Gracias por usar ADOCU! \n");

		}else if(option == '1'){
			u = askForUser();
			takeUsersFromFile(&ul,FILE_NAME);
			seeUserList(ul);

		}else if(option == '2'){

		}else if(option == '3'){

		}

	}while(option != '0');


	free(ul.uList);
	return 0;
}
