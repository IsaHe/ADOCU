#include "grupo.h"


void crearGrupo(char* optionGroup){
    // optionGroup contiene un char* con formato: "nombreGrupo;numUsuariosMax"
    for( ;*optionGroup != ';'; optionGroup++){

    }
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
    // Comprueba que el número de usuarios máximo sea un número
    for ( ; *numUsuariosMax; numUsuariosMax++){
        if (*numUsuariosMax < '0' || *numUsuariosMax > '9')
            return false;
    }

    return true;
}