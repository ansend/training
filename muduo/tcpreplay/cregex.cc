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


int main(int argc,char** argv)
{
    signal(SIGPIPE, SIG_IGN);

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
 
