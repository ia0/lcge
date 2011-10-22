.PHONY: test
test: Test ../lcge
	env TEST_MODE= ../lcge | ./Test

Test: Test.hs
	ghc --make Test

.PHONY: clean
clean:
	rm *.hi *.o

.PHONY: distclean
distclean: clean
	rm Test
