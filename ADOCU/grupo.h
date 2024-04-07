#include "user.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef ADOCU_GRUPO_H
#define ADOCU_GRUPO_H
#define MAX_NOMBRE_GRUPO 20

typedef struct {
  char name[30];
} Activity;

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

int seeActivities(Activity* activityList, int size);
void addActivity(Activity activity, Grupo* group);
void seeGroupActivities(Grupo* group);

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
