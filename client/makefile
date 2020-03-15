CC=g++
CFLAGS=-g  
# -std=c++11
LDFLAGS=-lpthread

main: main.o SLog.o MessagePackage.o SocketWraper.o ConnectionManager.o StreamBuffer.o 
	$(CC) $(CFLAGS) -o $@  $^  $(LDFLAGS)
main.o:	main.cpp
	$(CC) $(CFLAGS) -c $^ 
SocketWraper.o:	SocketWraper.cpp 
	$(CC) $(CFLAGS) -c $^
ConnectionManager.o: ConnectionManager.cpp
	$(CC) $(CFLAGS) -c $^
SLog.o: SLog.cpp
	$(CC) $(CFLAGS) -c $^
MessagePackage.o: MessagePackage.cpp
	$(CC) $(CFLAGS) -c $^
StreamBuffer.o: StreamBuffer.cpp
	$(CC) $(CFLAGS) -c $^


#### for test

test_bufferRing : StreamBuffer_Test.cpp StreamBuffer.o SLog.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o main test_*
