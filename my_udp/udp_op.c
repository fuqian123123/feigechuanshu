#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include "../util/util.h"
#include "../ipmsg.h"
#include "../my_udp/my_udp.h"

static const char BR_ADDR[] = "10.18.23.255";
static const int BR_PORT = 4001;
static const int RECV_PORT = 4002;
static char buffer[1024];
void br_entry_send(){
    int brFd;
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

    sprintf(buffer,"%ld:%ld:%s:%s:%d:%s",IPMSG_VERSION,time(NULL),myHostName,myHostName,IPMSG_BR_ENTRY,"");
    if((sendBytes = sendto(brFd,buffer,strlen(buffer),0,
            (struct sockaddr*)&theirAddr,sizeof(struct sockaddr)))== -1){
        perror("br_entry:udp send msg failed!");
    }
    printf("%d\n",sendBytes);
    close(brFd);
}
void br_exit_send(){
    int brFd;
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

    sprintf(buffer,"%ld:%ld:%s:%s:%d:%s",IPMSG_VERSION,time(NULL),myHostName,myHostName,IPMSG_BR_EXIT,"");
    if((sendBytes = sendto(brFd,buffer,strlen(buffer),0,
            (struct sockaddr*)&theirAddr,sizeof(struct sockaddr)))== -1){
        perror("br_exit:udp send msg failed!");
    }
    printf("%d\n",sendBytes);
    close(brFd);
}

void br_entry_rece(){
    int receFd;
    if((receFd = socket(AF_INET,SOCK_DGRAM,0) == -1)){
        perror("br_entry_rece:udp socket create failed!");
    }
    struct sockaddr_in myAddr;
    int addr_len = sizeof(struct sockaddr_in);
    memset(&myAddr,0,sizeof(struct sockaddr_in));
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = RECV_PORT;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret;
    ret = bind(receFd,(struct sockaddr_in*)&myAddr,sizeof(myAddr));
    if(ret < 0){
        perror("br_entry_rece:udp bind failed!");
    }
    while(1){
        recvfrom(receFd,&buffer,sizeof(buffer),0,(struct sockaddr_in*)&myAddr,(socklen_t*)&addr_len);
        printf("%s\n",buffer);
    }
    close(receFd);
}
