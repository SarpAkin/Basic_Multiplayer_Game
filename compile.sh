cd "${0%/*}"

python3 codeGen/componentSerializer.py

#cd automake
python3 automake/automake_config.py
#make -f client.mk -j 12 -s 2> build/client.mk.log 
#make -f server.mk -j 12 -s 2> build/server.mk.log
clear

mv automake/client_o_files/*.o .
make -f client.mk -j 12 -s
rm client.mk
mv *.o automake/client_o_files/

mv automake/server_o_files/*.o .
make -f server.mk -j 12 -s
rm server.mk
mv *.o automake/server_o_files/

cp client build/client
cp server build/server
