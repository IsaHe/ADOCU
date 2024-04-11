#include "user.h"

#define MAX_ACTIVITIES 10

#ifndef GROUP_H_
#define GROUP_H_

typedef struct {
  char name[30];
} Activity;

typedef struct {
    Activity activityList[MAX_ACTIVITIES];
    int numActivities;
} ActivityList;

typedef struct {
  char* name;
  User* users;
  int numUsers;
  int maxUsers;
  Activity activityList[MAX_ACTIVITIES];
  int numActivities;
} Group;

typedef struct {
  Group* groups;
  int numGroups;
} GroupList;

void createGroup(char* name, int maxUsers, GroupList* groupList);
void joinGroup(char* name, User user, GroupList* groupList);
void printGroups(GroupList groupList);
void freeGroup(Group* group);
char* menuJoinGroup();
char* menuCreateGroupName();
int menuCreateGroupMaxUsers();
int seeActivities(ActivityList* activityList);
void addActivityToGroup(Activity activity, Group* group);
void seeGroupActivities(Group* group);
void initActivities(ActivityList* activityList);
void deleteActivity(ActivityList* activityList);
void addActivity(ActivityList* activityList, Activity activity);

#endif
