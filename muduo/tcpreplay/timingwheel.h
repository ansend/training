#ifndef TIMING_WHEEL_H 
#define TIMING_WHEEL_H
#include <muduo/net/TcpServer.h>
#include <muduo/base/Types.h>

#include <boost/circular_buffer.hpp>
#include <boost/unordered_set.hpp>
#include <boost/version.hpp>

#include <map>
#include <utility>

#include "peer.h"

#if BOOST_VERSION < 104700
namespace boost
{
  template <typename T>
  inline size_t hash_value(const boost::shared_ptr<T>& x)
  {
     return boost::hash_value(x.get());
  }
}
#endif

class TimingWheel
{
 public:
  TimingWheel(int idleSeconds);

  void start();

  void onTimer();

  void insert(const boost::shared_ptr<Peer>& ptr);

  void update(const boost::weak_ptr<Peer>& ptr);

  void dumpBuckets() const;


  private:
  typedef boost::shared_ptr<Peer> SharePtr;
  typedef boost::weak_ptr<Peer> WeakPtr;
  typedef boost::unordered_set<SharePtr> Bucket;
  typedef boost::circular_buffer<Bucket> BucketList;
  

  BucketList bucklist_;
  boost::mutex wheel_mutex;
};

#endif
