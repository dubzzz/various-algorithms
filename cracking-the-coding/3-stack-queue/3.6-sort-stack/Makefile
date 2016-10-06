CFLAGS=-std=c++11 -Wall -I. -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread

a.out: main.cpp
	g++ -o a.out main.cpp $(CFLAGS) $(LDFLAGS)

clean:
	rm -f a.out

test: a.out
	chmod u+x a.out
	./a.out

all: clean test

