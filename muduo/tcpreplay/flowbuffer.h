#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define BUF_SIZE 1024*1024

class FlowBuffer
{

    public:
    FlowBuffer() 
    {
        writeinx = buf;
        readable = 0;
        writeable = BUF_SIZE; 
    }

    ~FlowBuffer();

    size_t readFd(int fd)
    {
        size_t n = read(fd, writeinx, writeable);  
        writeinx = writeinx + n;
        writeable = writeable -n;
        readable = readable + n;
    }

    char * retrieve(const char * src)
    {       
        readable = writeinx - src;
        writeinx = buf + readable;
        writeable = buf + BUF_SIZE - writeinx;
        
        memmove(buf, src, readable);

        return  writeinx;
    }

    char * retrieve(size_t n);

    const char * peek()
    {
        return buf;
    }

    private:

    char buf[BUF_SIZE]; 
    char * writeinx;
    size_t  writeable;
    size_t  readable;
};
