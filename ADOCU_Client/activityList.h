#include "activity.h"
#ifndef ACTIVITYLIST_H_
#define ACTIVITYLIST_H_

class ActivityList {
    private:
        Activity activityList[MAX_ACTIVITIES];
        int numActivities;
    public:
        ActivityList();
        ActivityList(const ActivityList &activityList);
        ActivityList(Activity *ativityList, int numActividades);
        virtual ~ActivityList();
};

#endif