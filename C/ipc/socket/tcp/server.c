#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

int initserver(int type,const struct sockaddr *addr,
                    socklen_t alen,int qlen)
{
    int fd, err;

    if((fd = socket(addr->sa_family,type,0)) < 0){
        fprintf(stderr,"creat socket error %s\n",strerror(errno));
        return -1;
    }
    if(bind(fd,addr,alen) < 0){
        fprintf(stderr,"bind socket error %s\n",strerror(errno));
        goto error;
    }
    //if TCP then start to listen
    if(type == SOCK_STREAM || type == SOCK_SEQPACKET){
        //limit the max length of listened queue to qlen 
        if(listen(fd,qlen) < 0){ 
            fprintf(stderr,"listen socket error %s\n",strerror(errno));
            goto error;
        }
    }
    return fd;

error:
    err = errno;
    close(fd);
    errno = err;
    return -1;
}

 int main(int argc,char **argv)
 {
 	int listenfd,connfd;
 	struct sockaddr_in sockaddr;
 	char buff[BUFLEN];
 	int n;
 
 	memset(&sockaddr,0,sizeof(sockaddr));
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	sockaddr.sin_port = htons(10004);

 	if((listenfd = initserver(SOCK_STREAM,(struct sockaddr *) &sockaddr,
                    sizeof(struct sockaddr_in),QLEN)) < 0){
 		printf("initserver failed!\n");
 		return -1;
 	}
 	fprintf(stdout,"wait for message ...\n");
 	for(;;)
 	{
 		if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1){
 			printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
 			continue;
 		}
 		n = recv(connfd,buff,BUFLEN,0);
 		buff[n] = '\0';
 		printf("recv msg from client:%s",buff);
 		close(connfd);
 	}
 		close(listenfd);
 }
