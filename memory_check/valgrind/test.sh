gcc -g -o test test.c
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./test
