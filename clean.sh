cd automake
rm -rf HeaderFiles.json
find . -name "*.o" | xargs rm
cd ../build
rm -rf server client
rm server client