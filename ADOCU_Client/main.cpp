#include "menus.h"
#include "user.h"
#include "userList.h"
#include "group.h"
#include "groupList.h"
#include "activity.h"
#include "activityList.h"
#include "valoration.h"
#include "valorationList.h"
#include <iostream>
#include "clientSocket.h"

using namespace std;

int main() {
    Menus menu;
    char option;
    User *user;
    UserList userList(100);
    Group *group;
    GroupList groupList(100);
    Valoration valoration;
    ValorationList valorationList(10);
    ActivityList activityList;

    //Enviar un mensaje de prueba al servidor
    ClientSocket clientSocket(27015);
    const char *message = "Hola"; //Pedir al servidor que envie todos los datos de la bd
    int bytesSent = clientSocket.sendData(message);
    if (bytesSent == -1) {
        cout << "Error al enviar el mensaje" << endl;
    } else {
        cout << "Mensaje enviado" << endl;
        char recvbuf[512];
        clientSocket.receiveData(recvbuf, 512);
        groupList = groupList.unJsonifyGroupList(recvbuf);
        for (int i = 0; i < groupList.getNumGroups(); i++) {
            cout << "Grupo Recivido: " << groupList.getGroups()[i]->getName() << endl;
            for (int j = 0; j < groupList.getGroups()[i]->getNumUsers(); j++) {
                userList.addUserToList(groupList.getGroups()[i]->getUsers()[j]);
                cout << "Usuario Recivido: " << groupList.getGroups()[i]->getUsers()[j]->getName() << endl;
            }
            for (int j = 0; j < groupList.getGroups()[i]->getNumActivities(); j++) {
                activityList.addActivity(groupList.getGroups()[i]->getActivityList()[j]);
                cout << "Actividad Recivida: " << groupList.getGroups()[i]->getActivityList()[j].getName() << endl;
            }
        }
        cout << "Grupos Recividos: " << groupList.getNumGroups() << endl;
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
                            clientSocket.sendGroup(groupAux);
                        } else if (option == '2') {
                            groupList.joinGroup(user);
                            clientSocket.sendGroup(groupList.getGroups()[groupList.getGroupPositionWithUser(*user)]);
                            clientSocket.sendUser(user,
                                                  groupList.getGroups()[groupList.getGroupPositionWithUser(*user)]);
                            break;
                        } else if (option == '3') {
                            option = menu.valorationMenu();
                            valoration.setValoration(option);
                            valorationList.addValoration(valoration);
                            clientSocket.sendValoration(&valoration);
                            cout << "¡Gracias por valorar!" << endl;
                        }
                    } while (option != '4');
                } else {
                    do {
                        group = groupList.getGroups()[groupList.getGroupPositionWithUser(*user)];
                        option = menu.groupMenu();
                        if (option == '1') {
                            activityList.seeActivities();
                            Activity activity = group->addActivity(activityList);
                            clientSocket.sendActivity(&activity, group);
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
            clientSocket.sendNewUser(userAux);
        }
    } while (option != '0');

    cout << "¡Gracias por usar ADOCU!" << endl;

    return 0;
}
