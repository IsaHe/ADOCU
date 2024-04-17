#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"

User askForUser(UserList userList) {
	User user;
	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s", user.username);
	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s", user.password);
	for (int i = 0; i < userList.numUsers; i++) {
		if (strcmp(user.username, userList.userList[i].username) == 0 && strcmp(user.password, userList.userList[i].password) == 0) {
			strcpy(user.name, userList.userList[i].name);
			user.age = userList.userList[i].age;
			user.admin = userList.userList[i].admin;
		}
	}
	return user;
}

User userToIntroduce() {
	User user;
	printf("Introduce el nombre: ");
	fflush(stdin);
	scanf("%s", user.name);
	printf("Introduce la edad: ");
	fflush(stdin);
	scanf("%i", &user.age);
	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s", user.username);
	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s", user.password);
	user.admin = 'U';
	return user;
}

int readUsersFromDB(UserList* userList, sqlite3* db) {
	sqlite3_stmt* statement;

	char sql[] = "select * from users";

	int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	
	userList -> size = 100;
	userList -> userList = (User*) malloc(userList -> size * sizeof(User));
	userList -> numUsers = 0;
	do {
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW) {
			User user;
			strcpy(user.name, (char*) sqlite3_column_text(statement, 0));
			strcpy(user.username, (char*) sqlite3_column_text(statement, 1));
			strcpy(user.password, (char*) sqlite3_column_text(statement, 2));
			user.age = sqlite3_column_int(statement, 3);
			char admin[2];
			strcpy(admin, (char*) sqlite3_column_text(statement, 4));
			user.admin = admin[0];
			userList -> userList[userList -> numUsers] = user;
			userList -> numUsers++;
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(statement);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int deleteDB(sqlite3* db, char* table) {
	sqlite3_stmt* statement;

	char sql[100];
	sprintf(sql, "delete from '%s'", table);

	int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (DELETE).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(statement);
	if (result != SQLITE_DONE) {
		printf("Error eliminando datos.\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(statement);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (DELETE).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int insertUsersInDB(UserList userList, sqlite3* db) {
	deleteDB(db, "users");
	for (int i = 0; i < userList.numUsers; i++) {
		sqlite3_stmt* statement;

		char sql[] = "insert into users (name, username, password, age, admin) values (?, ?, ?, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparando el statement (INSERT).\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

		sqlite3_bind_text(statement, 1, userList.userList[i].name, strlen(userList.userList[i].name), SQLITE_STATIC);
		sqlite3_bind_text(statement, 2, userList.userList[i].username, strlen(userList.userList[i].username), SQLITE_STATIC);
		sqlite3_bind_text(statement, 3, userList.userList[i].password, strlen(userList.userList[i].password), SQLITE_STATIC);
		sqlite3_bind_int(statement, 4, userList.userList[i].age);
		char admin[2];
		admin[0] = 'U';
		admin[1] = '\0';
		sqlite3_bind_text(statement, 5, admin, strlen(admin), SQLITE_STATIC);

		result = sqlite3_step(statement);
		if (result != SQLITE_DONE) {
			printf("Error insertando un usuario.\n");
			return result;
		}

		result = sqlite3_finalize(statement);
		if (result != SQLITE_OK) {
			printf("Error finalizando el statement (INSERT).\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	}

	return SQLITE_OK;
}

void seeUserList(UserList userList) {
	for (int i = 0; i < userList.numUsers; i++) {
			printf("%s %i %s %s %c\n", userList.userList[i].name, userList.userList[i].age, userList.userList[i].username, userList.userList[i].password, userList.userList[i].admin);
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
