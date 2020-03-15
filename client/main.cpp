#include <stdio.h>

#include "ConnectionManager.h"
#include "Message.h"
#include "MessagePackage.h"

char * MSOCKET = "first";
char * mainTag = "main";

int main(int argc, char *argv[]){
	

	ConnectionManager * manager = ConnectionManager::getInstance();

	//manager->createMSocket( MSOCKET, (char*) "luas.lianjia.com:9132");
//	manager->createMSocket( MSOCKET, (char*) "luas-test-tcp.lianjia.com:8082");
	manager->createMSocket( MSOCKET, (char*) "127.0.0.1:8080");


	// manager->createMSocket( "seconde", (char*) "127.0.0.1:8080");

	// for (int m=0 ;m < 2 ; m++){
		
	// 	//char *socketName = (char*) malloc(sizeof(char) * 20) ;
	// 	//char *socketName = new char[20];
	// 	char socketName[20];
	// 	sprintf(socketName, "socketId-%d",m);

	// 	printf("address  socktName : %ld \n",&socketName );

	// 	manager->createMSocket( socketName, (char*) "127.0.0.1:8080");

	// }

	char str[1024];
	//scanf("%s", str);
	while(scanf("%s", str)){
		printf("输入了 : %s \n", str);

		MSocketWraper* socketWraper = manager -> getMSocket(MSOCKET);
		if(socketWraper == nullptr){
			slog(mainTag, (char*)"连接不可用，请重新建！") ;
			return -1;
		}

		TextMessage* msg = new TextMessage(str);
		socketWraper->sendMessage((MessagePackage*)msg);
		//  int number = 16;
		//  char a[10];
		//  memcpy(a, &number, sizeof(number));
		//  socketWraper-> writeData(a, 10);

	}
	
	return 0;
}
