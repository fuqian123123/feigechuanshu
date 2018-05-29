#include "util.h"

char USERNAME[USERNAME_SIZ] = "";
char MYHOSTNAME[HOSTNAME_SIZ] = "";
char REALNAME[REALNAME_SIZ] = "";
static const char command1[] = "ls";
static const char command2[] = "sendto";
static const char command3[] = "sendfile";
static const char command4[] = "getfile";
static const char command5[] = "exit";

void username_get(void){
    int u_len,flag;
    do{
        printf("Please input your username(1~20):");
        fgets(USERNAME,USERNAME_SIZ + 1,stdin);
        u_len = strlen(USERNAME);
        if(USERNAME[0] == '\n'){
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
    printf("\t\t%-20s\n","1.ls");
    printf("\t\t%-20s\n","2.sendto x.x.x.x");
    printf("\t\t%-20s\n","3.sendfile x.x.x.x");
    printf("\t\t%-20s\n","4.getfile filename x.x.x.x");
    printf("\t\t%-20s\n","5.exit");
    fprintf(stdout,"\t****************************************\n");
}
void main_init(void){
    int ret;
    pthread_t id1,id2,id3;
    ret = pthread_create(&id1,NULL,(void*)br_rece,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id1);
    ret = pthread_create(&id2,NULL,(void*)uni_rece,NULL);
    if(ret){
        perror("id2 created failed!");
    }
    pthread_detach(id2);
    sleep(1);
    br_entry_send();

    menu_print();

    ret = pthread_create(&id3,NULL,(void*)listen_input,NULL);
    if(ret){
        perror("id1 created failed!");
    }
    pthread_detach(id3);
}
void main_exit(void){
    br_exit_send();
    user_clear();
}
void listen_input(void){
    setbuf(stdin,NULL);
    while(1){
        printf("\t%-20s\n\t","Please input your command:");
        char buffer[COM_SIZ];
        fgets(buffer,COM_SIZ,stdin);
        buffer[strlen(buffer)-1] = '\0';
        fflush(stdin);
        //show userlist
        if(!strcmp(buffer,command1)){
            user_printall();
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
        else if(!strncmp(buffer,command4,strlen(command4))){

        }
        else if(!strcmp(buffer,command5)){
            main_exit();
            exit(0);
        }
    }
}