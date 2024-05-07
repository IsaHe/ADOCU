#include "activity.h"
#ifndef ACTIVITYLIST_H_
#define ACTIVITYLIST_H_

class ActivityList {
    private:
        Activity activityList[10];
        int numActivities;
    public:
        ActivityList();
        ActivityList(Activity *ativityList, int numActividades);
        ActivityList(const ActivityList &activityList);
        virtual ~ActivityList();

        Activity getActivity(int position);
        int getNumActivities();
        void setActivityList(Activity *activityList);
        void setNumActivities(int numActivities);
        void seeActivities();
};

#endif