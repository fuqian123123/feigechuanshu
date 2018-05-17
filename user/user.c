#include "user.h"

static IPMSG_USER* ul_head_addr;
static IPMSG_USER* ul_cur_addr;

//userlist init
void userlist_init(void){
    ul_head_addr = userlist_ds_init();
    userlist_print();
    userlist_ds_destory(ul_head_addr);
}
//print all user
void userlist_print(void){
    IPMSG_USER* temp = ul_head_addr;
    while(temp != NULL){
        printf("%s\t%s\t\n",temp->name,temp->host);
        temp = temp->next;
    }
}