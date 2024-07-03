#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main(){
    char *ip="127.0.0.1";
    int port=2345;
    //Defines the type of client and server 
    struct sockaddr_in client_addr,server_addr;
    socklen_t addr_size;//This is passed into the accept function for writing the client address size.
    //file descriptors contains the returns of accept and socket function
    int client_sock,server_sock;
    char buffer[1024];
    int bind_val;

    server_sock=socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        printf("[-] SOCKET ERROR [-]");
        exit(1);
    }
    printf("[-] TCP ESTABLISHED [-]");


    //SERVER DEFINTIONS
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);

    //BIND SERVER WITH SOCKET ie ASSIGNING THE PARTICULAR PORT FOR THE SERVER.....
    //HERE SOCKADDR IS USED INSTEAD OF SOCKADDR_IN
    bind_val=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_val<0){
        perror("[-]BIND ERROR[-]");
    }
    listen(server_sock,10);
    while(1){
        addr_size=sizeof(client_addr);
        client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
        printf("[-] CONNECTED TO CLIENT [-]");
        bzero(buffer,1024);
        recv(client_sock,buffer,sizeof(buffer),0);
        strcpy(buffer, "HELLO , THIS IS SERVER ");
        printf(" Server : %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);
        close(client_sock);
        printf("[+] Client disconnected.\n\n");

    }
    close(server_sock);

}