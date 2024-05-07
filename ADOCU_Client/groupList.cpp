#include "groupList.h"
#include <string.h>
#include <iostream>

using namespace std;

GroupList::GroupList() {
    groups = NULL;
    size = 0;
    numGroups = 0;
}

GroupList::GroupList(int size) {
    this->groups = new Group*[size];
    this->size = size;
    this->numGroups = 0;
}

GroupList::GroupList(Group **groups, int size, int numGroups) {
    this->groups = groups;
    this->size = size;
    this->numGroups = numGroups;
}

GroupList::GroupList(const GroupList &groupList) {
    groups = groupList.groups;
    size = groupList.size;
    numGroups = groupList.numGroups;
}

GroupList::~GroupList() {}

Group** GroupList::getGroups() {
    return groups;
}

int GroupList::getSize() {
    return size;
}

int GroupList::getNumGroups() {
    return numGroups;
}

void GroupList::setGroups(Group **groups) {
    this->groups = groups;
}

void GroupList::setSize(int size) {
    this->size = size;
}

void GroupList::setNumGroups(int numGroups) {
    this->numGroups = numGroups;
}

void GroupList::addGroup(Group *group) {
    if (numGroups < size) {
        getGroups()[getNumGroups()] = group;
        setNumGroups(getNumGroups() + 1);
    } else {
        cout << "No se pueden añadir más grupos" << endl;
    }
}

int GroupList::findUserInGroup(User *user) {
    for (int i = 0; i < numGroups; i++) {
        for (int j = 0; j < groups[i]->getNumUsers(); j++) {
            if (strcmp(groups[i]->getUsers()[j]->getUsername(), user->getUsername()) == 0) {
                cout << "Si: " << groups[i]->getName() << groups[i]->getUsers()[j]->getName() << endl;
                return 1;
            }
        }
    }
    return 0;
}

void GroupList::createGroup(Group *group) {
    cout << "Crear Grupo" << endl;
    cout << "Introduce el nombre del grupo: ";
    char groupName[30];
    cin >> groupName;
    cin.ignore();
    for (int i = 0; i < getNumGroups(); i++) {
        if (strcmp(getGroups()[i]->getName(), groupName) == 0) {
            cout << "Ya existe un grupo con ese nombre" << endl;
            return;
        }
    }
    cout << "Introduce el número máximo de usuarios: ";
    int maxUsers;
    cin >> maxUsers;
    cin.ignore();
    char *groupNameDynamic = new char[strlen(groupName) + 1]; // Crear un espacio en memoria para que el nombre no sea local.
    strcpy(groupNameDynamic, groupName);
    group->setName(groupNameDynamic);
    group->setUsers(new User*[maxUsers]);
    group->setNumUsers(0);
    group->setMaxUsers(maxUsers);
    group->setActivityList(new Activity[10]);
    group->setNumActivities(0);
    this->addGroup(group);
    cout << "Grupo creado" << endl;
}

void GroupList::joinGroup(User *user) {
    cout << "Unirse a Grupo" << endl;
    cout << "Introduce el nombre del grupo: ";
    char groupName[30];
    cin >> groupName;
    cin.ignore();
    for (int i = 0; i < numGroups; i++) {
        if (strcmp(groups[i]->getName(), groupName) == 0) {
            if (groups[i]->getNumUsers() < groups[i]->getMaxUsers()) {
                groups[i]->addUser(user);
                cout << "Usuario unido al grupo" << endl;
                return;
            } else {
                cout << "El grupo está lleno" << endl;
                return;
            }
        }
    }
    cout << "No se ha podido unir al grupo" << endl;
}

int GroupList::getGroupPositionWithUser(User user) {
    for (int i = 0; i < numGroups; i++) {
        for (int j = 0; j < groups[i]->getNumUsers(); j++) {
            if (strcmp(groups[i]->getUsers()[j]->getUsername(), user.getUsername()) == 0) {
                return i;
            }
        }
    }
    return -1;
}

GroupList& GroupList::operator=(const GroupList &groupList) {
    groups = groupList.groups;
    size = groupList.size;
    numGroups = groupList.numGroups;
    return *this;
}