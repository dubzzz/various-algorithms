CFLAGS=-std=c++11 -Wall -I. -I/usr/local/include -I../../../rapidcheck/include -I../../../rapidcheck/extras/gtest/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread ../../../rapidcheck/librapidcheck.a
COLOR=\033[0;33m
CLEAR_COLOR=\033[0;0m

ALGORITHMS=DEFAULT NOSTRUCT

build: a_DEFAULT.out build_missing

a_DEFAULT.out: main.cpp
	$(MAKE) rebuild

build_missing:
	for algo in $(ALGORITHMS); do \
		(test -f a_$$algo.out && echo -e ":: $(COLOR)Up-to-date $$algo$(CLEAR_COLOR)") || (echo -e ":: $(COLOR)Building $$algo$(CLEAR_COLOR)" && g++ -o a_$$algo.out main.cpp -D$$algo $(CFLAGS) $(LDFLAGS)) ; \
	done

clean:
	for algo in $(ALGORITHMS); do \
		echo -e ":: $(COLOR)Cleaning $$algo$(CLEAR_COLOR)" ; \
		rm -f ./a_$$algo.out ; \
	done

rebuild: clean build_missing

test: build
	for algo in $(ALGORITHMS); do \
		echo -e ":: $(COLOR)Testing $$algo$(CLEAR_COLOR)" ; \
		chmod u+x a_$$algo.out ; \
		./a_$$algo.out ; \
	done

