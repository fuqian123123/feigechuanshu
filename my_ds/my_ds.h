#ifndef _DS_H_
#define _DS_H_
//用户信息结构体
typedef struct userlist
{
	char name[20];	//用户名
	char host[20];	//主机名
	int s_addr;		//IP地址(32位网络字节序)
	struct userlist *next;
	struct userlist *pre;
}IPMSG_USER;

//文件信息结构体
typedef struct filelist
{
	char name[50];//文件名
	int num;// 文件序号
	long pkgnum;//包编号
	long size;//文件大小
	long ltime;//最后修改时间
	char user[10];	//发送者用户名
	struct filelist *next;
}IPMSG_FILE;

#endif
