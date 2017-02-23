/************************************ 
A TCP BYPASS TOOL BASED ON TCPFLOW
author: Ansen DOng
************************************/

#include <regex.h>
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <cstring>
#include <sys/time.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

#include <muduo/net/EventLoopThread.h>
using namespace std;
using namespace boost;
using namespace muduo::net;

#include "peer.h"
#include "tcpflow.h"

const char * usage= "targetIp targetPort [timeout] [packetfilterpattern] \n \
targetIp    : the target address will forward to. \
targetPort  : the target port will forward to . \ 
timeout     : the idle connection timeout in second unit . \
packetfilterpattern: packet filter pattern is a perl regular expression\
                     will filter each packet";

struct  ArgCxt
{
        std::string   targetIp;
    uint16_t      targetPort;
        uint32_t      timeout;
        std::string   packetFilterPattern;

};


void DumpArgs(const struct ArgCxt & arg)
{
   printf(" target ip:     %s\n", arg.targetIp.c_str());
   printf(" target port:   %d\n", arg.targetPort);
   printf(" timeout    :   %d\n", arg.timeout);
   printf(" packet filter: %s\n", arg.packetFilterPattern.c_str());

}

void initArg(struct ArgCxt & arg, int argc, char** argv)
{
    if (argc < 3 || strcmp(argv[1], "-h") == 0 )
        {
                printf("%s %s\n", argv[0], usage);
                exit(0);
        }

    arg.targetIp =  argv[1];
        arg.targetPort = atoi(argv[2]);

        if (argc >= 4)
                arg.timeout = atoi(argv[3]);

        if (argc >= 5)
                arg.packetFilterPattern = argv[4];

    DumpArgs(arg);
}

int main(int argc,char** argv)
{
    signal(SIGPIPE, SIG_IGN);

    struct ArgCxt arg;
    initArg(arg, argc , argv);

    EventLoopThread loop_thread;
    EventLoop * loop = loop_thread.startLoop();

    TcpFlow tflow(loop);
   
    tflow.StartRun();

}


std::string& trim(std::string &s)   
{  
    if (s.empty())   
    {  
        return s;  
    }  
  
    s.erase(0,s.find_first_not_of(" "));  
    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
} 
 
