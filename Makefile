all: main

main: main.c
	gcc -o build/main main.c

clean:
	rm -rf build/* 
