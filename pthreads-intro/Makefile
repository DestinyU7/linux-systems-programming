CFLAGS=-O3 -g  -pthread
LDFLAGS=-pthread
LD=gcc

.PHONY: hello_thread

all: hello_thread

hello_thread: 
	$(LD) hello_thread.c -o hello_thread $(LDFLAGS)

clean:
	rm hello_thread
