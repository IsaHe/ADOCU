#include "user.h"
#include "activity.h"
#ifndef GROUP_H_
#define GROUP_H_

class Group {
    private:
        char* name;
        User* users;
        int numUsers;
        int maxUsers;
        Activity activityList[MAX_ACTIVITIES];
        int numActivities;
    public:
        Group();
        Group(const Group &group);
        Group(char *name, User *users, int numUsers, int masUsers, Activity *activityList, int numActivities);
        virtual ~Group();
};

#endif