#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define PIPE_NAME "\\\\.\\pipe\\TwoWayPipe"
#define BUFFER_SIZE 1024

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    
    hPipe = CreateFileA(
        PIPE_NAME,          
        GENERIC_READ | GENERIC_WRITE, 
        0,                  
        NULL,               
        OPEN_EXISTING,      
        0,                  
        NULL);              

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error connecting to pipe. Error code: %lu\n", GetLastError());
        return 1;
    }

    printf("Connected to the server.\n");

    
    const char* childMsg = "Hello from Child!";
    while (1) {
        
        if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0'; 
            printf("Child: Received message: %s\n", buffer);
        } else {
            printf("Error reading from pipe. Error code: %lu\n", GetLastError());
            break;
        }

        
        WriteFile(hPipe, childMsg, strlen(childMsg) + 1, &bytesWritten, NULL);
        printf("Child: Sent message: %s\n", childMsg);

        Sleep(1000); 
    }

    CloseHandle(hPipe);
    return 0;
}
