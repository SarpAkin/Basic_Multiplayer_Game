CC = g++
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -std=c++17 -lm -fPIE
OUT = client

$(OUT): _.._src_shared_Vector2.cpp.o _.._src_shared_connection.cpp.o _.._src_client_main.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_Vector2.cpp.o _.._src_shared_connection.cpp.o _.._src_client_main.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)

_.._src_shared_Vector2.cpp.o:../src/shared/Vector2.cpp ../src/shared/Vector2.h
	$(CC) -c ../src/shared/Vector2.cpp -o_.._src_shared_Vector2.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/message.h ../src/shared/Tsafe_queue.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_client_main.cpp.o:../src/client/main.cpp
	$(CC) -c ../src/client/main.cpp -o_.._src_client_main.cpp.o $(CFLAGS)
_.._vendor_olcPİxelGameEngine.cpp.o:../vendor/olcPİxelGameEngine.cpp
	$(CC) -c ../vendor/olcPİxelGameEngine.cpp -o_.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)
