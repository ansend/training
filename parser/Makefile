count.yy.c : count.ll
	flex -o count.yy.c count.ll   #fefaultly, flex will generate lex.yy.c as the default output file name with -o.

all: count.yy.c 
	gcc -g count.yy.c -o count

clean:
	rm count.yy.c
