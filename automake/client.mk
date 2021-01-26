CC = gcc
CFLAGS = -lX11 -lGL -pthread -lpthread -lpng -lstdc++fs -lstdc++ -std=c++17 -lm -g
OUT = client

$(OUT): _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_EntityComponents_component.cpp.o _.._src_shared_EntityComponents_TestComponent.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o
	$(CC) -o $(OUT)  _.._src_shared_entity.cpp.o _.._src_shared_message.cpp.o _.._src_shared_game.cpp.o _.._src_shared_connection.cpp.o _.._src_shared_EntityComponents_component.cpp.o _.._src_shared_EntityComponents_TestComponent.cpp.o _.._src_shared_vector2.cpp.o _.._src_client_client.cpp.o _.._src_client_c_game.cpp.o _.._src_client_main.cpp.o _.._src_client_renderer.cpp.o _.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)

_.._src_shared_entity.cpp.o:../src/shared/entity.cpp ../src/shared/entity.h ../src/shared/EntityComponents/component.h ../src/shared/dynamic_ptr_cast.h ../src/shared/message.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/vector2.h ../src/shared/EntityComponents/../message.h
	$(CC) -c ../src/shared/entity.cpp -o_.._src_shared_entity.cpp.o $(CFLAGS)
_.._src_shared_message.cpp.o:../src/shared/message.cpp ../src/shared/message.h
	$(CC) -c ../src/shared/message.cpp -o_.._src_shared_message.cpp.o $(CFLAGS)
_.._src_shared_game.cpp.o:../src/shared/game.cpp ../src/shared/EntityComponents/../message.h ../src/shared/message.h ../src/shared/message_types.h ../src/shared/vectorBinarySearch.h ../src/shared/entity.h ../src/shared/dynamic_ptr_cast.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/game.h ../src/shared/EntityComponents/component.h ../src/shared/vector2.h
	$(CC) -c ../src/shared/game.cpp -o_.._src_shared_game.cpp.o $(CFLAGS)
_.._src_shared_connection.cpp.o:../src/shared/connection.cpp ../src/shared/message.h ../src/shared/Tsafe_queue.h ../src/shared/connection.h
	$(CC) -c ../src/shared/connection.cpp -o_.._src_shared_connection.cpp.o $(CFLAGS)
_.._src_shared_EntityComponents_component.cpp.o:../src/shared/EntityComponents/component.cpp ../src/shared/EntityComponents/component.h ../src/shared/EntityComponents/../vector2.h ../src/shared/EntityComponents/../EntityComponents/componentTypes.h ../src/shared/EntityComponents/../message.h ../src/shared/EntityComponents/../EntityComponents/../message.h ../src/shared/EntityComponents/../dynamic_ptr_cast.h ../src/shared/EntityComponents/../EntityComponents/component.h ../src/shared/EntityComponents/TestComponent.h ../src/shared/EntityComponents/componentTypes.h ../src/shared/EntityComponents/allComponent.h ../src/shared/EntityComponents/../entity.h
	$(CC) -c ../src/shared/EntityComponents/component.cpp -o_.._src_shared_EntityComponents_component.cpp.o $(CFLAGS)
_.._src_shared_EntityComponents_TestComponent.cpp.o:../src/shared/EntityComponents/TestComponent.cpp ../src/shared/EntityComponents/component.h ../src/shared/EntityComponents/TestComponent.h ../src/shared/EntityComponents/../message.h ../src/shared/EntityComponents/componentTypes.h
	$(CC) -c ../src/shared/EntityComponents/TestComponent.cpp -o_.._src_shared_EntityComponents_TestComponent.cpp.o $(CFLAGS)
_.._src_shared_vector2.cpp.o:../src/shared/vector2.cpp ../src/shared/vector2.h
	$(CC) -c ../src/shared/vector2.cpp -o_.._src_shared_vector2.cpp.o $(CFLAGS)
_.._src_client_client.cpp.o:../src/client/client.cpp ../src/client/../shared/welcomeMessage.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/connection.h ../src/client/client.h ../src/client/../shared/message.h
	$(CC) -c ../src/client/client.cpp -o_.._src_client_client.cpp.o $(CFLAGS)
_.._src_client_c_game.cpp.o:../src/client/c_game.cpp ../src/client/../shared/EntityComponents/TestComponent.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/message_types.h ../src/client/../shared/vector2.h ../src/client/../shared/EntityComponents/componentTypes.h ../src/client/c_game.h ../src/client/../shared/dynamic_ptr_cast.h ../src/client/../shared/vectorBinarySearch.h ../src/client/client.h ../src/client/../shared/message.h ../src/client/renderer.h ../src/client/../shared/entity.h ../src/client/../shared/EntityComponents/component.h ../src/client/../shared/EntityComponents/../message.h ../src/client/../shared/connection.h ../src/client/../shared/game.h
	$(CC) -c ../src/client/c_game.cpp -o_.._src_client_c_game.cpp.o $(CFLAGS)
_.._src_client_main.cpp.o:../src/client/main.cpp ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/entity.h ../src/client/../shared/connection.h ../src/client/../shared/game.h ../src/client/renderer.h ../src/client/../shared/message.h ../src/client/../shared/EntityComponents/../message.h ../src/client/c_game.h ../src/client/../shared/message_types.h ../src/client/../shared/dynamic_ptr_cast.h ../src/client/../shared/EntityComponents/componentTypes.h ../src/client/../shared/vector2.h ../src/client/client.h ../src/client/../shared/EntityComponents/component.h
	$(CC) -c ../src/client/main.cpp -o_.._src_client_main.cpp.o $(CFLAGS)
_.._src_client_renderer.cpp.o:../src/client/renderer.cpp ../src/client/../shared/dynamic_ptr_cast.h ../src/client/renderer.h ../src/client/client.h ../src/client/../shared/Tsafe_queue.h ../src/client/../shared/vectorBinarySearch.h ../src/client/../shared/game.h ../src/client/../shared/EntityComponents/../message.h ../src/client/../shared/entity.h ../src/client/../shared/message.h ../src/client/../shared/EntityComponents/component.h ../src/client/../shared/vector2.h ../src/client/../shared/EntityComponents/componentTypes.h ../src/client/c_game.h ../src/client/../shared/message_types.h ../src/client/../shared/connection.h
	$(CC) -c ../src/client/renderer.cpp -o_.._src_client_renderer.cpp.o $(CFLAGS)
_.._vendor_olcPİxelGameEngine.cpp.o:../vendor/olcPİxelGameEngine.cpp
	$(CC) -c ../vendor/olcPİxelGameEngine.cpp -o_.._vendor_olcPİxelGameEngine.cpp.o $(CFLAGS)
