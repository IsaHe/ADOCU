#include "sqlite3.h"

#ifndef USER_H_
#define USER_H_

#define MAX_NAME 20
#define MAX_USERNAME 20
#define MAX_PASSWORD 20

typedef struct {
	char name[20];
	char username[20];
	char password[20];
	int age;
	char admin;
} User;

typedef struct {
	User* userList;
	int size;
	int numUsers;
} UserList;

void clearIfNeeded(char* str, int maxLine);
User askForUser(UserList userList);
User userToIntroduce();
int readUsersFromDB(UserList* userList, sqlite3* db);
int deleteDB(sqlite3* db, char* table);
int insertUsersInDB(UserList userList, sqlite3* db);
void seeUserList(UserList userList);
int findUserInList(UserList userList, User user, char* adminUsername, char* adminPassword);
void addUserToList(UserList* userList, User user);
int findUserInListRegister(UserList userList, User user);
int userToRemove(UserList userList);
void deleteUserWithPosition(UserList* userList, int position);
char* jsonifyUserList(UserList userList);
char* processUserDB(sqlite3* db);
UserList unJsonifyUserList(const char* json);
void parseUser(const char* p, User* user);
char parseAdmin(const char* p);
int parseAge(const char* p);
char* parseAttribute(const char* p, int skip, int max_length);


#endif
