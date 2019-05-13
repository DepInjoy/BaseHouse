#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_SIZE 512

/*
    father send data and child get data
*/
int child_read_pipe(int fd)
{
    char rbuf[BUF_SIZE] = {0};
    int nread = 0;
    fcntl(fd,F_SETFL,O_NONBLOCK);
    while(1){
        nread = read(fd,rbuf,sizeof(rbuf));
        if(nread > 0){
            fprintf(stdout,"read %d bytes data %d %d %d %d\n",nread,rbuf[0],rbuf[1],rbuf[2],rbuf[3]);
        }
        usleep(500000);
    }
    return 0;
}

int father_write_pipe(int fd,char *buf,int nwrite)
{
    char wbuf[BUF_SIZE] = {0};
    int i = 0;
    fcntl(fd,F_SETFL,O_NONBLOCK);
    while(1){
        memcpy(wbuf,&i,sizeof(int));
        write(fd,wbuf,nwrite);
        fprintf(stdout,"write data %d %d %d %d i %d\n",wbuf[0],wbuf[1],wbuf[2],wbuf[3],i);
        i = i + 1;
        usleep(500000);
    }
    return 0;
}


int main(int argc,char *argv[])
{
    int pid;
    int fd[2];
    if(pipe(fd) < 0){
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0){
        perror("fork failed\n");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        close(fd[1]);
        child_read_pipe(fd[0]);//then read
    }else{
        close(fd[0]);
        father_write_pipe(fd[1],NULL,4);// write open first
    }

    return 0;
}
