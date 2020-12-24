cd automake
python3 automake.py client_config.json client.mk
python3 automake.py server_config.json server.mk
make -f client.mk -j 12
make -f server.mk -j 12
cd ..
cp automake/client build/client
cp automake/server build/server
