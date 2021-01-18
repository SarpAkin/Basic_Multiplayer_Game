cd "${0%/*}"

python3 codeGen/compenentSerializer.py

cd automake
python3 automake.py client_config.json client.mk
python3 automake.py server_config.json server.mk
make -f client.mk -j 12 -s 2> ../build/client.mk.log 
make -f server.mk -j 12 -s 2> ../build/server.mk.log
clear
make -f client.mk -j 12 -s
make -f server.mk -j 12 -s
cd ..
cp automake/client build/client
cp automake/server build/server
