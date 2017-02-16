/*  write by xingming
 *  time:2012年10月19日15:51:53
 *  for: test regex
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

// include muduo head file
#include <muduo/base/Logging.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>


using namespace std;
using namespace boost;

class Peer
{
  public:
  Peer(int fdp, std::string ipp, int portp):fd(fdp),ip(ipp),port(portp){};
  int fd;
  std::string ip;
  int port;
  timeval last;

  void dump()
  {
      printf("peer fd is %d \n", fd);
      printf("peer ip is %s \n", ip.c_str());
      printf("peer port is %d \n", port);
  }
};

void dump_peer_map(std::map<std::string, Peer*>& );

const int times = 1000000;

std::map<std::string, Peer *> peer_map;

int main(int argc,char** argv)
{
   // char pattern[512]="finance\.sina\.cn|stock1\.sina\.cn|3g\.sina\.com\.cn.*(channel=finance|_finance$|ch=stock|/stock/)|dp.sina.cn/.*ch=9&";
    char pattern[512]="sina\\.";
    // since in c/c++ compiler  '\' is use for escape charactor, so the parrter is firstly compiled during c/c++ compile.
    // "\\" will firstly compile into \, so  \\d will compiled into \d,  a pure \, will be \\\\.
    // there is 2 phase compiler for regex regression.


    //tcp flow header  091.189.090.041.00080-010.000.002.015.47586:
   // char tcpflow_header[512]="\\d+\\.\\d+\\.\\d+\\.\\d+\\.\\d+-\\d+\\.\\d+\\.\\d+\\.\\d+\\.\\d+:";
    char tcpflow_header[512]="[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+:\\s";
    char msg[1024 * 1024];
    char hello[5];
    hello[0]='h';
    hello[1]='e';
    hello[2]='l';
    hello[3]='l';
    hello[4]='o';
   // hello[5]='\0';

    printf("hello array is %s \n", hello);

    int n;
    /*
    while ( n= fread(msg, 1, sizeof(msg), stdin))
    {

       printf("%d char read from stdin \n", n);
       printf("show the mesage read as string %s\n", msg);
 
    }
    */


     fread(msg, 1, sizeof(msg), stdin);
     printf("show the mesage read as string %s\n", msg);

    const size_t nmatch = 10;
    regmatch_t pm[10];
    int z ;
    regex_t reg;
    regex_t reg1;
    char lbuf[256]="set",rbuf[256];
    char buf[3][256] = {"finance.sina.cn/google.comsina.com/baidu.com.google.sina.cndddddddddddddddddddddda.sdfasdfeoasdfnahsfonadsdf",
                    "3g.com.sina.cn.google.com.dddddddddddsina.comddddddddddddddddddddddddddddddddddddddddddbaidu.com.sina.egooooooooo",
                    "http://3g.sina.com.cn/google.baiduchansina.comnel=financegogo.sjdfaposif;lasdjf.asdofjas;dfjaiel.sdfaosidfj"};
    printf("input strings:\n");
    timeval end,start;
    gettimeofday(&start,NULL);
    regcomp(&reg,pattern,REG_EXTENDED);
    regcomp(&reg1,tcpflow_header,REG_EXTENDED);

//    for(int i = 0 ; i < times; ++i)
 //   {
          // for(int j = 0 ; j < 3; ++j)
    char * msgref = msg;
    std::string last_ip;
    std::string last_port;

    char * last_body_begin = NULL;
    char * last_body_end = NULL;
    while((z= regexec(&reg1,msgref,nmatch,pm,REG_NOTBOL))  != REG_NOMATCH)
        {
            //z = regexec(&reg,buf[j],nmatch,pm,REG_NOTBOL);
            //z= regexec(&reg1,msg,nmatch,pm,REG_NOTBOL);
	    //z= regexec(&reg1,msgref,nmatch,pm,REG_NOTBOL)
            if(z==REG_NOMATCH)
                printf("no match\n");
            else
            {
                printf("ok\n");
                printf("%d match found \n", nmatch);
	        printf("match start is: %d\n",  pm[0].rm_so);
		printf("match  end  is: %d\n",  pm[0].rm_eo);

		/*for(int jj=pm[0].rm_so; jj<pm[0].rm_eo; jj++)
		{
		    //putchar(buf[j][jj]);
		    putchar(msgref[jj]);
		    printf("\n");
		}*/
		//printf("matched string is %s\n", msg + pm[i].rm_eo);

                
		std::string tmp (msgref+pm[0].rm_so, msgref+pm[0].rm_eo);
		printf("matched string is 2 %s\n", tmp.c_str());
                
                printf("length of string before tim %d \n", tmp.size());
		boost::trim(tmp);
		printf("length of string after tim %d\n", tmp.length());
		printf("timed string is %s\n", tmp.c_str());
               
                std::vector <string> strvec;
                string conn = "-";
		int sockfd = 0;		
                boost::split(strvec, tmp, boost::is_any_of(conn));

                cout << " size of the vector: " << strvec.size() << endl;
		for (vector<string>::iterator it = strvec.begin() + 1; it != strvec.end(); ++it)
		{
    			cout << "string" << *it << endl;
                        std::string str_h(*it);
			str_h.erase(str_h.end()-1);
			cout<< "string erased" << str_h <<endl;

			std::cout << "Splitting: " << str_h << '\n';
			std::size_t found = str_h.find_last_of(".");
			std::string str_ip = str_h.substr(0,found);
			std::string str_port = str_h.substr(found+1);
			std::cout << " ip: " << str_h.substr(0,found) << '\n';
			std::cout << " port: " << str_h.substr(found+1) << '\n'; 

			int num1 = std::atoi( str_port.c_str() );

			printf("port as int is %d\n", num1);
			last_ip = str_ip;
			last_port = str_port;

                        std::map<std::string,Peer*>::iterator itm;
                        itm = peer_map.find(str_h);


                        if (itm == peer_map.end()){ // no peer ip addr find in existing address book.
	
	 			struct sockaddr_in servaddr;
				int  n_send;
				sockfd = socket(AF_INET, SOCK_STREAM, 0);
				bzero(&servaddr, sizeof(servaddr));
				servaddr.sin_family = AF_INET;
				inet_pton(AF_INET, "127.0.0.001", &servaddr.sin_addr);
				servaddr.sin_port = htons(8000);
	
				connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	                        Peer * p = new Peer(sockfd, str_ip, num1);
	                        
			        peer_map.insert(std::pair<std::string, Peer*> (str_h, p));

                        }else {

                               sockfd = itm->second->fd;
                        
			}

		}

                if(NULL != last_body_begin)
                {
                        last_body_end = msgref + pm[0].rm_so;
                        std::string last_body(last_body_begin, last_body_end);
                        printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());

                        last_body.erase(last_body.end() - 1);
                        printf("length %d : last message body is %s\n",last_body.size(), last_body.c_str());
                        
                        
                        //char * writable = new char[last_body.size()];
			//std::copy(last_body.begin(), last_body.end(), writable);
			write(sockfd, last_body.c_str(), last_body.size()); 

                 }else
                 {
                         //do nothing 

                 }

                last_body_begin = msgref + pm[0].rm_eo;

		msgref = msgref + pm[0].rm_eo;

            }
                
        }
 //   }
    gettimeofday(&end,NULL);
    uint time = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
    cout<<time/1000000<<" s and "<<time%1000000<<" us."<<endl;

    dump_peer_map(peer_map);
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

