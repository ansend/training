#include "peer.h"
#include <boost/bind.hpp>

std::map<std::string,weak_ptr<Peer> > Peer::peer_map;

TimingWheel Peer::wheel(10);


Peer::Peer(int fdp, std::string ipp, int portp, EventLoop* loop ):fd(fdp),ip(ipp),port(portp)
{
     //client = new TcpClient(loop,InetAddress(ipp.c_str(), portp), ipp.c_str());
     client = new TcpClient(loop,InetAddress("127.0.0.1", 2007), ipp.c_str());
     //client->setConnectionCallback(clientConnectionCallback);
     client->setConnectionCallback(boost::bind(&Peer::clientConnectionCallback, this, _1));
     client->setMessageCallback(boost::bind(&Peer::clientMessageCallback, this, _1, _2, _3));

         printf("here in peers custructor we call  client connection \n");
     client->connect();
     //loop->runEvery(10, boost::bind(&TimingWheel::onTimer, &wheel));
           
         req_pattern = "GET\\s|POST\\s|DELETE\\s";
         reqmatch = 1;
         regcomp(&reg_req, req_pattern, REG_EXTENDED);
}

Peer::~Peer()
{
     client->disconnect();
         printf("descurtor peer\n");
         delete client;
         regfree (&reg_req);

}


void Peer::set_tcpconn(TcpConnectionPtr conn)
{
     tptr = conn;
}

void Peer::append(const char* target, size_t n)
{
    boost::mutex::scoped_lock lock(buf_mutex);
    out_buffer.append(target, n);
}

void Peer::dump()
{
    //printf("peer fd is %d  peer ip is %s, peer port is %d\n", fd, ip.c_str(), port);
    std::string tmp(out_buffer.peek(), out_buffer.peek()+ out_buffer.readableBytes());
    printf("peer's out buffer inernal capacity is ############## %d \n ", out_buffer.internalCapacity());
    //printf("peer 's output buffer is %s \n", tmp.c_str());

    
    //char req_pattern[124] = "GET\\s|POST\\s";
    /*char req_pattern[124] = "GET\\s|POST\\s|DELETE\\s";
    const size_t reqmatch = 1;
    regmatch_t reqm[1];
    regex_t reg_req;
    regcomp(&reg_req, req_pattern, REG_EXTENDED); */
    int z ;
    const char * req_begin = NULL;

    boost::mutex::scoped_lock lock(buf_mutex);

    const char * peek =  out_buffer.peek(); 

    while((z= regexec(&reg_req, peek, reqmatch, reqm, REG_NOTBOL))  != REG_NOMATCH)
    {
      if(out_buffer.readableBytes() < 2000) // left some bytes since there may no request line in the buffer.
       { 
           //printf("at the end of the buffer go out of the buffer \n");
           break;
       }   
       else
       {
           if( peek + reqm[0].rm_so > out_buffer.beginWrite()) // regex cause the buffer overflow,ignore
           {
              printf("buffer regex overflow occurs, go out \n");
                      break;
               }
          // printf("%d match found \n", reqmatch);
           
           std::string tmp1 (peek+reqm[0].rm_so, peek+reqm[0].rm_eo);
           //printf(" ansendong matched request is %s", tmp1.c_str());
           if(req_begin != NULL)
           {
              //write(fd, req_begin, peek+reqm[0].rm_so-req_begin);
              if(!tptr )
              printf("conn is empty\n");
                  else
              tptr->send(req_begin, peek+reqm[0].rm_so-req_begin);
              //write(fd, tmp1.c_str(), tmp1.size());

              std::string tmp (req_begin, peek+reqm[0].rm_so-req_begin);
             // printf("ansendong ansen  matched request is %s\n", tmp.c_str());
              
              out_buffer.retrieveUntil(peek+reqm[0].rm_so);
              
           }
           req_begin = peek+reqm[0].rm_so;
            
           peek = peek + reqm[0].rm_eo;

           std::string tmp2(out_buffer.peek(), out_buffer.peek()+ out_buffer.readableBytes());
           //printf("peer's out buffer size is %d \n ", out_buffer.readableBytes());
           //printf("peer 's output buffer is %s \n", tmp2.c_str());
       } 

    }


} 


void Peer::clientMessageCallback(const TcpConnectionPtr& conn,
                           Buffer* buffer,
                           muduo::Timestamp receiveTime)
{

    std::string connname = conn->name();
    std::size_t found = connname.find_first_of(":");
    std::string tname = connname.substr(0,found); 
    std::map<std::string,weak_ptr<Peer> >::iterator itm;
    itm = Peer::peer_map.find(tname);
    printf(" connection name is %s \n", tname.c_str());
    if (itm != Peer::peer_map.end()){ // no peer ip addr find in existing address book.
       
       //Peer::wheel.update(itm->second);
      // printf("update the reference of the current weak pointer\n");
        
    }else{
      printf(" no found  map client peer weak pointer \n");
    }
  // empty the buffer.
  uint32_t frameLen = 1000;
  int64_t message[2];

  while (buffer->readableBytes() > frameLen)
  {
    printf("before read in bufer %lu\n", buffer->readableBytes());
    //memcpy(message, buffer->peek(), frameLen);
    buffer->retrieve(frameLen);
    printf("after read in bufer %lu\n", buffer->internalCapacity());

  }
}

void Peer::clientConnectionCallback(const TcpConnectionPtr& conn)
{
   printf("now in the client call back functin \n");
   std::string connname = conn->name();
   std::size_t found = connname.find_first_of(":");
   std::string tname = connname.substr(0,found);
   if (conn->connected())
   {
    //clientConnection = conn;
    //TcpConnectionPtr tmp = conn;

    std::map<std::string,weak_ptr<Peer> >::iterator itm;
    itm = Peer::peer_map.find(tname);
    printf(" connection name is %s \n", tname.c_str());
    if (itm != Peer::peer_map.end()){ // no peer ip addr find in existing address book.
       
        printf("ansen found the connection name in the weak pointer list \n");
        boost::shared_ptr<Peer> item (itm->second.lock());
        if (item)
        {
           item->set_tcpconn(conn); 
           printf(" set the connection pointer to the shared pointer from week pinter\n");
        }
        
    }else{
      printf("ansen no found  map client name\n");
    }
    //conn->setTcpNoDelay(true);
    //printf("connection %s is connected \n ", conn->name();
  }
  else
  {
    printf("now close connection\n");

        //here no need the remove the weak_ptr in the peer map.
        //the tcpflow thread will detected the weak pointer is null
        //and remove the connection.

    //clientConnection.reset();
   // std::map<std::string,weak_ptr<Peer> >::iterator itm;
    //itm = Peer::peer_map.find(tname);

    //if (itm == Peer::peer_map.end()){ // no peer ip addr find in existing address book.
        //itm->second->tptr->reset();
     //   Peer::peer_map.erase(itm);
    // }

  }
}

