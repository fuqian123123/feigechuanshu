#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdbool.h>
#include <pwd.h>
#include <sys/utsname.h>
#include "../def.h"
#include "../ipmsg.h"
#include "../my-tcp/tcp-op.h"
#include "../my-udp/udp-op.h"
#include "../user/user-op.h"

void username_get(void);
void my_info_init(void);
void menu_print(void);
void listen_input(void);
void main_init(void);
void main_exit(void);
void help_print(void);
#endif
