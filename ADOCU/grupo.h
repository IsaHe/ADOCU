#include "user.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef ADOCU_GRUPO_H
#define ADOCU_GRUPO_H
#define MAX_NOMBRE_GRUPO 20
#define MAX_ACTIVITIES 10

typedef struct {
  char name[30];
} Activity;

typedef struct {
    Activity activityList[MAX_ACTIVITIES];
    int numActivities;
} ActivityList;

typedef struct {
    User* users;
    char* nombreGrupo;
    int numUsuariosMax;
    int numUsuariosAct;
    Activity activityList[10];
    int numActivities;
}Grupo;

typedef struct {
    Grupo* grupos;
    int numGrupos;
}GruposList;

int seeActivities(ActivityList* activityList);
void addActivityToGroup(Activity activity, Grupo* group);
void seeGroupActivities(Grupo* group);
void initActivities(ActivityList* activityList);
void deleteActivity(ActivityList* activityList);
void addActivity(ActivityList* activityList, Activity activity);

Grupo* crearGrupo(char* nombreGrupo, int numUsuariosMax, GruposList* gl);
Grupo* unirseGrupo(char* codInvitacion, User u, GruposList* gl);
void addUserToGrupo(Grupo* g, User u);

bool isGrupoLleno(Grupo* g, User u);
bool codigoInvitacionValido(char* codInvitacion, GruposList gl);

void seeGroupsNames(GruposList gl);
void freeGrupo(Grupo* g);

char* menuUnirseGrupo();
char* menuCrearGrupoNombre();
int menuCrearGrupoNumUsuarios();

#endif //ADOCU_GRUPO_H
