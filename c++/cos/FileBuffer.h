
// Author: Dongtc
//
// This is a public header file, it must only include public header files.

#ifndef BUFFER_H_
#define BUFFER_H_


#include <algorithm>
#include <vector>
#include <string>

#include <assert.h>
#include <string.h>
//#include <unistd.h>  // ssize_t


using namespace std;
/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class Buffer 
{
    public:
    static const size_t kInitialSize = 1024;
  
    explicit Buffer(size_t initialSize = kInitialSize)
      : buffer_(initialSize),
        read_index_(0),
        write_index_(0)
    {
        assert(readble_bytes() == 0);
        assert(writable_bytes() == initialSize);
    }
  
    // implicit copy-ctor, move-ctor, dtor and assignment are fine
    // NOTE: implicit move-ctor is added in g++ 4.6
  
    void swap(Buffer& rhs)
    {
        buffer_.swap(rhs.buffer_);
        std::swap(read_index_, rhs.read_index_);
        std::swap(write_index_, rhs.write_index_);
    }
  
    size_t readble_bytes() const
    { return write_index_ - read_index_; }
  
    size_t writable_bytes() const
    { return buffer_.size() - write_index_; }
  
    const char* peek() const
    { return begin() + read_index_; }
  
    // retrieve returns void, to prevent
    // string str(retrieve(readble_bytes()), readble_bytes());
    // the evaluation of two functions are unspecified
    void retrieve(size_t len)
    {
        assert(len <= readble_bytes());
        if (len < readble_bytes())
        {
            read_index_ += len;
        }
        else
        {
            retrieve_all();
        }
    }
  
    void retrieve_until(const char* end)
    {
        assert(peek() <= end);
        assert(end <= begin_write());
        retrieve(end - peek());
    }
  
    void retrieve_all()
    {
        read_index_  = 0;
        write_index_ = 0;
    }
  
    string retrieve_all_as_string()
    {
        return retrieve_as_string(readble_bytes());
    }
    
    string read_all_as_string()
    {
        return read_as_string(readble_bytes());
    }

    string retrieve_as_string(size_t len)
    {
        assert(len <= readble_bytes());
        string result(peek(), len);
        retrieve(len);
        return result;
    }
  

    string read_as_string(size_t len)
    {
        assert(len <= readble_bytes());
        string result(peek(), len);
        return result;
    }

    void append(const char* /*restrict*/ data, size_t len)
    {
        ensure_writeable_bytes(len);
        std::copy(data, data+len, begin_write());
        has_written(len);
    }
  
    void append(const void* /*restrict*/ data, size_t len)
    {
        append(static_cast<const char*>(data), len);
    }
  
    void ensure_writeable_bytes(size_t len)
    {
      if (writable_bytes() < len)
      {
        make_space(len);
      }
      assert(writable_bytes() >= len);
    }
  
    char* begin_write()
    { return begin() + write_index_; }
  
    const char* begin_write() const
    { return begin() + write_index_; }
  
    void has_written(size_t len)
    {
      assert(len <= writable_bytes());
      write_index_ += len;
    }
  
    void unwrite(size_t len)
    {
      assert(len <= readble_bytes());
      write_index_ -= len;
    }
  
    size_t internal_capacity() const
    {
      return buffer_.capacity();
    }
  
    /// Read data directly into buffer.
    ///
    /// It may implement with readv(2)
    /// @return result of read(2), @c errno is saved
    ssize_t read_fd(int fd, int* savedErrno);
  
   private:
  
    char* begin()
    { return &*buffer_.begin(); }
  
    const char* begin() const
    { return &*buffer_.begin(); }
  
    void make_space(size_t len)
    {
        if (writable_bytes()  < len )
        {
            // FIXME: move readable data
            buffer_.resize(write_index_+len);
        }
        else
        {
            // move readable data to the front, make space inside buffer
            size_t readable = readble_bytes();
            std::copy(begin()+read_index_,
                      begin()+write_index_,
                      begin());
            read_index_     = 0;
            write_index_    = read_index_ + readable;
            assert(readable == readble_bytes());
        }
    }
  
   private:
    std::vector<char>  buffer_;
    size_t             read_index_;
    size_t             write_index_;
  
    static const char  kCRLF[];
  };
  
  
#endif  // BUFFER_H
