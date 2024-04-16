#define FILE_NAME1 "users.txt"
#define FILE_NAME2 "valorations.txt"
#define MAX_ACTIVITIES 10

#include "menus.h"
#include "userList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valoration.h"
#include "valorationList.h"
#include "group.h"
#include "sqlite3.h"



int main() {
	// Declaracion de variables
	sqlite3* db;
	char option, optionValoration, optionAdmin, optionLogIn, optionActivity;
	User user;
	UserList userList;
	Valoration valoration;
	ValorationList valorationList;
	float meanValoration;
	Group group;
	GroupList groupList;
	groupList.groups = (Group*) malloc(sizeof(Group) * 100);
	groupList.numGroups = 0;
	ActivityList activityList;
	initActivities(&activityList);

	// Abrir base de datos
	int result = sqlite3_open("adocu.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
	printf("Database opened\n");

	// Coger los datos de fichero o base de datos
	int test = readUsersFromDB(&userList, db);
	printf("%i\n", test);
	seeUserList(userList);
	takeValorationsFromFile(&valorationList, FILE_NAME2);

	// Menus
	do {
		// Menu principal
		option = mainMenu();
		// Opcion 0 salir del menu
		if (option == '0') {
			printf("¡Gracias por usar ADOCU!\n");
		// Opcion 1 iniciar sesion
		} else if (option == '1') {
			user = askForUser();
			if (findUserInList(userList, user) == 1) { // Inicio sesion correcto
				// Menu inicio sesion
				printf("Bienvenido :)!\n");
				int userInGroup = 0;
				for (int i = 0; i < groupList.numGroups; i++) {
					for (int j = 0; j < groupList.groups[i].numUsers; j++) {
						if (strcmp(groupList.groups[i].users[j].username, user.username) == 0) {
							userInGroup = 1;
						}
					}
				}
				if (userInGroup == 0) {
				printf("El usuario NO esta en un grupo.\n");
					do {
						optionLogIn = menuLogIn();
						if (optionLogIn == '1') {
							// Menu crear grupo
							printf("Crear Grupo\n");
							group.name = menuCreateGroupName();
							group.maxUsers = menuCreateGroupMaxUsers();
							createGroup(group.name, group.maxUsers, &groupList);
						} else if (optionLogIn == '2') {
							printf("Unirse a Grupo\n");
							char* groupName = menuJoinGroup();
							joinGroup(groupName, user, &groupList);
							printGroups(groupList);
						}
					} while (optionLogIn != '3');
				} else {
					printf("El usuario SI tiene grupo.\n");
					do {
						optionActivity = menuActivity();
						if (optionActivity == '1') {
							int option = seeActivities(&activityList);
							if (option == -1) {
								printf("Seleccione una opcion valida.\n");
							} else {
								addActivityToGroup(activityList.activityList[option - 1], &group);
							}
						} else if (optionActivity == '2') {
							seeGroupActivities(&group);
						}
					} while (optionActivity != '3');
				}
			} else if (findUserInList(userList, user) == 2) { // Inicio sesion como Admin
				// Menu Admin
				printf("¡Has iniciado sesion como admin ;)!\n");
				do {
					optionAdmin = menuAdmin();
					if (optionAdmin == '1') { // Eliminar usuarios
						printf("Eliminar Usuarios\n");
						int position = userToRemove(userList); // Conseguir la posicion del array del usuario
						if (position < (userList.numUsers + 1)) {
							deleteUserWithPosition(&userList, position); // Eliminar al usuario por la posicion del array
						} else {
							printf("Ese usuario no esta, intentelo de nuevo!\n"); // Si el usuario no esta en el array
						}
					} else if (optionAdmin == '2') { // Añadir actividades
						printf("Añadir Actividades\n");
						if (activityList.numActivities == 10) {
							printf("No se pueden seleccionar mas actividades.\n");
						} else {
							printf("Escribe una actividad que van a poder seleccionar los grupos: ");
							fflush(stdin);
							Activity activity;
							scanf("%s", activity.name);
							addActivity(&activityList, activity);
						}
					} else if (optionAdmin == '3') { // Eliminar actividades
						printf("Eliminar Actividades\n");
						deleteActivity(&activityList);
					} else if (optionAdmin == '4') { // Ver valoracion media
						printf("Ver Valoracion Media\n");
						meanValoration = calculateMeanValoration(valorationList);
						seeMeanValoration(meanValoration);
					}
				} while (optionAdmin != '5');
			} else if (findUserInList(userList, user) == -1) { // Contraseña incorrecta
				printf("Contraseña incorrecta!\n");
			} else if (findUserInList(userList, user) == -2){ // No estar registrado
				printf("No estas registrado, pulse el 2.!\n");
			}
		// Opcion 2 registrarse
		} else if (option == '2') {
			user = userToIntroduce();
			if (findUserInListRegister(userList, user) != -1) { // Registro correcto
				addUserToList(&userList, user);
			}
		// Opcion 3 valorar la app
		} else if (option == '3') {
			//Menu de valoracion
			do {
				optionValoration = menuValoration();
				if (optionValoration == '1') { // Crear valoracion de 1
					printf("HAS VALORADO MUY MAL\n");
					valoration = insertIntoValoration(optionValoration);
					addToValorations(&valorationList, valoration);
				} else if (optionValoration == '2') { // Crear valoracion de 2
					printf("HAS VALORADO MAL\n");
					valoration = insertIntoValoration(optionValoration);
					addToValorations(&valorationList, valoration);
				} else if (optionValoration == '3') { // Crear valoracion de 3
					printf("HAS VALORADO REGULAR\n");
					valoration = insertIntoValoration(optionValoration);
					addToValorations(&valorationList, valoration);
				} else if (optionValoration == '4') { // Crear valoracion de 4
					printf("HAS VALORADO BIEN\n");
					valoration = insertIntoValoration(optionValoration);
					addToValorations(&valorationList, valoration);
				} else if (optionValoration == '5') { // Crear valoracion de 5
					printf("HAS VALORADO MUY BIEN\n");
					valoration = insertIntoValoration(optionValoration);
					addToValorations(&valorationList, valoration);
				}
			} while (optionValoration != '0');
		}
	} while (option != '0');

	// Escritura de datos en fichero o base de datos
	insertUsersInDB(userList, db);
	writeValorationsInFile(valorationList, FILE_NAME2);

	// Visualizacion de los datos
	seeUserList(userList);
	seeValorations(valorationList);
	printGroups(groupList);

	// Liberar memoria
	free(valorationList.valorations);
	free(userList.userList);
	free(groupList.groups);

	return 0;
}
