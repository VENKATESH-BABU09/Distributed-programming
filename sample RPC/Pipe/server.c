#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define PIPE_NAME  "\\\\.\\pipe.\\mypipe"

void main(){
    HANDLE pipe;
    DWORD bytesRead,bytesWrite;

    char buffer[1024];

    pipe=CreateNamedPipeA(PIPE_NAME,PIPE_ACCESS_DUPLEX,PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,1,1024,1024,0,NULL);

    printf("waiting for client to connect\n");
    ConnectNamedPipe(pipe,NULL);
    printf("client connected");
    while(1){
        ReadFile(pipe,buffer,sizeof(buffer),&bytesRead,NULL);
        buffer[bytesRead]='\0';

        if(!strcmp(buffer,"exit")){
            printf("exiting...");
            break;
        }
        printf("Received from client: %s\n", buffer);
        printf("enter the msg want to sent to client:\n");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer,"\n")] = '\0';
        WriteFile(pipe,buffer,strlen(buffer)+1,&bytesWrite,NULL);



    }
    CloseHandle(pipe);
    
}


