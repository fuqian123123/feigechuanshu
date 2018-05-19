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
    //br_exit_send();
    int i;
    for(i = 0; i < 2; i++){
        user_printall();
        sleep(5);
    }
    user_clear();
    return 0;
}    
