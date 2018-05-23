#include <string.h>
#include "user.h"

static IPMSG_USER* ul_head_addr;

//userlist init
void user_init(char* name,char* host,char* s_addr){
    ul_head_addr = userlist_ds_init();
    strcpy(ul_head_addr->name,name);
    strcpy(ul_head_addr->host,host);
    strcpy(ul_head_addr->s_addr,s_addr);
}
//add user
void user_entry(char* name,char* host,char* s_addr){
    if(ul_head_addr != NULL){
        userlist_ds_item_add(ul_head_addr,name,host,s_addr);
    }
    else{
        user_init(name,host,s_addr);
    }
}
//if user existed
int user_is_existed(char* s_addr){
    IPMSG_USER* temp = ul_head_addr;
    while(temp != NULL){
        //printf("is existed:%d\n",strcmp(temp->s_addr,s_addr));
        if(!strcmp(temp->s_addr,s_addr)){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
//delete user
void user_exit(char* s_addr){
    ul_head_addr = userlist_ds_item_delete(ul_head_addr,s_addr);
}
//print all user
void user_printall(void){
    IPMSG_USER* temp = ul_head_addr;
    printf("\t%-20s%-20s%-20s\n","username","hostname","ip");
    while(temp != NULL){
        printf("\t%-20s%-20s%-20s",temp->name,temp->host,temp->s_addr);
        temp = temp->next;
        printf("\n");
    }
}
//clear all user
void user_clear(void){
   userlist_ds_destory(ul_head_addr);         
}