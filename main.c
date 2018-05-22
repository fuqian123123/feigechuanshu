#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include "./my-udp/udp-op.h"
#include "./user/user.h"

int main(int argc,char* argv[]){
    int ret;
    pthread_t id1;
    ret = pthread_create(&id1,NULL,(void*)br_entry_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    sleep(1);
    br_entry_send();
             sleep(1);

    int i;
    for(i = 0; i < 3; i++){
         user_printall();
         sleep(1);
    }
    br_exit_send();
    sleep(1);
    user_printall();

    user_clear();
    return 0;
}    
