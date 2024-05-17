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
    for (int i = 0; i < groupList->numGroups; i++) {
        if (strcmp(groupList->groups[i]->name, name) == 0) {
            if (groupList->groups[i]->maxUsers > groupList->groups[i]->numUsers) {
                Group *group = groupList->groups[i];
                groupList->groups[i]->users[groupList->groups[i]->numUsers] = user;
                groupList->groups[i]->numUsers++;
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

ActivityList unJsonifyActivities(char *json) {
    ActivityList activityList;
    activityList.numActivities = 0;
    char *jsonAux = json;
    while (*jsonAux) {
        if (*jsonAux == '{') {
            Activity activity;
            parseActivity(jsonAux, &activity);
            addActivityToList(&activityList, activity);
        }
        jsonAux++;
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

void addGroupToList(GroupList *groupList, Group *group) {
    Group **groupsAux = (Group **) malloc(sizeof(Group*) * groupList->numGroups + 1);
    for (int i = 0; i < groupList->numGroups; i++) {
        groupsAux[i] = groupList->groups[i];
    }
    groupsAux[groupList->numGroups] = group;

    free(groupList->groups);
    groupList->groups = groupsAux;
    groupList->numGroups++;
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