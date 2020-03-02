#ifndef __CONNECTION_MANAGER_H__
#define __CONNECTION_MANAGER_H__

#include "SocketWraper.h"
#include <vector>
#include <string.h>
#include "SLog.h"
#include <pthread.h>
#include <unistd.h>

class ConnectionManager {

    private:
		char* TAG = (char*)"ConnectionManager";

        static ConnectionManager instance;
//        static std::vector<MSocketWraper*> mSocketList;
//        static pthread_t thread_receive;

        ConnectionManager(){
        }


    public:
        ~ConnectionManager();

        static ConnectionManager* getInstance(){
            return &ConnectionManager::instance;
        }

        MSocketWraper* createMSocket(char *socketName, char* url);

        MSocketWraper* getMSocket(char *socketName);

        
};

#endif