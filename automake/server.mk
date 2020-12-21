CC = clang
CFLAGS = -std=c++17 -pthread -lstdc++ -g -lX11 -lGL -lpthread -lpng
OUT = server

$(OUT): _.._src_shared_connection.cpp.o _.._src_server_server.cpp.o
	$(CC) $(CFLAGS) -o $(OUT)  _.._src_shared_connection.cpp.o _.._src_server_server.cpp.o

_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/Tsafe_queue.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_server_server.cpp.o:../src/server/server.cpp ../src/server/../shared/connection.h ../src/server/../shared/Tsafe_queue.h
	$(CC) -c ../src/server/server.cpp -o_.._src_server_server.cpp.o $(CFLAGS)
