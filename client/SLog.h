#ifndef __S_LOG__H__
#define __S_LOG__H__
#include <stdio.h>
#include <unistd.h>


void slog(char*clz ,char *err);


void slog(char*clz ,char *err, int value);


void slog(char*clz ,char *err, char* value);



#endif