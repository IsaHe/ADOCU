#include "user.h"
#include "sqlite3.h"

#define MAX_ACTIVITIES 10

#ifndef GROUP_H_
#define GROUP_H_

#define MAX_NAME_ACTIVITY 30

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
  Group** groups;
  int numGroups;
} GroupList;

void createGroup(char* name, int maxUsers, GroupList* groupList, Group* group);
Group* joinGroup(char* name, User user, GroupList* groupList);
void printGroups(GroupList groupList);
void freeGroup(Group* group);
char* menuJoinGroup();
char* menuCreateGroupName();
int menuCreateGroupMaxUsers();
int seeActivities(ActivityList* activityList);
void addActivityToGroup(Activity activity, Group* group);
void updateGroupActivitiesInGroupList(GroupList* groupList, Group* group);
void seeGroupActivities(Group* group);
int readActivitiesInDB(ActivityList* activityList, sqlite3* db);
int insertActivitiesInDB(ActivityList activityList, sqlite3* db);
void deleteActivity(ActivityList* activityList);
void addActivity(ActivityList* activityList, Activity activity);
void addActivityToList(ActivityList *activityList, Activity activity);
char *processActivitiesDB(sqlite3 *db);
ActivityList unJsonifyActivities(char *json);
void addGroupToList(GroupList* groupList, Group* group);
char *jsonifyActivities(ActivityList activityList);
void parseActivity(const char* p, Activity* activity);
ActivityList fromActivityArrayToActivityList(Activity activities[]);
char *jsonifyGroupList(GroupList groupList);

#endif
