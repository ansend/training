#include "tcpflow.h"

void TcpFlow::Init()
{
    regcomp(&reg_tcpflow,tcpflow_header,REG_EXTENDED);
}

void dump_peer_map(std::map<std::string, boost::weak_ptr<Peer> > & pmap)
{
   for (std::map<std::string, boost::weak_ptr<Peer> >::iterator it=pmap.begin(); it!=pmap.end(); ++it)
   {  std::cout <<"complete strign"<< it->first << '\n';
      boost::shared_ptr<Peer> item (it->second.lock());
        if (item)
        {
           item->dump();
           printf(" set the connection pointer to the shared pointer from week pinter\n");
        }
   }
    
}

