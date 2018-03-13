FileBuffer.o : FileBuffer.h FileBuffer.cpp
	g++ -c FileBuffer.cpp
FileSys.o : FileSys.cpp FileSys.h FileBuffer.h
	g++ -c FileSys.cpp
CosServer.o: CosServer.cpp CosServer.h CommandHandler.h
	g++ -c CosServer.cpp
cos : FileBuffer.o FileSys.o  CosServer.o
	g++ FileBuffer.o FileSys.o CosServer.o -o cos

all : cos

clean : 
	rm -rf *.o
	rm -rf cos
