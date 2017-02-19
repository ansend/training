#include "flowbuffer.h"

char * FlowBuffer::retrieve(size_t n)
{
   assert(readable >= n);
   readable = readable - n;
   writeinx = writeinx - n;
   writeable = writeable + n;

   memmove(buf, buf+n, readable - n);
   return  writeinx;
}
