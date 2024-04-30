#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#define MAX_ACTIVITIES 10

class Activity {
    private:
        char name[30];
    public:
        Activity();
        Activity(const Activity &activity);
        Activity(char *name);
        virtual ~Activity();
};

#endif