import automake

compiler = "gcc"
shared_cflags = "-pthread -std=c++17 -lstdc++ -lm -Wall"
shared_src_dirs = ["src/shared"]

debug_cflags = "-D_GLIBCXX_DEBUG -g"

client_cflags = "-lX11 -lGL -lpthread -lpng -lstdc++fs -DCLIENT_SIDE"
client_src_dirs = ["src/client","vendor"]

server_cflags = "-DSERVER_SIDE"
server_src_dirs = ["src/server"]

shared_cflags += " " + debug_cflags 

automake.Make_makefile(compiler,shared_cflags + " " + client_cflags,shared_src_dirs + client_src_dirs,"client")
automake.Make_makefile(compiler,shared_cflags + " " + server_cflags,shared_src_dirs + server_src_dirs,"server")