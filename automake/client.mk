CC = g++
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -std=c++17 -lm -fPIE -g
OUT = client

$(OUT): _.._src_shared_entity.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_entity.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)

_.._src_shared_entity.cpp.o:../src/shared/entity.cpp ../src/shared/vector2.h ../src/shared/message.h ../src/shared/entity.h
	$(CC) -c ../src/shared/entity.cpp -o_.._src_shared_entity.cpp.o $(CFLAGS)
_.._src_shared_game.cpp.o:../src/shared/game.cpp ../src/shared/message_types.h ../src/shared/entity.h ../src/shared/vector2.h ../src/shared/message.h ../src/shared/game.h
	$(CC) -c ../src/shared/game.cpp -o_.._src_shared_game.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/Tsafe_queue.h ../src/shared/message.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_shared_vector2.cpp.o:../src/shared/vector2.cpp ../src/shared/vector2.h
	$(CC) -c ../src/shared/vector2.cpp -o_.._src_shared_vector2.cpp.o $(CFLAGS)
_.._src_client_client.cpp.o:../src/client/client.cpp ../src/client/../shared/connection.h ../src/client/client.h ../src/client/../shared/welcomeMessage.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/message.h
	$(CC) -c ../src/client/client.cpp -o_.._src_client_client.cpp.o $(CFLAGS)
_.._src_client_c_game.cpp.o:../src/client/c_game.cpp ../src/client/../shared/entity.h ../src/client/../shared/message_types.h ../src/client/../shared/connection.h ../src/client/../shared/message.h ../src/client/../shared/vector2.h ../src/client/renderer.h ../src/client/../shared/game.h ../src/client/c_game.h ../src/client/client.h ../src/client/../shared/Tsafe_queue.h
	$(CC) -c ../src/client/c_game.cpp -o_.._src_client_c_game.cpp.o $(CFLAGS)
_.._src_client_main.cpp.o:../src/client/main.cpp ../src/client/../shared/entity.h ../src/client/../shared/connection.h ../src/client/client.h ../src/client/renderer.h ../src/client/../shared/vector2.h ../src/client/../shared/game.h ../src/client/c_game.h ../src/client/../shared/message.h ../src/client/../shared/Tsafe_queue.h
	$(CC) -c ../src/client/main.cpp -o_.._src_client_main.cpp.o $(CFLAGS)
_.._src_client_renderer.cpp.o:../src/client/renderer.cpp ../src/client/../shared/entity.h ../src/client/../shared/connection.h ../src/client/../shared/message.h ../src/client/renderer.h ../src/client/../shared/vector2.h ../src/client/../shared/game.h ../src/client/c_game.h ../src/client/client.h ../src/client/../shared/Tsafe_queue.h
	$(CC) -c ../src/client/renderer.cpp -o_.._src_client_renderer.cpp.o $(CFLAGS)
_.._vendor_olcPİxelGameEngine.cpp.o:../vendor/olcPİxelGameEngine.cpp
	$(CC) -c ../vendor/olcPİxelGameEngine.cpp -o_.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)
