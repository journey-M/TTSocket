#ifndef __BLOCK_QUEUE_H__
#define __BLOCK_QUEUE_H__


#include <pthread.h>




class BlockQueue 
{
private:
    /* data */

    // pthread_mutex_getprioceiling();
    pthread_mutex_t mutex;


public:
    BlockQueue (/* args */);
    ~BlockQueue ();
};





#endif