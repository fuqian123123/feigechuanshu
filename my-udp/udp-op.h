#ifndef _MY_UDP_H
#define _MY_UDP_H

int get_br_sock_fd(void);
int get_uni_sock_fd(void);
void br_send(int flag);
void br_entry_send(void);
void br_exit_send(void);
void br_rece(void);
void uni_answer_entry_send(char* s_addr,int port);
void uni_rece();
#endif