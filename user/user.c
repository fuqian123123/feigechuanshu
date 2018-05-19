#include <string.h>
#include "user.h"

static IPMSG_USER* ul_head_addr;
static IPMSG_USER* ul_nail_addr;

//userlist init
void user_init(char* name,char* host,char* s_addr){
    ul_head_addr = userlist_ds_init();
    strcpy(ul_head_addr->name,name);
    strcpy(ul_head_addr->host,host);
    strcpy(ul_head_addr->s_addr,s_addr);
    ul_nail_addr = ul_head_addr;
}
//add user
void user_entry(char* name,char* host,char* s_addr){
    if(ul_head_addr != NULL){
        ul_nail_addr = userlist_ds_item_add(ul_nail_addr,name,host,s_addr);
    }
    else{
        user_init(name,host,s_addr);
    }
}
//print all user
void user_printall(void){
    IPMSG_USER* temp = ul_head_addr;
    while(temp != NULL){
        printf("%s\t%s\t",temp->name,temp->host);
        temp = temp->next;
        printf("\n");
    }
}
//clear all user
void user_clear(void){
   userlist_ds_destory(ul_head_addr);         
}