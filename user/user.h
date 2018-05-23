#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include "../my-ds/ds-op.h"

void user_init(char* name,char* host,char* s_addr);
void user_entry(char* name,char* host,char* s_addr);
void user_exit(char* s_addr);
void user_printall(void);
void user_clear(void);
int user_is_existed(char* s_addr);
#endif