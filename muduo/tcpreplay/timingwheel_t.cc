#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>


#include "timingwheel_t.h"

using namespace muduo;
using namespace muduo::net;

template <typename TT>
TimingWheel <TT> ::TimingWheel(int idleSeconds)
  :bucklist_(idleSeconds)
{
  bucklist_.resize(idleSeconds);
  dumpBuckets();
}

template <typename TT>
void TimingWheel<TT>::insert(const boost::shared_ptr<TT>& entry)
{
    bucklist_.back().insert(entry);
   
}

template <typename TT>
void TimingWheel<TT>::update(const boost::weak_ptr<TT>& weakentry)
{

     boost::shared_ptr<TT> entry(weakentry.lock());
     if (entry)
     {
       bucklist_.back().insert(entry);
       dumpBuckets();
     }

}

template <typename TT>
void TimingWheel<TT>::onTimer()
{
  bucklist_.push_back(Bucket());
  dumpBuckets();
}

template <typename TT>
void TimingWheel<TT>::dumpBuckets() const
{
  LOG_INFO << "size = " << bucklist_.size();
  int idx = 0;
  for (typename TimingWheel<TT>::BucketList::const_iterator bucketI = bucklist_.begin();
      bucketI != bucklist_.end();
      ++bucketI, ++idx)
  {
    const Bucket& bucket = *bucketI;
    printf("[%d] len = %zd : ", idx, bucket.size());
    for (typename Bucket::const_iterator it = bucket.begin();
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


