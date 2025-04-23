#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> 
#define PORT 8080
#define BUFFER_SIZE 1024

void chat(SOCKET server_sock) {
    char buffer[BUFFER_SIZE];
    int n;
    while (1) {
        printf("Client: ");
        memset(buffer, 0, BUFFER_SIZE); 
        fgets(buffer, sizeof(buffer), stdin);
        send(server_sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);  
        n = recv(server_sock, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            printf("Server disconnected or error.\n");
            break;
        }
        printf("Server: %s\n", buffer);
    }
}

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char server_ip[] = "127.0.0.1";
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);  
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected to server at %s:%d\n", server_ip, PORT);
    chat(sock);
    closesocket(sock);
    WSACleanup();
    return 0;
}
