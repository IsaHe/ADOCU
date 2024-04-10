#ifndef USER_H_
#define USER_H_

typedef struct {
	char name[20];
	char username[20];
	char password[20];
	char age[4];
	char admin;
} User;

User askForUser();
User userToIntroduce();

#endif
