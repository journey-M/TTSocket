#ifndef __M_SOCKET_WRAPER_H__
#define __M_SOCKET_WRAPER_H__

#include"SLog.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "MessagePackage.h"
#include "StreamBuffer.h"
#include <vector>

class MSocketWraper {

	private:
		char* TAG = (char*)"MSocketWraper";
		
		char* socketName;
		int fd_socket;
		struct sockaddr_in sockaddr;
		StreamBuffer* bufferStream;

		
		void (*onClose)(const char*);
		void (*onMessage)(int cmdId, const char*, int size);


	public:
		static const int INIT_SUCCESS = 0x00;
		static const int INIT_INVALIDATE_URL = 0x01;
		static const int INIT_SOCKET_CREATER_ERROR = 0x02;

		//connect
		static const int CONNECT_SUCCESS = 0x00;
		static const int CONNECT_ERROR = 0x01;

		bool connected = false;


		MSocketWraper(char *name );
		
		~MSocketWraper();

		int init(const char* url, void (*onRceive)(void* data));	

		int initAddress(const char* url);
		
		int connect();

		int close();
		
		int writeData(char* data , int size);

		void receiveData(char* data, int size);
	
		char* getSocketName();

		int getSocketFd();

		void sendMessage(MessagePackage* msgPkg);

		std::vector<MessagePackage *>* trigleReceive();
	
};


#endif
