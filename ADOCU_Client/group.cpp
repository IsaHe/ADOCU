#include "group.h"
#include "groupList.h"
#include "activity.h"
#include "user.h"
#include <string.h>
#include <iostream>

using namespace std;

Group::Group() {
    strcpy(name, "");
    users = NULL;
    numUsers = 0;
    maxUsers = 0;
    numActivities = 0;
}

Group::Group(char *name, User **users, int numUsers, int maxUsers, Activity *activityList, int numActivities) {
    strcpy(this->name, name);
    this->users = users;
    this->numUsers = numUsers;
    this->maxUsers = maxUsers;
    for (int i = 0; i < 10; i++) {
        this->activityList[i] = activityList[i];
    }
    this->numActivities = numActivities;
}

Group::Group(const Group &group) {
    strcpy(name, group.name);
    users = group.users;
    numUsers = group.numUsers;
    maxUsers = group.maxUsers;
    for (int i = 0; i < 10; i++) {
        activityList[i] = group.activityList[i];
    }
    numActivities = group.numActivities;
}

Group::~Group() {
    delete[] users;
}

char* Group::getName() {
    return name;
}

User** Group::getUsers() {
    return users;
}

int Group::getNumUsers() {
    return numUsers;
}

int Group::getMaxUsers() {
    return maxUsers;
}

Activity* Group::getActivityList() {
    return activityList;
}

int Group::getNumActivities() {
    return numActivities;
}

void Group::setName(char* name) {
    strcpy(this->name, name);
}

void Group::setUsers(User **users) {
    if (this->users != NULL) {
        delete[] this->users;
    }

    this->users = new User *[this->numUsers];

    for (int i = 0; i < this->numUsers; i++) {
        this->users[i] = new User(*users[i]);
    }
}

void Group::setNumUsers(int numUsers) {
    this->numUsers = numUsers;
}

void Group::setMaxUsers(int maxUsers) {
    this->maxUsers = maxUsers;
}

void Group::setActivityList(Activity *activityList) {
    for (int i = 0; i < 10; i++) {
        this->activityList[i] = activityList[i];
    }
}

void Group::setNumActivities(int numActivities) {
    this->numActivities = numActivities;
}

void Group::addUser(User *user) {
    users[numUsers] = user;
    numUsers++;
}

Activity Group::addActivity(ActivityList activityList2) {
    cout << "Introce el número de la actividad: ";
    int option;
    cin >> option;
    cin.ignore();
    getActivityList()[getNumActivities()] = activityList2.getActivity(option - 1);
    setNumActivities(getNumActivities() + 1);
    cout << "Actividad añadida" << endl;
    return getActivityList()[getNumActivities() - 1];
}

void Group::showActivities() {
    cout << "Actividades " << "(" << getNumActivities() << "):" << endl;
    for (int i = 0; i < getNumActivities(); i++) {
        cout << getActivityList()[i].getName() << endl;
    }
}

Group& Group::operator=(const Group &group) {
    strcpy(name, group.name);
    users = group.users;
    numUsers = group.numUsers;
    maxUsers = group.maxUsers;
    for (int i = 0; i < 10; i++) {
        activityList[i] = group.activityList[i];
    }
    numActivities = group.numActivities;
    return *this;
}

char *Group::jsonifyGroup() {
    std::string jsonString = "\"group\"{";
    jsonString += "\"name\": \"" + std::string(name) + "\",";
    jsonString += "\"numUsers\": " + std::to_string(numUsers) + ",";
    jsonString += "\"maxUsers\": " + std::to_string(maxUsers) + ",";
    jsonString += "\"numActivities\": " + std::to_string(numActivities);

    jsonString += "}";

    char *cstr = new char[jsonString.length() + 1];
    strcpy(cstr, jsonString.c_str());

    return cstr;
}
