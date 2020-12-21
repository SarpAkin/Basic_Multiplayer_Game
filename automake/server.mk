CC = g++
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -std=c++17
OUT = server

$(OUT): _.._src_shared_connection.cpp.o _.._src_server_server.cpp.o _.._src_server_main.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_connection.cpp.o _.._src_server_server.cpp.o _.._src_server_main.cpp.o $(CFLAGS)

_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/connection.h ../src/shared/Tsafe_queue.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_server_server.cpp.o:../src/server/server.cpp ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/connection.h ../src/server/server.h
	$(CC) -c ../src/server/server.cpp -o_.._src_server_server.cpp.o $(CFLAGS)
_.._src_server_main.cpp.o:../src/server/main.cpp ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/connection.h ../src/server/server.h
	$(CC) -c ../src/server/main.cpp -o_.._src_server_main.cpp.o $(CFLAGS)
