#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valoration.h"
#include "valorationList.h"
#include "group.h"
#include "sqlite3.h"
#include "logger.h"

#define MAX_ACTIVITIES 10

void readConfigFile(char* databaseName, char* adminUsername, char* adminPassword, char* groupsFileName) {
	FILE* file = fopen("config.properties", "r");
	if (file == NULL) {
		printf("Error opening file\n");
        logAction("Error abriendo el fichero de configuracion", "sistema", 'f');
		return;
	}
	char line[100];
	while (fgets(line, 100, file) != NULL) {
		char* key = strtok(line, "=");
		char* value = strtok(NULL, "=");
		if (strcmp(key, "databaseName") == 0) {
			strcpy(databaseName, value);
			databaseName[strcspn(databaseName, "\n")] = 0;
		} else if (strcmp(key, "adminUsername") == 0) {
			strcpy(adminUsername, value);
			adminUsername[strcspn(adminUsername, "\n")] = 0;
		} else if (strcmp(key, "adminPassword") == 0) {
			strcpy(adminPassword, value);
			adminPassword[strcspn(adminPassword, "\n")] = 0;
		} else if (strcmp(key, "groupsFileName") == 0) {
			strcpy(groupsFileName, value);
			groupsFileName[strcspn(groupsFileName, "\n")] = 0;
		}
	}
	fclose(file);
    logAction("Cargada la configuracion", "sistema", 's');
}

int main() {
	// Declaracion de variables
	sqlite3* db;
	char option, optionValoration, optionAdmin, optionLogIn, optionActivity;
	User user;
	UserList userList;
	Valoration valoration;
	ValorationList valorationList;
	float meanValoration;
	Group* group;
	GroupList groupList;
	groupList.groups = (Group**) malloc(sizeof(Group*) * 100);
	groupList.numGroups = 0;
	ActivityList activityList;
	char databaseName[20];
	char adminUsername[20];
	char adminPassword[20];
	char groupsFileName[20];
	readConfigFile(databaseName, adminUsername, adminPassword, groupsFileName);

	// Abrir base de datos
	int result = sqlite3_open(databaseName, &db);
	if (result != SQLITE_OK) {
        logAction("Error abriendo la base de datos", "sistema", 'f');
		return result;
	}

	// Coger los datos de fichero o base de datos
	readUsersFromDB(&userList, db);
	seeUserList(userList);
	readValorationsFromDB(&valorationList, db);
	readActivitiesInDB(&activityList, db);

	// Menus
	do {
		// Menu principal
		option = mainMenu();
		// Opcion 0 salir del menu
		if (option == '0') {
			printf("¡Gracias por usar ADOCU!\n");
		// Opcion 1 iniciar sesion
		} else if (option == '1') {
			user = askForUser(userList);
			if (findUserInList(userList, user, adminUsername, adminPassword) == 1) { // Inicio sesion correcto
				// Menu inicio sesion
				printf("Bienvenido :)!\n");
				int userInGroup = 0;
				for (int i = 0; i < groupList.numGroups; i++) {
					for (int j = 0; j < groupList.groups[i] -> numUsers; j++) {
						if (strcmp(groupList.groups[i] -> users[j].username, user.username) == 0) {
							userInGroup = 1;
							group = groupList.groups[i];
						}
					}
				}
				if (userInGroup == 0) {
					do {
						optionLogIn = menuLogIn();
						if (optionLogIn == '1') {
							// Menu crear grupo
							printf("Crear Grupo\n");
							Group* group = (Group*) malloc(sizeof(Group));
							group -> name = menuCreateGroupName();
							group -> maxUsers = menuCreateGroupMaxUsers();
							createGroup(group -> name, group -> maxUsers, &groupList, group);
                            logAction("Grupo creado", user.username, 's');
						} else if (optionLogIn == '2') {
							printf("Unirse a Grupo\n");
							char* groupName = menuJoinGroup();
							group = joinGroup(groupName, user, &groupList);
							if (group != NULL) {
								userInGroup = 1;
                                logAction("Usuario unido al grupo", user.username, 's');
								break;
							} else {
								printf("No se ha podido unir al grupo.\n");
                                logAction("Error uniendo al usuario al grupo", user.username, 'f');
							}
						} else if (optionLogIn == '3') {
							do {
								optionValoration = menuValoration();
								if (optionValoration == '1') { // Crear valoracion de 1
									printf("HAS VALORADO MUY MAL\n");
                                    logAction("Valoracion muy mala", user.username, 's');
									valoration = insertIntoValoration(optionValoration);
									addToValorations(&valorationList, valoration);
									insertUserValorationInDB(valoration, user, db);
								} else if (optionValoration == '2') { // Crear valoracion de 2
									printf("HAS VALORADO MAL\n");
                                    logAction("Valoracion mala", user.username, 's');
									valoration = insertIntoValoration(optionValoration);
									addToValorations(&valorationList, valoration);
									insertUserValorationInDB(valoration, user, db);
								} else if (optionValoration == '3') { // Crear valoracion de 3
									printf("HAS VALORADO REGULAR\n");
                                    logAction("Valoracion regular", user.username, 's');
									valoration = insertIntoValoration(optionValoration);
									addToValorations(&valorationList, valoration);
									insertUserValorationInDB(valoration, user, db);
								} else if (optionValoration == '4') { // Crear valoracion de 4
									printf("HAS VALORADO BIEN\n");
                                    logAction("Valoracion buena", user.username, 's');
									valoration = insertIntoValoration(optionValoration);
									addToValorations(&valorationList, valoration);
									insertUserValorationInDB(valoration, user, db);
								} else if (optionValoration == '5') { // Crear valoracion de 5
									printf("HAS VALORADO MUY BIEN\n");
                                    logAction("Valoracion muy buena", user.username, 's');
									valoration = insertIntoValoration(optionValoration);
									addToValorations(&valorationList, valoration);
									insertUserValorationInDB(valoration, user, db);
								}
							} while (optionValoration != '0');
						}
					} while (optionLogIn != '4');
				}
				if (userInGroup == 1) {
					do {
						optionActivity = menuActivity();
						if (optionActivity == '1') {
							int option = seeActivities(&activityList);
							if (option == -1) {
								printf("Seleccione una opcion valida.\n");
                                logAction("Actividad no valida introducida", user.username, 'f');
							} else {
								addActivityToGroup(activityList.activityList[option - 1], group);
                                logAction("Actividad añadida al grupo", user.username, 's');
							}
						} else if (optionActivity == '2') {
							seeGroupActivities(group);
                            logAction("Mostrando las actividades del grupo", user.username, 's');
						}
					} while (optionActivity != '3');
					updateGroupActivitiesInGroupList(&groupList, group);
				}
			} else if (findUserInList(userList, user, adminUsername, adminPassword) == 2) { // Inicio sesion como Admin
				// Menu Admin
				printf("¡Has iniciado sesion como admin ;)!\n");
				do {
					optionAdmin = menuAdmin();
					if (optionAdmin == '1') { // Eliminar usuarios
						printf("Eliminar Usuarios\n");
                        logAction("Eliminando usuarios", "admin", 's');
						int position = userToRemove(userList); // Conseguir la posicion del array del usuario
						if (position < (userList.numUsers + 1)) {
							deleteUserWithPosition(&userList, position); // Eliminar al usuario por la posicion del array
						} else {
							printf("Ese usuario no esta, intentelo de nuevo!\n"); // Si el usuario no esta en el array
                            logAction("Usuario no encontrado", "admin", 'f');
						}
					} else if (optionAdmin == '2') { // Añadir actividades
						printf("Añadir Actividades\n");
                        logAction("Añadiendo actividades", "admin", 's');
						if (activityList.numActivities == 10) {
							printf("No se pueden seleccionar mas actividades.\n");
                            logAction("No se pueden añadir mas actividades", "admin", 'f');
						} else {
							printf("Escribe una actividad que van a poder seleccionar los grupos: ");
							fflush(stdin);
							Activity activity;
							fflush(stdout);
							fgets(activity.name, MAX_ACTIVITIES, stdin);
							clearIfNeeded(activity.name, MAX_ACTIVITIES);
							activity.name[strcspn(activity.name, "\n")] = 0;
							addActivity(&activityList, activity);
						}
					} else if (optionAdmin == '3') { // Eliminar actividades
						printf("Eliminar Actividades\n");
						deleteActivity(&activityList);
					} else if (optionAdmin == '4') { // Ver valoracion media
						printf("Ver Valoracion Media\n");
						meanValoration = calculateMeanValoration(valorationList);
						seeMeanValoration(meanValoration);
					} else if (optionAdmin == '5') { // Ver valoracion por usuario
						printf("Ver Valoracion Por Usuario\n");
						readUserValorationsFromDB(db);
					}
				} while (optionAdmin != '6');
			} else if (findUserInList(userList, user, adminUsername, adminPassword) == -1) { // Contraseña incorrecta
				printf("Contraseña incorrecta!\n");
			} else if (findUserInList(userList, user, adminUsername, adminPassword) == -2){ // No estar registrado
				printf("No estas registrado, pulse el 2.!\n");
			}
		// Opcion 2 registrarse
		} else if (option == '2') {
			user = userToIntroduce();
			if (findUserInListRegister(userList, user) != -1) { // Registro correcto
				addUserToList(&userList, user);
			}
		}
	} while (option != '0');

	// Escritura de datos en fichero o base de datos
	insertUsersInDB(userList, db);
	insertValorationsInDB(valorationList, db);
	insertActivitiesInDB(activityList, db);
	writeGroupsInFile(groupList, groupsFileName);

	// Visualizacion de los datos
	seeUserList(userList);
	seeValorations(valorationList);
	printGroups(groupList);

	// Liberar memoria
	free(valorationList.valorations);
	free(userList.userList);
	free(groupList.groups);
	sqlite3_close(db);

	return 0;
}
