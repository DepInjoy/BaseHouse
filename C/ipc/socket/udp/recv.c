#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define RECV_NET_WORK_PORT 9000
#define BUF_SIZE 256

static int _socket_recv_fd = -1;

static int init_udp()
{
	int nOptval = 1;
    struct sockaddr_in RSockAddr;
    RSockAddr.sin_port = htons(RECV_NET_WORK_PORT);
    RSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    RSockAddr.sin_family=AF_INET;
    if((_socket_recv_fd = socket(PF_INET,SOCK_DGRAM,0)) < 0){
    	return -1;
    }
	setsockopt(_socket_recv_fd, SOL_SOCKET, SO_REUSEADDR,
			(const void *)&nOptval , sizeof(int));
    bind(_socket_recv_fd, (struct sockaddr *)&RSockAddr,
			sizeof(RSockAddr));
    return 0;
}
static void udp_recv_thread(void)
{
    int timeout = 10;
    int nreads  = 0;
    char buf[BUF_SIZE] = {0};
    struct pollfd fds[1];
    fds[0].fd = _socket_recv_fd;
    fds[0].events = POLLIN;
	struct sockaddr_in sockAddr_for_recv;
    int addrlen = sizeof(struct sockaddr_in);
    while(1){	
		if(poll(&fds[0], 1, timeout) > 0){
	    	if (fds[0].revents & POLLIN){
				nreads = recvfrom(_socket_recv_fd, buf,
					sizeof(buf), 0, 
					(struct sockaddr *)&sockAddr_for_recv,
					(socklen_t *)&addrlen);
				printf("received data %d ",nreads);
				int i = 0;
				for(i = 0;i < nreads;i++)
					printf("%d ",buf[i]);
				printf("\n");
			}
		}
		usleep(10000);
	}
}

static void start_udp_recv_task(void)
{
	pthread_t pid = 0;
	pthread_create(&pid,NULL,(void *)&udp_recv_thread,NULL);
	pthread_detach(pid);
}
int main(int argc,char *argv[])
{
	int iRet = init_udp();
	if(iRet != 0){
		printf("init_udp failed\n");
		return -1;
	}
	start_udp_recv_task();
	while(1){
		usleep(10000);
	}
	return 0;
	
}
