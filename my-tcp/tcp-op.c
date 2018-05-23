#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <unistd.h>
#include "../util/util.h"
#include "../ipmsg.h"
#include "../user/user.h"
#include "tcp-op.h"

static const int TCP_PORT = 17989;
static const int MAX_LEN = 80;

void tcp_msg_send(char* s_addr){
    int client_sock;
    char buffer[BUFSIZ] = "tcp_msg_send:tcp test";
    
    client_sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(client_sock == -1){
        perror("tcp_msg_send: socket create error");
    }
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);
    server.sin_addr.s_addr = inet_addr(s_addr);

    int ret;
    ret = connect(client_sock,(struct sockaddr*)&server,sizeof(server));
    if(ret == -1){
        perror("tcp_msg_send: socket connect error");
    }
    int send_bytes;
    send_bytes = write(client_sock,buffer,strlen(buffer));
    printf("%d\n",send_bytes);

    close(client_sock);
}
void tcp_msg_rece(){
    int server_sock;
    char buffer[BUFSIZ];

    server_sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_sock == -1){
        perror("tcp_msg_rece: socket create error");
    }
    int set = 1;  
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(int)); 
    struct sockaddr_in server,client;
    memset(&server,0,sizeof(server));
    //memset(&client,0,sizeof(client));
    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    int addr_len = sizeof(client);

    if(bind(server_sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        perror("tcp_msg_rece: socket bind error");
    };
    if(listen(server_sock,4) < 0){
        perror("tcp_msg_rece: socket listen error");
    };
    int cli_sock;
    cli_sock = accept(server_sock,(struct sockaddr*)&client,&addr_len);
    if(cli_sock < 0){
        perror("tcp_msg_rece: accept client error");
    }
    int rece_bytes;
    rece_bytes = recv(cli_sock,buffer,MAX_LEN,0);
    if(rece_bytes > 0){
        puts(buffer);
    }
}