#include "grupo.h"


Grupo* listaGrupos[255];
int numGrupos = 0;

Grupo* crearGrupo(char* optionGroup){

    if(numGrupos >= 255)
        return NULL;

    char* nombreGrupo = malloc(MAX_NOMBRE_GRUPO);
    for(int i = 0 ;*optionGroup != ';'; optionGroup++, i++){
        nombreGrupo[i] = *optionGroup;
    }

    optionGroup++;

    char* numUsuariosMax = malloc(3);
    for(int i = 0; *optionGroup; optionGroup++, i++){
        numUsuariosMax[i] = *optionGroup;
    }

    //Crear el grupo
    Grupo* g = malloc(sizeof(Grupo));
    g->nombreGrupo = nombreGrupo;
    g->numUsuariosMax = atoi(numUsuariosMax);
    g->numUsuariosAct = 1;
    g->users = malloc(sizeof(User) * g->numUsuariosMax);

    listaGrupos[numGrupos] = g;
    numGrupos++;
    return g;
}

void addUserToGrupo(Grupo* g, User u){
    g->users[g->numUsuariosAct - 1] = u;
}

Grupo* unirseGrupo(char* codInvitacion, User u){

    Grupo* g = validarCodInvitacion(codInvitacion);

    if (g == NULL || isGrupoLleno(g) || isUserInGrupo(g, u))
        return NULL;

    g->numUsuariosAct++;
    addUserToGrupo(g, u);
    return g;
}

bool isGrupoLleno(Grupo* g){
    if (g->numUsuariosAct == g->numUsuariosMax)
        return true;
    return false;
}

bool isUserInGrupo(Grupo* g, User u){
    for (int i = 0; i < g->numUsuariosAct; ++i){
        if (strcmp(g->users[i].username, u.username) == 0)
            return true;
    }
    return false;
}

Grupo* validarCodInvitacion(char* codInvitacion){
    // El codigo de invitacion sera: "nombreGrupo/numUsuariosActuales"

    char* nombreGrupo = malloc(MAX_NOMBRE_GRUPO);
    for ( int i = 0; *codInvitacion; codInvitacion++, i++){
        if(i >= MAX_NOMBRE_GRUPO)
            return NULL;
        if (*codInvitacion == '/'){
            nombreGrupo[i] = '\0';
            break;
        }
        nombreGrupo[i] = *codInvitacion;
    }

    codInvitacion++;

    char* numUsuariosAct = malloc(3);
    for ( int i = 0; *codInvitacion; codInvitacion++, i++){
        if(i >= 3 || (*codInvitacion < '0' || *codInvitacion > '9'))
            return NULL;

        numUsuariosAct[i] = *codInvitacion;
    }

    for (int i = 0; i < numGrupos; ++i) {
        if ((strcmp(listaGrupos[i]->nombreGrupo, nombreGrupo) == 0 && listaGrupos[i]->numUsuariosAct == atoi(numUsuariosAct))){
            return listaGrupos[i];
        }
    }

    return NULL;
}

bool validateNombreGrupo(char* nombreGrupo){
    //Comprueba que el nombre del grupo no sea mayor que MAX_NOMBRE_GRUPO y que no contenga el caracter ';'
    if (strlen(nombreGrupo) > MAX_NOMBRE_GRUPO)
        return false;

    for ( ; *nombreGrupo; nombreGrupo++){
        if (*nombreGrupo == ';')
            return false;
    }

    return true;
}

bool validateNumUsuariosMax(char* numUsuariosMax){
    // Comprueba que el número de usuarios máximo sea un número entero y no tenga más de 3 dígitos
    for ( ; *numUsuariosMax; numUsuariosMax++){
        if (*numUsuariosMax < '0' || *numUsuariosMax > '9')
            return false;
    }

    if (strlen(numUsuariosMax) > 3)
        return false;

    return true;
}

void freeGrupo(Grupo* g){
    // TODO: Aplicar al cerrar la app
    free(g->nombreGrupo);
    free(g->users);
    free(g);
}
