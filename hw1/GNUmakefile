prog=deq

include ../GNUmakefile

try: main.o libdeq.so tests.o
	gcc -o $@ $< -L. -ldeq -Wl,-rpath=.
