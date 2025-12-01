CC = g++
CFLAGS = -std=c++11 -O3 -Wall
CFLAGS_DEBUG = -std=c++11 -O3 -Wall -g
LDFLAGS = -lm


TARGET = projeto
SRC = projeto.cpp
TARGET_NONDP = bruteforce
SRC_NONDP = bruteforce.cpp
EXAMPLE = tests/test1000

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

$(TARGET)_debug: $(SRC)
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET) $(SRC) $(LDFLAGS)

$(TARGET_NONDP): $(SRC_NONDP)
	$(CC) $(CFLAGS) -o $(TARGET_NONDP) $(SRC_NONDP) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	time ./$(TARGET) < $(EXAMPLE).in > $(EXAMPLE).out
	diff $(EXAMPLE).out $(EXAMPLE).sol.out

test_nondp: $(TARGET_NONDP)
	time ./$(TARGET_NONDP) < $(EXAMPLE).in

val: $(TARGET)_debug
	valgrind --leak-check=full ./$(TARGET) < $(EXAMPLE).in 2> valgrind.txt || rm ./vgcore.*