CFLAGS=-std=c++11 -Wall -I. -I/usr/local/include -I../../../rapidcheck/include -I../../../rapidcheck/extras/gtest/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread ../../../rapidcheck/librapidcheck.a

a.out: main.cpp
	g++ -o a.out main.cpp $(CFLAGS) $(LDFLAGS)

clean:
	rm -f a.out

build: a.out

test: build
	chmod u+x a.out
	./a.out

all: clean test

