
#include "SLog.h"

void slog(char*clz ,char *err){
	printf("%s:%s \n",clz, err);
}

void slog(char*clz ,char *err, int value){
	printf("%s:%s %d \n",clz, err, value);
}

void slog(char*clz ,char *err, char* value){
	printf("%s:%s %s \n",clz, err, value);
}