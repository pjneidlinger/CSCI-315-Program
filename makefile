MAIN=src/main.cpp
SRCS := $(filter-out $(MAIN),$(wildcard src/*.cpp))
PAGES := $(wildcard pages/*)
CFLAGS=-g -I src/
.PHONY: clean test all
BIN=html-parser

all:
	g++ -o $(BIN) $(CFLAGS) ${SRCS} ${MAIN}

run: all
	./$(BIN) $(PAGES)

%test:
	cxxtestgen --runner=ErrorPrinter -o test/test-runner.cpp test/$@.cpp ${SRCS}
	g++ ${CFLAGS} test/test-runner.cpp $(SRCS) -o test-runner
	./test-runner

clean:
	rm -rf $(BIN) test/test-runner.cpp test-runner
