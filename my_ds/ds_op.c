#include <stdio.h>
#include <stdlib.h>
#include "my_ds.h"

IPMSG_USER* uListInit(){
    IPMSG_USER* ul = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(ul == NULL){
        perror("Userlist init error");
    }
    return ul;
}
IPMSG_USER* uListItemAdd(IPMSG_USER* cur,char* name,char* host,int s_addr){
    IPMSG_USER* next = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(next == NULL){
        perror("Add user error");
    }
    next->pre = cur;
    cur->next = next;
    return next;
}
void uListItemDelete(IPMSG_USER* head,int s_addr){
    IPMSG_USER* temp = head;
    while(temp != NULL){
        if(temp->s_addr == s_addr){
            temp->next->pre = temp->pre;
            temp->pre->next = temp->next;
            free(temp);
            temp = NULL;
        }
        temp = temp->next;
    }
}
void uListDelete(IPMSG_USER* ul){
    free(ul);
    ul = NULL;
}