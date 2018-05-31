#ifndef _UDP_OP_H
#define _UDP_OP_H

#include "../util/util.h"

int get_br_sock_fd(void);
int get_uni_sock_fd(void);
void br_send(int flag);
void br_entry_send(void);
void br_exit_send(void);
void br_rece(void);
void uni_msg_send(char* s_addr,char* msg);
void uni_answer_entry_send(char* s_addr);
void uni_rece(void);
void udp_rece(void);
#endif