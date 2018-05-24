#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include "udp-op.h"
#include "../util/util.h"
#include "../ipmsg.h"
#include "../user/user.h"

#define BR_ENTRY_FLAG 0
#define BR_EXIT_FLAG 1
//static const char BR_ADDR[] = "10.22.255.255";
static const char BR_ADDR[] = "192.168.43.255";
static const int BR_PORT = 4001;
static const int BR_RECV_PORT = 4001;
static const int UNI_PORT = 4003;
static const int UNI_RECV_PORT = 4003;

int get_br_sock_fd(void){
    int br_fd;
    br_fd = socket(PF_INET,SOCK_DGRAM,0);
    if(br_fd == -1){
        perror("get_br_sock_fd:udp socket create failed!");
    }
    int optval = 1;
    setsockopt(br_fd,SOL_SOCKET,SO_BROADCAST | SO_REUSEADDR,&optval,sizeof(int));
    return br_fd;
}

int get_uni_sock_fd(void){
    int uni_fd;
    uni_fd = socket(PF_INET,SOCK_DGRAM,0);
    if(uni_fd == -1){
        perror("get_uni_sock_fd:udp socket create error");
    }
    int optval = 1;  
    setsockopt(uni_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); 
    return uni_fd;
}
void br_send(int flag){
    int br_fd = get_br_sock_fd();
    char buffer[BUFSIZ];
    struct sockaddr_in theirAddr;
    memset(&theirAddr,0,sizeof(struct sockaddr_in));
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_addr.s_addr = inet_addr(BR_ADDR);
    theirAddr.sin_port = htons(BR_PORT);
    int send_bytes;
    char myHostName[256];
    struct passwd* pwd;
    pwd = getpwuid(getuid());
    gethostname(myHostName,sizeof(myHostName));
    switch (flag)
    {
        case BR_ENTRY_FLAG:
            sprintf(buffer,"%d:%ld:%s:%s:%d:%s",(int)IPMSG_VERSION,
                (long int)time(NULL),pwd->pw_name,myHostName,(int)IPMSG_BR_ENTRY,USERNAME);
            break;
        case BR_EXIT_FLAG:
            sprintf(buffer,"%d:%ld:%s:%s:%d:%s",(int)IPMSG_VERSION,
                (long int)time(NULL),pwd->pw_name,myHostName,(int)IPMSG_BR_EXIT,"");
            break;
        default:
            perror("no defined flag");
            break;
    }
    send_bytes = sendto(br_fd,buffer,strlen(buffer),0,
        (struct sockaddr*)&theirAddr,sizeof(struct sockaddr));
    if(send_bytes== -1){
        perror("br_entry_send:udp send msg failed!");
    }
    close(br_fd);
};
//user entry
void br_entry_send(void){
    br_send(BR_ENTRY_FLAG);
}
//user exit
void br_exit_send(void){
    br_send(BR_EXIT_FLAG);
}
//receive user send message
void br_rece(void){
    char buffer[BUFSIZ];
    int rece_fd = get_br_sock_fd();
    struct sockaddr_in server;
    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(BR_RECV_PORT);
    server.sin_addr.s_addr = INADDR_ANY; 

    struct sockaddr_in fromwho;
    int addr_len = sizeof(struct sockaddr_in);
    memset(&fromwho,0,sizeof(struct sockaddr_in));
    fromwho.sin_family = AF_INET;
    fromwho.sin_port = htons(BR_RECV_PORT);
    fromwho.sin_addr.s_addr = INADDR_ANY;

    int ret;
    ret = bind(rece_fd,(struct sockaddr*)&server,sizeof(server));
    if(ret < 0){
        perror("br_rece:udp bind failed!");
    }
    int receBytes;
    while(1){
        receBytes = recvfrom(rece_fd,buffer,sizeof(buffer),0,
            (struct sockaddr*)&fromwho,(socklen_t*)&addr_len);
        if(receBytes > 0){
            buffer[receBytes] = '\0';
            char ipmsg_v[20],ipmsg_flag[20],ipmsg_pack[20],username[20],hostname[25],addtion[20];
            sscanf(buffer,"%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%s",
                ipmsg_v,ipmsg_pack,username,hostname,ipmsg_flag,addtion);
            //receive user entry message
            //username is in addtion
            if(IPMSG_BR_ENTRY == (ipmsg_flag[0] - '0')){
                if(!user_is_existed(inet_ntoa(fromwho.sin_addr))){
                    user_entry(addtion,hostname,inet_ntoa(fromwho.sin_addr));
                }
                uni_answer_entry_send(inet_ntoa(fromwho.sin_addr),UNI_PORT);
            }
            //receive user exit message
            if(IPMSG_BR_EXIT == (ipmsg_flag[0] - '0')){
                if(user_is_existed(inet_ntoa(fromwho.sin_addr))){
                    user_exit(inet_ntoa(fromwho.sin_addr));
                }
            }
        }
        receBytes = 0;
    }
    close(rece_fd);
}

void uni_answer_entry_send(char* s_addr,int port){
    int ret;
    int uni_fd = get_uni_sock_fd();
    char buffer[BUFSIZ];

    struct sockaddr_in target;
    memset(&target,0,sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    target.sin_addr.s_addr = inet_addr(s_addr);

    char myHostName[256];
    struct passwd* pwd;
    pwd = getpwuid(getuid());
    gethostname(myHostName,sizeof(myHostName));

    sprintf(buffer,"%d:%ld:%s:%s:%d:%s",
        (int)IPMSG_VERSION,(long int)time(NULL),pwd->pw_name,myHostName,(int)IPMSG_ANSENTRY,USERNAME);
    int send_bytes;
    send_bytes = sendto(uni_fd,buffer,strlen(buffer),0,(struct sockaddr*)&target,sizeof(target));
    if(send_bytes == -1){
        perror("uni_answer_entry_send:send msg error");
    }
    close(uni_fd);
}
void uni_rece(){
    char buffer[BUFSIZ];
    int rece_fd = get_uni_sock_fd();
    struct sockaddr_in server;
    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(UNI_RECV_PORT);
    server.sin_addr.s_addr = INADDR_ANY; 

    struct sockaddr_in fromwho;
    int addr_len = sizeof(struct sockaddr_in);
    memset(&fromwho,0,sizeof(struct sockaddr_in));
    fromwho.sin_family = AF_INET;
    fromwho.sin_port = htons(UNI_RECV_PORT);
    fromwho.sin_addr.s_addr = INADDR_ANY;

    int ret;
    ret = bind(rece_fd,(struct sockaddr*)&server,sizeof(server));
    if(ret < 0){
        perror("uni_rece:udp bind error");
    }
    int receBytes;
    while(1){
        receBytes = recvfrom(rece_fd,buffer,sizeof(buffer),0,
                (struct sockaddr*)&fromwho,(socklen_t*)&addr_len);
        if(receBytes > 0){
            char ipmsg_v[20],ipmsg_flag[20],ipmsg_pack[20],username[20],hostname[25],addtion[20];
            sscanf(buffer,"%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%s",
                ipmsg_v,ipmsg_pack,username,hostname,ipmsg_flag,addtion);
            //username is in addtion
            if(IPMSG_ANSENTRY == (ipmsg_flag[0] - '0')){
                if(!user_is_existed(inet_ntoa(fromwho.sin_addr))){
                    user_entry(addtion,hostname,inet_ntoa(fromwho.sin_addr));
                }
            }
        }
    }
    close(rece_fd);
}
