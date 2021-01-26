CC = gcc
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -lstdc++ -std=c++17 -lm -g
OUT = server

$(OUT): _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_EntityComponents_component.cpp.o _.._src_shared_EntityComponents_TestComponent.cpp.o _.._src_shared_vector2.cpp.o _.._src_server_server.cpp.o _.._src_server_s_game.cpp.o _.._src_server_main.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_EntityComponents_component.cpp.o _.._src_shared_EntityComponents_TestComponent.cpp.o _.._src_shared_vector2.cpp.o _.._src_server_server.cpp.o _.._src_server_s_game.cpp.o _.._src_server_main.cpp.o $(CFLAGS)

_.._src_shared_entity.cpp.o:../src/shared/entity.cpp ../src/shared/entity.h ../src/shared/EntityComponents/component.h ../src/shared/dynamic_ptr_cast.h ../src/shared/message.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/vector2.h ../src/shared/EntityComponents/../message.h
	$(CC) -c ../src/shared/entity.cpp -o_.._src_shared_entity.cpp.o $(CFLAGS)
_.._src_shared_message.cpp.o:../src/shared/message.cpp ../src/shared/message.h
	$(CC) -c ../src/shared/message.cpp -o_.._src_shared_message.cpp.o $(CFLAGS)
_.._src_shared_game.cpp.o:../src/shared/game.cpp ../src/shared/EntityComponents/../message.h ../src/shared/message.h ../src/shared/message_types.h ../src/shared/vectorBinarySearch.h ../src/shared/entity.h ../src/shared/dynamic_ptr_cast.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/game.h ../src/shared/EntityComponents/component.h ../src/shared/vector2.h
	$(CC) -c ../src/shared/game.cpp -o_.._src_shared_game.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/message.h ../src/shared/Tsafe_queue.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_shared_EntityComponents_component.cpp.o:../src/shared/EntityComponents/component.cpp ../src/shared/EntityComponents/allComponent.h ../src/shared/EntityComponents/component.h ../src/shared/EntityComponents/../message.h ../src/shared/EntityComponents/TestComponent.h ../src/shared/EntityComponents/../dynamic_ptr_cast.h ../src/shared/EntityComponents/../EntityComponents/../message.h ../src/shared/EntityComponents/../entity.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/EntityComponents/../vector2.h ../src/shared/EntityComponents/../EntityComponents/componentTypes.h ../src/shared/EntityComponents/../EntityComponents/component.h
	$(CC) -c ../src/shared/EntityComponents/component.cpp -o_.._src_shared_EntityComponents_component.cpp.o $(CFLAGS)
_.._src_shared_EntityComponents_TestComponent.cpp.o:../src/shared/EntityComponents/TestComponent.cpp ../src/shared/EntityComponents/../message.h ../src/shared/EntityComponents/component.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/EntityComponents/TestComponent.h
	$(CC) -c ../src/shared/EntityComponents/TestComponent.cpp -o_.._src_shared_EntityComponents_TestComponent.cpp.o $(CFLAGS)
_.._src_shared_vector2.cpp.o:../src/shared/vector2.cpp ../src/shared/vector2.h
	$(CC) -c ../src/shared/vector2.cpp -o_.._src_shared_vector2.cpp.o $(CFLAGS)
_.._src_server_server.cpp.o:../src/server/server.cpp ../src/server/../shared/connection.h ../src/server/server.h ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/welcomeMessage.h ../src/server/../shared/message.h
	$(CC) -c ../src/server/server.cpp -o_.._src_server_server.cpp.o $(CFLAGS)
_.._src_server_s_game.cpp.o:../src/server/s_game.cpp ../src/server/server.h ../src/server/../shared/EntityComponents/componentTypes.h ../src/server/../shared/message_types.h ../src/server/../shared/Tsafe_queue.h ../src/server/s_game.h ../src/server/../shared/game.h ../src/server/../shared/EntityComponents/component.h ../src/server/../shared/entity.h ../src/server/../shared/vectorBinarySearch.h ../src/server/../shared/vector2.h ../src/server/../shared/connection.h ../src/server/../shared/EntityComponents/../message.h ../src/server/../shared/message.h ../src/server/../shared/dynamic_ptr_cast.h
	$(CC) -c ../src/server/s_game.cpp -o_.._src_server_s_game.cpp.o $(CFLAGS)
_.._src_server_main.cpp.o:../src/server/main.cpp ../src/server/s_game.h ../src/server/../shared/Tsafe_queue.h ../src/server/../shared/EntityComponents/../message.h ../src/server/../shared/message.h ../src/server/../shared/dynamic_ptr_cast.h ../src/server/../shared/vector2.h ../src/server/../shared/connection.h ../src/server/../shared/EntityComponents/componentTypes.h ../src/server/server.h ../src/server/../shared/message_types.h ../src/server/../shared/game.h ../src/server/../shared/EntityComponents/component.h ../src/server/../shared/entity.h
	$(CC) -c ../src/server/main.cpp -o_.._src_server_main.cpp.o $(CFLAGS)
