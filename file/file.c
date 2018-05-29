#include "file.h"

static IPMSG_FILE* fl_send_head_addr;
static IPMSG_FILE* fl_rece_head_addr;

void file_transfer_init(int type,char* name,int num,long pkgnum,long size,long ltime,char* user){
    IPMSG_FILE* temp = filelist_ds_init();
    strcpy(temp->name,name);
    strcpy(temp->user,user);
    temp->num = num;
    temp->pkgnum = pkgnum;
    temp->size = size;
    temp->ltime = ltime;
    
    switch (type)
    {
        case FILELIST_SEND_TYPE:
            fl_send_head_addr = temp;
            break;
        case FILELIST_RECE_TYPE:
            fl_rece_head_addr = temp;
            break;
        default:
            break;
    }
}

void file_transfer_add(int type,char* name,int num,long pkgnum,long size,long ltime,char* user){
    switch (type)
    {
        case FILELIST_SEND_TYPE:
            if(fl_send_head_addr != NULL){
                filelist_ds_item_add(fl_send_head_addr,name,num,pkgnum,size,ltime,user);
            }
            else{
                file_transfer_init(FILELIST_SEND_TYPE,name,num,pkgnum,size,ltime,user);
            }
            break;
        case FILELIST_RECE_TYPE:
            if(fl_rece_head_addr != NULL){
                filelist_ds_item_add(fl_rece_head_addr,name,num,pkgnum,size,ltime,user);
            }
            else{
                file_transfer_init(FILELIST_RECE_TYPE,name,num,pkgnum,size,ltime,user);
            }
            break;
        default:
            break;
    }
}

void file_transfer_printall(int type){
    IPMSG_FILE* temp = NULL;
    switch(type){
        case FILELIST_SEND_TYPE:
            temp = fl_send_head_addr;
            break;
        case FILELIST_RECE_TYPE:
            temp = fl_rece_head_addr;
            break;
        default:
            break;
    }
    printf("\t%-30s%-20s%-5s%-20s%-20s%-20s\n","filename","username","num","pkgnum","size","ltime");
    while(temp != NULL){
        printf("\t%-30s%-20s%-5d%-20ld%-20ld%-20ld",
            temp->name,temp->user,temp->num,temp->pkgnum,temp->size,temp->ltime);
        temp = temp->next;
        printf("\n");
    }
}