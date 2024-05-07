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
    this->users = new User[size];
    this->size = size;
    this->numUsers = 0;
}

UserList::UserList(User *users, int numUsers, int size) {
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

User* UserList::getUsers() {
    return users;
}

int UserList::getNumUsers() {
    return numUsers;
}

int UserList::getSize() {
    return size;
}

void UserList::setUsers(User *users) {
    this->users = users;
}

void UserList::setNumUsers(int numUsers) {
    this->numUsers = numUsers;
}

void UserList::setSize(int size) {
    this->size = size;
}

User UserList::askForUser() {
    User user;
    cout << "Introduce el usuario: ";
    cin.getline(user.getUsername(), MAX_LINE);
    cout << "Introduce la contraseña: ";
    cin.getline(user.getPassword(), MAX_LINE);
    for (int i = 0; i < this->getNumUsers(); i++) {
        if (strcmp(user.getUsername(), this->getUsers()[i].getUsername()) == 0 && strcmp(user.getPassword(), this->getUsers()[i].getPassword()) == 0) {
            return this->getUsers()[i];
        }
    }
    return User();
}

int UserList::findUserInList(User user) {
    for (int i = 0; i < this->getNumUsers(); i++) {
        if (strcmp(user.getUsername(), this->getUsers()[i].getUsername()) == 0 && strcmp(user.getPassword(), this->getUsers()[i].getPassword()) == 0) {
            return 1;
        }
    }
    return 0;
}

void UserList::addUserToList(User *user) {
    if (numUsers < size) {
        users[numUsers] = *user;
        numUsers++;
    } else {
        cout << "No se pueden añadir más usuarios" << endl;
    }
}