//
// Created by Isaac Herbozo on 26/4/24.
//

#ifndef ADOCU_MENUS_H
#define ADOCU_MENUS_H

#include <iostream>
using namespace std;

class Menus {
public:
    Menus();
    static char mainMenu();
    static char menuValoration();
    static char menuAdmin();
    static char menuLogIn();
    static char menuActivity();
    static char* menuCreateGroupName();
    static char* menuJoinGroup();
    static int menuCreateGroupMaxUsers();
    static int seeActivities();
    static void seeGroupActivities();
    static char menuRegistro();
};

#endif //ADOCU_MENUS_H
