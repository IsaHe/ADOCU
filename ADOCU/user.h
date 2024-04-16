#ifndef USER_H_
#define USER_H_

typedef struct {
	char name[20];
	char username[20];
	char password[20];
	int age;
	char admin;
} User;

User askForUser();
User userToIntroduce();

#endif
