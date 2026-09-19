cc = gcc
CFLAGS=-O3 -std=c11 -g -fPIC -pthread
LDFLAGS=-pthread -lm
LD=gcc

all: sequential 

sequential: sequential.o 
	$(LD) $(LDFLAGS) sequential.o $(LDLIBS) -o sequential

bench: sequential
	./bench_sequential.sh 

clean:
	./clean.sh

