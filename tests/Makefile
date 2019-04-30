CC = g++
TESTFLAGS = -lboost_unit_test_framework

BoardTest:
	$(CC) BoardTests.cpp $(TESTFLAGS) -o bTests.out

RulesTest:
	$(CC) RulesTests.cpp $(TESTFLAGS) -o rTests.out

test:
	make BoardTest
	make RulesTest
	./bTests.out
	./rTests.out

clean:
	rm -f *.out

	