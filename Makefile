.PHONY: clean

all: build main

main: main.o fraction.o service.o
	gcc -g build/main.o build/fraction.o build/service.o -o main
	
fraction.o: fraction.c fraction.h
	gcc -g -c fraction.c -o build/fraction.o
	
service.o: service.c fraction.h
	gcc -g -c service.c -o build/service.o
	
main.o: main.c fraction.h
	gcc -g -c main.c -o build/main.o

receiver: receiver.o func.o
	gcc -g build/receiver.o build/func.o -o receiver

sender: sender.o func.o
	gcc -g build/sender.o build/func.o -o sender

sender.o: src/sender.c src/func.h
	gcc -g -c src/sender.c -o build/sender.o

receiver.o: src/receiver.c src/func.h
	gcc -g -c src/receiver.c -o build/receiver.o

func.o: src/func.c src/func.h
	gcc -g -c src/func.c -o build/func.o

build:
	mkdir build

clean:
	rm -rf build main
