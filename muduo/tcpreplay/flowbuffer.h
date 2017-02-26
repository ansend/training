#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#ifndef FLOW_BUFFER_H
#define FLOW_BUFFER_H
#define BUF_SIZE 1024 * 2

class FlowBuffer
{

    public:
    FlowBuffer() 
    {
        writeinx = buf;
        readable = 0;
        writeable = BUF_SIZE; 
    }

    ~FlowBuffer(){}

    size_t readFd(int fd)
    {
        //dump();
        size_t n = read(fd, writeinx, writeable);  
	printf(" this time read %d byte\n ", n);
        writeinx = writeinx + n;
        writeable = writeable -n;
        readable = readable + n;
	//dump();
	return n;
    }

    char * retrieve(const char * src)
    {      
        assert(writeinx >= src); // make sure the src is valid.
        readable = writeinx - src;
        writeinx = buf + readable;
        writeable = buf + BUF_SIZE - writeinx;
        
        memmove(buf, src, readable);

        return  writeinx;
    }

    char * retrieve(size_t n);
    size_t get_readable()
    {
        return readable;
    }
    const char * peek()
    {
        return buf;
    }

    const char * get_writeinx()
    {
        return writeinx;
    }

    void dump()
    {
        printf("size is %d\n ", BUF_SIZE);
	printf("readable is %d\n ", readable);
	printf("writeable is %d\n", writeable);
    }   

    private:

    char buf[BUF_SIZE]; 
    char * writeinx;
    size_t  writeable;
    size_t  readable;
};

#endif
