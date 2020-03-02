#include <string.h>
#include "SocketWraper.h"
#include <sys/select.h>
#include <unistd.h>

#define BUFFER_SIZE  1204 * 65

MSocketWraper::MSocketWraper(char *name ){
	this->socketName = new char[strlen(name)];
	memcpy(this->socketName, name, strlen(name));
	this->bufferStream = new StreamBuffer(BUFFER_SIZE);
}
MSocketWraper::~MSocketWraper(){
	delete this->socketName;
}


int MSocketWraper::init(const char* url, void (*onRceive)(void * data)){

	if(initAddress(url) != 0) {
		return INIT_INVALIDATE_URL;
	}
	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_socket == -1){
		perror("init socket err :");
		return INIT_SOCKET_CREATER_ERROR;
	}
	
	return INIT_SUCCESS;
}


int MSocketWraper::initAddress(const char* url){
	if(!url){
		slog(TAG, (char*)"empty url");
		return -1;
	}
	int len = strnlen(url, 40);
	int index = -1;
	for(int i=0; i< len; i++){
		if(url[i] == ':'){
			index = i;
			break;
		}
	}

	//解析网络地址	
	char address [index]; 
	memset(address, '\0', index+1);
	memcpy(address, url, index);
	slog(TAG,(char*) "地址:" ,address);

	//解析网络端口
	int port = 80;
	if(index >= len -1){
		port = 80;
	}else
	{
		char portStr [len - index];
		memset(portStr, '\0', len -index);

		for(int i = 0; i< len - index ; i++){
			portStr[i] = url[index + 1+ i];
		}
		port = atoi(portStr);
	}
	slog(TAG,(char*)"端口号：", port);
	
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET; /* 主机字节序 */
	sockaddr.sin_port = htons(port); /* short, 网络字节序 */
	sockaddr.sin_addr.s_addr = inet_addr(address); 

	return 0;
}

int MSocketWraper::connect(){
	bzero(&(sockaddr.sin_zero), 8);

	int err = ::connect(fd_socket, (struct sockaddr *) & sockaddr, sizeof (sockaddr));

	slog(TAG, (char*)"连接结果: ", err);
	if(err == 0){
		slog(TAG, (char*)"连接成功！");
		// initSelectEvent();
		this->connected = true;
		return CONNECT_SUCCESS;
	}
	perror((char*)"socket连接失败：");
	return CONNECT_ERROR;
}

int MSocketWraper::close(){
	int ret = ::close(fd_socket);
	if(ret == 0){
		connected = false;
	}
	return 0;
}

int MSocketWraper::writeData(char* data, int size ){

	slog(TAG, data, size );	
	int err = send(fd_socket, data,size, 0);
	if(err == -1){
		perror((char*) "发送消息失败 :");
	}
	return 0;
}

void MSocketWraper::sendMessage(MessagePackage* msgPkg){

	int size = msgPkg->package();
	this->writeData(msgPkg -> getBuffer() ,size);
}

/**
 * in a child thread
 **/
void MSocketWraper::receiveData(char* data, int size){
	slog(socketName,  (char*)"Receive :" , data);
	bool ret = bufferStream ->writeEnd(data, size);
	if(ret){
		trigleReceive();
	}else
	{
		slog(TAG, (char*)"写入buffer失败");
	}
	
}

char* MSocketWraper::getSocketName(){
	return socketName;
}

int MSocketWraper::getSocketFd(){
	return fd_socket;
}

void MSocketWraper::trigleReceive(){

}