#include "user.h"
#include "sqlite3.h"

#ifndef USERLIST_H_
#define USERLIST_H_

typedef struct {
	User * userList;
	int size;
	int numUsers;
} UserList;

int readUsersFromDB(UserList* userList, sqlite3* db);
int deleteDB(sqlite3* db, char* table);
int insertUsersInDB(UserList userList, sqlite3* db);
void seeUserList(UserList userList);
int findUserInList(UserList userList, User user);
void addUserToList(UserList* userList, User user);
int findUserInListRegister(UserList userList, User user);
int userToRemove(UserList userList);
void deleteUserWithPosition(UserList* userList, int position);

#endif
