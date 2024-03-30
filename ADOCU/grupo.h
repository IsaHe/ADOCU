#include "user.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef ADOCU_GRUPO_H
#define ADOCU_GRUPO_H
#define MAX_NOMBRE_GRUPO 20

typedef struct {
    User* users;
    char* nombreGrupo;
    int numUsuariosMax;
    int numUsuariosAct;
}Grupo;

Grupo* crearGrupo(char* optionGroup);
Grupo* unirseGrupo(char* codInvitacion, User u);
void addUserToGrupo(Grupo* g, User u);

bool isGrupoLleno(Grupo* g);
bool isUserInGrupo(Grupo* g, User u);
Grupo* validarCodInvitacion(char* codInvitacion);
bool validateNombreGrupo(char* nombreGrupo);
bool validateNumUsuariosMax(char* numUsuariosMax);

void freeGrupo(Grupo* g);

#endif //ADOCU_GRUPO_H
