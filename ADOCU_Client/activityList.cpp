#include "activityList.h"
#include <iostream>

using namespace std;

ActivityList::ActivityList() {
    activityList = new Activity[10];
    numActivities = 0;
}

ActivityList::ActivityList(Activity *ativityList, int numActividades) {
    this->activityList = activityList;
    this->numActivities = numActivities;
}

ActivityList::ActivityList(const ActivityList &activityList) {
    this->activityList = activityList.activityList;
    this->numActivities = activityList.numActivities;
}

ActivityList::~ActivityList() {
    delete[] activityList;
}

Activity ActivityList::getActivity(int position) {
    return activityList[position];
}

int ActivityList::getNumActivities() {
    return numActivities;
}

void ActivityList::setActivityList(Activity *activityList) {
    this->activityList = activityList;
}

void ActivityList::setNumActivities(int numActivities) {
    this->numActivities = numActivities;
}

void ActivityList::seeActivities() {
    for (int i = 0; i < numActivities; i++) {
        cout << i + 1 << ". " << activityList[i].getName() << endl;
    }
}