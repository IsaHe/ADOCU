#include "menus.h"
#include "user.h"
#include "userList.h"
#include "group.h"
#include "groupList.h"
#include "activity.h"
#include "activityList.h"
#include "valoration.h"
#include "valorationList.h"
#include <string.h>
#include <iostream>

using namespace std;

int main() {
    Menus menu;
    char option;
    User *user;
    User user1("Erik", "Erik", "111", 20);
    User user2("Peral", "Peral", "222", 20);
    User user3("Urrutia", "Urrutia", "333", 20);
    User user4("Isaac", "Isaac", "444", 20);
    UserList userList(10);
    userList.addUserToList(&user1);
    userList.addUserToList(&user2);
    userList.addUserToList(&user3);
    userList.addUserToList(&user4);
    Group *group;
    GroupList groupList(10);
    Valoration valoration;
    ValorationList valorationList(10);
    ActivityList activityList;
    Activity a1("Futbol");
    Activity a2("Baloncesto");
    Activity a3("Tenis");
    Activity activities[3] = {a1, a2, a3};
    activityList.setNumActivities(3);
    activityList.setActivityList(activities);

    //Enviar un mensaje de prueba al servidor
    ClientSocket clientSocket(27015);
    const char *message = "Hola servidor";
    int bytesSent = clientSocket.sendData(message);
    if (bytesSent == -1) {
        cout << "Error al enviar el mensaje" << endl;
    } else {
        cout << "Mensaje enviado" << endl;
    }

    do {
        option = menu.mainMenu();
        if (option == '1') {
            user = userList.askForUser();
            if (userList.findUserInList(user) == 1) {
                cout << "¡Bienvenido " << user->getUsername() << "!" << endl;
                if (groupList.findUserInGroup(user) == 0) {
                    do {
                        option = menu.userMenu();
                        if (option == '1') {
                            Group *groupAux = new Group();
                            groupList.createGroup(groupAux);
                        } else if (option == '2') {
                            groupList.joinGroup(user);
                            break;
                        } else if (option == '3') {
                            option = menu.valorationMenu();
                            valoration.setValoration(option);
                            valorationList.addValoration(valoration);
                            cout << "¡Gracias por valorar!" << endl;
                        }
                    } while (option != '4');
                } else {
                    do {
                        group = groupList.getGroups()[groupList.getGroupPositionWithUser(*user)];
                        option = menu.groupMenu();
                        if (option == '1') {
                            activityList.seeActivities();
                            group->addActivity(activityList);
                        } else if (option == '2') {
                            group->showActivities();
                        }
                    } while (option != '3');
                }
            } else {
                cout << "Usuario o contraseña incorrectos" << endl;
            }
        } else if (option == '2') {
            User *userAux = new User();
            menu.registerMenu(&userList, userAux);
        }
    } while (option != '0');

    cout << "¡Gracias por usar ADOCU!" << endl;

    return 0;
}