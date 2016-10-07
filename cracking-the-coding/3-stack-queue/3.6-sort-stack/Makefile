CFLAGS=-std=c++11 -Wall -I. -I/usr/local/include -I../../../rapidcheck/include -I../../../rapidcheck/extras/gtest/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread ../../../rapidcheck/librapidcheck.a

a_quick.out: main.cpp
	g++ -o a_quick.out main.cpp -DQUICK $(CFLAGS) $(LDFLAGS)
a_merge.out: main.cpp
	g++ -o a_merge.out main.cpp -DMERGE $(CFLAGS) $(LDFLAGS)
a_selection.out: main.cpp
	g++ -o a_selection.out main.cpp $(CFLAGS) $(LDFLAGS)

clean:
	rm -f a_quick.out
	rm -f a_merge.out
	rm -f a_selection.out

test: a_quick.out a_merge.out a_selection.out
	chmod u+x a_quick.out
	./a_quick.out
	chmod u+x a_merge.out
	./a_merge.out
	chmod u+x a_selection.out
	./a_selection.out

all: clean test

