#include <stdio.h>
#include "user.h"

User askForUser() {
	User user;
	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s", user.username);
	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s", user.password);
	return user;
}

User userToIntroduce() {
	User user;
	printf("Introduce el nombre: ");
	fflush(stdin);
	scanf("%s", user.name);
	printf("Introduce la edad: ");
	fflush(stdin);
	scanf("%i", &user.age);
	printf("Introduce el usuario: ");
	fflush(stdin);
	scanf("%s", user.username);
	printf("Introduce la contraseña: ");
	fflush(stdin);
	scanf("%s", user.password);
	user.admin = 'U';
	return user;
}
