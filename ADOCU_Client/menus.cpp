#include "menus.h"
#include <iostream>

using namespace std;

Menus::Menus() {}

char Menus::mainMenu() {
    cout << "1. Iniciar Sesión" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << "Introduce opción: ";
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
