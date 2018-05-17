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
    struct passwd* pwd;
    pwd = getpwuid(getuid());
    strcpy(head->name,pwd->pw_name);
    gethostname(head->host,sizeof(head->host));
    //get_ip_by_hostname(head->host);
    return head;
}
IPMSG_USER* userlist_ds_item_add(IPMSG_USER* cur,char* name,char* host,int s_addr){
    IPMSG_USER* next = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(next == NULL){
        perror("Add user error");
    }
    strcpy(next->name,name);
    strcpy(next->host,host);
    next->s_addr = s_addr;
    next->pre = cur;
    cur->next = next;
    return next;
}
void userlist_ds_item_delete(IPMSG_USER* head,int s_addr){
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