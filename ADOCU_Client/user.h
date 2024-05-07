#ifndef USER_H_
#define USER_H_

class User {
    private:
        char name[20];
	    char username[20];
	    char password[20];
	    int age;
    public:
        User();
        User(char *name, char *username, char *password, int age);
        User(const User &user);
        virtual ~User();

        char* getName();
        char* getUsername();
        char* getPassword();
        int getAge();
        void setName(char* name);
        void setUsername(char* username);
        void setPassword(char* password);
        void setAge(int age);
        User& operator=(const User &user);
};

#endif