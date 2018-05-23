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
#include "util.h"

static const char[] command1 = "ls";
static const char[] command2 = "chat ";
static const char[] command3 = "file ";

void menu_print(){
    fprintf(stdout,"\t****************************************\n");
    printf("\t\t%-20s\n","1.ls");
    printf("\t\t%-20s\n","2.chat with sb.");
    printf("\t\t%-20s\n","3.transfer file to sb.");
    fprintf(stdout,"\t****************************************\n");
}
void listen_input(){
    char buffer[BUFSIZ];
    while(1){
        printf("\t\t%-20s\n","Please input your command:");
        gets(buffer);
        // if(!strcmp(buffer,)){

        // }
    }
}