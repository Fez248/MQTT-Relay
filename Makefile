# I need to add static compilation and understand better dynamic but I'll
# do that once I link the MQTT libraries

all: mqttCFez mqttCFez-Dynamic c-test
test: c_test

mqttCFez: src/mqttCFez.c
	gcc -I./include/ -o build/mqttCFez.o -c src/mqttCFez.c -lm

mqttCFez-Dynamic: src/mqttCFez.c
	gcc -I./include/ -fPIC -shared -o build/mqttCFez.so src/mqttCFez.c -lm

c-test: src/c-test.c src/mqttCFez.c
	gcc -I./include/ -o build/c-test src/mqttCFez.c src/c-test.c -lm

clean:
	rm -rf build/* 
