#include "user.h"

#ifndef USERLIST_H_
#define USERLIST_H_

typedef struct {
	User * userList;
	int size;
	int numUsers;
} UserList;

void takeUsersFromFile(UserList* userList, char* fileName);
void seeUserList(UserList userList);
int findUserInList(UserList userList, User user);
void addUserToList(UserList* userList, User user);
void writeUsersInFile(UserList userList, char* fileName);
int findUserInListRegister(UserList userList, User user);
int userToRemove(UserList userList);
void deleteUserWithPosition(UserList* userList, int position);

#endif
