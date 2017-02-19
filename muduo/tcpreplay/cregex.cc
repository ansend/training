/*  write by ansendong
 *  */
 
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

#include <muduo/base/Logging.h>
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

void dump_peer_map(std::map<std::string, Peer*>& );

const int times = 1000000;


int main(int argc,char** argv)
{
    signal(SIGPIPE, SIG_IGN);

    EventLoopThread loop_thread;
    EventLoop * loop = loop_thread.startLoop();

    // since in c/c++ compiler  '\' is use for escape charactor, 
    // so the parrter is firstly compiled during c/c++ compile.
    // "\\" will firstly compile into \, so  \\d will compiled into \d, 
    // a pure \, will be \\\\.
    // there is 2 phase compiler for regex regression.

    char tcpflow_header[512]="[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+:\\s";
    char conlength[128]="Content-Length:\\s[0-9]\\n\\r";
    
    char msg[1024];
    int n;
  
    size_t leftbyte = 0;
    size_t availbyte = sizeof(msg) - leftbyte;

    while ( n= fread(msg + leftbyte, 1, availbyte, stdin))
    {

       char * msg1 = msg + 128;
       leftbyte =  msg  + leftbyte + n - msg1 ;
       memmove(msg1, msg, leftbyte);
       availbyte = sizeof(msg) - leftbyte;

    
        
       printf("%d char read from stdin \n", n);
       //printf("show the mesage read as string %s\n", msg);
 
    }
    


    
    fread(msg, 1, sizeof(msg), stdin);

    const size_t nmatch = 1;
    regmatch_t pm[1];

    const size_t conmatch = 2;
    regmatch_t conm[2];
    int z ;
    regex_t reg;
    regex_t reg_tcpflow;
    regex_t reg_con;

    printf("input strings:\n");
    timeval end,start;
    gettimeofday(&start,NULL);
    regcomp(&reg_tcpflow,tcpflow_header,REG_EXTENDED);
    regcomp(&reg_con, conlength, REG_EXTENDED);

    char * msgref = msg;
    std::string last_ip;
    std::string last_port;

    char * last_body_begin = NULL;
    char * last_body_end = NULL;

    while((z= regexec(&reg_tcpflow, msgref, nmatch, pm, REG_NOTBOL))  != REG_NOMATCH)
        {
            if(z==REG_NOMATCH)
            {
                printf("no matched, exit loop\n");
            }
            else
            {
                printf("%d match found \n", nmatch);
	        printf("match start is: %d\n",  pm[0].rm_so);
		printf("match  end  is: %d\n",  pm[0].rm_eo);

		for(int jj=pm[0].rm_so; jj<pm[0].rm_eo; jj++)
		{
		    //putchar(msgref[jj]);
		    //printf("\n");
		}
                
		std::string mark (msgref+pm[0].rm_so, msgref+pm[0].rm_eo);
		//printf("matched string is 2 %s\n", mark.c_str());
                
		boost::trim(mark);
               
                std::vector <string> strvec;
                string dim = "-";
		int sockfd = 0;		
                boost::split(strvec, mark, boost::is_any_of(dim));

		Peer* curr_peer; // pointer to curring handling peer
                cout << " size of the vector: " << strvec.size() << endl;
                
		for (vector<string>::iterator it = strvec.begin() + 1; it != strvec.end(); ++it)
		{
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
			
                        last_ip = str_ip;
			last_port = str_port;

                        std::map<std::string,Peer*>::iterator itm;
                        itm = Peer::peer_map.find(str_ip);

                        if (itm == Peer::peer_map.end()){ // no peer ip addr find in existing address book.
	
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

                        }else {

                               sockfd = itm->second->fd;
			       curr_peer = itm->second;
			}

		}

                if(NULL != last_body_begin)
                {
                        last_body_end = msgref + pm[0].rm_so;
                        std::string last_body(last_body_begin, last_body_end);
                        //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());

                        last_body.erase(last_body.end() - 1); //remove the '\n' which is not part of http request.
                        //printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());
                        
                        //char * writable = new char[last_body.size()];
			//std::copy(last_body.begin(), last_body.end(), writable);
			//write(sockfd, last_body.c_str(), last_body.size()); 
                        
                        // save the conent to buffer for following parse the request and filtering function.
			curr_peer->out_buffer.append(last_body.c_str(), last_body.size()); 

                 }else
                 {
                         //do nothing 

                 }

                last_body_begin = msgref + pm[0].rm_eo;
	 	msgref = msgref + pm[0].rm_eo;

            }
                
        }

    printf ("end of loop\n");
    gettimeofday(&end,NULL);
    uint time = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
    cout<<time/1000000<<" s and "<<time%1000000<<" us."<<endl;
 
    printf(" dump the peer map\n");   
    
   dump_peer_map(Peer::peer_map);
   
    return 0 ;
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

void dump_peer_map(std::map<std::string, Peer*> & pmap)
{
   for (std::map<std::string,Peer*>::iterator it=pmap.begin(); it!=pmap.end(); ++it)
   {  std::cout <<"complete strign"<< it->first << '\n';
      it->second->dump();
   }
    
}


