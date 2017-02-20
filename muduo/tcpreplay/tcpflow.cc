#include "tcpflow.h"

void TcpFlow::Init()
{
    regcomp(&reg_tcpflow,tcpflow_header,REG_EXTENDED);
}

void dump_peer_map(std::map<std::string, Peer*> & pmap)
{
   for (std::map<std::string,Peer*>::iterator it=pmap.begin(); it!=pmap.end(); ++it)
   {  std::cout <<"complete strign"<< it->first << '\n';
      it->second->dump();
   }
    
}

