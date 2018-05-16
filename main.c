#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include "./my_udp/my_udp.h"

void test1(){
    int i;
    for(i = 0; i < 3; i++){
        printf("one test %d\n",i);
        sleep(1);
    }
}
void test2(){
    int i;
    for(i = 0; i < 3; i++){
        printf("two test %d\n",i);
        sleep(1);
    }
}
int main(int argc,char* argv[]){
    
    int ret;
    pthread_t id1;
    ret = pthread_create(&id1,NULL,(void*)br_entry_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    //pthread_join(id1,NULL);
    br_entry_send();
    //br_exit_send();
    while(1){
        //br_entry_send();
        sleep(1);
    };
    return 0;
}    
