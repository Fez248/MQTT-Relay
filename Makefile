# I need to add static compilation and understand better dynamic but I'll
# do that once I link the MQTT libraries

all: mqttCFez mqttCFez-Dynamic c-test
test: c_test

mqttCFez: src/mqttCFez.c
	gcc -I./include/ -c src/mqttCFez.c -o build/mqttCFez.o

mqttCFez-Dynamic: src/mqttCFez.c
	gcc -I./include/ -fPIC -shared src/mqttCFez.c -o build/mqttCFez.so	

c-test: src/c-test.c src/mqttCFez.c
	gcc -I./include/ -o build/c-test src/mqttCFez.c src/c-test.c 

clean:
	rm -rf build/* 
