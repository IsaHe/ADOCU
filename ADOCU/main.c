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
	//Creación de variables
	char option, optionVal;
	User u;
	UserList ul;
	Valoration v;
	ValorationList vl;

	//Coger los Datos de Fichero o BD
	takeUsersFromFile(&ul,FILE_NAME1);
	takeValorationsFromFile(&vl,FILE_NAME2);

	//Menus
	do{
		//Menu Principal
		option = mainMenu();

		//Opcion 0 salir del menu
		if (option == '0'){
			printf("¡Gracias por usar ADOCU! \n");

		//Opcion 1 iniciar sesion
		}else if(option == '1'){
			u = askForUser();
			if (findUserInList(ul,u) == 1) { //Inicio de sesion correcto
				//Aqui va otro menu.
				printf("Bienvenido :)! \n");
			}else if(findUserInList(ul,u) == 2){ //Inicio sesion como admin
				//Aqui va otro menu
				printf("Has iniciado sesion como admin ;)! \n");
			}else if(findUserInList(ul,u) == -1){ //Contraseña incorrecta
				printf("Contraseña incorrecta!\n");
			}else if(findUserInList(ul,u) == -2){ //No estar registrado
				printf("No estas registrado, pulse el 2. ! \n");
			}

		//Opcion 2 registrarse
		}else if(option == '2'){
			u = userToIntroduce();
			if (findUserInListRegis(ul,u) != -1){ //Registro correcto
				addUserToList(&ul,u);
			}
		//Opcion 3 Valorar la app
		}else if(option == '3'){
			//Menu de Valoracion
			optionVal = menuValoracion();
			//Opcion 0 volver a menu principal
			if(optionVal == '0'){

			}else if(optionVal == '1'){ //Crear valoracion de 1
				printf("HAS VALORADO MUY MAL\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '2'){ //Crear valoracion de 2
				printf("HAS VALORADO MAL\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '3'){ //Crear valoracion de 3
				printf("HAS VALORADO REGULAR\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '4'){ //Crear valoracion de 4
				printf("HAS VALORADO BIEN\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}else if(optionVal == '5'){ //Crear valoracion de 5
				printf("HAS VALORADO MUY BIEN\n");
				v = insertIntoValoration(optionVal);
				addToValorations(&vl,v);
			}
		}

	}while(option != '0');

	//Escritura de datos en Fichero o BD
	writeUsersInFile(ul,FILE_NAME1);
	writeValorationsInFile(vl,FILE_NAME2);

	//Visualización de los datos
	seeUserList(ul);
	seeValorations(vl);

	//Liberar Memoria
	free(vl.valorations);
	free(ul.uList);

	return 0;
}
