#ifndef _FILE_H_
#define _FILE_H_

#include "../util/util.h"

void file_transfer_init(int type,char* name,int num,long pkgnum,long size,long ltime,char* user);
void file_transfer_add(int type,char* name,int num,long pkgnum,long size,long ltime,char* user);
void file_transfer_printall(int type);
#endif