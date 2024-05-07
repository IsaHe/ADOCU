#include "server.h"

int main() {
    WSADATA wsaData;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Inicializar la biblioteca Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logAction("WSAStartup failed", "server", 'f');
        return 1;
    }

    // Crear el socket del servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        logAction("Socket creation failed", "server", 'f');
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Adjuntar el socket al puerto 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        logAction("Bind failed", "server", 'f');
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        logAction("Listen failed", "server", 'f');
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
        logAction("Accept failed", "server", 'f');
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Enviar mensaje al cliente


    // Limpiar y cerrar
    closesocket(new_socket);
    WSACleanup();

    return 0;
}