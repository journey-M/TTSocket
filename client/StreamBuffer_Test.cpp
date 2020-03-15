#include "StreamBuffer.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){

    StreamBuffer * sBuffer = new StreamBuffer(270);

    char* DATA_T = (char*) "1234567890abcdefghi ";

    bool ret;
    for (int i=0; i< 20 ;i++){
        ret = sBuffer->writeEnd(DATA_T, 20);
        if(ret){
            printf("插入成功! \n");
        }else
        {
            printf("插入失败 ! \n");
        }
        
    }

		char toRead[30];
		srand(time(NULL));
    while (sBuffer ->size() > 20)
    {
        memset(toRead, '\0', 30);
        /* code */
       int num = rand()%31;
			 //printf("number is : %d \n", num);
       sBuffer->readHead(toRead, num);
       printf("%s \n", &toRead);
       
    }
    


    char read[25];

  //  scanf("%s", &read);

}
