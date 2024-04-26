
#include "menus.h"
Menus menu;

int main() {
    char option;
    char* name;
    char* userData;
    do {
        option = menu.mainMenu();
        switch (option) {
            case '1':
                option = menu.menuLogIn();
                switch (option) {
                    case '1':
                        name = menu.menuCreateGroupName();
                        // Crear grpo
                        break;
                    case '2':
                        name = menu.menuJoinGroup();
                        // Unirse a grupo
                        break;
                    case '3':
                        option = menu.menuValoration();
                        switch (option) {
                            case '1':
                                // Valoracion muy mala
                                break;
                            case '2':
                                // Valoracion mala
                                break;
                            case '3':
                                // Valoracion regular
                                break;
                            case '4':
                                // Valoracion bien
                                break;
                            case '5':
                                // Valoracion muy bien
                                break;
                            case '0':
                                // Volver
                                break;
                            default:
                                cout << "Opcion no valida" << endl;
                                break;
                        }
                        break;
                    case '4':
                        // Volver
                        break;
                    default:
                        cout << "Opcion no valida" << endl;
                        break;
                }
                break;
            case '2':
                char* userData = menu.menuRegistro();
                break;
            case '0':
                // Salir
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    } while (option != '0');
    return 0;
}