#include "group.h"
#include "groupList.h"
#include "activity.h"
#include "user.h"
#include <string.h>
#include <iostream>

using namespace std;

Group::Group() {
    name = NULL;
    users = NULL;
    numUsers = 0;
    maxUsers = 0;
    activityList = NULL;
    numActivities = 0;
}

Group::Group(char *name, User **users, int numUsers, int maxUsers, Activity *activityList, int numActivities) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->users = users;
    this->numUsers = numUsers;
    this->maxUsers = maxUsers;
    this->activityList = activityList;
    this->numActivities = numActivities;
}

Group::Group(const Group &group) {
    name = new char[strlen(group.name) + 1];
    strcpy(name, group.name);
    users = group.users;
    numUsers = group.numUsers;
    maxUsers = group.maxUsers;
    activityList = group.activityList;
    numActivities = group.numActivities;
}

Group::~Group() {
    delete[] name;
    delete[] users;
    delete[] activityList;
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
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Group::setUsers(User **users) {
    this->users = users;
}

void Group::setNumUsers(int numUsers) {
    this->numUsers = numUsers;
}

void Group::setMaxUsers(int maxUsers) {
    this->maxUsers = maxUsers;
}

void Group::setActivityList(Activity *activityList) {
    this->activityList = activityList;
}

void Group::setNumActivities(int numActivities) {
    this->numActivities = numActivities;
}

void Group::addUser(User *user) {
    users[numUsers] = user;
    numUsers++;
}

void Group::addActivity(Activity activity) {
    activityList[numActivities] = activity;
    numActivities++;
}

void Group::showActivities() {
    for (int i = 0; i < numActivities; i++) {
        cout << activityList[i].getName() << endl;
    }
}

Group& Group::operator=(const Group &group) {
    delete[] name;
    name = new char[strlen(group.name) + 1];
    strcpy(name, group.name);
    users = group.users;
    numUsers = group.numUsers;
    maxUsers = group.maxUsers;
    activityList = group.activityList;
    numActivities = group.numActivities;
    return *this;
}