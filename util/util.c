#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include "util.h"

void i_error(char* msg,int erflg){
    perror(msg);
    return erflg;
}

char* get_host_name(){
    char host[256];
    gethostname(host,256);
    return host;
}