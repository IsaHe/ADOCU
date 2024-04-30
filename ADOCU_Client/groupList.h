#include "group.h"
#ifndef GROUPLIST_H_
#define GROUPLIST_H_

class GroupList {
    private:
        Group** groups;
        int numGroups;
    public:
        GroupList();
        GroupList(const GroupList &groupList);
        GroupList(Group **groups, int numGroups);
        virtual ~GroupList();
};

#endif