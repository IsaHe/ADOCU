#include "grupo.h"


Grupo* crearGrupo(char* optionGroup){
    // optionGroup contiene un char* con formato: "nombreGrupo;numUsuariosMax"
    // Se debe separar el nombre del grupo y el número de usuarios máximo

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

    return g;
}

void unirseGrupo(char* codInvitacion){

}

bool isGrupoLleno(Grupo* g){
    return false;
}

bool isUserInGrupo(Grupo* g, User u){
    return false;
}

bool validarCodInvitacion(char* codInvitacion){
    return false;
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