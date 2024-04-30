#ifndef USER_H_
#define USER_H_

class User {
    private:
        char name[20];
	    char username[20];
	    char password[20];
	    int age;
	    char admin;
    public:
        User();
        User(char *name, char *username, char *password, int age, char * admin);
        User(const User &user);
        virtual ~User();
};

#endif