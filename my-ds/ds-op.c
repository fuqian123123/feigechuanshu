#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <netdb.h>
#include "ds-op.h"
#include "../util/util.h"

IPMSG_USER* userlist_ds_init(void){
    IPMSG_USER* head = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(head == NULL){
        perror("Userlist init error");
    }
    return head;
}
IPMSG_USER* userlist_ds_item_add(IPMSG_USER* cur,char* name,char* host,char* s_addr){
    IPMSG_USER* next = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(next == NULL){
        perror("Add user error");
    }
    strcpy(next->name,name);
    strcpy(next->host,host);
    strcpy(next->s_addr,s_addr);
    next->pre = cur;
    cur->next = next;
    return next;
}
IPMSG_USER* userlist_ds_item_delete(IPMSG_USER* uhead,char* s_addr){
    if(!strcmp(uhead->s_addr,s_addr)){
        IPMSG_USER* new_head = uhead->next;
        free(uhead);
        uhead = NULL;
        return new_head;
    }
    IPMSG_USER* temp = uhead;
    while(temp != NULL){
        //is not tail
        if(temp->next != NULL){
            if(!strcmp(temp->s_addr,s_addr)){
                temp->next->pre = temp->pre;
                temp->pre->next = temp->next;
                free(temp);
                temp = NULL;
                return uhead;
            }            
        }
        else{
            if(!strcmp(temp->s_addr,s_addr)){
                free(temp);
                temp = NULL;
                temp->pre->next = NULL;
                return uhead;
            }
        }
        temp = temp->next;
    }
    return uhead;
}
void userlist_ds_destory(IPMSG_USER* head){
    if(head != NULL){
        IPMSG_USER* tail = head->next;
        while(tail != NULL){
            IPMSG_USER* temp = tail;
            tail = tail->next;
            free(temp);
            temp = NULL;
        }
        free(head);
        head = NULL;
    }
}