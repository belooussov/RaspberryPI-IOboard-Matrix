all: build run

build:
	gcc -Wall -o out LEDexample.c -lwiringPi -lstdc++

run:
	./out
