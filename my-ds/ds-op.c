#include "ds-op.h"

IPMSG_USER* userlist_ds_init(void){
    IPMSG_USER* ul = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(ul == NULL){
        perror("Userlist init error");
    }
    return ul;
}
IPMSG_USER* userlist_item_add(IPMSG_USER* cur,char* name,char* host,int s_addr){
    IPMSG_USER* next = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(next == NULL){
        perror("Add user error");
    }
    next->pre = cur;
    cur->next = next;
    return next;
}
void userlist_item_delete(IPMSG_USER* head,int s_addr){
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
void userlist_ds_destory(IPMSG_USER* head){
    IPMSG_USER* nail = head->next;
    while(nail != NULL){
        IPMSG_USER* temp = nail;
        nail = nail->next;
        free(temp);
        temp = NULL;
    }
    free(head);
    head = NULL;
}