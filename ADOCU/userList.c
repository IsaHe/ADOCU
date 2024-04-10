#include "userList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void takeUsersFromFile(UserList* userList, char* fileName) {
	User user;
	userList -> size = 100;
	FILE* file;
	file = fopen(fileName, "r");
	if (file != (FILE*) NULL) {
		userList -> userList = (User*) malloc(userList -> size * sizeof(User));
		userList -> numUsers = 0;
		while (fscanf(file, "%s %s %s %s %c", user.name, user.age, user.username, user.password, &user.admin) != EOF) {
			userList -> userList[userList -> numUsers] = user;
			userList -> numUsers++;
		}
		fclose(file);
	}
}

void seeUserList(UserList userList) {
	for (int i = 0; i < userList.numUsers; i++) {
			printf("%s %s %s %s %c \n", userList.userList[i].name, userList.userList[i].age, userList.userList[i].username, userList.userList[i].password, userList.userList[i].admin);
		}
}

int findUserInList(UserList userList, User user) {
	int position = 0;
	int find = 0;
	while (find == 0 && position < userList.numUsers) {
		if (strcmp(userList.userList[position].username, user.username) == 0 && strcmp(userList.userList[position].password, user.password) == 0) {
			find = 1;
		} else if (strcmp(userList.userList[position].username, user.username) == 0 && strcmp(userList.userList[position].password, user.password) != 0) {
			find = 2;
		} else if (strcmp(user.username, "Admin") == 0 && strcmp(user.password, "Admin") == 0) {
			find = 3;
		} else {
			position++;
		}
	}
	if (find == 1) {
		return 1;
	} else if (find == 2) {
		return -1;
	} else if (find == 3) {
		return 2;
	} else {
		return -2;
	}
}

void addUserToList(UserList* userList, User user) {
	if (userList -> numUsers < userList -> size) {
		userList -> userList[userList -> numUsers] = user;
		userList -> numUsers++;
	} else {
		printf("Lo sentimos el limite de usuarios esta completo :(\n");
	}
}

void writeUsersInFile(UserList userList, char* fileName) {
	FILE* file;
	file = fopen(fileName, "w");
	if (file != (FILE*) NULL) {
		for (int i = 0; i < userList.numUsers; i++) {
			fprintf(file, "%s %s %s %s %c\n", userList.userList[i].name, userList.userList[i].age, userList.userList[i].username, userList.userList[i].password, userList.userList[i].admin);
		}
	}
	fclose(file);
}

int findUserInListRegister(UserList userList, User user) {
	int position = 0;
	int find = 0;
	while (find == 0 && position < userList.numUsers) {
		if (strcmp(userList.userList[position].username, user.username) == 0) {
			find = 1;
		} else {
			position++;
		}
	}
	if (find == 1) {
		printf("Ese usuario ya esta registrado, pruebe otro :(\n");
		return -1;
	} else {
		printf("Usuario registrado correctamente :)\n");
		return position;
	}
}

int userToRemove(UserList userList) {
	int position;
	for (int i = 0; i < userList.numUsers; i++) {
		if (strcmp(userList.userList[i].username, "Admin") != 0) {
			printf("%d. %s\n", i + 1, userList.userList[i].username);
		}
	}
	printf("0. Volver\n");
	printf("Elige una opcion: ");
	fflush(stdin);
	scanf("%d", &position);
	return position;
}

void deleteUserWithPosition(UserList* userList, int position) {
	int j = 0;
	if (position == 0) {
		printf("No se ha eliminado ningun usuario.\n");
	} else {
		User* auxUser = (User*) malloc(sizeof(User) * userList -> size);
		for (int i = 0; i < userList -> numUsers; i++) {
			if (i == position - 1) {
				printf("Usuario eliminado correctamente!\n");
			} else {
				auxUser[j] = userList -> userList[i];
				j++;
			}
		}
		free(userList -> userList);
		userList -> userList = (User*) malloc(sizeof(User) * userList -> size);
		userList -> numUsers = 0;
		for (int i = 0; i < j; i++) {
			userList -> userList[i] = auxUser[i];
			userList -> numUsers++;
		}
	}
}
