#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>

#define COM_SIZ 80
#define UESRNAME_SIZ 20

void username_get(void);
void menu_print(void);
void listen_input(void);
void main_init(void);
void main_exit(void);
extern char USERNAME[UESRNAME_SIZ];
#endif
