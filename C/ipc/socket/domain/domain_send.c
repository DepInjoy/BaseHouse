#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h> 

#define DOMAIN_BUF_SIZE 2048
#define SO_PATH_NAME "/tmp/so.domainsocket"
#define APP_PATH_NAME "/tmp/app.domainsocket"
 
static int domain_socket_fd = -1;

int init_domain_socket(void)
{
	int reuse = 1;
	int domain_socket_fd = -1;
	struct sockaddr_un domain_addr;	 
	domain_socket_fd = socket(AF_UNIX,SOCK_DGRAM,0);
	if(domain_socket_fd == -1){
		perror("socket");
		return -1;
	}
	memset(&domain_addr,0,sizeof(struct sockaddr_un));
	if((setsockopt(domain_socket_fd, SOL_SOCKET,
			SO_REUSEADDR, &reuse, sizeof(reuse))) < 0){
		perror("domain setsockopt error");		
		return -1;
	}
    unlink(APP_PATH_NAME);
	domain_addr.sun_family = AF_UNIX;
	strcpy(domain_addr.sun_path,APP_PATH_NAME);
	if((bind(domain_socket_fd,(struct sockaddr *)&domain_addr,
			sizeof(domain_addr))) < 0){
		perror("domain bind");
		close(domain_socket_fd);
		unlink(APP_PATH_NAME);
		return -1;
	}
	return domain_socket_fd;
}
static void domain_recv_thread(void)
{
    char buf[DOMAIN_BUF_SIZE] = {0};
    while(1){
		int timeout = 10;
    	struct pollfd fds[1];
    	fds[0].fd = domain_socket_fd;
    	fds[0].events = POLLIN;
		if (poll(&fds[0], 1, timeout) > 0){
	    	if (fds[0].revents & POLLIN){
        		int nreads = recvfrom(domain_socket_fd,buf,DOMAIN_BUF_SIZE,0,NULL,NULL);
        		if(nreads == -1){  
           		 	printf("recvfrom,%d %s\n",errno,strerror(errno));
        		} 
        		printf("recv data:");
        		int i = 0;
        		for(i = 0;i < nreads;i++)
            		printf("%d ",buf[i]);
        		printf("\n");            
    		}
		}
	}  
    close(domain_socket_fd);  
    unlink(APP_PATH_NAME);  
    return ;
}

static void start_domain_recv_task(void)
{
	pthread_t tid = 0;
	pthread_create(&tid,NULL,(void *)&domain_recv_thread,NULL);
	pthread_detach(tid);
}

static int domain_send_data(char *buf,int nbytes)
{
	int nsends = 0;
	struct sockaddr_un domain_addr;
	domain_addr.sun_family = AF_UNIX;
	strcpy(domain_addr.sun_path,SO_PATH_NAME);	 
	if((nsends = sendto(domain_socket_fd,buf,nbytes,0,(struct sockaddr*)&domain_addr,
			sizeof(domain_addr))) == -1){
			perror("domain send");	
	}
	return nsends;
}
void main(void)
{
	if((domain_socket_fd = init_domain_socket()) < 0){
		printf("init domain socket failed\n");	
	}
	start_domain_recv_task();
	while(1){
		char buf[DOMAIN_BUF_SIZE] = {0};
		int i = 0;
		for(i = 0;i < 16;i++)
			buf[i] = i;
		if(domain_send_data(buf,16) == -1){
			printf("send data failed\n");
		}
		usleep(10000);	
	}
}
