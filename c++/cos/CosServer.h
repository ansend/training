#ifndef COS_SERVER_INCLUDE_H_
#define COS_SERVER_INCLUDE_H_

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <vector>
#include <map>
#include "FileSys.h"
#include "CommandHandler.h"

using namespace std;
class CosServer
{
    public:
        CosServer(){;}
        virtual ~CosServer(){;}


        bool init(){
            init_filesys();
        }

        bool init_filesys(){
            main_f_ = NULL;
        }

    protected:


        uint32_t random(){
           
            reg_random_ = (uint32_t)::random();
            return reg_random_;
        }

        uint32_t get_random(){
        
            return reg_random_;
        }
       
        
        uint32_t set_random(){
    
            uint32_t feed = time(NULL);
            feed += getpid();
            ::srandom(feed);
        }
    
    protected:

        uint32_t                              reg_random_;
        AbsFile *                             main_f_;

};

class PsamServer : CosServer
{
    public:
        PsamServer(){;}
        virtual ~PsamServer(){;}


        virtual void Process(RpcChannel *channel, uint32_t uri, std::string & buf) {
           while (1) {
                //uint32_t uri;
                uint16_t rescode;
                //std::string buf;
        
                //if (channel->read(&uri, &rescode, &buf) != 0)
                //    break;
        
                std::map<uint32_t, _CommandHandler *>::const_iterator it = handlers_.find(uri);
                if (it != handlers_.end()) {
                    _CommandHandler *h = it->second;
                    if (!h->Process(channel, buf))
                        break;
                }
            }
        }


        //template<typename Request, typename Handler>
        //void AddCommandHandler(uint32_t uri, Handler *h, bool (Handler::*mf)(RpcChannel *, std::string&  buff)) {
        
        template<typename Request, typename Handler>
        void AddCommandHandler(uint32_t uri, Handler *h, bool (Handler::*mf)(RpcChannel *, Request&  buff)) {
            handlers_[uri] = new CommandHandler<Request, Handler>(h, mf);
        }

        bool handle_get_random(RpcChannel* chl, std::string & buff){
        
            printf(" handle get random %s \n", buff.c_str());
        }
    private:

        // MPK: master purchase key
        // DPK: derived purchase key
        // SESKEY: session key for current transaction to
        //         caculate MAC1 and verify MAC2(from Icc)
        // APPNR:  Icc card serial number in file 0015.
        // R_icc:  icc card random number(2 bytes)
        // NT_OFF_XX: icc offline transaction number(2bytes)
        // NT_TERM:   PSAM(terminal) transaction number(2bytes)
        // DPK = 3DES(MPK, APPNR)
        // SESKEY = 3DES(DPK, R_icc||NT_OFF_xx||NT_TERM)
        std::string                           MPK;

        // current des key 
        std::string                           deskey_reg_;
        std::map<uint32_t, _CommandHandler*>  handlers_;
};



#else


#endif

