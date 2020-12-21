cd automake
python3 automake.py client_config.json client.mk
python3 automake.py server_config.json server.mk
make -f client.mk
make -f server.mk
cp client ../client
cp server ../server
