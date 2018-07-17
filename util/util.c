#include "util.h"

char USERNAME[USERNAME_SIZ] = "";
char MYHOSTNAME[HOSTNAME_SIZ] = "";
char REALNAME[REALNAME_SIZ] = "";
static const char command1[] = "ls";
static const char command2[] = "sendto";
static const char command3[] = "sendfile";
static const char command4[] = "getfile";
static const char command5[] = "exit";
static const char command6[] = "help";

void username_get(void){
    int u_len,flag = 0;
    do{
        printf("Please entry your username(1~20):");
        fgets(USERNAME,USERNAME_SIZ,stdin);
        u_len = strlen(USERNAME);
        if(u_len <= 1){
            printf("Your username cannot be empty,try again.\n");
        }
        else if(USERNAME[u_len-1] == '\n'){
            USERNAME[u_len-1] = '\0';
            flag = 1;
        }
        else{
            USERNAME[USERNAME_SIZ] = '\0';
            flag = 1;
        }
    }while(!flag);
    fflush(stdin);
}
void my_info_init(void){
    gethostname(MYHOSTNAME,sizeof(MYHOSTNAME));
    struct passwd* pwd;
    pwd = getpwuid(getuid());
    strcpy(REALNAME,pwd->pw_name);
}
void menu_print(void){
    fprintf(stdout,"\t****************************************\n");
    printf("\t\t%-20s\n","1.chat");
    printf("\t\t%-20s\n","2.tranfer file");
    printf("\t\t%-20s\n","3.help");
    fprintf(stdout,"\t****************************************\n");
}
void help_print(void){
    fprintf(stdout,"\t****************************************\n");
    printf("usage: \n");
    printf("\tls -u\t\t\t\t\t%-50s\n","show user list");
    printf("\tls -f\t\t\t\t\t%-50s\n","show file list");
    printf("\tsendto x.x.x.x\t\t\t\t%-50s\n","entry 'quit' to get back to main menu");
    printf("\tsendfile x.x.x.x\t\t\t%-50s\n","entry 'quit' to get back to main menu");
    printf("\tgetfile [filename] x.x.x.x\t\t%-50s\n","filename must be absolute file path");
    printf("\texit\t\t\t\t\t%-50s\n","exit program");
    fprintf(stdout,"\t****************************************\n");
}
void main_init(void){
    int ret;
    pthread_t id1,id2,id3;
    ret = pthread_create(&id1,NULL,(void*)udp_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    
    ret = pthread_create(&id2,NULL,(void*)tcp_rece,NULL);
    if(ret){
        perror("id2 created failed!");
    }
    pthread_detach(id2);
    sleep(1);

    br_entry_send();
    menu_print();

    ret = pthread_create(&id3,NULL,(void*)listen_input,NULL);
    if(ret){
        perror("id3 created failed!");
    }
    pthread_detach(id3);
    
}
void main_exit(void){
    br_exit_send();
    user_clear();
    file_transfer_clear(FILELIST_RECE_TYPE);
}
void listen_input(void){
    char buffer[COM_SIZ];
    setbuf(stdin,NULL);
    while(1){
        printf("\t%-20s\n\t","Please entry your command:");
        fgets(buffer,COM_SIZ,stdin);
        if(buffer[strlen(buffer)-1] == '\n')
            buffer[strlen(buffer)-1] = '\0';
        //show userlist
        if(!strncmp(buffer,command1,2)){
            char* para = strstr(buffer,"-");
            if(para){
                if(!strcmp(para,"-u"))
                    user_printall();
                else if(!strcmp(para,"-f"))
                    file_transfer_printall(FILELIST_RECE_TYPE);
            }
        }
        //chat with sb.
        else if(!strncmp(buffer,command2,strlen(command2))){
            char s_addr[20];
            sscanf(buffer,"%*s%s", s_addr);
            user_chat(s_addr);
        }
        //sendfile to sb.
        else if(!strncmp(buffer,command3,strlen(command3))){
            char s_addr[20];
            sscanf(buffer,"%*s%s", s_addr);
            file_transfer_send_file(s_addr);
        }
        //getfile
        else if(!strncmp(buffer,command4,strlen(command4))){
            char s_addr[20],filename[128];
            sscanf(buffer,"%*s%s%s",filename,s_addr);
            file_transfer_ready(FILELIST_RECE_TYPE,s_addr,filename);
            sleep(1);
        }
        else if(!strcmp(buffer,command5)){
            main_exit();
            exit(0);
        }
        else if(!strcmp(buffer,command6)){
            help_print();
        }
    }
}