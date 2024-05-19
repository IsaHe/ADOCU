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

char *User::jsonifyUser(char *group) {
    std::string json = "\"user\": \"";
    json += std::string(group) + "\"{";
    json += "\"name\": \"" + std::string(name) + "\",";
    json += "\"username\": \"" + std::string(username) + "\",";
    json += "\"password\": \"" + std::string(password) + "\",";
    json += "\"age \": " + std::to_string(age) + ",";
    json += "\"admin\": \"U\"";
    json += "}";
    char *cstr = new char[json.length() + 1];
    strcpy(cstr, json.c_str());
    return cstr;
}

char *User::jsonifyNewUser() {
    std::string json = "\"userNew\"{";
    json += "\"name\": \"" + std::string(name) + "\",";
    json += "\"username\": \"" + std::string(username) + "\",";
    json += "\"password\": \"" + std::string(password) + "\",";
    json += "\"age \": " + std::to_string(age) + ",";
    json += "\"admin\": \"U\"";
    json += "}";
    char *cstr = new char[json.length() + 1];
    strcpy(cstr, json.c_str());
    return cstr;
}
