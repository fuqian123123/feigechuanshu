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
    //br_entry_send();
    //br_exit_send();
    int ret;
    pthread_t id1,id2;
    ret = pthread_create(&id1,NULL,(void*)test1,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    ret = pthread_create(&id2,NULL,(void*)test2,NULL);
    if(ret){
        perror("id2 created failed!");
    }
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    return 0;
}    
