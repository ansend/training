#ifndef TIMING_WHEEL_H 
#define TIMING_WHEEL_H
#include <muduo/net/TcpServer.h>
#include <muduo/base/Types.h>

#include <boost/circular_buffer.hpp>
#include <boost/unordered_set.hpp>
#include <boost/version.hpp>

#include <map>
#include <utility>
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

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);


  void dumpConnectionBuckets() const;

  typedef boost::weak_ptr<muduo::net::TcpConnection> WeakTcpConnectionPtr;

  struct Entry : public muduo::copyable
  {
    explicit Entry(const WeakTcpConnectionPtr& weakConn)
      : weakConn_(weakConn)
    {
    }

    ~Entry()
    {
      muduo::net::TcpConnectionPtr conn = weakConn_.lock();
      if (conn)
      {
        conn->shutdown();
       }
    }

    WeakTcpConnectionPtr weakConn_;
  };
  typedef boost::shared_ptr<Entry> EntryPtr;
  typedef boost::weak_ptr<Entry> WeakEntryPtr;
  typedef boost::unordered_set<EntryPtr> Bucket;
  typedef boost::circular_buffer<Bucket> WeakConnectionList;
  
  std::map<std::string, WeakEntryPtr> weekPtrMap;

  WeakConnectionList connectionBuckets_;
};

#endif
