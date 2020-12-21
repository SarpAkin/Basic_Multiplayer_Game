CC = clang
CFLAGS = -std=c++17 -pthread -lstdc++ -g -lX11 -lGL -lpthread -lpng
OUT = client

$(OUT): _.._src_shared_connection.cpp.o _.._src_client_main.cpp.o
	$(CC) $(CFLAGS) -o $(OUT)  _.._src_shared_connection.cpp.o _.._src_client_main.cpp.o

_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/Tsafe_queue.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_client_main.cpp.o:../src/client/main.cpp
	$(CC) -c ../src/client/main.cpp -o_.._src_client_main.cpp.o $(CFLAGS)
