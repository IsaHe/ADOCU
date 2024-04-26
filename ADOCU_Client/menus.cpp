//
// Created by Isaac Herbozo on 26/4/24.
//

#include "menus.h"

Menus::Menus() {}

char Menus::mainMenu() {
    cout << "1. Iniciar Sesión" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << "Introduce opción: ";
    char option;
    cin >> option;
    cin.ignore();
    return option;
}

char Menus::menuValoration() {
    cout << "1. MUY MAL" << endl;
    cout << "2. MAL" << endl;
    cout << "3. REGULAR" << endl;
    cout << "4. BIEN" << endl;
    cout << "5. MUY BIEN" << endl;
    cout << "0. Volver" << endl;
    cout << "Introduce opción: ";
    char option;
    cin >> option;
    cin.ignore();
    return option;
}

char Menus::menuAdmin() {
    cout << "1. Eliminar Usuarios" << endl;
    cout << "2. Añadir Actividades" << endl;
    cout << "3. Eliminar Actividades" << endl;
    cout << "4. Ver Valoracion Media" << endl;
    cout << "5. Ver Valoracion Por Usuario" << endl;
    cout << "6. Volver" << endl;
    cout << "Introduce una opción: ";
    char option;
    cin >> option;
    cin.ignore();
    return
}

char* Menus::menuRegistro() {
    // TODO: Implementar
}

char Menus::menuLogIn() {
    cout << "1. Crear Grupo" << endl;
    cout << "2. Unirse a Grupo" << endl;
    cout << "3. Valorar Aplicacion" << endl;
    cout << "4. Volver" << endl;
    cout << "Introduce una opción: ";
    char option;
    cin >> option;
    cin.ignore();
    return option;
}

char Menus::menuActivity() {
    cout << "1. Ver Actividades" << endl;
    cout << "2. Crear Actividad" << endl;
    cout << "3. Eliminar Actividad" << endl;
    cout << "4. Volver" << endl;
    cout << "Introduce una opción: ";
    char option;
    cin >> option;
    cin.ignore();
    return option;
}

char* Menus::menuCreateGroupName() {
    cout << "Introduce el nombre del grupo: ";
    char* groupName = new char[MAX_LINE];
    cin.getline(groupName, MAX_LINE);
    return groupName;
}

int Menus::menuCreateGroupMaxUsers() {
    cout << "Introduce el número máximo de usuarios del grupo: ";
    int maxUsers;
    cin >> maxUsers;
    cin.ignore();
    return maxUsers;
}

char* Menus::menuJoinGroup() {
    cout << "Introduce el nombre del grupo: ";
    char* groupName = new char[MAX_LINE];
    cin.getline(groupName, MAX_LINE);
    return groupName;
}

int Menus::seeActivities() {
    //TODO: Implement using the shocket
}

void Menus::seeGroupActivities() {
    //TODO: Implement using the shocket
}