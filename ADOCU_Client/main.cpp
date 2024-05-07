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
    UserList userList(10);
    userList.addUserToList(&user1);
    userList.addUserToList(&user2);
    userList.addUserToList(&user3);
    Group *group;
    // Group group1("Hola", new User*[10], 0, 10, new Activity[10], 0);
    // group1.addUser(&user1);
    GroupList groupList(10);
    // groupList.addGroup(&group1);
    Valoration valoration;
    ValorationList valorationList(10);
    ActivityList activityList;
    Activity a1("Futbol");
    Activity a2("Baloncesto");
    Activity a3("Tenis");
    Activity activities[3] = {a1, a2, a3};
    activityList.setNumActivities(3);
    activityList.setActivityList(activities);

    do {
        // El problema es que cuando se crean los grupos, se crean con la misma direccion de memoria porque se pasa la direccion de memoria de la variable group que está definida arriba y nunca cambia. Por eso, cuando se añade un usuario a un grupo, se añade a todos los grupos. La solucion es crear un nuevo grupo cada vez que se crea un grupo.
        option = menu.mainMenu();
        cout << groupList.getNumGroups() << endl;
        for (int i = 0; i < groupList.getNumGroups(); i++) {
            cout << groupList.getGroups()[i]->getName() << endl;
        }
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
                        cout << group->getNumActivities() << endl;
                        cout << "¡Bienvenido al grupo " << group->getName() << "!" << endl;
                        cout << groupList.getGroupPositionWithUser(*user) << endl;
                        option = menu.groupMenu();
                        if (option == '1') {
                            activityList.seeActivities();
                            group->addActivity(activityList);
                            group->showActivities();
                        } else if (option == '2') {
                            group->showActivities();
                        }
                    } while (option != '3');
                }
            } else {
                cout << "Usuario o contraseña incorrectos" << endl;
            }
        } else if (option == '2') {
            cout << "Registrarse" << endl;
        }
    } while (option != '0');

    cout << "¡Gracias por usar ADOCU!" << endl;

    return 0;
}