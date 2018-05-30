#ifndef _FILE_OP_H_
#define _FILE_OP_H_

#include "../util/util.h"

void file_transfer_init(int type,char* name,int num,long pkgnum,long size,long ltime,char* user,char* s_addr);
void file_transfer_add(int type,char* name,int num,long pkgnum,long size,long ltime,char* user,char* s_addr);
void file_transfer_printall(int type);
void file_transfer_send_file(char* s_addr);
void file_transfer_clear(int type);
void file_transfer_ready(int type,char* s_addr,char* filename);
void file_transfer_launch(int type,long num,long pkgnum,char* s_addr);
#endif