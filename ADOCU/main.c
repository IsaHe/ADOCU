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
#include "grupo.h"

int main(){
	//Creación de variables
	char option, optionVal, optionAdmin, optionLogIn;
	User u;
	UserList ul;
	Valoration v;
	ValorationList vl;
    Grupo* g;
    GruposList* gl = malloc(sizeof(GruposList));
    gl->numGrupos = 0;
    gl->grupos = malloc(100 * sizeof(Grupo*));

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
				//Menu Inicio Sesion
				printf("Bienvenido :)! \n");
				do{
					optionLogIn = menuLogIn();
					if(optionLogIn == '1'){
						printf("Crear Grupo\n");
                        char* nombreGrupo = menuCrearGrupoNombre();
                        int numUsuarios = menuCrearGrupoNumUsuarios();
                        g = crearGrupo(nombreGrupo, numUsuarios, gl);
                        printf("Grupo creado con éxito\n");

					}else if(optionLogIn == '2'){
						printf("Unirse a Grupo\n");
                        g = unirseGrupo(menuUnirseGrupo(), u, gl);
					}else{
						printf("Caracter no valido!\n");
					}
				}while(optionLogIn != '3');

			}else if(findUserInList(ul,u) == 2){ //Inicio sesion como admin
				//Menu Admin
				printf("Has iniciado sesion como admin ;)! \n");
				do{
					optionAdmin = menuAdmin();
					if(optionAdmin == '1'){ //Eliminar Usuarios
						printf("Eliminar Usuarios\n");
					}else if (optionAdmin == '2'){ //Eliminar Grupos
						printf("Eliminar Grupo\n");
					}else if (optionAdmin == '3'){ //Eliminar Actividades
						printf("Eliminar Actividades\n");
					}else if (optionAdmin == '4'){ //Ver Valoracion Media
						printf("Ver Valoracion Media\n");
					}else{ //Caracter no valido
						printf("Caracter no valido!\n");
					}
				}while(optionAdmin != '5');
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
			do{
				optionVal = menuValoracion();
				if(optionVal == '1'){ //Crear valoracion de 1
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
				}else{ //Caracteres no validos
					printf("Caracter no valido!\n");
				}
			}while(optionVal != '0');
		}

	}while(option != '0');

	//Escritura de datos en Fichero o BD
	writeUsersInFile(ul,FILE_NAME1);
	writeValorationsInFile(vl,FILE_NAME2);

	//Visualización de los datos
	seeUserList(ul);
	seeValorations(vl);
	seeGroupsNames(*gl);

	//Liberar Memoria
	free(vl.valorations);
	free(ul.uList);
	freeGrupo(g);
	free(gl);
	return 0;
}
