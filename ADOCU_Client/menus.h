#include "activityList.h"
#include "activity.h"

#ifndef MENUS_H_
#define MENUS_H_

class Menus {
    public:
        Menus();

        char mainMenu();
        char userMenu();
        char valorationMenu();
        char groupMenu();
};

#endif
