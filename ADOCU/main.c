#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valoration.h"
#include "valorationList.h"
#include "group.h"
#include "sqlite3.h"
#include "logger.h"
#include "server.h"

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

void procesClientBuff(char *recvbuf, UserList* userList, ValorationList* valorationList, GroupList* groupList, ActivityList* activityList, sqlite3* db, SOCKET ClientSocket) {
    if (strncmp(recvbuf, "Hola", 4) == 0) {
        logAction("Primer contacto con el cliente establecido", "cliente", 's');
        send_data(ClientSocket, jsonifyGroupList(*groupList));
    } else if (strcmp(recvbuf, "Adios") == 0) {
        logAction("Cerrando el servidor", "sistema", 's');
        exit(0);
    } else if (strncmp(recvbuf, "\"group\"{", 8) == 0) {
        Group* group = malloc(sizeof(Group));
        parseGroup(recvbuf, group, 0);
        addGroupToList(groupList, group, 100);
    }  else if (strncmp(recvbuf, "\"user\": \"", 9) == 0) {
        User* user = malloc(sizeof(User));
        parseUser(recvbuf, user);
        joinGroup(seekGroupName(recvbuf, 9), *user, groupList);
    } else if (strncmp(recvbuf, "\"valoration\": \"", 15) == 0) {
        Valoration valoration;
        parseValoration(recvbuf, &valoration);
        User user = getUserFromListByUserName(*userList, seekUserName(recvbuf));
        insertUserValorationInDB(valoration, user, db);
        addToValorations(valorationList, valoration);
    } else if (strncmp(recvbuf, "\"activity\": \"", 13) == 0) {
        Activity activity;
        parseActivity(recvbuf, &activity);
        Group* group = findGroupByName(*groupList, seekGroupName(recvbuf, 13));
        addActivityToList(activityList, activity);
        addActivityToGroup(activity, group);
    } else if (strncmp(recvbuf, "\"userNew\"{", 10) == 0) {
        User* user = malloc(sizeof(User));
        parseUser(recvbuf, user);
        addUserToList(userList, *user);
    }
}


int main() {
	// Declaracion de variables
	sqlite3* db;
//	char option, optionValoration, optionAdmin, optionLogIn, optionActivity;
//	User user;
	UserList userList;
//	Valoration valoration;
	ValorationList valorationList;
//	float meanValoration;
//	Group* group;
	GroupList groupList;
//	groupList.groups = (Group**) malloc(sizeof(Group*) * 100);
//	groupList.numGroups = 0;
	ActivityList activityList;
	char databaseName[20];
	char adminUsername[20];
	char adminPassword[20];
	char groupsFileName[20];
	readConfigFile(databaseName, adminUsername, adminPassword, groupsFileName);
//
	// Abrir base de datos
	int result = sqlite3_open(databaseName, &db);
	if (result != SQLITE_OK) {
        logAction("Error abriendo la base de datos", "sistema", 'f');
		return result;
	}

	// Coger los datos de fichero o base de datos
	readUsersFromDB(&userList, db);
	readValorationsFromDB(&valorationList, db);
	readActivitiesInDB(&activityList, db);
    readGroupsFromFile(groupsFileName, &groupList);

    // Inicializar el servidor
    initialize_winsock();
    SOCKET ListenSocket = create_server(27015);

    char recvbuf[DEFAULT_BUFLEN];

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        logAction("Error escuchando las conexiones entrantes", "sistema", 'f');
        close_server(ListenSocket);
        exit(1);
    }
    logAction("Escuchando las conexiones entrantes...", "sistema", 's');
    printf("Escuchando las conexiones entrantes...\n");

    SOCKET ClientSocket;
    if ((ClientSocket = accept(ListenSocket, NULL, NULL)) == INVALID_SOCKET) {
        logAction("Error aceptando las conexiones entrantes", "sistema", 'f');
        close_server(ListenSocket);
        exit(1);
    }
    logAction("Conexión aceptada", "sistema", 's');
    printf("Conexión aceptada\n");

    int bytesRecividos;
    do {
        bytesRecividos = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (bytesRecividos > 0) {
            logAction("Bytes recibidos: %d", "sistema", 's', bytesRecividos);
            logAction(recvbuf, "sistema", 's');
            printf("Datos recibidos: %s\n", recvbuf);

            procesClientBuff(recvbuf, &userList, &valorationList, &groupList, &activityList, db, ClientSocket);

        } else if (bytesRecividos == 0) {
            logAction("Conexión cerrada", "sistema", 's');
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            logAction("Error recibiendo datos", "sistema", 'f');
            close_server(ListenSocket);
            exit(1);
        }
    } while (bytesRecividos > 0);

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
