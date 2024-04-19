#include "group.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GROUP_NAME 30
#define MAX_USERS 10
#define MAX_ACTIVITIES 10

void createGroup(char* name, int maxUsers, GroupList* groupList, Group* group) {
  group -> name = name;
  group -> maxUsers = maxUsers;
  group -> numUsers = 0;
  group -> users = (User*) malloc(sizeof(User) * maxUsers);
  group -> numActivities = 0;
  int exists = 0;
  for (int i = 0; i < groupList -> numGroups; i++) {
    if (strcmp(groupList -> groups[i] -> name, group -> name) == 0) {
      exists = 1;
    }
  }
  if (exists == 0) {
    groupList -> groups[groupList -> numGroups] = group;
    groupList -> numGroups++;
    printf("Grupo creado correctamente.\n");
  } else {
    printf("Ya existe un grupo con ese nombre.\n");
  }
}

Group* joinGroup(char* name, User user, GroupList* groupList) {
  for (int i = 0; i < groupList -> numGroups; i++) {
    if (strcmp(groupList -> groups[i] -> name, name) == 0) {
      if (groupList -> groups[i] -> maxUsers > groupList -> groups[i] -> numUsers) {
        Group* group = groupList -> groups[i];
        groupList -> groups[i] -> users[groupList -> groups[i] -> numUsers] = user;
        groupList -> groups[i] -> numUsers++;
        printf("Te has unido al grupo correctamente.\n");
        return group;
      } else {
        printf("Este grupo ha alcanzado el numero maximo de usuarios.\n");
        return NULL;
      }
    }
  }
  return NULL;
}

void printGroups(GroupList groupList) {
  printf("Numero de grupos: %i\n", groupList.numGroups);
  for (int i = 0; i < groupList.numGroups; i++) {
    printf("Grupo %i: %s  %i\n", i + 1, groupList.groups[i] -> name, groupList.groups[i] -> numUsers);
  }
}

void freeGroup(Group* group) {
  free(group -> users);
  free(group -> name);
}

char* menuJoinGroup() {
  char* name = (char*) malloc(sizeof(char) * (MAX_GROUP_NAME + 1));
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

char* menuCreateGroupName() {
    char* name = (char*) malloc(sizeof(char) * (MAX_GROUP_NAME + 1));
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

int seeActivities(ActivityList* activityList) {
  int option;
  for (int i = 0; i < activityList -> numActivities; i++) {
    printf("%i. %s\n", i + 1, activityList -> activityList[i].name);
  }
  printf("Elige una opcion: ");
  fflush(stdout);
  char optionStr[MAX_ACTIVITIES];
  fgets(optionStr, MAX_ACTIVITIES, stdin);
  sscanf(optionStr, "%i", &option);
  clearIfNeeded(optionStr, MAX_ACTIVITIES);
  optionStr[strcspn(optionStr, "\n")] = 0;
  if (option <= activityList -> numActivities) {
      return option;
  } else {
      return -1;
  }
}

void addActivityToGroup(Activity activity, Group* group) {
  int activityInList = 0;
  for (int i = 0; i < group -> numActivities; i++) {
    if (strcmp(activity.name, group -> activityList[i].name) == 0) {
      activityInList = 1;
    }
  }

  if (activityInList == 0) {
    group -> activityList[group -> numActivities] = activity;
    group -> numActivities += 1;
    printf("Actividad seleccionada.\n");
  } else {
    printf("Lo siento esa actividad ya está seleccionada.\n");
  }
}

void updateGroupActivitiesInGroupList(GroupList* groupList, Group* group) {
    for (int i = 0; i < groupList -> numGroups; i++) {
        if (strcmp(groupList -> groups[i] -> name, group -> name) == 0) {
            groupList -> groups[i] = group;
        }
    }
}

void seeGroupActivities(Group* group) {
    printf("Actividades del grupo:\n");
    for (int i = 0; i < group -> numActivities; i++) {
        printf("%s\n", group -> activityList[i].name);
    }
}

int readActivitiesInDB(ActivityList* activityList, sqlite3* db) {
	sqlite3_stmt* statement;

	char sql[] = "select * from activities";

	int result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (SELECT).\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	activityList -> numActivities = 0;
	do {
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW) {
			strcpy(activityList -> activityList[activityList -> numActivities].name, sqlite3_column_text(statement, 0));
			activityList -> numActivities++;
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

int insertActivitiesInDB(ActivityList activityList, sqlite3* db) {
  deleteDB(db, "activities");

  for (int i = 0; i < activityList.numActivities; i++) {
    sqlite3_stmt* statement;

    char sql[] = "insert into activities (name) values (?)";
		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &statement, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparando el statement (INSERT).\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

		sqlite3_bind_text(statement, 1, activityList.activityList[i].name, strlen(activityList.activityList[i].name), SQLITE_STATIC);

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

void deleteActivity(ActivityList* activityList) {
    int option = seeActivities(activityList);
    if (option == -1) {
        printf("Seleccione una opcion valida.\n");
    } else {
        Activity activityListAux[(activityList -> numActivities) - 1];
        int count = 0;
        for (int i = 0; i < activityList -> numActivities; i++) {
            if (option - 1 != i) {
                activityListAux[count] = activityList -> activityList[i];
                count++;
            }
        }
        activityList -> numActivities -= 1;
        printf("La actividad se ha eliminado correctamente.\n");

        for (int i = 0; i < activityList -> numActivities; i++) {
            activityList -> activityList[i] = activityListAux[i];
        }
    }
}

void addActivity(ActivityList* activityList, Activity activity) {
    int activityIsInList = 0;
    for (int i = 0; i < activityList -> numActivities; i++) {
        if (strcmp(activityList -> activityList[i].name, activity.name) == 0) {
            activityIsInList = 1;
        }
    }

    if (activityIsInList == 0) {
        activityList -> activityList[activityList -> numActivities] = activity;
        activityList -> numActivities += 1;
        printf("La actividad se ha añadido correctamente.\n");
    } else {
        printf("La actividad ya esta en la lista.\n");
    }
}

void writeGroupsInFile(GroupList groupList, char* fileName) {
  FILE* file;

  file = fopen(fileName, "w");

  if (file != (FILE*) NULL) {
    for (int i = 0; i < groupList.numGroups; i++) {
      fprintf(file, "Grupo: %s (%i usuarios max).\n", groupList.groups[i] -> name, groupList.groups[i] -> maxUsers);
      fprintf(file, "Users (%i usuarios):\n", groupList.groups[i] -> numUsers);
      for (int j = 0; j < groupList.groups[i] -> numUsers; j++) {
        fprintf(file, "\tNombre: %s, Usuario: %s, Contraseña: %s, Edad: %i, Admin: %c.\n", groupList.groups[i] -> users[j].name, groupList.groups[i] -> users[j].username, groupList.groups[i] -> users[j].password, groupList.groups[i] -> users[j].age, groupList.groups[i] -> users[j].admin);
      }
      fprintf(file, "Activities (%i actividades):\n", groupList.groups[i] -> numActivities);
      for (int j = 0; j < groupList.groups[i] -> numActivities; j++) {
        fprintf(file, "\t- %s\n", groupList.groups[i] -> activityList[j].name);
      }
    }
    fclose(file);
  }
}
