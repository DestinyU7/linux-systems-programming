cc = gcc
CFLAGS=-O3 -std=c11 -g -fPIC -pthread
LDFLAGS=-pthread -lm
LD=gcc

.PHONY: plot static_sched

all: static_sched

approx:
	$(LD) $(CXXFLAGS) $(LDFLAGS) approx.c -o approx

static_sched: static_sched.o
	$(LD) static_sched.o -o static_sched $(LDFLAGS)

bench: static_sched
	./run_static.sh

test: static_sched approx
	./test.sh static cases.txt 

plot:
	bash plot.sh

clean:
	./clean.sh
