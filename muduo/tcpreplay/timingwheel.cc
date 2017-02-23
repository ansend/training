#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>


#include "timingwheel.h"

using namespace muduo;
using namespace muduo::net;

TimingWheel::TimingWheel(int idleSeconds)
  :connectionBuckets_(idleSeconds)
{
  connectionBuckets_.resize(idleSeconds);
  dumpConnectionBuckets();
}


void TimingWheel::onConnection(const TcpConnectionPtr& conn)
{
  LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");

  if (conn->connected())
  {
    EntryPtr entry(new Entry(conn));
    connectionBuckets_.back().insert(entry);
    dumpConnectionBuckets();
    WeakEntryPtr weakEntry(entry);
    weekPtrMap.insert(std::pair<std::string, WeakEntryPtr> (conn->name(),weakEntry));
  }
  else
  {
     std::map<std::string,WeakEntryPtr>::iterator it;
     it = weekPtrMap.find(conn->name());
     if (it != weekPtrMap.end())
     weekPtrMap.erase(it);
  }
}


void TimingWheel::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " echo " << msg.size()
           << " bytes at " << time.toString();
		   
  std::map<std::string,WeakEntryPtr>::iterator it;
  it = weekPtrMap.find(conn->name());
  if (it != weekPtrMap.end())
  { 
     EntryPtr entry(it->second.lock());
     if (entry)
     {
       connectionBuckets_.back().insert(entry);
       dumpConnectionBuckets();
     }
  }
}

void TimingWheel::onTimer()
{
  connectionBuckets_.push_back(Bucket());
  dumpConnectionBuckets();
}

void TimingWheel::dumpConnectionBuckets() const
{
  LOG_INFO << "size = " << connectionBuckets_.size();
  int idx = 0;
  for (WeakConnectionList::const_iterator bucketI = connectionBuckets_.begin();
      bucketI != connectionBuckets_.end();
      ++bucketI, ++idx)
  {
    const Bucket& bucket = *bucketI;
    printf("[%d] len = %zd : ", idx, bucket.size());
    for (Bucket::const_iterator it = bucket.begin();
        it != bucket.end();
        ++it)
    {
      bool connectionDead = (*it)->weakConn_.expired();
      printf("%p(%ld)%s, ", get_pointer(*it), it->use_count(),
          connectionDead ? " DEAD" : "");
    }
    puts("");
  }
}

