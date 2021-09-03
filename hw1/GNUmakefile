prog=deq

include ../GNUmakefile

try: main.o tests.o libdeq.so 
	gcc -o try main.o tests.o -L. -ldeq -Wl,-rpath=.

