CC = gcc
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -lstdc++ -std=c++17 -lm -g
OUT = client

$(OUT): _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_EntityCompenents_compenent.cpp.o _.._src_shared_EntityCompenents_TestCompenent.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_EntityCompenents_compenent.cpp.o _.._src_shared_EntityCompenents_TestCompenent.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)

_.._src_shared_entity.cpp.o:../src/shared/entity.cpp ../src/shared/EntityCompenents/compenent.h ../src/shared/vector2.h ../src/shared/message.h ../src/shared/entity.h ../src/shared/EntityCompenents/../message.h ../src/shared/dynamic_ptr_cast.h ../src/shared/EntityCompenents/compenentTypes.h
	$(CC) -c ../src/shared/entity.cpp -o_.._src_shared_entity.cpp.o $(CFLAGS)
_.._src_shared_message.cpp.o:../src/shared/message.cpp ../src/shared/message.h
	$(CC) -c ../src/shared/message.cpp -o_.._src_shared_message.cpp.o $(CFLAGS)
_.._src_shared_EntityCompenents_compenent.cpp.o:../src/shared/EntityCompenents/compenent.cpp ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/TestCompenent.h ../src/shared/EntityCompenents/compenent.h ../src/shared/EntityCompenents/../EntityCompenents/../message.h ../src/shared/EntityCompenents/../vector2.h ../src/shared/EntityCompenents/allCompenent.h ../src/shared/EntityCompenents/../EntityCompenents/compenent.h ../src/shared/EntityCompenents/../EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/../message.h ../src/shared/EntityCompenents/../dynamic_ptr_cast.h ../src/shared/EntityCompenents/../entity.h
	$(CC) -c ../src/shared/EntityCompenents/compenent.cpp -o_.._src_shared_EntityCompenents_compenent.cpp.o $(CFLAGS)
_.._src_shared_EntityCompenents_TestCompenent.cpp.o:../src/shared/EntityCompenents/TestCompenent.cpp ../src/shared/EntityCompenents/compenent.h ../src/shared/EntityCompenents/compenentTypes.h ../src/shared/EntityCompenents/../message.h ../src/shared/EntityCompenents/TestCompenent.h
	$(CC) -c ../src/shared/EntityCompenents/TestCompenent.cpp -o_.._src_shared_EntityCompenents_TestCompenent.cpp.o $(CFLAGS)
_.._src_shared_game.cpp.o:../src/shared/game.cpp ../src/shared/vector2.h ../src/shared/message_types.h ../src/shared/entity.h ../src/shared/EntityCompenents/../message.h ../src/shared/dynamic_ptr_cast.h ../src/shared/game.h ../src/shared/message.h ../src/shared/EntityCompenents/compenent.h ../src/shared/EntityCompenents/compenentTypes.h
	$(CC) -c ../src/shared/game.cpp -o_.._src_shared_game.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/Tsafe_queue.h ../src/shared/connection.h ../src/shared/message.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_shared_vector2.cpp.o:../src/shared/vector2.cpp ../src/shared/vector2.h
	$(CC) -c ../src/shared/vector2.cpp -o_.._src_shared_vector2.cpp.o $(CFLAGS)
_.._src_client_client.cpp.o:../src/client/client.cpp ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/message.h ../src/client/client.h ../src/client/../shared/welcomeMessage.h ../src/client/../shared/connection.h
	$(CC) -c ../src/client/client.cpp -o_.._src_client_client.cpp.o $(CFLAGS)
_.._src_client_c_game.cpp.o:../src/client/c_game.cpp ../src/client/../shared/vector2.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/EntityCompenents/compenent.h ../src/client/../shared/message.h ../src/client/../shared/EntityCompenents/TestCompenent.h ../src/client/../shared/dynamic_ptr_cast.h ../src/client/renderer.h ../src/client/../shared/message_types.h ../src/client/../shared/connection.h ../src/client/c_game.h ../src/client/../shared/EntityCompenents/compenentTypes.h ../src/client/../shared/entity.h ../src/client/client.h ../src/client/../shared/EntityCompenents/../message.h ../src/client/../shared/game.h
	$(CC) -c ../src/client/c_game.cpp -o_.._src_client_c_game.cpp.o $(CFLAGS)
_.._src_client_main.cpp.o:../src/client/main.cpp ../src/client/../shared/vector2.h ../src/client/../shared/Tsafe_queue.h ../src/client/c_game.h ../src/client/../shared/EntityCompenents/compenent.h ../src/client/../shared/message.h ../src/client/client.h ../src/client/../shared/entity.h ../src/client/../shared/EntityCompenents/compenentTypes.h ../src/client/renderer.h ../src/client/../shared/dynamic_ptr_cast.h ../src/client/../shared/EntityCompenents/../message.h ../src/client/../shared/game.h ../src/client/../shared/connection.h ../src/client/../shared/message_types.h
	$(CC) -c ../src/client/main.cpp -o_.._src_client_main.cpp.o $(CFLAGS)
_.._src_client_renderer.cpp.o:../src/client/renderer.cpp ../src/client/../shared/vector2.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/EntityCompenents/../message.h ../src/client/c_game.h ../src/client/../shared/EntityCompenents/compenent.h ../src/client/../shared/message.h ../src/client/client.h ../src/client/../shared/entity.h ../src/client/../shared/dynamic_ptr_cast.h ../src/client/renderer.h ../src/client/../shared/message_types.h ../src/client/../shared/EntityCompenents/compenentTypes.h ../src/client/../shared/game.h ../src/client/../shared/connection.h
	$(CC) -c ../src/client/renderer.cpp -o_.._src_client_renderer.cpp.o $(CFLAGS)
_.._vendor_olcPİxelGameEngine.cpp.o:../vendor/olcPİxelGameEngine.cpp
	$(CC) -c ../vendor/olcPİxelGameEngine.cpp -o_.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)
