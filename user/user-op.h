#ifndef _USER_OP_H_
#define _USER_OP_H_

void user_init(char* name,char* host,char* s_addr);
void user_entry(char* name,char* host,char* s_addr);
void user_exit(char* s_addr);
void user_chat(char* s_addr);
void user_printall(void);
void user_clear(void);
int user_is_existed(char* s_addr);
#endif