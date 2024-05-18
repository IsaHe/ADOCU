#include "userList.h"
#include <iostream>
#include <string.h>

#define MAX_LINE 100

using namespace std;

UserList::UserList() {
    users = NULL;
    numUsers = 0;
    size = 0;
}

UserList::UserList(int size) {
    this->users = new User*[size];
    this->size = size;
    this->numUsers = 0;
}

UserList::UserList(User **users, int numUsers, int size) {
    this->users = users;
    this->numUsers = numUsers;
    this->size = size;
}

UserList::UserList(const UserList &userList) {
    users = userList.users;
    numUsers = userList.numUsers;
    size = userList.size;
}

UserList::~UserList() {
    delete[] users;
}

User** UserList::getUsers() {
    return users;
}

int UserList::getNumUsers() const {
    return numUsers;
}

int UserList::getSize() const {
    return size;
}

void UserList::setUsers(User **users) {
    this->users = users;
}

void UserList::setNumUsers(int numUsers) {
    this->numUsers = numUsers;
}

void UserList::setSize(int size) {
    this->size = size;
}

User* UserList::askForUser() {
    User user;
    cout << "Introduce el usuario: ";
    cin.getline(user.getUsername(), MAX_LINE);
    cout << "Introduce la contraseña: ";
    cin.getline(user.getPassword(), MAX_LINE);
    for (int i = 0; i < this->getNumUsers(); i++) {
        if (strcmp(user.getUsername(), this->getUsers()[i]->getUsername()) == 0 && strcmp(user.getPassword(), this->getUsers()[i]->getPassword()) == 0) {
            return this->getUsers()[i];
        }
    }
    cout << "Usuario no encontrado" << endl;
    User *noUser = new User();
    return noUser;
}

int UserList::findUserInList(User *user) {
    for (int i = 0; i < this->getNumUsers(); i++) {
        if (strcmp(user->getUsername(), this->getUsers()[i]->getUsername()) == 0 && strcmp(user->getPassword(), this->getUsers()[i]->getPassword()) == 0) {
            return 1;
        }
    }
    return 0;
}

void UserList::addUserToList(User *user) {
    if (numUsers < size) {
        users[numUsers] = user;
        numUsers++;
    } else {
        cout << "No se pueden añadir más usuarios" << endl;
    }
}

UserList& UserList::operator=(const UserList &userList) {
    users = userList.users;
    numUsers = userList.numUsers;
    size = userList.size;
    return *this;
}

#define MAX_NAME_LENGTH 100
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

char* parseAttribute(const char* p, int skip, int max_length) {
    p += skip;
    char* attribute = new char[max_length];
    char* attributePtr = attribute;
    while (*p != '\"') {
        *attributePtr++ = *p++;
    }
    *attributePtr = '\0';
    return attribute;
}

int parseAge(const char* p) {
    p += 7; // Saltar "\"age\": "
    int age = 0;
    while (*p != ',') {
        age = age * 10 + (*p++ - '0');
    }
    return age;
}

char parseAdmin(const char* p) {
    p += 10; // Saltar "\"admin\": \""
    return *p;
}

void parseUser(const char* p, User* user) {
    while (*p != '}') {
        if (strncmp(p, "\"name\": \"", 9) == 0) {
            user->setName(parseAttribute(p, 9, MAX_NAME_LENGTH));
        } else if (strncmp(p, "\"username\": \"", 13) == 0) {
            user->setUsername(parseAttribute(p, 13, MAX_USERNAME_LENGTH));
        } else if (strncmp(p, "\"password\": \"", 13) == 0) {
            user->setPassword(parseAttribute(p, 13, MAX_PASSWORD_LENGTH));
        } else if (strncmp(p, "\"age\": ", 7) == 0) {
            user->setAge(parseAge(p));
        } else if (strncmp(p, "\"admin\": \"", 10) == 0) {
            p++; // Saltar el caracter de admin
        }
        p++;
    }
}

UserList UserList::unJsonifyUserList(const char* jsonString, int* numCicles) {
    UserList userList = UserList(100);
    const char* p = jsonString;
    while (*p != ']') {
        if (*p == '{') {
            User* user = new User();
            parseUser(p, user);
            userList.addUserToList(user);
        }
        p++;
        (*numCicles)++;
    }
    return userList;
}