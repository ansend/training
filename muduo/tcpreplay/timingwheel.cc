#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>


#include "timingwheel.h"

using namespace muduo;
using namespace muduo::net;

TimingWheel::TimingWheel(int idleSeconds)
  :bucklist_(idleSeconds)
{
  bucklist_.resize(idleSeconds);
  dumpBuckets();
}

void TimingWheel::insert(const boost::shared_ptr<Peer>& entry)
{
        boost::mutex::scoped_lock lock(wheel_mutex);
    bucklist_.back().insert(entry);
   
}

void TimingWheel::update(const boost::weak_ptr<Peer>& weakentry)
{
         boost::mutex::scoped_lock lock(wheel_mutex);

     boost::shared_ptr<Peer> entry(weakentry.lock());
     if (entry)
     {
       bucklist_.back().insert(entry);
       //dumpBuckets();
     }

}

void TimingWheel::onTimer()
{
  boost::mutex::scoped_lock lock(wheel_mutex);
  bucklist_.push_back(Bucket());
  printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
  //dumpBuckets();
}

void TimingWheel::dumpBuckets() const
{
  LOG_INFO << "size = " << bucklist_.size();
  int idx = 0;
  for (BucketList::const_iterator bucketI = bucklist_.begin();
      bucketI != bucklist_.end();
      ++bucketI, ++idx)
  {
    const Bucket& bucket = *bucketI;
    printf("[%d] len = %zd : ", idx, bucket.size());
    for (Bucket::const_iterator it = bucket.begin();
        it != bucket.end();
        ++it)
    {/*
      bool connectionDead = (*it)->weakConn_.expired();
      printf("%p(%ld)%s, ", get_pointer(*it), it->use_count(),
          connectionDead ? " DEAD" : "");
                  */
    }
    puts("");
  }
}
