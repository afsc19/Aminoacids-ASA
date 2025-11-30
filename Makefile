CC = g++
CFLAGS = -std=c++11 -O3 -Wall
CFLAGS_DEBUG = -std=c++11 -O3 -Wall -g
LDFLAGS = -lm


TARGET = projeto
SRC = projeto.cpp
EXAMPLE = tests/example2.in

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

$(TARGET)_debug: $(SRC)
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) < $(EXAMPLE)

val: $(TARGET)_debug
	valgrind --leak-check=full ./$(TARGET) < $(EXAMPLE) 2> valgrind.txt || rm ./vgcore.*