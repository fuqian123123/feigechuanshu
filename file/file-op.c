#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "../def.h"
#include "../ipmsg.h"
#include "../my-ds/ds-op.h"

static IPMSG_FILE* fl_send_head_addr;
static IPMSG_FILE* fl_rece_head_addr;

void file_transfer_init(int type,char* name,int num,long pkgnum,long size,long ltime,char* user,char* s_addr){
    IPMSG_FILE* temp = filelist_ds_init();
    strcpy(temp->name,name);
    strcpy(temp->user,user);
    strcpy(temp->s_addr,s_addr);
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

void file_transfer_add(int type,char* name,int num,long pkgnum,long size,long ltime,char* user,char* s_addr){
    switch (type)
    {
        case FILELIST_SEND_TYPE:
            if(fl_send_head_addr != NULL){
                filelist_ds_item_add(fl_send_head_addr,name,num,pkgnum,size,ltime,user,s_addr);
            }
            else{
                file_transfer_init(FILELIST_SEND_TYPE,name,num,pkgnum,size,ltime,user,s_addr);
            }
            break;
        case FILELIST_RECE_TYPE:
            if(fl_rece_head_addr != NULL){
                filelist_ds_item_add(fl_rece_head_addr,name,num,pkgnum,size,ltime,user,s_addr);
            }
            else{
                file_transfer_init(FILELIST_RECE_TYPE,name,num,pkgnum,size,ltime,user,s_addr);
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
    printf("\t%-30s%-20s%-20s%-5s%-20s%-8s%-20s\n","filename","username","ip","num","pkgnum","size","ltime");
    while(temp != NULL){
        char buffer[128];
        struct tm* local = localtime(&temp->ltime);
        strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", local);  
        printf("\t%-30s%-20s%-20s%-5d%-20ld%-8ld%-20s",
            temp->name,temp->user,temp->s_addr,temp->num,temp->pkgnum,temp->size,buffer);
        temp = temp->next;
        printf("\n");
    }
}

void file_transfer_send_file(char* s_addr){
    printf("\tNow entry the files' absolute path you wanna transfer:\n");
    char filename[INPUT_SIZ],buffer[BUFFER_SIZ];
    int file_order_num = 0;
    long pkgnum = (long)time(NULL);

    sprintf(buffer,"%x:%ld:%s:%s:%x:\\0",
                    (u32)IPMSG_VERSION,pkgnum,USERNAME,MYHOSTNAME,
                    (u32)(IPMSG_SENDMSG|IPMSG_SENDCHECKOPT|IPMSG_FILEATTACHOPT));
    //puts(base_msg);
    while(1){
        char temp_msg[BUFFER_SIZ];
        fgets(filename,INPUT_SIZ,stdin);
        if(filename[strlen(filename)-1] == '\n')
            filename[strlen(filename)-1] = '\0';

        if(strcmp(filename,"quit")){
            struct stat buf;
            int status;
            status = stat(filename,&buf);
            if(!status){
                sprintf(temp_msg,"\\a%d:%s:%x:%x::",file_order_num,filename,(u32)buf.st_size,(u32)buf.st_mtime);
                file_transfer_add(FILELIST_SEND_TYPE,filename,file_order_num,pkgnum,
                                    (long)buf.st_size,(long)buf.st_mtime,USERNAME,"");
                strcat(buffer,temp_msg);
                file_order_num++;
            }
            else{
                printf("Please check your file name and try again.\n");
            }
        }
        else{
            uni_msg_send(s_addr,buffer);
            //fflush(stdin);
            break;
        }
    }
}

void file_transfer_clear(int type){
    switch (type)
    {
        case FILELIST_SEND_TYPE:
            filelist_ds_destory(fl_send_head_addr);
            break;
        case FILELIST_RECE_TYPE:
            filelist_ds_destory(fl_rece_head_addr);
            break;
        default:
            break;
    }
}
//rece terminal wanna transfer file
void file_transfer_ready(int type,char* s_addr,char* filename){
    char buffer[BUFFER_SIZ];
    IPMSG_FILE* temp = NULL;
    switch(type)
    {
        case FILELIST_SEND_TYPE:
            temp = filelist_ds_item_get(fl_send_head_addr,filename);
        case FILELIST_RECE_TYPE:
            temp = filelist_ds_item_get(fl_rece_head_addr,filename);
        default:
            break;
    }
    if(!temp){
        printf("\tNo such file,please check your filename.\n");
    }
    else{
        long num,pkgnum,size; 
        num = temp->num;
        pkgnum = temp->pkgnum;
        size = temp->size;
        sprintf(buffer,"%x:%ld:%s:%s:%x:%x:%x:%x",
                (u32)IPMSG_VERSION,(long int)time(NULL),REALNAME,MYHOSTNAME,
                (u32)IPMSG_GETFILEDATA,(u32)pkgnum,(u32)num,(u32)size);
        uni_msg_send(s_addr,buffer);
    }
}
//send terminal begin to transfer file
void file_transfer_launch(int type,long num,long pkgnum,char* s_addr){
    IPMSG_FILE* temp = NULL;
    switch(type){
        case FILELIST_SEND_TYPE:
            temp = filelist_search(fl_send_head_addr,num,pkgnum);
            break;
        case FILELIST_RECE_TYPE:
            temp = filelist_search(fl_rece_head_addr,num,pkgnum);
            break;
        default:
            break;
    }
    if(temp != NULL)
        tcp_send(s_addr,temp->name);
    else
        perror("\tfile_transfer_launch: filelist_search null");
}