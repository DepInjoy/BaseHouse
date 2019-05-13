#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RECV_NET_WORK_PORT 9000
#define BUF_SIZE 256
#define POLL_NUM 5

static void recv_udp_thread(void)
{
	char buff[BUF_SIZE] = {0};
	struct epoll_event collections[5],obj;
    int _socket_recv_fd;
	int index = 0, fdSum;
	int nOptval = 1;
    int epollHandle = epoll_create(POLL_NUM);
	struct sockaddr_in recv_addr;
    if((_socket_recv_fd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        perror("socket");
		return;
    }
    memset(&recv_addr,0,sizeof(struct sockaddr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(RECV_NET_WORK_PORT);
    recv_addr.sin_addr.s_addr = INADDR_ANY;
	setsockopt(_socket_recv_fd, SOL_SOCKET, SO_REUSEADDR,(const void *)&nOptval , sizeof(int));
    if(bind(_socket_recv_fd, (struct sockaddr *)&recv_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		return;
	}
    obj.data.fd = _socket_recv_fd;
    obj.events =  EPOLLIN;
    //add the listen
    epoll_ctl(epollHandle, EPOLL_CTL_ADD, _socket_recv_fd, &obj);
	while(1){
        fdSum = epoll_wait(epollHandle, collections,5, -1);
        for(index = 0; index < fdSum; index++){
            if(collections[index].events&EPOLLIN){
                int nreads = recvfrom(_socket_recv_fd, buff,sizeof(buff), 0, NULL,NULL);
				if(nreads < 0){
					printf("recv failed %d %s\n",errno,strerror(errno));
					close(collections[index].data.fd);
				}else{
					printf("received %d data ",nreads);
					int i = 0;
					for(i = 0;i < nreads;i++)
						printf("%d ",buff[i]);
					printf("\n");
				}
			}
		}

	}
	if(_socket_recv_fd > 0)
		close(_socket_recv_fd);
}
static void start_recv_task(void)
{
	pthread_t tid = 0;
	pthread_create(&tid,NULL,(void *)&recv_udp_thread,NULL);
	pthread_detach(tid);
}

int main(int argc,char *argv[])
{
	start_recv_task();
	while(1){
		usleep(1000000);
	}
	return 0;
}
