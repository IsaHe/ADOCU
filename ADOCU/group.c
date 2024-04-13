#include "group.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GROUP_NAME 30

void createGroup(char* name, int maxUsers, GroupList* groupList) {
  Group group;
  group.name = name;
  group.maxUsers = maxUsers;
  group.numUsers = 0;
  group.users = (User*) malloc(sizeof(User) * maxUsers);
  int exists = 0;
  for (int i = 0; i < groupList -> numGroups; i++) {
    if (groupList -> groups[i].name == group.name) {
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

void joinGroup(char* name, User user, GroupList* groupList) {
  for (int i = 0; i < groupList -> numGroups; i++) {
    if (strcmp(groupList -> groups[i].name, name) == 0) {
      if (groupList -> groups[i].maxUsers > groupList -> groups[i].numUsers) {
        groupList -> groups[i].users[groupList -> groups[i].numUsers] = user;
        groupList -> groups[i].numUsers++;
        printf("Te has unido al grupo correctamente.\n");
      } else {
        printf("Este grupo ha alcanzado el numero maximo de usuarios.\n");
      }
    }
  }
}

void printGroups(GroupList groupList) {
  printf("Numero de grupos: %i\n", groupList.numGroups);
  for (int i = 0; i < groupList.numGroups; i++) {
    printf("Grupo %i: %s  %i\n", i + 1, groupList.groups[i].name, groupList.groups[i].numUsers);
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
    fflush(stdin);
    scanf("%s", name);
  } while (strlen(name) < 1);
  name[strcspn(name, "\n")] = 0;
  return name;
}

char* menuCreateGroupName() {
    char* name = (char*) malloc(sizeof(char) * (MAX_GROUP_NAME + 1));
    do {
        printf("Introduce el nombre del grupo: ");
        fflush(stdin);
        scanf("%s", name);
    } while (strlen(name) < 1);
    name[strcspn(name, "\n")] = 0;
    return name;
}

int menuCreateGroupMaxUsers() {
  int maxUsers;
  char str[10];
  do {
    printf("Introduce el número máximo de usuarios del grupo: ");
    fflush(stdin);
    scanf("%s", str);
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
  scanf(" %i", &option);
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

void seeGroupActivities(Group* group) {
    printf("Actividades del grupo:\n");
    for (int i = 0; i < group -> numActivities; i++) {
        printf("%s\n", group -> activityList[i].name);
    }
}

void initActivities(ActivityList* activityList) {
  strcpy(activityList -> activityList[0].name, "Futbol");
  strcpy(activityList -> activityList[1].name, "Boxeo");
  strcpy(activityList -> activityList[2].name, "Baloncesto");
  strcpy(activityList -> activityList[3].name, "Piraguismo");
  strcpy(activityList -> activityList[4].name, "Tenis");
  strcpy(activityList -> activityList[5].name, "Padel");
  strcpy(activityList -> activityList[6].name, "Golf");
  strcpy(activityList -> activityList[7].name, "Ajedrez");
  strcpy(activityList -> activityList[8].name, "Senderismo");
  strcpy(activityList -> activityList[9].name, "Surf");
  activityList -> numActivities = 10;
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
