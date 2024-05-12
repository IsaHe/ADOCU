
#ifndef ADOCU_SERVER_H
#define ADOCU_SERVER_H

#include <stdio.h>
#include <winsock2.h>
#include "logger.h"
#include "sqlite3.h"
#include <string.h>
#include "user.h"

#define DEFAULT_BUFLEN 512

void initialize_winsock();
SOCKET create_server(int port);
void start_listening(SOCKET ListenSocket, sqlite3* db);
void close_server(SOCKET ListenSocket);
void process_client(char* recvbuf, int recvbuflen, sqlite3* db, SOCKET ClientSocket);
void send_data(SOCKET ClientSocket, const char* sendbuf);

#endif //ADOCU_SERVER_H
