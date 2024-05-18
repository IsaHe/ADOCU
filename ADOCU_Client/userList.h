#ifndef USERLIST_H_
#define USERLIST_H_

#include "user.h"
#include "groupList.h"

class UserList {
    private:
        User **users;
        int numUsers;
        int size;
    public:
        UserList();
        UserList(int size);
        UserList(User **users, int numUsers, int size);
        UserList(const UserList &userList);
        virtual ~UserList();

        User** getUsers();
        int getNumUsers() const;
        int getSize() const;
        void setUsers(User **users);
        void setNumUsers(int numUsers);
        void setSize(int size);
        User* askForUser();
        int findUserInList(User *user);
        void addUserToList(User *user);
        UserList& operator=(const UserList &userList);
        static UserList unJsonifyUserList(const char *json, int *numCicles);
};

#endif