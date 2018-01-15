cc = gcc
cflags = -std=c99 -pedantic -Wall -g
srcpath = ./src/
outputpath = ./bin/

compile:
	$(cc) $(cflags) $(srcpath)main.c $(srcpath)hashTableApi.c -Iinclude -o $(outputpath)program

run:
	clear; $(outputpath)program ./assets/dict.txt


remove:
	rm $(outputpath)
