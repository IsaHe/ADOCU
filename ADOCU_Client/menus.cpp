#include "menus.h"
#include <iostream>

using namespace std;

Menus::Menus() {}

char Menus::mainMenu() {
    cout << "1. Iniciar Sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << "Introduce opcion: ";
    char option;
    cin >> option;
    cin.ignore(); // Se descarta el salto de línea
    return option;
}

char Menus::userMenu() {
    cout << "1. Crear Grupo" << endl;
    cout << "2. Unirse a Grupo" << endl;
    cout << "3. Valorar Aplicacion" << endl;
    cout << "4. Volver" << endl;
    cout << "Introduce opción: ";
    char option;
    cin >> option;
    cin.ignore(); // Se descarta el salto de línea
    return option;
}

char Menus::valorationMenu() {
    cout << "Valorar Aplicacion" << endl;
    cout << "1. MUY MAL" << endl;
    cout << "2. MAL" << endl;
    cout << "3. REGULAR" << endl;
    cout << "4. BIEN" << endl;
    cout << "5. MUY BIEN" << endl;
    cout << "0. Volver" << endl;
    cout << "Introduce opción: ";
    char option;
    cin >> option;
    cin.ignore(); // Se descarta el salto de línea
    return option;
}

char Menus::groupMenu() {
    cout << "1. Añadir Actividad" << endl;
    cout << "2. Ver Actividades" << endl;
    cout << "3. Volver" << endl;
    cout << "Introduce opción: ";
    char option;
    cin >> option;
    cin.ignore(); // Se descarta el salto de línea
    return option;
}

void Menus::registerMenu(UserList *userList, User *user) {
    cout << "Introduce tu nombre de usuario: ";
    char username[20];
    cin.getline(username, 20);
    cout << "Introduce tu contraseña: ";
    char password[20];
    cin.getline(password, 20);
    cout << "Introduce tu edad: ";
    int age;
    cin >> age;
    cin.ignore(); // Se descarta el salto de línea
    user->setName(username);
    user->setUsername(username);
    user->setPassword(password);
    user->setAge(age);
    userList->addUserToList(user);
    cout << "¡Usuario registrado con éxito!" << endl;
}