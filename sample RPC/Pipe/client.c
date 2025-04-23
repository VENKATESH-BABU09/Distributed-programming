#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define PIPE_NAME  "\\\\.\\pipe.\\mypipe"

void main(){
    HANDLE pipe;
    DWORD bytesRead,bytesWrite;

    char buffer[1024];

    pipe=CreateFileA(PIPE_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

    printf("server connected");
    while(1){
        printf("enter the msg want to send to server\n");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        WriteFile(pipe,buffer,strlen(buffer)+1,&bytesWrite,NULL);
        if(!strcmp(buffer,"exit")){
            printf("client disconnected...");
            break;
        }
        
        ReadFile(pipe,buffer,sizeof(buffer),&bytesRead,NULL);
        buffer[bytesRead]='\0';
        printf("Received from server: %s\n", buffer);
    }

CloseHandle(pipe);
}