#include "user.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 20

void clearIfNeeded(char *str, int maxLine) {
    if ((strlen(str) == maxLine - 1) && (str[maxLine - 2] != '\n')) {
        while (getchar() != '\n');
    }
}

User askForUser(UserList userList) {
    User user;
    printf("Introduce el usuario: ");
    fflush(stdout);
    fgets(user.username, MAX_LINE, stdin);
    clearIfNeeded(user.username, MAX_LINE);
    user.username[strcspn(user.username, "\n")] = 0;
    printf("Introduce la contraseña: ");
    fflush(stdout);
    fgets(user.password, MAX_LINE, stdin);
    clearIfNeeded(user.password, MAX_LINE);
    user.password[strcspn(user.password, "\n")] = 0;
    for (int i = 0; i < userList.numUsers; i++) {
        if (strcmp(user.username, userList.userList[i].username) == 0 &&
            strcmp(user.password, userList.userList[i].password) == 0) {
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
    fflush(stdout);
    fgets(user.name, MAX_LINE, stdin);
    clearIfNeeded(user.name, MAX_LINE);
    user.name[strcspn(user.name, "\n")] = 0;
    printf("Introduce la edad: ");
    fflush(stdout);
    char age[MAX_LINE];
    fgets(age, MAX_LINE, stdin);
    sscanf(age, "%d", &user.age);
    clearIfNeeded(age, MAX_LINE);
    printf("Introduce el usuario: ");
    fflush(stdout);
    fgets(user.username, MAX_LINE, stdin);
    clearIfNeeded(user.username, MAX_LINE);
    user.username[strcspn(user.username, "\n")] = 0;
    printf("Introduce la contraseña: ");
    fflush(stdout);
    fgets(user.password, MAX_LINE, stdin);
    clearIfNeeded(user.password, MAX_LINE);
    user.password[strcspn(user.password, "\n")] = 0;
    user.admin = 'U';
    return user;
}

int readUsersFromDB(UserList *userList, sqlite3 *db) {
    sqlite3_stmt *statement;

    char sql[] = "select * from users";

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "sistema", 'f');
        return result;
    }

    userList->size = 100;
    userList->userList = (User *) malloc(userList->size * sizeof(User));
    userList->numUsers = 0;
    do {
        result = sqlite3_step(statement);
        if (result == SQLITE_ROW) {
            User user;
            strcpy(user.name, (char *) sqlite3_column_text(statement, 0));
            strcpy(user.username, (char *) sqlite3_column_text(statement, 1));
            strcpy(user.password, (char *) sqlite3_column_text(statement, 2));
            user.age = sqlite3_column_int(statement, 3);
            char admin[2];
            strcpy(admin, (char *) sqlite3_column_text(statement, 4));
            user.admin = admin[0];
            userList->userList[userList->numUsers] = user;
            userList->numUsers++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(statement);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "sistema", 'f');
        return result;
    }

    logAction("Usuarios leidos correctamente", "sistema", 's');
    return SQLITE_OK;
}

char *jsonifyUserList(UserList userList) {
    char *json = (char *) malloc(1000);
    strcpy(json, "[");
    for (int i = 0; i < userList.numUsers; i++) {
        strcat(json, "{");
        strcat(json, "\"name\": \"");
        strcat(json, userList.userList[i].name);
        strcat(json, "\", ");
        strcat(json, "\"username\": \"");
        strcat(json, userList.userList[i].username);
        strcat(json, "\", ");
        strcat(json, "\"password\": \"");
        strcat(json, userList.userList[i].password);
        strcat(json, "\", ");
        strcat(json, "\"age\": ");
        char age[5];
        sprintf(age, "%d", userList.userList[i].age);
        strcat(json, age);
        strcat(json, ", ");
        strcat(json, "\"admin\": \"");
        char admin[2];
        admin[0] = userList.userList[i].admin;
        admin[1] = '\0';
        strcat(json, admin);
        strcat(json, "\"");
        strcat(json, "}");
        if (i < userList.numUsers - 1) {
            strcat(json, ", ");
        }
    }
    strcat(json, "]");
    strcat(json, "\0");
    return json;
}

char *parseAttribute(const char *p, int skip, int max_length) {
    p += skip;
    char *attribute = (char *) malloc(max_length);
    char *attributePtr = attribute;
    while (*p != '\"') {
        *attributePtr++ = *p++;
    }
    *attributePtr = '\0';
    return attribute;
}

int parseAge(const char *p) {
    p += 7;
    int age = 0;
    while (*p != ',') {
        age = age * 10 + (*p++ - '0');
    }
    return age;
}

char parseAdmin(const char *p) {
    p += 10;
    return *p;
}

void parseUser(const char *p, User *user) {
    while (*p != '}') {
        if (strncmp(p, "\"name\": \"", 9) == 0) {
            strcpy(user->name, parseAttribute(p, 9, MAX_NAME));
        } else if (strncmp(p, "\"username\": \"", 13) == 0) {
            strcpy(user->username, parseAttribute(p, 13, MAX_USERNAME));
        } else if (strncmp(p, "\"password\": \"", 13) == 0) {
            strcpy(user->password, parseAttribute(p, 13, MAX_PASSWORD));
        } else if (strncmp(p, "\"age\": ", 7) == 0) {
            user->age = parseAge(p);
        } else if (strncmp(p, "\"admin\": \"", 10) == 0) {
            user->admin = parseAdmin(p);
        }
        p++;
    }
}

UserList unJsonifyUserList(const char *json) {
    UserList userList;
    userList.size = 100;
    userList.userList = (User *) malloc(userList.size * sizeof(User));
    userList.numUsers = 0;
    const char *p = json;
    while (*p) {
        if (*p == '{') {
            User user;
            parseUser(p, &user);
            addUserToList(&userList, user);
        }
        p++;
    }
    return userList;
}

char *processUserDB(sqlite3 *db) {
    UserList userList;
    readUsersFromDB(&userList, db);
    char *json = jsonifyUserList(userList);
    free(userList.userList);
    return json;
}

int deleteDB(sqlite3 *db, char *table) {
    sqlite3_stmt *statement;

    char sql[100];
    sprintf(sql, "delete from '%s'", table);

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "Preprar statment", 'f');
        return result;
    }

    result = sqlite3_step(statement);
    if (result != SQLITE_DONE) {
        logAction(sqlite3_errmsg(db), "Ejecutar statment", 'f');
        return result;
    }

    result = sqlite3_finalize(statement);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "Finalizar statment", 'f');
        return result;
    }

    return SQLITE_OK;
}

int insertUsersInDB(UserList userList, sqlite3 *db) {
    deleteDB(db, "users");
    for (int i = 0; i < userList.numUsers; i++) {
        sqlite3_stmt *statement;

        char sql[] = "insert into users (name, username, password, age, admin) "
                     "values (?, ?, ?, ?, ?)";
        int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
        if (result != SQLITE_OK) {
            logAction(sqlite3_errmsg(db), "Preprar statment", 'f');
            return result;
        }

        sqlite3_bind_text(statement, 1, userList.userList[i].name,
                          strlen(userList.userList[i].name), SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, userList.userList[i].username,
                          strlen(userList.userList[i].username), SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, userList.userList[i].password,
                          strlen(userList.userList[i].password), SQLITE_STATIC);
        sqlite3_bind_int(statement, 4, userList.userList[i].age);
        char admin[2];
        admin[0] = 'U';
        admin[1] = '\0';
        sqlite3_bind_text(statement, 5, admin, strlen(admin), SQLITE_STATIC);

        result = sqlite3_step(statement);
        if (result != SQLITE_DONE) {
            logAction(sqlite3_errmsg(db), "Ejecutar statment", 'f');
            return result;
        }

        result = sqlite3_finalize(statement);
        if (result != SQLITE_OK) {
            logAction(sqlite3_errmsg(db), "Finalizar statment", 'f');
            return result;
        }
    }

    return SQLITE_OK;
}

void seeUserList(UserList userList) {
    for (int i = 0; i < userList.numUsers; i++) {
        printf("%s %i %s %s %c\n", userList.userList[i].name,
               userList.userList[i].age, userList.userList[i].username,
               userList.userList[i].password, userList.userList[i].admin);
    }
}

int findUserInList(UserList userList, User user, char *adminUsername,
                   char *adminPassword) {
    int position = 0;
    int find = 0;
    while (find == 0 && position < userList.numUsers) {
        if (strcmp(userList.userList[position].username, user.username) == 0 &&
            strcmp(userList.userList[position].password, user.password) == 0) {
            find = 1;
        } else if (strcmp(userList.userList[position].username, user.username) ==
                   0 &&
                   strcmp(userList.userList[position].password, user.password) !=
                   0) {
            find = 2;
        } else if (strcmp(user.username, adminUsername) == 0 &&
                   strcmp(user.password, adminPassword) == 0) {
            find = 3;
        } else {
            position++;
        }
    }
    if (find == 1) {
        logAction("Usuario encontrado", user.username, 's');
        return 1;
    } else if (find == 2) {
        logAction("Contraseña incorrecta", user.username, 'f');
        return -1;
    } else if (find == 3) {
        logAction("Admin encontrado", user.username, 's');
        return 2;
    } else {
        logAction("Usuario no encontrado", user.username, 'f');
        return -2;
    }
}

void addUserToList(UserList *userList, User user) {
    if (userList->numUsers < userList->size) {
        userList->userList[userList->numUsers] = user;
        userList->numUsers++;
        logAction("Usuario añadido correctamente", user.username, 's');
    } else {
        printf("Lo sentimos el limite de usuarios esta completo :(\n");
        logAction("Limite de usuarios completado", user.username, 'f');
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
        logAction("Usuario ya registrado", user.username, 'f');
        return -1;
    } else {
        printf("Usuario registrado correctamente :)\n");
        logAction("Usuario registrado correctamente", user.username, 's');
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
    fflush(stdout);
    char positionStr[MAX_LINE];
    fgets(positionStr, MAX_LINE, stdin);
    sscanf(positionStr, "%d", &position);
    clearIfNeeded(positionStr, MAX_LINE);
    return position;
}

void deleteUserWithPosition(UserList *userList, int position) {
    int j = 0;
    if (position == 0) {
        printf("No se ha eliminado ningun usuario.\n");
        logAction("No se ha eliminado ningun usuario", "sistema", 'f');
    } else {
        User *auxUser = (User *) malloc(sizeof(User) * userList->size);
        for (int i = 0; i < userList->numUsers; i++) {
            if (i == position - 1) {
                printf("Usuario eliminado correctamente!\n");
                logAction("Usuario eliminado correctamente",
                          userList->userList[i].username, 's');
            } else {
                auxUser[j] = userList->userList[i];
                j++;
            }
        }
        free(userList->userList);
        userList->userList = (User *) malloc(sizeof(User) * userList->size);
        userList->numUsers = 0;
        for (int i = 0; i < j; i++) {
            userList->userList[i] = auxUser[i];
            userList->numUsers++;
        }
    }
}

UserList fromUserArrayToUserList(User* users, int numUsers) {
    UserList userList;
    userList.size = 100;
    userList.userList = (User *) malloc(userList.size * sizeof(User));
    userList.numUsers = numUsers;
    for (int i = 0; i < userList.numUsers; i++) {
        if (users[i].username[0] != '\0') {
            addUserToList(&userList, users[i]);
        }
    }
    return userList;
}
