#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define SEND_NET_WORK_PORT 9000
#define BUF_SIZE 256

static int _socket_send_fd = -1;

static int init_udp()
{
	int nOptval = 1;
    struct sockaddr_in RSockAddr;
    RSockAddr.sin_port = htons(SEND_NET_WORK_PORT);
    RSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    RSockAddr.sin_family=AF_INET;
    if((_socket_send_fd = socket(PF_INET,SOCK_DGRAM,0)) < 0){
    	return -1;
    }
	setsockopt(_socket_send_fd, SOL_SOCKET,
			SO_REUSEADDR,(const void *)&nOptval , sizeof(int));
#if 0
	bind(_socket_recv_fd, (struct sockaddr *)&RSockAddr,
			sizeof(RSockAddr));
#endif
	return 0;
}
int send_udp(char *buf,int len)
{
	struct sockaddr_in sockAddr_for_send;
    if(_socket_send_fd < 0){
		printf("socket is not init or failede\n");
		return -1;
    }
    int iRet = sendto(_socket_send_fd,buf,len,0,
			(struct sockaddr *)&sockAddr_for_send,
			sizeof(struct sockaddr_in));
	if(iRet != len){
		printf("send failed %d %s\n",errno,strerror(errno));
	}
	return iRet;
}
int main(int argc,char *argv[])
{
	char buf[16] = {1,2,3,4};
	int iRet = init_udp();
	if(iRet != 0){
		printf("init udp for sending failed\n");
		return -1;
	}
	while(1){
		iRet = send_udp(buf,4);
		if(iRet != 4){
			printf("send failed %d!\n",iRet);
			usleep(10000);
		}
	}
	return 0;
}
