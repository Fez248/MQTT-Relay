all: msgQueue

msgQueue: src/msgQueue.c
	gcc -I./include -o build/msgQueue src/msgQueue.c

clean:
	rm -rf build/* 
