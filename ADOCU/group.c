#include "group.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GROUP_NAME 30
#define MAX_USERS 10
#define MAX_ACTIVITIES 10

void createGroup(char *name, int maxUsers, GroupList *groupList, Group *group) {
    group->name = name;
    group->maxUsers = maxUsers;
    group->numUsers = 0;
    group->users = (User *) malloc(sizeof(User) * maxUsers);
    group->numActivities = 0;
    int exists = 0;
    for (int i = 0; i < groupList->numGroups; i++) {
        if (strcmp(groupList->groups[i]->name, group->name) == 0) {
            exists = 1;
        }
    }
    if (exists == 0) {
        groupList->groups[groupList->numGroups] = group;
        groupList->numGroups++;
        printf("Grupo creado correctamente.\n");
        logAction("Grupo creado correctamente", "sistema", 's');
    } else {
        printf("Ya existe un grupo con ese nombre.\n");
        logAction("Error creando el grupo", "sistema", 'f');
    }
}

Group *joinGroup(char *name, User user, GroupList *groupList) {
    logAction("Intentando unir al usuario al grupo", user.username, 's');
    for (int i = 0; i < groupList->numGroups; i++) {
        logAction("Buscando grupo", groupList->groups[i]->name, 's');
        if (strcmp(groupList->groups[i]->name, name) == 0) {
            logAction("Grupo encontrado", groupList->groups[i]->name, 's');
            if (groupList->groups[i]->maxUsers > groupList->groups[i]->numUsers) {
                Group *group = groupList->groups[i];
                logAction("Añadiendo usuario al grupo", user.username, 's');
                groupList->groups[i]->users[groupList->groups[i]->numUsers] = user;
                logAction("Usuario añadido al grupo", user.username, 's');
                groupList->groups[i]->numUsers++;
                logAction("Usuario añadido al grupo correctamente", user.username, 's');
                printf("Te has unido al grupo correctamente.\n");
                logAction("Usuario unido al grupo correctamente", user.username, 's');
                return group;
            } else {
                printf("Este grupo ha alcanzado el numero maximo de usuarios.\n");
                logAction("Error uniendo al usuario al grupo", user.username, 'f');
                return NULL;
            }
        }
    }
    logAction("Error uniendo al usuario al grupo", user.username, 'f');
    return NULL;
}

void printGroups(GroupList groupList) {
    printf("Numero de grupos: %i\n", groupList.numGroups);
    for (int i = 0; i < groupList.numGroups; i++) {
        printf("Grupo %i: %s  %i\n", i + 1, groupList.groups[i]->name,
               groupList.groups[i]->numUsers);
    }
}

void freeGroup(Group *group) {
    free(group->users);
    free(group->name);
}

char *menuJoinGroup() {
    char *name = (char *) malloc(sizeof(char) * (MAX_GROUP_NAME + 1));
    do {
        printf("Introduce el código de invitación del grupo: ");
        fflush(stdout);
        fgets(name, MAX_GROUP_NAME, stdin);
        clearIfNeeded(name, MAX_GROUP_NAME);
        name[strcspn(name, "\n")] = 0;
    } while (strlen(name) < 1);
    name[strcspn(name, "\n")] = 0;
    return name;
}

char *menuCreateGroupName() {
    char *name = (char *) malloc(sizeof(char) * (MAX_GROUP_NAME + 1));
    do {
        printf("Introduce el nombre del grupo: ");
        fflush(stdout);
        fgets(name, MAX_GROUP_NAME, stdin);
    } while (strlen(name) < 1);
    name[strcspn(name, "\n")] = 0;
    return name;
}

int menuCreateGroupMaxUsers() {
    int maxUsers;
    char str[10];
    do {
        printf("Introduce el número máximo de usuarios del grupo: ");
        fflush(stdout);
        fgets(str, MAX_USERS, stdin);
        clearIfNeeded(str, MAX_USERS);
        str[strcspn(str, "\n")] = 0;
    } while (str[0] == 0);
    sscanf(str, "%i", &maxUsers);
    return maxUsers;
}

int seeActivities(ActivityList *activityList) {
    int option;
    for (int i = 0; i < activityList->numActivities; i++) {
        printf("%i. %s\n", i + 1, activityList->activityList[i].name);
    }
    printf("Elige una opcion: ");
    fflush(stdout);
    char optionStr[MAX_ACTIVITIES];
    fgets(optionStr, MAX_ACTIVITIES, stdin);
    sscanf(optionStr, "%i", &option);
    clearIfNeeded(optionStr, MAX_ACTIVITIES);
    optionStr[strcspn(optionStr, "\n")] = 0;
    if (option <= activityList->numActivities) {
        return option;
    } else {
        return -1;
    }
}

void addActivityToGroup(Activity activity, Group *group) {
    int activityInList = 0;
    for (int i = 0; i < group->numActivities; i++) {
        if (strcmp(activity.name, group->activityList[i].name) == 0) {
            activityInList = 1;
        }
    }

    if (activityInList == 0) {
        group->activityList[group->numActivities] = activity;
        group->numActivities += 1;
        printf("Actividad seleccionada.\n");
        logAction("Actividad seleccionada", group->name, 's');
    } else {
        printf("Lo siento esa actividad ya está seleccionada.\n");
        logAction("Intentando añadir una actividad ya seleccionada", group->name,
                  'f');
    }
}

void updateGroupActivitiesInGroupList(GroupList *groupList, Group *group) {
    for (int i = 0; i < groupList->numGroups; i++) {
        if (strcmp(groupList->groups[i]->name, group->name) == 0) {
            groupList->groups[i] = group;
        }
    }
}

void seeGroupActivities(Group *group) {
    printf("Actividades del grupo:\n");
    for (int i = 0; i < group->numActivities; i++) {
        printf("%s\n", group->activityList[i].name);
    }
}

int readActivitiesInDB(ActivityList *activityList, sqlite3 *db) {
    sqlite3_stmt *statement;

    char sql[] = "select * from activities";

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "Preparar statment", 'f');
        return result;
    }

    activityList->numActivities = 0;
    do {
        result = sqlite3_step(statement);
        if (result == SQLITE_ROW) {
            strcpy(activityList->activityList[activityList->numActivities].name,
                   sqlite3_column_text(statement, 0));
            activityList->numActivities++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(statement);
    if (result != SQLITE_OK) {
        logAction(sqlite3_errmsg(db), "Finalizar statment", 'f');
        return result;
    }

    return SQLITE_OK;
}

char *jsonifyActivities(ActivityList activityList) {
    char *json = (char *) malloc(1000);
    strcpy(json, "[");
    for (int i = 0; i < activityList.numActivities; i++) {
        strcat(json, "{");
        strcat(json, "\"name\": \"");
        strcat(json, activityList.activityList[i].name);
        strcat(json, "\"");
        strcat(json, "}");
        if (i < activityList.numActivities - 1) {
            strcat(json, ",");
        }
    }
    strcat(json, "]");
    strcat(json, "\0");
    return json;
}

void parseActivity(const char *p, Activity *activity) {
    while (*p != '}') {
        if(strncmp(p, "\"name\": \"", 9) == 0) {
            strcpy(activity->name, parseAttribute(p, 9, MAX_NAME_ACTIVITY));
        }
        p++;
    }
}

ActivityList unJsonifyActivities(char *json, int *numCicles) {
    ActivityList activityList;
    activityList.numActivities = 0;
    char *jsonAux = json;
    while (*jsonAux && *jsonAux != ']') {
        if (*jsonAux == '{') {
            Activity activity;
            parseActivity(jsonAux, &activity);
            addActivityToList(&activityList, activity);
        }
        jsonAux++;
        (*numCicles)++;
    }
    return activityList;
}

char *processActivitiesDB(sqlite3 *db) {
    ActivityList activityList;
    int result = readActivitiesInDB(&activityList, db);
    if (result != SQLITE_OK) {
        logAction("Error leyendo las actividades de la base de datos", "sistema",
                  'f');
        return NULL;
    }
    char *json = jsonifyActivities(activityList);
    return json;
}

int insertActivitiesInDB(ActivityList activityList, sqlite3 *db) {
    deleteDB(db, "activities");

    for (int i = 0; i < activityList.numActivities; i++) {
        sqlite3_stmt *statement;

        char sql[] = "insert into activities (name) values (?)";
        int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
        if (result != SQLITE_OK) {
            logAction(sqlite3_errmsg(db), "Preprar statment", 'f');
            return result;
        }

        sqlite3_bind_text(statement, 1, activityList.activityList[i].name,
                          strlen(activityList.activityList[i].name), SQLITE_STATIC);

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

void deleteActivity(ActivityList *activityList) {
    int option = seeActivities(activityList);
    if (option == -1) {
        printf("Seleccione una opcion valida.\n");
        logAction("Actividad no valida seleccionada", "sistema", 'f');
    } else {
        Activity activityListAux[(activityList->numActivities) - 1];
        int count = 0;
        for (int i = 0; i < activityList->numActivities; i++) {
            if (option - 1 != i) {
                activityListAux[count] = activityList->activityList[i];
                count++;
            }
        }
        activityList->numActivities -= 1;
        printf("La actividad se ha eliminado correctamente.\n");
        logAction("Actividad eliminada correctamente", "sistema", 's');

        for (int i = 0; i < activityList->numActivities; i++) {
            activityList->activityList[i] = activityListAux[i];
        }
    }
}

void addActivity(ActivityList *activityList, Activity activity) {
    int activityIsInList = 0;
    for (int i = 0; i < activityList->numActivities; i++) {
        if (strcmp(activityList->activityList[i].name, activity.name) == 0) {
            activityIsInList = 1;
        }
    }

    if (activityIsInList == 0) {
        activityList->activityList[activityList->numActivities] = activity;
        activityList->numActivities += 1;
        printf("La actividad se ha añadido correctamente.\n");
        logAction("Actividad añadida correctamente", activity.name, 's');
    } else {
        printf("La actividad ya esta en la lista.\n");
        logAction("Error añadiendo la actividad", activity.name, 'f');
    }
}

void addGroupToList(GroupList *groupList, Group *group, int maxGroups) {
    if (groupList->numGroups == maxGroups) {
        printf("No se pueden añadir más grupos.\n");
        logAction("Error añadiendo grupo", "sistema", 'f');
        return;
    }
    // Check if the groupList is null
    if (groupList->groups == NULL) {
        printf("Los grupos son nulos\n");
        logAction("Grupos eran nulos al añadir", "sistema", 'f');
        groupList->groups = (Group **) malloc(sizeof(Group *) * maxGroups);
    }
    groupList->groups[groupList->numGroups] = group;
    groupList->numGroups++;
    logAction("Grupo añadido correctamente", group->name, 's');
}

void addActivityToList(ActivityList *activityList, Activity activity) {
    if (activityList->numActivities == MAX_ACTIVITIES) {
        printf("No se pueden añadir más actividades.\n");
        logAction("Error añadiendo actividad", "sistema", 'f');
        return;
    }
    activityList->activityList[activityList->numActivities] = activity;
    activityList->numActivities++;
}

ActivityList fromActivityArrayToActivityList(Activity activities[], int numActividades) {
    ActivityList activityList;
    activityList.numActivities = 0;
    for (int i = 0; i < numActividades; i++) {
        addActivityToList(&activityList, activities[i]);
    }
    return activityList;
}

char *jsonifyGroupList(GroupList groupList) {
    char *json = (char *) malloc(1000);
    strcpy(json, "[");
    for (int i = 0; i < groupList.numGroups; i++) {
        strcat(json, "{");
        strcat(json, "\"name\": \"");
        strcat(json, groupList.groups[i]->name);
        strcat(json, "\", ");

        int numUsers = groupList.groups[i]->numUsers;
        UserList userList = fromUserArrayToUserList(groupList.groups[i]->users, numUsers);
        strcat(json, "\"users\": ");
        strcat(json, jsonifyUserList(userList));

        ActivityList activityList = fromActivityArrayToActivityList(groupList.groups[i]->activityList, groupList.groups[i]->numActivities);
        strcat(json, ", \"activities\": ");
        strcat(json, jsonifyActivities(activityList));

        strcat(json, "}");
        if (i < groupList.numGroups - 1) {
            strcat(json, ",");
        }
    }
    strcat(json, "]");
    strcat(json, "\0");
    return json;
}

void parseGroup(char *p, Group *group, int *numCiclesAux) {
    int numCicles = 0;
    while (*p != '}' && *p) {
        if (strncmp(p, "\"name\": \"", 9) == 0) {
            group->name = parseAttribute(p, 9, MAX_GROUP_NAME);
        } else if (strncmp(p, "\"users\": ", 8) == 0) {
            numCicles = 0;
            UserList userList = unJsonifyUserList(p, &numCicles);
            p+=numCicles;
            (*numCiclesAux) += numCicles;
            group->numUsers = userList.numUsers;
            group->users = userList.userList;
        } else if (strncmp(p, "\"activities\": ", 14) == 0) {
            numCicles = 0;
            ActivityList activityList = unJsonifyActivities(p, &numCicles);
            p+=numCicles;
            (*numCiclesAux) += numCicles;
            group->numActivities = activityList.numActivities;
            for (int i = 0; i < activityList.numActivities; i++) {
                group->activityList[i] = activityList.activityList[i];
            }
        }
        p++;
        (*numCiclesAux)++;
    }
}

void parseNewGroup(char *json, Group *group) {
    int numCicles = 0;
    while (*json != '}') {
        if (strncmp(json, "\"name\": \"", 9) == 0) {
            group->name = parseAttribute(json, 9, MAX_GROUP_NAME);
        } else if (strncmp(json, "\"maxUsers\": ", 12) == 0) {
            group->maxUsers = parseAge(json);
        } else if (strncmp(json, "\"numUsers\": ", 12) == 0) {
            group->numUsers = parseAge(json);
        } else if (strncmp(json, "\"numActivities\": ", 17) == 0) {
            group->numActivities = parseAge(json);
        }
        json++;
        numCicles++;
    }
}

GroupList unJsonifyGroupList(char *json) {
    GroupList* groupList = (GroupList *) malloc(sizeof(GroupList));
    int maxGroups = 100;
    groupList->groups = (Group **) malloc(sizeof(Group *) * maxGroups);
    groupList->numGroups = 0;
    int numCicles = 0;
    char *jsonAux = json;
    while (*jsonAux) {
        if (*jsonAux == '{') {
            Group* group = (Group *) malloc(sizeof(Group));
            numCicles = 0;
            parseGroup(jsonAux, group, &numCicles);
            jsonAux+=numCicles;
            group->users = (User *) malloc(sizeof(User) * group->maxUsers);
            addGroupToList(groupList, group, maxGroups);
        }
        jsonAux++;
    }
    return *groupList;
}

void writeGroupsInFile(GroupList groups, char *file) {
    char *json = jsonifyGroupList(groups);
    FILE *f = fopen(file, "w");
    fprintf(f, "%s", json);
    free(json);
}

void readGroupsFromFile(char *fileName, GroupList *groupList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", fileName);
        return;
    }
    GroupList result = readGroupsFromFileAux(file);
    if (result.groups == NULL) {
        printf("Error al leer los grupos del archivo: %s\n", fileName);
        return;
    }
    *groupList = result;
    fclose(file);
}

GroupList readGroupsFromFileAux(FILE *file) {
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *json = (char *) malloc(fileSize + 1);
    fread(json, 1, fileSize, file);
    json[fileSize] = '\0';
    GroupList groupList = unJsonifyGroupList(json);
    free(json);
    return groupList;
}

Group *findGroupByName(GroupList groupList, char *name) {
    for (int i = 0; i < groupList.numGroups; i++) {
        if (strcmp(groupList.groups[i]->name, name) == 0) {
            return groupList.groups[i];
        }
    }
    return NULL;
}

char *seekGroupName(char *json, int skip) {
    json += skip;
    char *name = (char *) malloc(30);
    char *namePtr = name;
    while (*json != '\"') {
        *namePtr++ = *json++;
    }
    *namePtr = '\0';
    return name;
}