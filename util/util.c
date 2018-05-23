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

static const char command1[] = "ls";
static const char command2[] = "chat ";
static const char command3[] = "file ";
static const char command4[] = "exit";

void menu_print(){
    fprintf(stdout,"\t****************************************\n");
    printf("\t\t%-20s\n","1.ls");
    printf("\t\t%-20s\n","2.chat with sb.");
    printf("\t\t%-20s\n","3.transfer file to sb.");
    printf("\t\t%-20s\n","4.exit");
    fprintf(stdout,"\t****************************************\n");
}
void main_init(){
    int ret;
    pthread_t id1,id2,id3;
    ret = pthread_create(&id1,NULL,(void*)br_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    ret = pthread_create(&id2,NULL,(void*)uni_answer_entry_rece,NULL);
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
void main_exit(){
    br_exit_send();
    user_clear();
}
void listen_input(){
    char buffer[BUFSIZ];
    while(1){
        printf("\t%-20s\n\t","Please input your command:");
        gets(buffer);
        if(!strcmp(buffer,command1)){
            user_printall();
        }
        else if(!strcmp(buffer,command4)){
            main_exit();
            exit(0);
        }
    }
}