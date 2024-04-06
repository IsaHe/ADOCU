#include "grupo.h"

Grupo* crearGrupo(char* nombreGrupo, int numUsuariosMax, GruposList* gl){
    Grupo* g = (Grupo*)malloc(sizeof(Grupo));
    g->nombreGrupo = nombreGrupo;
    g->numUsuariosMax = numUsuariosMax;
    g->numUsuariosAct = 0;
    g->users = (User*)malloc(numUsuariosMax * sizeof(User));

    for (int i = 0; i < gl->numGrupos; i++){
    	if (strcmp(gl->grupos[i].nombreGrupo,g->nombreGrupo) == 0){
    		return NULL;
    	}
    }
    gl->grupos[gl->numGrupos] = *g;
    gl->numGrupos++;

    return g;
}

void addUserToGrupo(Grupo* g, User u){
    g->users[g->numUsuariosAct] = u;
    g->numUsuariosAct++;
}

Grupo* unirseGrupo(char* codInvitacion, User u, GruposList* gl){
    if(!codigoInvitacionValido(codInvitacion, *gl)){
        printf("Código de invitación inválido.\n");
        return NULL;
    }

    for(int i = 0; i < gl->numGrupos; i++){
        if(strcmp(gl->grupos[i].nombreGrupo, codInvitacion) == 0 && !isGrupoLleno(&gl->grupos[i]) && !isUserInGrupo(&gl->grupos[i], u)){
            addUserToGrupo(&gl->grupos[i], u);
            printf("Te has unido al grupo con éxito\n");
            return &gl->grupos[i];
        }
    }
    printf("No se ha podido unir al grupo.\n");
    return NULL;
}

bool isGrupoLleno(Grupo* g){
    return g->numUsuariosAct == g->numUsuariosMax;
}

bool isUserInGrupo(Grupo* g, User u){
    for(int i = 0; i < g->numUsuariosAct; i++){
        if(strcmp(g->users[i].username, u.username) == 0){
            return true;
        }
    }
    return false;
}

bool codigoInvitacionValido(char* codInvitacion, GruposList gl){

    // El codigo de invitacion es el nombre del grupo
    for(int i = 0; i < gl.numGrupos; i++){
        if(strcmp(gl.grupos[i].nombreGrupo, codInvitacion) == 0){
            return true;
        }
    }
    return false;
}

void seeGroupsNames(GruposList gl){
	for(int i = 0; i < gl.numGrupos; i++){
		printf("Grupo: %s, con %d usuarios, y un maximo de %d usuarios\n", gl.grupos[i].nombreGrupo, gl.grupos[i].numUsuariosAct, gl.grupos[i].numUsuariosMax);

	}
}

void freeGrupo(Grupo* g){
    // TODO: Aplicar al cerrar la app
    free(g->nombreGrupo);
    free(g->users);
    free(g);
}

char* menuCrearGrupoNombre() {
    char* nombreGrupo = malloc(MAX_NOMBRE_GRUPO + 1);

    do {
        printf("Introduce el nombre del grupo: ");
        fflush(stdout);
        fflush(stdin);
        fgets(nombreGrupo, MAX_NOMBRE_GRUPO, stdin);
    } while (strlen(nombreGrupo) < 1);

    nombreGrupo[strcspn(nombreGrupo, "\n")] = 0;

    return nombreGrupo;
}

int menuCrearGrupoNumUsuarios() {
    char str[10];

    do {
        printf("Introduce el número máximo de usuarios del grupo: ");
        fflush(stdin);
        fgets(str, 10, stdin);
    } while (str[0] == 0);

    // Convertir la cadena a un número entero
    char *end;
    long numUsuarios = strtol(str, &end, 10);

    // Verificar si la conversión fue exitosa
    if (end == str || *end != '\n' || numUsuarios > INT_MAX) {
        printf("Entrada inválida. Por favor, introduce un número.\n");
        return -1;
    }

    return (int)numUsuarios;
}

char* menuUnirseGrupo() {
    char* codInvitacion = malloc(MAX_NOMBRE_GRUPO + 1);

    do {
        printf("Introduce el código de invitación del grupo: ");
        fflush(stdin);
        fgets(codInvitacion, MAX_NOMBRE_GRUPO + 1, stdin);
    } while (strlen(codInvitacion) == 1);

    codInvitacion[strcspn(codInvitacion, "\n")] = 0;

    return codInvitacion;
}
