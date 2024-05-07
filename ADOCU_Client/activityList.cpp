#include "activityList.h"
#include <iostream>

using namespace std;

ActivityList::ActivityList() {
    numActivities = 0;
}

ActivityList::ActivityList(Activity *ativityList, int numActividades) {
    for (int i = 0; i < numActividades; i++) {
        activityList[i] = ativityList[i];
    }
    this->numActivities = numActivities;
}

ActivityList::ActivityList(const ActivityList &activityList) {
    for (int i = 0; i < activityList.numActivities; i++) {
        this->activityList[i] = activityList.activityList[i];
    }
    this->numActivities = activityList.numActivities;
}

ActivityList::~ActivityList() {
}

Activity ActivityList::getActivity(int position) {
    return activityList[position];
}

int ActivityList::getNumActivities() {
    return numActivities;
}

void ActivityList::setActivityList(Activity *activityList) {
    for (int i = 0; i < numActivities; i++) {
        this->activityList[i] = activityList[i];
    }
}

void ActivityList::setNumActivities(int numActivities) {
    this->numActivities = numActivities;
}

void ActivityList::seeActivities() {
    for (int i = 0; i < numActivities; i++) {
        cout << i + 1 << ". " << activityList[i].getName() << endl;
    }
}