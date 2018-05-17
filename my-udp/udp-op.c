#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "../util/util.h"
#include "../ipmsg.h"
#include "../my-udp/my-udp.h"

//static const char BR_ADDR[] = "10.18.23.255";
static const char BR_ADDR[] = "192.168.43.255";
static const int BR_PORT = 4001;
static const int RECV_PORT = 4001;
//user entry
void br_entry_send(void){
    int brFd;
    char buffer[BUFSIZ];
    if((brFd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        perror("br_entry:udp socket create failed!");
    }
    int optval = 1;
    setsockopt(brFd,SOL_SOCKET,SO_BROADCAST | SO_REUSEADDR,&optval,sizeof(int));
    struct sockaddr_in theirAddr;
    memset(&theirAddr,0,sizeof(struct sockaddr_in));
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_addr.s_addr = inet_addr(BR_ADDR);
    theirAddr.sin_port = htons(BR_PORT);
    int sendBytes;
    char myHostName[256];
    gethostname(myHostName,sizeof(myHostName));

    sprintf(buffer,"%d:%ld:%s:%s:%d:%s",(int)IPMSG_VERSION,(long int)time(NULL),myHostName,myHostName,(int)IPMSG_BR_ENTRY,"");
    if((sendBytes = sendto(brFd,buffer,strlen(buffer),0,
            (struct sockaddr*)&theirAddr,sizeof(struct sockaddr)))== -1){
        perror("br_entry:udp send msg failed!");
    }
    printf("%d\n",sendBytes);
    close(brFd);
}
//user exit
void br_exit_send(void){
    int brFd;
    char buffer[BUFSIZ];
    if((brFd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        perror("br_exit:udp socket create failed!");
    }
    int optval = 1;
    setsockopt(brFd,SOL_SOCKET,SO_BROADCAST | SO_REUSEADDR,&optval,sizeof(int));
    struct sockaddr_in theirAddr;
    memset(&theirAddr,0,sizeof(struct sockaddr_in));
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_addr.s_addr = inet_addr(BR_ADDR);
    theirAddr.sin_port = htons(BR_PORT);
    int sendBytes;
    char myHostName[256];
    gethostname(myHostName,sizeof(myHostName));

    sprintf(buffer,"%d:%ld:%s:%s:%d:%s",(int)IPMSG_VERSION,(long int)time(NULL),myHostName,myHostName,(int)IPMSG_BR_EXIT,"");
    if((sendBytes = sendto(brFd,buffer,strlen(buffer),0,
            (struct sockaddr*)&theirAddr,sizeof(struct sockaddr)))== -1){
        perror("br_exit:udp send msg failed!");
    }
    printf("%d\n",sendBytes);
    close(brFd);
}
//receive user online info
void br_entry_rece(void){
    char buffer[BUFSIZ];
    int receFd;
    receFd = socket(AF_INET,SOCK_DGRAM,0);
    if(receFd == -1){
        perror("br_entry_rece:udp socket create failed!");
    }
    int set = 1;  
    setsockopt(receFd, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(int)); 
    struct sockaddr_in server;
    int addr_len = sizeof(struct sockaddr_in);
    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(RECV_PORT);
    server.sin_addr.s_addr = INADDR_ANY;    
    int ret;
    ret = bind(receFd,(struct sockaddr*)&server,sizeof(server));
    if(ret < 0){
        perror("br_entry_rece:udp bind failed!");
    }
    int receBytes;
    while(1){
        receBytes = recvfrom(receFd,buffer,sizeof(buffer),0,
            (struct sockaddr*)&server,(socklen_t*)&addr_len);
        if(receBytes > 0){
            buffer[receBytes] = '\0';
            puts(buffer);
        }
    }
    close(receFd);
}
