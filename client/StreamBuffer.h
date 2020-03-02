#ifndef __STREAM_BUFFER_H__
#define __STREAM_BUFFER_H__

#include <string.h> 
#include "SLog.h"

struct BufferRing{

    unsigned int head;
    unsigned int tail;
    unsigned int size;
    char* data;

    BufferRing(int len){
        head = 0;
        tail = 0;       //链表元素结尾的下一个指针
        size = len;
        data = new char[len];
    }
};

 class StreamBuffer
 {
 private:
     /* data */
     char* TAG = (char*) "StreamBuffer";

     struct BufferRing *streamRing = nullptr;
 public:
     StreamBuffer(int size);
     ~StreamBuffer();

    
     bool writeEnd(char * data, int size);

     bool readHead( char a[], int size);
     
     bool readHead( char a[], int size, bool move);

     bool peekHead( char a[], int size);

     int size();

 };
 
 
#endif