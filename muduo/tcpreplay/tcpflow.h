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

#include <fcntl.h>

#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

#include <muduo/net/EventLoopThread.h>

#include "peer.h"
#include "flowbuffer.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>

using namespace std;
using namespace boost;
using namespace muduo::net;

#ifndef TCP_FLOW_H
#define TCP_FLOW_H

void dump_peer_map(std::map<std::string, boost::weak_ptr<Peer> > & pmap);

class TcpFlow
{
    public:

    TcpFlow(EventLoop * lp)
    {
        loop = lp;
        tcpflow_header = "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+:\\s";
        conlength = "Content-Length:\\s[0-9]\\n\\r";
        nmatch = 1;
        last_body_begin = NULL;
        last_body_end = NULL;

            //loop->runEvery(5.0, boost::bind(&TimingWheel::onTimer, &Peer::wheel));

       Init();
  
    }
    ~TcpFlow(){}
    void Init();
    
    void StartRun() 
    {

        struct sockaddr_in servaddr;
        int ncfd, n;

        ncfd = socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, "221.228.91.252", &servaddr.sin_addr);
        servaddr.sin_port = htons(8890);

        uint16_t retry = 0;
        
        while(connect(ncfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            retry ++;
            if(retry == 3)
            {
                printf("can not connect to host and exit\n");
                printf("%s\n", strerror(errno));
                exit(1);
            }
        }

                int tfd = open("./testlog", O_RDWR);
            if (tfd == -1)
                {
                perror("open file testlog");
                close(tfd);
                    return ;
            }

        while (1) 
        { 
            //cregex can not assign the length of string to be parsed.
            //so it there may be string overflow if it don't match the pattern
            //in given string length. how to avoid.
            if(buf.readFd(ncfd) <= 0 )
            {
                printf("at end of the buffer\n");
        //      printf(" the byets inf buffer %lu \n", buf.get_readable());
                break;
            }
            //only the buffer is almost full, equal or more than BUF_SIZE -8
            //then start the parse 
            while (buf.get_readable() < BUF_SIZE - 8)
            {
                buf.readFd(ncfd);
                printf("the left string  is to short for match , go out\n");
            //.if (buf.get_readable() >= 4090)
            //  break;
            }
            /*
            if (buf.get_readable() < BUF_SIZE)
            {
                printf("the left string  is to short for match , go out\n");
                break;
            } */
            std::string tmp2(buf.peek(), buf.get_readable());
           // printf(" after read fd the buf is %s\n", tmp2.c_str());   
            boost::shared_ptr<Peer>  curr_peer; // pointer to curring handling peer
            const char * bufptr = buf.peek();

            //printf("********************buf pointer is %p \n ", bufptr);
            int32_t z;
            while(1) 
            {

                if(buf.get_writeinx() - bufptr < 50)
                {
                    printf("to prevent regex overflow , exit loop\n");
                    buf.retrieve(bufptr); // retrieve the flow buffer and run match again. 
                            last_body_begin = last_body_begin - (bufptr - buf.peek());
                    break;
                }

                        z= regexec(&reg_tcpflow, bufptr, nmatch, pm, REG_NOTBOL);
                if(z==REG_NOMATCH)
                {
                    printf("no matched, exit loop\n");
                    buf.retrieve(bufptr); // retrieve the flow buffer and run match again. 
                            last_body_begin = last_body_begin - (bufptr - buf.peek());

                    // last_body_begin is aslo need to move ahead. 
                    break;
                }
                else
                {
                    if(buf.get_writeinx() < bufptr + pm[0].rm_so)// here regex overflow occured go out 
                                        {
                                                 printf(" regex overflow occured here \n");
                         break;
                                        }
                    // printf("%d match found  start is %lu , end is %lu \n", nmatch, pm[0].rm_so,pm[0].rm_eo);
                        //printf("match start is: %lu\n",  pm[0].rm_so);
                            //printf("match  end  is: %lu\n",  pm[0].rm_eo);
                
                        std::string mark (bufptr+pm[0].rm_so, bufptr+pm[0].rm_eo);
                
                    boost::trim(mark);
               
                    std::vector <string> strvec;
                    string dim = "-";
                            int sockfd = 0;
                    boost::split(strvec, mark, boost::is_any_of(dim));

                   // cout << " size of the vector: " << strvec.size() << endl;
                
                    vector<string>::iterator it = strvec.begin(); 
                    
                    //cout << "string" << *it << endl;
                    std::string str_h(*it);
                            //str_h.erase(str_h.end()-1);
                    //cout<< "string erased \n" << str_h <<endl;

                    std::size_t found = str_h.find_last_of(".");
                    std::string str_ip = str_h.substr(0,found);
                    std::string str_port = str_h.substr(found+1);
                    std::cout << " ip: " << str_h.substr(0,found) << " port: " << str_h.substr(found+1)<< '\n';
                  //  std::cout << " port: " << str_h.substr(found+1) << '\n'; 
                    int n_port = std::atoi( str_port.c_str() );

                                  //printf(" it's here to begin \n");

                 if((NULL != last_body_begin) && ("" != last_ip))
                 {
                    last_body_end = bufptr + pm[0].rm_so;
                   // printf(" current start offset is %d \n ", int(pm[0].rm_so));
                   // printf(" last body begin %p \n", last_body_begin);
                   // printf(" last body end %p \n ", last_body_end);
                    std::string last_body(last_body_begin, last_body_end);
                    //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());

                    last_body.erase(last_body.end() - 1); //remove the '\n' which is not part of http request.
                    //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());
                        
                    //char * writable = new char[last_body.size()];
                    //std::copy(last_body.begin(), last_body.end(), writable);
                    //write(sockfd, last_body.c_str(), last_body.size()); 
                        
                    // save the conent to buffer for following parse the request and filtering function.
                    std::map<std::string, boost::weak_ptr<Peer> >::iterator itm;
                    itm = Peer::peer_map.find(last_ip);
                    if (itm == Peer::peer_map.end())
                    { // no peer ip addr find in existing address book.

                        sockfd = 10;

                        //Peer * p = new Peer(sockfd, str_ip, n_port, loop);
                                            printf("new a connection to 8000 from src %s\n", last_ip.c_str());
                        boost::shared_ptr<Peer> p (new Peer(sockfd, last_ip, n_port, loop));
                        boost::weak_ptr<Peer> wp (p);
                            curr_peer = p;

                        Peer::peer_map.insert(std::pair<std::string, boost::weak_ptr<Peer> > (last_ip, wp));
                        Peer::wheel.insert(p);

                    }else{

                        curr_peer = itm->second.lock();
                        //here , the shared pointer maybe timeout and have be released and the  
                        //if it's null renew a shared_pointer to the timing wheel, and save
                        //the weak pointer to the map. 
                                if(!curr_peer) 
                                {
                           //firstly remove the map item, then and a new one for the same src ip)
                           Peer::peer_map.erase(itm);
         
                           boost::shared_ptr<Peer> p (new Peer(sockfd, last_ip, n_port, loop));
                                   boost::weak_ptr<Peer> wp (p);
                                   curr_peer = p;
                                   Peer::peer_map.insert(std::pair<std::string, boost::weak_ptr<Peer> > (last_ip, wp));

                                   Peer::wheel.insert(p);
                                }

                                                curr_peer->append(last_body.c_str(), last_body.size());
                    }

                }else
                {
                    //do nothing 
                }

                last_body_begin = bufptr + pm[0].rm_eo;
                                last_ip = str_h;
                bufptr = bufptr + pm[0].rm_eo; 

                //printf("************ after all the buf ptr is  %p \n ", bufptr);

             }

            }//end of while regexe

            dump_peer_map(Peer::peer_map);
                
        }//end of read buffer

 
    }
     
    private:

    FlowBuffer buf;
 //   char tcpflow_header[512]="[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+:\\s";
 //   char conlength[128]="Content-Length:\\s[0-9]\\n\\r";
    char * tcpflow_header;
    char  * conlength;
   
    size_t nmatch ;
    regmatch_t pm[1];

    regex_t reg_tcpflow;

    const char * last_body_begin ;
        std::string last_ip;
    const char * last_body_end ;

    EventLoop * loop;

};

#endif
