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

build:
	mkdir build

clean:
	rm -rf build main
