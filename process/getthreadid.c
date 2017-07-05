#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//Linux中，每个进程有一个pid，类型pid_t，由getpid()取得。Linux下的POSIX线程也有一个id，类型 pthread_t，由pthread_self()取得，该id由线程库维护，其id空间是各个进程独立的（即不同进程中的线程可能有相同的id）。Linux中的POSIX线程库实现的线程其实也是一个进程（LWP），只是该进程与主进程（启动线程的进程）共享一些资源而已，比如代码段，数据段等。
// 有时候我们可能需要知道线程的真实pid。比如进程P1要向另外一个进程P2中的某个线程发送信号时，既不能使用P2的pid，更不能使用线程的pthread id，而只能使用该线程的真实pid，称为tid。
// 有一个函数gettid()可以得到tid，但glibc并没有实现该函数，只能通过Linux的系统调用syscall来获取。

int main(int argc, char *argv[])
{
     pid_t tid;

     tid = syscall(SYS_gettid);
     printf("tid : %d\n",tid);
     
     sleep(50);
     //tid = syscall(SYS_tgkill, getpid(), tid, SIGHUP);
     //printf("tid : %d ...\n",tid);
}


