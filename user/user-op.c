#include "user-op.h"

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
//chat with sb.
void user_chat(char* s_addr){
    printf("\tNow chat with %s:\n",s_addr);
    char buffer[INPUT_SIZ],send_msg[BUFFER_SIZ];
    while(1){
        fgets(buffer,INPUT_SIZ,stdin);
        if(buffer[strlen(buffer)-1] == '\n')
            buffer[strlen(buffer)-1] = '\0';
        if(strncmp(buffer,"quit",4)){
            sprintf(send_msg,"%u:%ld:%s:%s:%u:%s",
            (u32)IPMSG_VERSION,(long int)time(NULL),REALNAME,MYHOSTNAME,(u32)IPMSG_SENDMSG,buffer);
            uni_msg_send(s_addr,send_msg);
        }
        else{
            fflush(stdin);
            break;
        }
    }
}
//check user existed 
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
        //if username is too long,hide some chars
        if(strlen(temp->name) > 15){
            char username[20];
            char ellipsis[3] = "...";
            strncpy(username,temp->name,12);
            username[12] = '\0';
            strcat(username,ellipsis);
            username[15] = '\0';
            printf("\t%-20s%-20s%-20s",username,temp->host,temp->s_addr);
        }
        else{
            printf("\t%-20s%-20s%-20s",temp->name,temp->host,temp->s_addr);
        }
        temp = temp->next;
        printf("\n");
    }
}
//clear all user
void user_clear(void){
   userlist_ds_destory(ul_head_addr);         
}