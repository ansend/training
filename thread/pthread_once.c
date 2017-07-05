/*
*
* once_run()函数仅执行一次，且究竟在哪个线程中执行是不定的，尽管pthread_once(&once,once_run)出现在两个线程中
*/

#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

pthread_once_t  once=PTHREAD_ONCE_INIT;

// actually, in linux one thread is a LWP, so we can using a system call to get the pid of the LWP.
int get_thread_id()
{
     pid_t tid;
     tid = syscall(SYS_gettid);
     printf("pid of LWP in thread context, tid : %d\n",tid);
     return tid;

}

void    once_run(void)
{
        printf("once_run in thread %d\n",pthread_self());
}
void * child1(void *arg)
{
        int tid=pthread_self();
        printf("thread %d enter\n",tid);
        get_thread_id();
        pthread_once(&once,once_run);
        printf("thread %d returns\n",tid);
}
void * child2(void *arg)
{
        int tid=pthread_self();
        printf("thread %d enter\n",tid);
        get_thread_id();
        pthread_once(&once,once_run);
        printf("thread %d returns\n",tid);
}
int main(void)
{
        pthread_t tid1,tid2;
        printf("hello\n");
        pthread_create(&tid1,NULL,child1,NULL);
        pthread_create(&tid2,NULL,child2,NULL);
        sleep(20);
        printf("main thread exit\n");
        return 0;
}
