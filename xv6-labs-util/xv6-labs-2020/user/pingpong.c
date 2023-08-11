#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int main(int argc, char *argv[]){
    int p1[2];
    int p2[2];
    pipe(p1);//创建管道
    pipe(p2);
    int pid = fork();//创建子进程，子进程会复制父进程
    if(pid == 0){
        close(p1[1]);
        close(p2[0]);      
        char son[2];       
        read(p1[0],son,1); //读取管道内容
        close(p1[0]);
        printf("%d: received ping\n",getpid());//getpid获取进程ID
        write(p2[1],"a",2);//向管道写入内容
        close(p2[1]);
    }else if(pid > 0){
        close(p1[0]);
        close(p2[1]);      
        write(p1[1],"a",2); 
        close(p1[1]);       
        char father[2];   
        read(p2[0],father,1);
        printf("%d: received pong\n",getpid());
        close(p2[0]);
    }
    exit(0);
}