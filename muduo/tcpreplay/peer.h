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


class Peer
{
  public:
  Peer(int fdp, std::string ipp, int portp, EventLoop* loop ):fd(fdp),ip(ipp),port(portp),wheel(10)
  {
     //client = new TcpClient(loop,InetAddress(ipp.c_str(), portp), ipp.c_str());
     client = new TcpClient(loop,InetAddress("127.0.0.1", 8000), ipp.c_str());
     //client->setConnectionCallback(clientConnectionCallback);
     client->setConnectionCallback(boost::bind(&Peer::clientConnectionCallback, this, _1));
     client->setMessageCallback(boost::bind(&Peer::clientMessageCallback, this, _1, _2, _3));
     
     client->connect();
     loop->runEvery(1.0, boost::bind(&TimingWheel::onTimer, &wheel));
  }
/*
  void init()
  {
     client->setConnectionCallback(boost::bind(&Peer::clientConnectionCallback, this, _1));
     client->setMessageCallback(boost::bind(&Peer::clientMessageCallback, this, _1, _2, _3));

     client->connect();
     loop->runEvery(1.0, boost::bind(&TimingWheel::onTimer, &wheel));

  }
*/
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


  TcpClient* client;
  TcpConnectionPtr tptr;
  timeval last;
  
  Buffer out_buffer; // buffer for out put target sock fd.

  static std::map<std::string,Peer*> peer_map;

  boost::mutex buf_mutex; 
  TimingWheel wheel;
};

#endif
