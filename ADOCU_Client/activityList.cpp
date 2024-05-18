#include "activityList.h"
#include <iostream>
#include <string.h>

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

char *ActivityList::jsonifyActivityList(ActivityList activityList) {
    char *json = new char[1000];
    strcpy(json, "[");
    for (int i = 0; i < activityList.numActivities; i++) {
        strcat(json, "{");
        strcat(json, "\"name\": \"");
        strcat(json, activityList.activityList[i].getName());
        strcat(json, "\"");
        strcat(json, "}");
        if (i < activityList.numActivities - 1) {
            strcat(json, ",");
        }
    }
    strcat(json, "]");
    strcat(json, "\0");
    return json;

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

void parseActivity(char *json, Activity *activity) {
    while (*json != '}') {
        if (strncmp(json, "\"name\": \"", 9) == 0) {
            activity->setName(parseName(json));
        }
        json++;
    }
}

ActivityList ActivityList::unjsonifyActivityList(char *json, int* numCicles) {
    char *jsonPtr = json;
    while (*jsonPtr && *jsonPtr != ']') {
        if (*jsonPtr == '{') {
            Activity activity;
            parseActivity(jsonPtr, &activity);
            addActivity(activity);
        }
        jsonPtr++;
        (*numCicles)++;
    }
    return *this;
}

void ActivityList::addActivity(const Activity& activity) {
    activityList[numActivities] = activity;
    numActivities++;
}

Activity* ActivityList::getActivityList() {
    return activityList;
}
