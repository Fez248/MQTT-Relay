all: main

main: src/main.c
	gcc -o build/main src/main.c

clean:
	rm -rf build/* 
