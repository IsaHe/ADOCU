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
    User* users;
    char* nombreGrupo;
    int numUsuariosMax;
    int numUsuariosAct;
}Grupo;

typedef struct {
    Grupo* grupos;
    int numGrupos;
}GruposList;

Grupo* crearGrupo(char* nombreGrupo, int numUsuariosMax, GruposList* gl);
Grupo* unirseGrupo(char* codInvitacion, User u, GruposList* gl);
void addUserToGrupo(Grupo* g, User u);

bool isGrupoLleno(Grupo* g);
bool isUserInGrupo(Grupo* g, User u);
bool codigoInvitacionValido(char* codInvitacion, GruposList gl);

void freeGrupo(Grupo* g);

char* menuUnirseGrupo();
char* menuCrearGrupoNombre();
int menuCrearGrupoNumUsuarios();
#endif //ADOCU_GRUPO_H
