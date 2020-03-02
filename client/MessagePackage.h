#ifndef  __MESSAGE_PACKAGE_H__
#define  __MESSAGE_PACKAGE_H__

#include <string.h>
#include "SLog.h"
/**
 *  消息体格式， 20字节head 
 *   1~4 字节  保留
 *   5～8 字节  版本 
 *   9~12 字节  命令号   cmdid
 *   13~16     消息序列号  请求和响应的序列号要保持一致
 *   17~20     消息body长度     
 * 
 **/ 

struct Head
{
    /* data */
    unsigned int start = 0;
    unsigned int version;
    unsigned int comdId;
    unsigned int seq = 0;
    unsigned int bodyLen;
};


class MessagePackage
{
private:
    
    char* TAG = (char*) "MessagePackage";

    struct Head head;

    /* data */
    char * body;

    char* buffer;

    void buildHeader();    

public:
    MessagePackage(/* args */);

    ~MessagePackage();

    int package();

    void unPackage();
    
    const void setBody(char *mbody);

    char* getBuffer();

    virtual const int getClientVersion(){};
    
    virtual const int getCmdId(){};
    

};


#endif