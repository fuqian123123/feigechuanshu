#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../util/util.h"

static const int TCP_PORT = 17989;
static const int MAX_LEN = 128;

void tcp_send(char* s_addr,char* filename){
    int client_sock;
    char buffer[BUFFER_SIZ];
    FILE* fp;

    if ((fp = fopen(filename, "r")) == NULL) {  
        perror("tcp_send: open file error");  
        exit(0);  
    }
    
    client_sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(client_sock == -1){
        perror("tcp_send: socket create error");
    }
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);
    server.sin_addr.s_addr = inet_addr(s_addr);

    int ret;
    ret = connect(client_sock,(struct sockaddr*)&server,sizeof(server));
    if(ret == -1){
        perror("tcp_send: socket connect error");
    }
    bzero(buffer,MAX_LEN);
    int send_bytes,read_bytes;
    while((read_bytes = fread(buffer, sizeof(char), MAX_LEN, fp)) >0 ){
        send_bytes = send(client_sock, buffer, read_bytes, 0);
        if(send_bytes < 0){
            perror("tcp_send: send file error");  
            exit(0); 
        }
        bzero(buffer,MAX_LEN);
    }
    fclose(fp);
    close(client_sock);
    printf("Transfer finished.\n");
}
void tcp_rece(){
    int server_sock;
    char buffer[BUFFER_SIZ];
    char file_store_path[BUFFER_SIZ];
    FILE* fp;
    sprintf(file_store_path,"/tmp/%d",(int)time(NULL));
    if ((fp = fopen(file_store_path, "w")) == NULL) {  
        perror("tcp_rece: open file error");  
        exit(0);  
    }

    server_sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(server_sock == -1){
        perror("tcp_rece: socket create error");
    }
    int set = 1;  
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(int)); 
    struct sockaddr_in server,client;
    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));
    server.sin_family = AF_INET;
    server.sin_port = htons(TCP_PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    int addr_len = sizeof(client);

    if(bind(server_sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        perror("tcp_rece: socket bind error");
    };
    if(listen(server_sock,4) < 0){
        perror("tcp_rece: socket listen error");
    };
    
    while(1){
        int cli_sock;
        cli_sock = accept(server_sock,(struct sockaddr*)&client,&addr_len);
        if(cli_sock < 0){
            perror("tcp_rece: accept client error");
        }
        int rece_bytes,write_bytes;
        bzero(buffer,MAX_LEN);
        while(rece_bytes = recv(cli_sock,buffer,MAX_LEN,0)){
            if(rece_bytes > 0){
                //puts(buffer);
                write_bytes = fwrite(buffer, sizeof(char),rece_bytes, fp);
                if(write_bytes < rece_bytes){
                    printf("tcp_rece: write file error");
                    break;
                }
                bzero(buffer,MAX_LEN);
            }
            //rece_bytes = 0;
        }
        printf("\tReceived finished.\n");
        fclose(fp);
        close(cli_sock);
    }
    close(server_sock);    
}
