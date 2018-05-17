#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include "util.h"

int get_ip_by_hostname(char* hostname){
        struct hostent* hent;
        hent = gethostbyname(hostname);
        puts("notion:\n");
        for(int i = 0; hent->h_addr_list[i];i++){
            printf("%s\t",inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
        };
        return 1;
}