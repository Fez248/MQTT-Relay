# I need to add static compilation and understand better dynamic but I'll
# do that once I link the MQTT libraries

all: mqtt_c_fez mqtt_c_fez_Dynamic

mqtt_c_fez: src/mqtt_c_fez.c
	gcc -I./include/ -c src/mqtt_c_fez.c -o build/mqtt_c_fez.o

mqtt_c_fez_Dynamic: src/mqtt_c_fez.c
	gcc -I./include/ -fPIC -shared src/mqtt_c_fez.c -o build/mqtt_c_fez.so	

clean:
	rm -rf build/* 
