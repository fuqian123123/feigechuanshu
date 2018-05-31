#include "ds-op.h"

IPMSG_USER* userlist_ds_init(void){
    IPMSG_USER* head = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
    if(head == NULL){
        perror("userlist_ds_init init error");
    }
    return head;
}
void userlist_ds_item_add(IPMSG_USER* head,char* name,char* host,char* s_addr){
    if(head != NULL){
        IPMSG_USER* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        IPMSG_USER* next = (IPMSG_USER*)malloc(sizeof(IPMSG_USER));
        if(next == NULL){
            perror("userlist_ds_item_add error");
        }
        strcpy(next->name,name);
        strcpy(next->host,host);
        strcpy(next->s_addr,s_addr);
        next->pre = temp;
        temp->next = next;
    }
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
                temp->pre->next = NULL;
                free(temp);
                temp = NULL;
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


IPMSG_FILE* filelist_ds_init(void){
    IPMSG_FILE* head = (IPMSG_FILE*)malloc(sizeof(IPMSG_FILE));
    if(head == NULL){
        perror("filelist_ds_init error");
    }
    return head;
}
void filelist_ds_item_add(IPMSG_FILE* head,char* name,int num,long pkgnum,long size,long ltime,char* user,char* s_addr){
    if(head != NULL){
        IPMSG_FILE* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        IPMSG_FILE* next = (IPMSG_FILE*)malloc(sizeof(IPMSG_FILE));
        if(next == NULL){
            perror("filelist_ds_item_add error");
        }
        strcpy(next->name,name);
        strcpy(next->user,user);
        strcpy(next->s_addr,s_addr);
        next->num = num;
        next->pkgnum = pkgnum;
        next->size = size;
        next->ltime = ltime;

        next->pre = temp;
        temp->next = next;
    }
}
IPMSG_FILE* filelist_ds_item_delete(IPMSG_FILE* uhead,char* name){
    if(!strcmp(uhead->name,name)){
        IPMSG_FILE* new_head = uhead->next;
        free(uhead);
        uhead = NULL;
        return new_head;
    }
    IPMSG_FILE* temp = uhead;
    while(temp != NULL){
        //is not tail
        if(temp->next != NULL){
            if(!strcmp(temp->name,name)){
                temp->next->pre = temp->pre;
                temp->pre->next = temp->next;
                free(temp);
                temp = NULL;
                return uhead;
            }            
        }
        else{
            if(!strcmp(temp->name,name)){
                temp->pre->next = NULL;
                free(temp);
                temp = NULL;
                return uhead;
            }
        }
        temp = temp->next;
    }
    return uhead;
}
IPMSG_FILE* filelist_ds_item_get(IPMSG_FILE* uhead,char* filename){
        IPMSG_FILE* temp = uhead;
        while(temp != NULL){
            if(!strcmp(temp->name,filename)){
                return temp;
            }
            temp = temp->next;            
        }
        return NULL;
}
void filelist_ds_destory(IPMSG_FILE* head){
    if(head != NULL){
        IPMSG_FILE* tail = head->next;
        while(tail != NULL){
            IPMSG_FILE* temp = tail;
            tail = tail->next;
            free(temp);
            temp = NULL;
        }
        free(head);
        head = NULL;
    }
}

IPMSG_FILE* filelist_search(IPMSG_FILE* uhead,long num,long pkgnum){
    IPMSG_FILE* temp = uhead;
    while(temp != NULL){
        if(temp->num == num && temp->pkgnum == pkgnum){
            return temp;
        }
        temp = temp->next;            
    }
    return NULL;
}