#ifndef RPC_CHANNEL_INCLUDE_H_
#define RPC_CHANNEL_INCLUDE_H_

//#include "packet.h"
//#include "socketinc.h"
//#include "rc4_helper.h"


class RpcChannel {
public:
    RpcChannel(): sock_(-1), connected_(false) {}
/*
    RpcChannel(int sock): sock_(sock), connected_(true) {
        setTimeout(10 * 1000);
    }

    virtual ~RpcChannel() { close(); }

    int getRemoteAddress(std::string *ip, int *port);

    int open(const char *addr);

    int open(const std::string &ip, int port);

    void close();

    int write(const char *str) {
        return write(str, strlen(str));
    }

    int write(const char *data, size_t len);

    int read(char *data, size_t *len);

    int read(uint32_t *uri, uint16_t *rescode, std::string *buf);

    int readMessage(uint32_t expect_uri, uint16_t *rescode, sox::Marshallable *msg);

    int writeMessage(uint32_t uri, uint16_t rescode, const sox::Marshallable &msg);

    void setTimeout(int milliseconds);

    int getLastErrno();

    bool checkEOF(int timeout);
*/
private:
    //sox::BlockBuffer<sox::def_block_alloc_16k, 65536> recv_buf_;

    int sock_;
    bool connected_;
};


#else

#endif

