#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include "./my-udp/udp-op.h"
#include "./my-tcp/tcp-op.h"
#include "./user/user.h"

int main(int argc,char* argv[]){
    // int ret;
    // pthread_t id1,id2;
    // ret = pthread_create(&id1,NULL,(void*)br_rece,NULL);
    // if(ret){
    //     perror("id1 created failed!");
    // }
    // pthread_detach(id1);
    // ret = pthread_create(&id2,NULL,(void*)uni_answer_entry_rece,NULL);
    // if(ret){
    //     perror("id2 created failed!");
    // }
    // pthread_detach(id2);
    // sleep(1);
    // br_entry_send();
    // sleep(1);

    // int i;
    //  for(i = 0; i < 10; i++){
    //       user_printall();
    //       sleep(1);
    //  }
    // br_exit_send();
    // sleep(1);
    // user_printall();

    // user_clear();

    int ret;
    pthread_t id1;
    ret = pthread_create(&id1,NULL,(void*)tcp_msg_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    sleep(1);
    tcp_msg_send("127.0.0.1");
    while(1);
    return 0;
}    
