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

#include "peer.h"
#include "flowbuffer.h"

using namespace std;
using namespace boost;
using namespace muduo::net;

#ifndef TCP_FLOW_H
#define TCP_FLOW_H

void dump_peer_map(std::map<std::string, Peer*> & pmap);

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

       Init();
  
    }
    ~TcpFlow(){}
    void Init();
    
    void StartRun() 
    {
        while (1) 
        { 
            //cregex can not assign the length of string to be parsed.
	    //so it there may be string overflow if it don't match the pattern
	    //in given string length. how to avoid.
	    if(buf.readFd(0) <= 0 )
	    {
		printf("at end of the buffer\n");
                break;
	    }
            //only the buffer is almost full, equal or more than BUF_SIZE -8
            //then start the parse 
            while (buf.get_readable() < BUF_SIZE - 8)
            {
                buf.readFd(0);
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
            printf(" after read fd the buf is %s\n", tmp2.c_str());   
            Peer* curr_peer; // pointer to curring handling peer
            const char * bufptr = buf.peek();

	    printf("********************buf pointer is %p \n ", bufptr);
            int32_t z;
            while(1) 
 	    {
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
                    printf("%d match found \n", nmatch);
	            printf("match start is: %lu\n",  pm[0].rm_so);
		    printf("match  end  is: %lu\n",  pm[0].rm_eo);
                
	            std::string mark (bufptr+pm[0].rm_so, bufptr+pm[0].rm_eo);
                
                    boost::trim(mark);
               
                    std::vector <string> strvec;
                    string dim = "-";
		    int sockfd = 0;		
                    boost::split(strvec, mark, boost::is_any_of(dim));

                    cout << " size of the vector: " << strvec.size() << endl;
                
                    vector<string>::iterator it = strvec.begin() + 1; 
		    
    		    //cout << "string" << *it << endl;
                    std::string str_h(*it);
		    str_h.erase(str_h.end()-1);
		    cout<< "string erased \n" << str_h <<endl;

                    std::size_t found = str_h.find_last_of(".");
                    std::string str_ip = str_h.substr(0,found);
                    std::string str_port = str_h.substr(found+1);
                    std::cout << " ip: " << str_h.substr(0,found) << '\n';
                    std::cout << " port: " << str_h.substr(found+1) << '\n'; 
                    int n_port = std::atoi( str_port.c_str() );
		
                    std::map<std::string,Peer*>::iterator itm;
                    itm = Peer::peer_map.find(str_ip);
                    if (itm == Peer::peer_map.end())
                    { // no peer ip addr find in existing address book.
	
	 		/*struct sockaddr_in servaddr;
			int  n_send;
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			bzero(&servaddr, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			inet_pton(AF_INET, "127.0.0.001", &servaddr.sin_addr);
			servaddr.sin_port = htons(8000);
	
			connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); */
                        sockfd = 10;
	
	                Peer * p = new Peer(sockfd, str_ip, n_port, loop);

	                curr_peer = p;

                        Peer::peer_map.insert(std::pair<std::string, Peer*> (str_ip, p));

                    }else{

                        sockfd = itm->second->fd;
                        curr_peer = itm->second;
                    }
		 printf(" it's here to begin \n");

                 if(NULL != last_body_begin)
                 {
                    printf(" last body begin is not null\n");
                    last_body_end = bufptr + pm[0].rm_so;
		    printf(" current start offset is %d \n ", int(pm[0].rm_so));
		    printf(" last body begin %p \n", last_body_begin);
		    printf(" last body end %p \n ", last_body_end);
                    std::string last_body(last_body_begin, last_body_end);
                    //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());

                    last_body.erase(last_body.end() - 1); //remove the '\n' which is not part of http request.
                    //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());
                        
                    //char * writable = new char[last_body.size()];
                    //std::copy(last_body.begin(), last_body.end(), writable);
                    //write(sockfd, last_body.c_str(), last_body.size()); 
                        
                    // save the conent to buffer for following parse the request and filtering function.
                    curr_peer->append(last_body.c_str(), last_body.size()); 

                }else
                {
                    //do nothing 
                }

                last_body_begin = bufptr + pm[0].rm_eo;
	 	bufptr = bufptr + pm[0].rm_eo; 

		printf("************ after all the buf ptr is  %p \n ", bufptr);

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
    const char * last_body_end ;

    EventLoop * loop;

};

#endif
