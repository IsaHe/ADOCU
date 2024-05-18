#include "groupList.h"
#include "userList.h"
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

char *parseName(char *json) {
    json += 9;
    char *name = new char[30];
    char *namePtr = name;
    while (*json != '\"') {
        *namePtr++ = *json++;
    }
    *namePtr = '\0';
    return name;
}

void parseGroup(char *json, Group *group, int* numCiclesAux) {
    int numCicles = 0;
    while (*json != '}' && *json) {
        if (strncmp(json, "\"name\": \"", 9) == 0) {
            group->setName(parseName(json));
        } else if (strncmp(json, "\"users\": ", 8) == 0) {
            numCicles = 0;
            UserList userList = UserList::unJsonifyUserList(json, &numCicles);
            json+=numCicles;
            (*numCiclesAux) += numCicles;
            group->setNumUsers(userList.getNumUsers());
            group->setUsers(userList.getUsers());
        } else if (strncmp(json, "\"activities\": ", 14) == 0) {
            numCicles = 0;
            ActivityList activityList;
            activityList = activityList.unjsonifyActivityList(json, &numCicles);
            json+=numCicles;
            (*numCiclesAux) += numCicles;
            group->setNumActivities(activityList.getNumActivities());
            group->setActivityList(activityList.getActivityList());
        }
        json++;
        (*numCiclesAux)++;
    }
}

GroupList GroupList::unJsonifyGroupList(char *json) {
    int maxGroups = 100;
    groups = new Group*[maxGroups];
    numGroups = 0;
    int numCicles = 0;
    char *jsonAux = json;
    while (*jsonAux) {
        if (*jsonAux == '{') {
            Group* group = new Group();
            numCicles = 0;
            parseGroup(jsonAux, group, &numCicles);
            jsonAux+=numCicles;
            addNewGroup(group);
        }
        jsonAux++;
    }
    return *this;
}

void GroupList::addNewGroup(Group *group) {
    if (numGroups < size) {
        groups[numGroups] = group;
        numGroups++;
    } else {
        cout << "No se pueden añadir más grupos" << endl;
    }

}
