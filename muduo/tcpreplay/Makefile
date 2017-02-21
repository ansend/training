CPP=g++
LIB_FLAG= -lboost_system
LD_FLAGS= -Wl,--gc-sections,-rpath,../bin

cregex: cregex.o peer.o flowbuffer.o tcpflow.o
	g++ ./cregex.o ./peer.o ./flowbuffer.o ./tcpflow.o -I/home/ansen/muduo /home/ansen/build/release/lib/libmuduo_net.a /home/ansen/build/release/lib/libmuduo_base.a $(LD_FLAGS) $(LIB_FLAG) -lpthread -lstdc++ -o cregex
cregex.o: cregex.cc
	g++ -g  -I/home/ansen/muduo -c cregex.cc
peer.o: peer.cc 
	g++  -g -I/home/ansen/muduo -c peer.cc 
flowbuffer.o: flowbuffer.cc flowbuffer.h
	g++  -g -I/home/ansen/muduo -c flowbuffer.cc 
tcpflow.o : tcpflow.cc tcpflow.h
	g++ -g -I/home/ansen/muduo -c tcpflow.cc
clean:
	rm *.o ; rm cregex
