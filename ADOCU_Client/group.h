#include "user.h"
#include "activity.h"
#ifndef GROUP_H_
#define GROUP_H_

class Group {
    private:
        char *name;
        User **users;
        int numUsers;
        int maxUsers;
        Activity *activityList;
        int numActivities;
    public:
        Group();
        Group(char *name, User **users, int numUsers, int maxUsers, Activity *activityList, int numActivities);
        Group(const Group &group);
        virtual ~Group();

        char* getName();
        User** getUsers();
        int getNumUsers();
        int getMaxUsers();
        Activity* getActivityList();
        int getNumActivities();
        void setName(char* name);
        void setUsers(User **users);
        void setNumUsers(int numUsers);
        void setMaxUsers(int maxUsers);
        void setActivityList(Activity *activityList);
        void setNumActivities(int numActivities);
        void addUser(User *user);
        void addActivity(Activity activity);
        void showActivities();
        Group& operator=(const Group &group);
};

#endif