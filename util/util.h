#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/utsname.h>
#include "../def.h"
#include "../ipmsg.h"
#include "../my-ds/ds-op.h"
#include "../my-tcp/tcp-op.h"
#include "../my-udp/udp-op.h"
#include "../user/user.h"

#define COM_SIZ 80
#define USERNAME_SIZ 20
#define HOSTNAME_SIZ 256
#define REALNAME_SIZ 50
#define CHAT_SIZ 128

#define FILELIST_SEND_TYPE 0
#define FILELIST_RECE_TYPE 1

void username_get(void);
void my_info_init(void);
void menu_print(void);
void listen_input(void);
void main_init(void);
void main_exit(void);
extern char USERNAME[USERNAME_SIZ];
extern char MYHOSTNAME[HOSTNAME_SIZ];
extern char REALNAME[REALNAME_SIZ];
#endif
