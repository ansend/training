#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <muduo/net/TcpServer.h>


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

#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/InetAddress.h>

#include <stdio.h>

#include "timingwheel.h"

#ifndef PEER_H
#define PEER_H
//using namespace muduo;
using namespace muduo::net;
using namespace boost;
//void clientConnectionCallback(const TcpConnectionPtr& conn);

class TimingWheel;
class Peer
{
  public:
  Peer(int fdp, std::string ipp, int portp, EventLoop* loop );
/*
  void init()
  {
     client->setConnectionCallback(boost::bind(&Peer::clientConnectionCallback, this, _1));
     client->setMessageCallback(boost::bind(&Peer::clientMessageCallback, this, _1, _2, _3));

     client->connect();
     loop->runEvery(1.0, boost::bind(&TimingWheel::onTimer, &wheel));

  }
*/

 virtual  ~Peer();
  void dump();
  void append(const char*, size_t);
  void set_tcpconn(TcpConnectionPtr conn);

  void clientConnectionCallback(const TcpConnectionPtr& conn);
  void clientMessageCallback(const TcpConnectionPtr& conn,
                             Buffer* buffer,
                             muduo::Timestamp receiveTime);
  public:
  int fd;
  std::string ip;
  int port;

  static std::map<std::string,weak_ptr<Peer> > peer_map;
  static TimingWheel wheel;

  TcpClient* client;
  TcpConnectionPtr tptr;
  timeval last;
  
  Buffer out_buffer; // buffer for out put target sock fd.

  boost::mutex buf_mutex; 

    
  //char req_pattern[124] = "GET\\s|POST\\s";
  char * req_pattern ;
  size_t reqmatch ;
  regmatch_t reqm[1];
  regex_t reg_req;


};

#endif
