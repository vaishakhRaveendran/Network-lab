#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>

void main(){
    char *ip="127.0.0.1";
    int port =2345;
    struct sockaddr_in client_addr,server_addr;
    int client_sock,server_sock,bind_value;
    socklen_t addr_size;
    char buffer[1024];


    client_sock=socket(AF_INET,SOCK_DGRAM,0);
    if(client_sock){
        printf("[+] SOCKET NOT CREATED [+]");
        exit(1);
    }

    //DEFINTION OF SERVER
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);

    bind_value=bind(client_sock,(struct addr*)&client_addr,sizeof(client_addr));
    if(bind_value<0){
         printf("[+] SBIND ERROR [+]");
         exit(1);     
    }
    bzero(buffer,1024);
    addr_size=sizeof(client_addr);

    recvfrom(client_sock,buffer,sizeof(buffer),0,(struct addr*)&client_addr,&addr_size);
    printf("[+] Data from client: %s\n", buffer);

    strcpy(buffer, "Data successfully received.");
    printf("(Server) Data to client: %s\n", buffer);

    sendto(client_sock, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));

}
