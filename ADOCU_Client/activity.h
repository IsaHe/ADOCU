#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#define MAX_ACTIVITIES 10

class Activity {
    private:
        char name[30];
    public:
        Activity();
        Activity(char *name);
        Activity(const Activity &activity);
        virtual ~Activity();

        char* getName();
        void setName(char* name);
};

#endif