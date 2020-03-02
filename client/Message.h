#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "MessagePackage.h"

#define CLIENT_VERSION  0x01;
#define CMD_ID_HEART_BEAT 0x06;

class TextMessage:MessagePackage
{
private:

    /* data */

public:
    TextMessage(char* body){
        this->setBody(body);
    }

    ~TextMessage(){

    }


    const int getClientVersion(){
        return CLIENT_VERSION;
    }

    const int getCmdId(){
        return CMD_ID_HEART_BEAT;
    }
    
};

#endif