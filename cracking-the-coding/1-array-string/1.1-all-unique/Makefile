CFLAGS=-std=c++11 -Wall -I. -I/usr/local/include -I../../../rapidcheck/include -I../../../rapidcheck/extras/gtest/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread ../../../rapidcheck/librapidcheck.a

a.out: main.cpp
	g++ -o a.out main.cpp $(CFLAGS) $(LDFLAGS)

a_nostruct.out: main.cpp
	g++ -o a_nostruct.out main.cpp -DNO_STRUCT $(CFLAGS) $(LDFLAGS)

clean:
	rm -f a.out
	rm -f a_nostruct.out

build: a.out a_nostruct.out

test: build
	chmod u+x a.out
	./a.out
	chmod u+x a_nostruct.out
	./a_nostruct.out

all: clean test

