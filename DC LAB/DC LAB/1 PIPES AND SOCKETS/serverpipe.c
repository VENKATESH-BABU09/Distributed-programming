#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define PIPE_NAME "\\\\.\\pipe\\TwoWayPipe"
#define BUFFER_SIZE 1024

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    
    hPipe = CreateNamedPipeA(
        PIPE_NAME, 
        PIPE_ACCESS_DUPLEX, 
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 
        1, 
        BUFFER_SIZE, 
        BUFFER_SIZE, 
        0, 
        NULL); 

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating pipe. Error code: %lu\n", GetLastError());
        return 1;
    }

    printf("Waiting for a client to connect...\n");

    
    if (!ConnectNamedPipe(hPipe, NULL)) {
        printf("Error connecting to pipe. Error code: %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected.\n");

    
    const char* parentMsg = "Hello from Parent!";
    while (1) {
        
        WriteFile(hPipe, parentMsg, strlen(parentMsg) + 1, &bytesWritten, NULL);
        printf("Parent: Sent message: %s\n", parentMsg);

        
        if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0'; 
            printf("Parent: Received message: %s\n", buffer);
        } else {
            printf("Error reading from pipe. Error code: %lu\n", GetLastError());
            break;
        }

        Sleep(1000); 
    }

    CloseHandle(hPipe);
    return 0;
}