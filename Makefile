FLAGS=-Wall -Wextra -g -O
FLAGS+=$(DEBUG)
GPP=g++ $(FLAGS)

.PHONY: all
all: test

test: term.o test.o
	$(GPP) $^ -o $@

test.o: test.cc term.hh
	$(GPP) -c $<

term.o: term.cc
	$(GPP) -c $<

.PHONY: clean
clean:
	rm -f *.o
