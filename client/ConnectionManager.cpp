#include "ConnectionManager.h"

//初始化
ConnectionManager ConnectionManager::instance;

/**
 * 不在类中的方法做声明
 */
static void startReceiveThread();
static void *receiveingWork(void*);
static int freeInvalidateSocket();

int SELECT_POLL_TIME = 10;
static std::vector<MSocketWraper*> mSocketList;
static pthread_t thread_receive;
pthread_cond_t pcondithon = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

ConnectionManager::~ConnectionManager(){
}

MSocketWraper* ConnectionManager::createMSocket(char *socketName, char* url){

    MSocketWraper* socketWraper = new MSocketWraper(socketName);
    int ret = socketWraper->init(url, nullptr);
    if(ret != MSocketWraper::INIT_SUCCESS){
        delete socketWraper;
        return nullptr;
    }
    ret = socketWraper->connect();
    if(ret != MSocketWraper::CONNECT_SUCCESS){
        delete socketWraper;
        return nullptr;
    }
    //锁定临界值，发送signal唤醒
    pthread_mutex_lock(&mutex);
    mSocketList.push_back(socketWraper);
    pthread_cond_signal(&pcondithon);
    pthread_mutex_unlock(&mutex);
    //startThread
    startReceiveThread();
    return socketWraper;
}


MSocketWraper* ConnectionManager::getMSocket(char *socketName){

    for(int i=0; i<mSocketList.size(); i++) {
        if( strcmp (mSocketList[i]->getSocketName() , socketName) == 0){
            return mSocketList[i];
        }
    }
    return nullptr;
}

static void startReceiveThread(){
    if(thread_receive == 0){
        int ret = pthread_create(&thread_receive,NULL, receiveingWork, NULL );
        if(ret != 0) {
            slog((char*)"ConnectionManager_thread:", (char*) "thread craete error");
        }
        //需要线程等待才使用
        //pthread_join(thread_receive, NULL);
    }
}

/**
 * 所有链接的接收消息都放到这里
 **/
 static void *receiveingWork(void*){

    sleep(2);

    fd_set readSet;
	char buffer[256] = {0};

    //枷锁
    pthread_mutex_lock(&mutex);
	while(1){

        //移除断开的socket不再监听

        while (freeInvalidateSocket() == 0)
        {
            /* code */
            pthread_cond_wait(&pcondithon, &mutex);
        }
        

		FD_ZERO(&readSet);
        MSocketWraper * socketTmp;
        int fdMax = 0;
        for(int i=0; i < mSocketList.size(); i++){
            socketTmp = mSocketList[i];
            fdMax = socketTmp->getSocketFd() > fdMax ? socketTmp->getSocketFd(): fdMax;
		    FD_SET(socketTmp->getSocketFd(), &readSet);
        }

		struct timeval timeout;
		  /* 设置最大等待时间 */  
        timeout.tv_sec = SELECT_POLL_TIME;  
        timeout.tv_usec = 0;  
		int ret = select(fdMax+1, &readSet,nullptr, nullptr,  &timeout);
		if(ret == -1){
			perror(nullptr);
		}else if(ret){
            memset(buffer,'\0',256);
            for(int i=0 ;i<mSocketList.size(); i++){
                socketTmp = mSocketList[i];
                if(FD_ISSET( socketTmp->getSocketFd(),&readSet )){
                    ret = recv(socketTmp->getSocketFd(),buffer,256,0);
                    if(ret){
                        socketTmp->receiveData(buffer, ret);
                    }else {
                        slog((char*)"ConnectionManager", (char*)"receive error : ", ret );
                        socketTmp->close();
                    }
                }
            }
		}
	}

    //解锁
    pthread_mutex_unlock(&mutex);
}

//擦除去失效的socket
static int freeInvalidateSocket(){
    if(mSocketList.size() == 0){
        return 0;
    }

    for(std::vector<MSocketWraper*>::iterator it = mSocketList.begin(); it != mSocketList.end() ;){
        if((*it)->connected == false) {
            //TODO 在此处擦除是否合适，是否要重试
            slog((char*)"free--", (*it)->getSocketName());
            delete (*it);
            it = mSocketList.erase(it);
        } else
        {
            it ++;
        }
        
    }
    return mSocketList.size();
}