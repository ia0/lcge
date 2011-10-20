.PHONY: test
test: Test ../lcge
	../lcge | ./Test

Test: Test.hs
	ghc --make Test

.PHONY: clean
clean:
	rm *.hi *.o

.PHONY: distclean
distclean: clean
	rm Test
