//
// Created by PC on 07/05/2024.
//

#ifndef ADOCU_SERVER_H
#define ADOCU_SERVER_H

#include <stdio.h>
#include <winsock2.h>
#include "logger.h"

#define DEFAULT_BUFLEN 512

void initialize_winsock();
SOCKET create_server(int port);
void start_listening(SOCKET ListenSocket);
void close_server(SOCKET ListenSocket);

#endif //ADOCU_SERVER_H
