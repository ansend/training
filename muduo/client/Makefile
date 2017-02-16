timeclient: timeclient.o
	g++ ./timeclient.o  /home/ansen/muduo/lib/libmuduo_net.a /home/ansen/muduo/lib/libmuduo_base.a -lpthread -o timeclient
timeclient.o: timeclient.cc
	g++ -I/home/ansen/muduo -c timeclient.cc

