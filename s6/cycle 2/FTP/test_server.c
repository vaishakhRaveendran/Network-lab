#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main()
{
    char* ip="127.0.0.1";
    int port=4567;
    char buffer[1024];
    struct sockaddr_in client_addr,server_addr;
    int bindval,client_sock,server_sock;
    socklen_t addr_size;

    server_sock=socket(AF_INET,SOCK_STREAM,0);
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);

    bindval=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(client_sock,12);
    addr_size=sizeof(client_addr);

    client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);

    char buffer[1024];
    char filename[100];
    FILE *fptr;
    while(1){
        bzero(buffer,1024);
        recv(client_sock,buffer,1024,0);
        if(strcmp(buffer,"PUT")){
            bzero(buffer,1024);
            recv(client_sock,buffer,1024,0);
            strcpy(filename,buffer);
            fptr=open(filename,"w");
            while(1){
                bzero(buffer,1024);
                recv(client_sock,buffer,1024,0);
                if(strcmp(buffer,"END$")==0)break;
                fprintf(fptr,"%s",buffer);

            }
            printf("File %s received\n", filename);
            fclose(fptr);
        }
        else if(strcmp(buffer,"GET")==0){
            bzero(buffer, 1024);
            recv(client_sock, buffer, 1024, 0);
            strcpy(filename, buffer);
            fptr = fopen(filename, "r");
            if (!fptr)
            {
                printf("File %s does not exist\n", filename);
                strcpy(buffer, "404");
                send(client_sock, buffer, 1024, 0);
            }

            else
            {
                strcpy(buffer, "200");
                send(client_sock, buffer, 1024, 0);

                while (!feof(fptr))
                {
                    bzero(buffer, 1024);
                    fscanf(fptr, "%[^\n] ", buffer);
                    send(client_sock, buffer, 1024, 0);
                }
                bzero(buffer, 1024);
                strcpy(buffer, "END$");
                send(client_sock, buffer, 1024, 0);
                fclose(fptr);
                printf("File %s sent\n", filename);
            }
        }

    }
} 
        
