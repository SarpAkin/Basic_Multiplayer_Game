CC = gcc
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -lstdc++ -std=c++17 -lm -g
OUT = server

$(OUT): _.._src_shared_entity.cpp.o _.._src_shared_EntityCompenents_compenent.cpp.o _.._src_shared_EntityCompenents_TestCompenent.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_server_server.cpp.o _.._src_server_s_game.cpp.o _.._src_server_main.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_entity.cpp.o _.._src_shared_EntityCompenents_compenent.cpp.o _.._src_shared_EntityCompenents_TestCompenent.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_server_server.cpp.o _.._src_server_s_game.cpp.o _.._src_server_main.cpp.o $(CFLAGS)

_.._src_shared_entity.cpp.o:../src/shared/entity.cpp ../src/shared/vector2.h ../src/shared/EntityCompenents/../message.h ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/entity.h ../src/shared/dynamic_ptr_cast.h ../src/shared/EntityCompenents/compenent.h ../src/shared/message.h
	$(CC) -c ../src/shared/entity.cpp -o_.._src_shared_entity.cpp.o $(CFLAGS)
_.._src_shared_EntityCompenents_compenent.cpp.o:../src/shared/EntityCompenents/compenent.cpp ../src/shared/EntityCompenents/../entity.h ../src/shared/EntityCompenents/../EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/../message.h ../src/shared/EntityCompenents/../vector2.h ../src/shared/EntityCompenents/../EntityCompenents/../message.h ../src/shared/EntityCompenents/compenent.h ../src/shared/EntityCompenents/allCompenent.h ../src/shared/EntityCompenents/../dynamic_ptr_cast.h ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/../EntityCompenents/compenent.h ../src/shared/EntityCompenents/TestCompenent.h
	$(CC) -c ../src/shared/EntityCompenents/compenent.cpp -o_.._src_shared_EntityCompenents_compenent.cpp.o $(CFLAGS)
_.._src_shared_EntityCompenents_TestCompenent.cpp.o:../src/shared/EntityCompenents/TestCompenent.cpp ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/compenent.h ../src/shared/EntityCompenents/../message.h ../src/shared/EntityCompenents/TestCompenent.h
	$(CC) -c ../src/shared/EntityCompenents/TestCompenent.cpp -o_.._src_shared_EntityCompenents_TestCompenent.cpp.o $(CFLAGS)
_.._src_shared_game.cpp.o:../src/shared/game.cpp ../src/shared/vector2.h ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/entity.h ../src/shared/message_types.h ../src/shared/EntityCompenents/../message.h ../src/shared/game.h ../src/shared/dynamic_ptr_cast.h ../src/shared/EntityCompenents/compenent.h ../src/shared/message.h
	$(CC) -c ../src/shared/game.cpp -o_.._src_shared_game.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/Tsafe_queue.h ../src/shared/message.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_shared_vector2.cpp.o:../src/shared/vector2.cpp ../src/shared/vector2.h
	$(CC) -c ../src/shared/vector2.cpp -o_.._src_shared_vector2.cpp.o $(CFLAGS)
_.._src_server_server.cpp.o:../src/server/server.cpp ../src/server/../shared/welcomeMessage.h ../src/server/../shared/message.h ../src/server/server.h ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/connection.h
	$(CC) -c ../src/server/server.cpp -o_.._src_server_server.cpp.o $(CFLAGS)
_.._src_server_s_game.cpp.o:../src/server/s_game.cpp ../src/server/../shared/message.h ../src/server/../shared/entity.h ../src/server/s_game.h ../src/server/server.h ../src/server/../shared/EntityCompenents/compenent.h ../src/server/../shared/dynamic_ptr_cast.h ../src/server/../shared/game.h ../src/server/../shared/EntityCompenents/../message.h ../src/server/../shared/connection.h ../src/server/../shared/EntityCompenents/compenentTypes.h ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/vector2.h ../src/server/../shared/message_types.h
	$(CC) -c ../src/server/s_game.cpp -o_.._src_server_s_game.cpp.o $(CFLAGS)
_.._src_server_main.cpp.o:../src/server/main.cpp ../src/server/../shared/message.h ../src/server/../shared/entity.h ../src/server/s_game.h ../src/server/server.h ../src/server/../shared/EntityCompenents/compenent.h ../src/server/../shared/dynamic_ptr_cast.h ../src/server/../shared/game.h ../src/server/../shared/EntityCompenents/../message.h ../src/server/../shared/connection.h ../src/server/../shared/EntityCompenents/compenentTypes.h ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/vector2.h ../src/server/../shared/message_types.h
	$(CC) -c ../src/server/main.cpp -o_.._src_server_main.cpp.o $(CFLAGS)
