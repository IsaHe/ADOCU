
#include "clientSocket.h"

void ClientSocket::initializeWinsock() {
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        WSACleanup();
        exit(1);
    }
}

void ClientSocket::createSocket() {
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
}

void ClientSocket::setupSocket(int port) {
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(port);
}

void ClientSocket::connectToServer() {
    int iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
    if (iResult == SOCKET_ERROR) {
        closesocket (ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
}

int ClientSocket::sendData(const char* sendbuf) const {
    int iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        cout << "send failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return -1;
    }
    return iResult;
}

int ClientSocket::receiveData(char* recvbuf, int bufLen) const {
    int iResult = recv(ConnectSocket, recvbuf, bufLen, 0);
    if (iResult > 0) {
        cout << "Received: " << recvbuf << endl;
    } else if (iResult == 0) {
        cout << "Connection closed\n";
    } else {
        cout << "recv failed with error: " << WSAGetLastError() << endl;
    }
    return iResult;
}

ClientSocket::ClientSocket(int port) {
    initializeWinsock();
    createSocket();
    setupSocket(port);
    connectToServer();
}

ClientSocket::~ClientSocket() {
    // shutdown the connection since no further data will be sent
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        cout << "shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
}

int ClientSocket::sendGroup(Group *group) const {
    int resultadoOperacion = sendData(group->jsonifyGroup());
    return resultadoOperacion;
}

int ClientSocket::sendUser(User *user, Group *group) const {
    int resultadoOperacion = sendData(user->jsonifyUser(group->getName()));
    return resultadoOperacion;
}

int ClientSocket::sendValoration(Valoration *valoration, const User& user) const {
    int resultadoOperacion = sendData(valoration->jsonifyValoration(user));
    return resultadoOperacion;
}

int ClientSocket::sendActivity(Activity *activity, Group *group) const {
    int resultadoOperacion = sendData(activity->jsonifyActivity(group->getName()));
    return resultadoOperacion;
}

int ClientSocket::sendNewUser(User *user) const {
    int resultadoOperacion = sendData(user->jsonifyNewUser());
    return resultadoOperacion;
}
