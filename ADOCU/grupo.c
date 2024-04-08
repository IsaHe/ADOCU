#include "grupo.h"
#include <string.h>

Grupo* crearGrupo(char* nombreGrupo, int numUsuariosMax, GruposList* gl){
    Grupo* g = (Grupo*)malloc(sizeof(Grupo));
    g->nombreGrupo = nombreGrupo;
    g->numUsuariosMax = numUsuariosMax;
    g->numUsuariosAct = 0;
    g->users = (User*)malloc(numUsuariosMax * sizeof(User));
    g -> numActivities = 0;

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
    int find = 0;
    for (int i = 0; i < g -> numUsuariosAct; i++) {
        if (strcmp(g -> users[i].username, u.username) == 0) {
            find = 1;
        }
    }

    if (find == 0) {
        g->users[g->numUsuariosAct] = u;
        g->numUsuariosAct++;
    }
}

Grupo* unirseGrupo(char* codInvitacion, User u, GruposList* gl){
    if(!codigoInvitacionValido(codInvitacion, *gl)){
        printf("Código de invitación inválido.\n");
        return NULL;
    }

    for(int i = 0; i < gl->numGrupos; i++){
        if(strcmp(gl->grupos[i].nombreGrupo, codInvitacion) == 0 && isGrupoLleno(&gl->grupos[i], u)){
            addUserToGrupo(&gl->grupos[i], u);
            printf("Te has unido al grupo con éxito\n");
            return &gl->grupos[i];
        }
    }
    printf("No se ha podido unir al grupo.\n");
    return NULL;
}

bool isGrupoLleno(Grupo* g, User u){
    return g -> numUsuariosAct < g -> numUsuariosMax;
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
        fflush(stdin);
        scanf("%s", nombreGrupo);
    } while (strlen(nombreGrupo) < 1);

    nombreGrupo[strcspn(nombreGrupo, "\n")] = 0;

    return nombreGrupo;
}

int menuCrearGrupoNumUsuarios() {
    char str[10];

    do {
        printf("Introduce el número máximo de usuarios del grupo: ");
        fflush(stdin);
        scanf("%s", str);
    } while (str[0] == 0);

    // Convertir la cadena a un número entero
    char *end;
    long numUsuarios = strtol(str, &end, 10);

    return (int)numUsuarios;
}

char* menuUnirseGrupo() {
    char* codInvitacion = malloc(MAX_NOMBRE_GRUPO + 1);

    do {
        printf("Introduce el código de invitación del grupo: ");
        fflush(stdin);
        scanf("%s", codInvitacion);
    } while (strlen(codInvitacion) < 1);

    codInvitacion[strcspn(codInvitacion, "\n")] = 0;

    return codInvitacion;
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

void addActivityToGroup(Activity activity, Grupo* group) {
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

void seeGroupActivities(Grupo* group) {
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
