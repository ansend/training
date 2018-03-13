#ifndef COMMAND_HANDLER_H_
#define COMMAND_HANDLER_H_

#include "stdio.h"
#include "../common/RpcChannel.h"

class _CommandHandler {
public:
    virtual ~_CommandHandler() {}

    virtual bool Process(RpcChannel *channel, std::string &buf) = 0;
};

template<typename Request, typename Handler>
class CommandHandler: public _CommandHandler {
public:
    //typedef bool (Handler::*Method)(RpcChannel *, const Request *);
    //explicit CommandHandler(Handler *handler, Method method): h_(handler), mf_(method) {}
    
    
    typedef bool (Handler::*Method)(RpcChannel *, std::string & buf);
    explicit CommandHandler(Handler *handler, Method method): h_(handler), mf_(method) {}

    virtual ~CommandHandler() {}

    virtual bool Process(RpcChannel *channel, Request &buf) {

        // ansen just skip packet codec.  handler do the codec itself.
        
        //Request req;
        //sox::Unpack p(buf.data(), buf.size());
        /*
        try {
            req.unmarshal(p);
        } catch (sox::UnpackError &e) {
            return false;
        }

        */

        return (h_->*mf_)(channel, buf);
    }

private:
    Handler *h_;
    Method mf_;
};


#else


#endif
