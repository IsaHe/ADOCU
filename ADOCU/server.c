
#include "server.h"

void initialize_winsock() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        logAction("WSAStartup a fallado", "sistema", 'f');
        exit(1);
    }
    logAction("WSAStartup iniciado correctamente", "sistema", 's');
}

SOCKET create_server(int port) {
    SOCKET ListenSocket = INVALID_SOCKET;
    struct sockaddr_in serv_addr;

    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        logAction("Error creando el socket", "sistema", 'f');
        WSACleanup();
        exit(1);
    }
    logAction("Socket creado correctamente", "sistema", 's');

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(ListenSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        logAction("Error vinculando el socket al puerto", "sistema", 'f');
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }
    logAction("Socket vinculado correctamente", "sistema", 's');

    return ListenSocket;
}

void start_listening(SOCKET ListenSocket, sqlite3* db)  {
    char recvbuf[DEFAULT_BUFLEN];

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        logAction("Error escuchando las conexiones entrantes", "sistema", 'f');
        close_server(ListenSocket);
        exit(1);
    }
    logAction("Escuchando las conexiones entrantes...", "sistema", 's');
    printf("Escuchando las conexiones entrantes...\n");

    SOCKET ClientSocket;
    if ((ClientSocket = accept(ListenSocket, NULL, NULL)) == INVALID_SOCKET) {
        logAction("Error aceptando las conexiones entrantes", "sistema", 'f');
        close_server(ListenSocket);
        exit(1);
    }
    logAction("Conexión aceptada", "sistema", 's');
    printf("Conexión aceptada\n");

    int bytesRecividos;
    do {
        bytesRecividos = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (bytesRecividos > 0) {
            logAction("Bytes recibidos: %d", "sistema", 's', bytesRecividos);
            logAction(recvbuf, "sistema", 's');
            printf("Datos recibidos: %s\n", recvbuf);

            if (strcmp(recvbuf, "Hola") == 0) {
                logAction("Primer contacto con el cliente establecido", "cliente", 's');
                send_data(ClientSocket, recvbuf);
            }

        } else if (bytesRecividos == 0) {
            logAction("Conexión cerrada", "sistema", 's');
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            logAction("Error recibiendo datos", "sistema", 'f');
            close_server(ListenSocket);
            exit(1);
        }
    } while (bytesRecividos > 0);
}

void process_client(char* recvbuf, sqlite3* db, SOCKET ClientSocket) {
    if(strcmp(recvbuf, "0") == 0){
        logAction("Cerrando el servidor", "sistema", 's');
        exit(0);
    }
    if(strcmp(recvbuf, "1") == 0) {
        logAction("Primer contacto con el cliente establecido", "cliente", 's');
        send_data(ClientSocket, processUserDB(db));
        send_data(ClientSocket, processValorationDB(db));
    }
}

void send_data(SOCKET ClientSocket, const char* sendbuf) {
    int iResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        logAction("Error enviando datos", "sistema", 'f');
        closesocket(ClientSocket);
        WSACleanup();
        exit(1);
    }
    logAction("Datos enviados correctamente", "sistema", 's');
}

void close_server(SOCKET ListenSocket) {
    if (closesocket(ListenSocket) == SOCKET_ERROR) {
        printf("close failed: %d\n", WSAGetLastError());
        logAction("Error cerrando el socket", "sistema", 'f');
        WSACleanup();
        exit(1);
    }
    logAction("Socket cerrado correctamente", "sistema", 's');

    WSACleanup();
}
