#include <stdio.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <stdlib.h>
 #include <netinet/in.h>
 #include <errno.h>
 #include <string.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 
 #define BUFLEN 1024
 #define MAXSLEEP 128
 
/*
 * transferable retry-connection for about 2 minutes
*/
int connect_retry(int domain, int type,int pro,
                const struct sockaddr * addr,socklen_t alen){
    int numsec,fd;
    /*try to connect with exponent backoff.*/
    for(numsec = 1;numsec <= MAXSLEEP;numsec <<= 1){
        if((fd = socket(domain,type,pro)) < 0)
            return -1;

        //connection accept
        if(connect(fd,addr,alen) == 0)
            return fd;

        close(fd);
        if(numsec <= MAXSLEEP / 2)
            sleep(numsec);
    }
    return -1;
}
 int main(int argc,char **argv)
 {
 	int socketfd;
 	char buf[BUFLEN];
 	int n;
 	struct sockaddr_in sockaddr;
 	char *servInetAddr = "127.0.0.1";
 
 	memset(&sockaddr,0,sizeof(sockaddr));
 	sockaddr.sin_family = AF_INET;
 	sockaddr.sin_port = htons(10004);
 	inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);
 	
	if((socketfd = connect_retry(AF_INET,SOCK_STREAM,0,
			(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0){
		printf("connect_retry failed!\n");
		return -1;			
	}
	fprintf(stdout,"input the message to send out\n");
 	fgets(buf,1024,stdin);
 	if((send(socketfd,buf,strlen(buf),0)) < 0){
 		printf("send mes error: %s errno : %d",strerror(errno),errno);
 		exit(0);
 	}
 	close(socketfd);
 	printf("exit\n");
 	exit(0);
 }
