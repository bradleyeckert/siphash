test: test.c ./src/siphash.c
	gcc -o test test.c ./src/siphash.c -I./src
