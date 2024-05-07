#include "group.h"
#ifndef GROUPLIST_H_
#define GROUPLIST_H_

class GroupList {
    private:
        Group** groups;
        int size;
        int numGroups;
    public:
        GroupList();
        GroupList(int size);
        GroupList(Group **groups, int size, int numGroups);
        GroupList(const GroupList &groupList);
        virtual ~GroupList();

        Group** getGroups();
        int getSize();
        int getNumGroups();
        void setGroups(Group **groups);
        void setSize(int size);
        void setNumGroups(int numGroups);
        void addGroup(Group *group);
        int findUserInGroup(User user);
        void createGroup(Group *group);
        void joinGroup(User *user);
        int getGroupPositionWithUser(User user);
};

#endif