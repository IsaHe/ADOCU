#include "user.h"
#include <string.h>
#include <iostream>

using namespace std;

User::User() {
    strcpy(name, "");
    strcpy(username, "");
    strcpy(password, "");
    age = 0;
};

User::User(char *name, char *username, char *password, int age) {
    strcpy(this->name, name);
    strcpy(this->username, username);
    strcpy(this->password, password);
    this->age = age;
}

User::User(const User &user) {
    strcpy(this->name, user.name);
    strcpy(this->username, user.username);
    strcpy(this->password, user.password);
    this->age = user.age;
}

User::~User() {};

char* User::getName() {
    return name;
}

char* User::getUsername() {
    return username;
}

char* User::getPassword() {
    return password;
}

int User::getAge() {
    return age;
}

void User::setName(char* name) {
    strcpy(this->name, name);
}

void User::setUsername(char* username) {
    strcpy(this->username, username);
}

void User::setPassword(char* password) {
    strcpy(this->password, password);
}

void User::setAge(int age) {
    this->age = age;
}

User& User::operator=(const User &user) {
    strcpy(this->name, user.name);
    strcpy(this->username, user.username);
    strcpy(this->password, user.password);
    this->age = user.age;
    return *this;
}

User* User::unJsonifyUser(char *json) {
    User* user = new User();
    char *token = strtok(json, ",");
    while (token != NULL) {
        char *key = strtok(token, ":");
        char *value = strtok(NULL, ":");
        if (strcmp(key, "\"name\"") == 0) {
            value = strtok(value, "\"");
            value = strtok(NULL, "\"");
            user->setName(value);
        } else if (strcmp(key, "\"username\"") == 0) {
            value = strtok(value, "\"");
            value = strtok(NULL, "\"");
            user->setUsername(value);
        } else if (strcmp(key, "\"password\"") == 0) {
            value = strtok(value, "\"");
            value = strtok(NULL, "\"");
            user->setPassword(value);
        } else if (strcmp(key, "\"age\"") == 0) {
            value = strtok(value, "\"");
            value = strtok(NULL, "\"");
            user->setAge(atoi(value));
        }
        token = strtok(NULL, ",");
    }
    return user;
}