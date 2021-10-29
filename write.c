#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#define BUFES PIPE_BUF

int main()
{
	int fd,n,i;
	char buf[BUFES];
	time_t tp;
	printf("I am %d\n",getpid());	//说明进程的id
	if((fd=open("fifo1",O_WRONLY))<0){	//以只写方式打开一个FIFO，管道名为fifo1 
		printf("Open failed!\n");
		exit(1);
	} 
	for(i=0;i<10;i++){
		time(&tp);		//取系统当前时间
		n=sprintf(buf,"write_fifo %d sends NO.%d",getpid(),i);
				//使用sprintf 函数向 buf 中格式化写入进程id和当前为第几次传送 
		printf("Send msg:%s\n",buf);
		if((write(fd,buf,n+1))<0){
			//写入到FIFO中
			printf("Write failed!\n");
			close(fd);	//关闭FIFO文件 
			exit(1); 
		} 
		sleep(3);	//进入睡眠3秒，便于观察 
	} 
	close(fd);		//关闭FIFO文件
	exit(0);
}