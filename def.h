#ifndef _DEF_H_
#define _DEF_H_

#define COM_SIZ 80
#define USERNAME_SIZ 20
#define HOSTNAME_SIZ 256
#define REALNAME_SIZ 50
#define INPUT_SIZ 128
#define BUFFER_SIZ 1024
#define FILELIST_SEND_TYPE 0
#define FILELIST_RECE_TYPE 1

typedef unsigned int        u32;
typedef unsigned short      u16;
typedef unsigned char       u8;
typedef signed int          s32;
typedef signed short        s16;
typedef signed char         s8;
typedef float               fp32;
typedef double              fp64;

extern char USERNAME[USERNAME_SIZ];
extern char MYHOSTNAME[HOSTNAME_SIZ];
extern char REALNAME[REALNAME_SIZ];
#endif