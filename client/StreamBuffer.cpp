#include "StreamBuffer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
 StreamBuffer::StreamBuffer(int size)
 {
   if(size <= 0){
       slog(TAG, "create StreamBuffer errer size =", size);
       assert("create StreamBuffer errer size ");
    }
    streamRing = new struct BufferRing(size);
 }
 
 StreamBuffer::~StreamBuffer()
 {
     if(streamRing){
         delete streamRing->data;
         delete streamRing;
     }
     
 }


bool StreamBuffer::writeEnd(char * data, int len){
    if(len + this->size() > streamRing->size){
        return false;
    }
    if(streamRing->size - streamRing->tail >= len){
        memcpy(&streamRing->data[streamRing->tail], data, len);
    }else
    {
        //如果尾部在边界位置，则分两次拷贝
        int firstLen = streamRing->size - streamRing->tail;
        int second = len - firstLen;
        memcpy(&streamRing->data[streamRing->tail], data, firstLen);
        memcpy(&streamRing->data[0], &data[firstLen], second);
    }
    
    streamRing->tail = (streamRing->tail + len) % streamRing->size;

    return true;
}

bool StreamBuffer::popHead( char*a , int len){
    return readHead( a , len, true);
}

bool StreamBuffer::peekHead( char a[], int size){
    return readHead(a, size, false) ;
}

bool StreamBuffer::dropHead(int len){
    if(len > this->size()){
        return false;
    } 
    streamRing->head = (streamRing->head +len)% streamRing->size;
    return true;
}

bool StreamBuffer::readHead( char*a , int len, bool move){
    if(len > this->size()){
        return false;
    }
    //如果碰到边界位置，则分两次读取
    if(streamRing->size -streamRing->head > len){
        memcpy(a, &streamRing->data[streamRing->head],len);
    }else{
        int firstLen = streamRing->size - streamRing->head;
        int second = len - firstLen;
        memcpy(a, &streamRing->data[streamRing->head], firstLen);
        memcpy(&a[firstLen], &streamRing->data[0], second);
    }

    if(move){
        streamRing->head = (streamRing->head +len)% streamRing->size;
    }
    
    return true;
}

int StreamBuffer::size(){
    return (streamRing->tail - streamRing->head + streamRing->size) % streamRing->size;
}



