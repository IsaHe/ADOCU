#include "activity.h"
#include <string.h>
#include <iostream>

using namespace std;

Activity::Activity() {
    strcpy(name, "");
}

Activity::Activity(char *name) {
    strcpy(this->name, name);
}

Activity::Activity(const Activity &activity) {
    strcpy(name, activity.name);
}

Activity::~Activity() {
}

char* Activity::getName() {
    return name;
}

void Activity::setName(char* name) {
    strcpy(this->name, name);
}

Activity& Activity::operator=(const Activity &activity) {
    strcpy(name, activity.name);
    return *this;
}

char *Activity::jsonifyActivity(char *groupname) {
    char *json = new char[100];
    strcpy(json, "\"activity\": \"");
    strcat(json, groupname);
    strcat(json, "\"{");
    strcat(json, "\"name\": \"");
    strcat(json, name);
    strcat(json, "\"");
    strcat(json, "}");
    return json;
}
