#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <pthread.h>
#include "util.h"
#include "../user/user.h" 
#include "../my-udp/udp-op.h"
#include "../my-tcp/tcp-op.h"

char USERNAME[UESRNAME_SIZ] = "";
static const char command1[] = "ls";
static const char command2[] = "chat ";
static const char command3[] = "file ";
static const char command4[] = "exit";

void username_get(void){
    int u_len,flag;
    do{
        printf("Please input your username(1~20):");
        fgets(USERNAME,UESRNAME_SIZ + 1,stdin);
        u_len = strlen(USERNAME);
        if(USERNAME[0] == '\n'){
            printf("Your username cannot be empty,try again.\n");
        }
        else if(USERNAME[u_len-1] == '\n'){
            USERNAME[u_len-1] = '\0';
            flag = 1;
        }
        else{
            USERNAME[UESRNAME_SIZ] = '\0';
            flag = 1;
        }
    }while(!flag);
    fflush(stdin);
    fflush(stdout);
}
void menu_print(void){
    fprintf(stdout,"\t****************************************\n");
    printf("\t\t%-20s\n","1.ls");
    printf("\t\t%-20s\n","2.chat with sb.");
    printf("\t\t%-20s\n","3.transfer file to sb.");
    printf("\t\t%-20s\n","4.exit");
    fprintf(stdout,"\t****************************************\n");
}
void main_init(void){
    int ret;
    pthread_t id1,id2,id3;
    ret = pthread_create(&id1,NULL,(void*)br_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    ret = pthread_create(&id2,NULL,(void*)uni_rece,NULL);
    if(ret){
        perror("id2 created failed!");
    }
    pthread_detach(id2);
    sleep(1);
    br_entry_send();

    menu_print();

    ret = pthread_create(&id3,NULL,(void*)listen_input,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id3);
}
void main_exit(void){
    br_exit_send();
    user_clear();
}
void listen_input(void){
    char buffer[COM_SIZ];
    while(1){
        printf("\t%-20s\n\t","Please input your command:");
        fgets(buffer,COM_SIZ,stdin);
        if(!strncmp(buffer,command1,strlen(buffer)-1)){
            user_printall();
        }
        else if(!strncmp(buffer,command4,strlen(buffer)-1)){
            main_exit();
            exit(0);
        }
    }
}