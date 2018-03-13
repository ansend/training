cos_buffer.o : cos_buffer.h cos_buffer.cpp
	g++ -c cos_buffer.cpp
file_sys.o : file_sys.cpp file_sys.h cos_buffer.h
	g++ -c file_sys.cpp
cos_sys.o: cos_sys.cpp cos_sys.h CommandHandler.h
	g++ -c cos_sys.cpp
cos : cos_buffer.o file_sys.o 
	g++ cos_buffer.o file_sys.o cos_sys.o -o cos

all : cos

clean : 
	rm -rf *.o
	rm -rf cos
