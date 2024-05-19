
#ifndef ADOCU_CLIENTSOCKET_H
#define ADOCU_CLIENTSOCKET_H

#include <string>
#include <winsock2.h>
#include <iostream>
#include "group.h"
#include "valoration.h"

using namespace std;

#define DEFAULT_BUFLEN 512

class ClientSocket {
private:
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;

    void initializeWinsock();
    void createSocket();
    void setupSocket(int port);
    void connectToServer();

public:
    ClientSocket(int port);
    ~ClientSocket();

    int sendData(const char* sendbuf) const;
    int receiveData(char* recvbuf, int bufLen) const;

    int sendGroup(Group *group) const;

    int sendUser(User *user, Group *group) const;

    int sendValoration(Valoration *valoration, const User& user) const;

    int sendActivity(Activity *activity, Group *group) const;

    int sendNewUser(User *user) const;
};

#endif //ADOCU_CLIENTSOCKET_H