CC = g++
CFLAGS = -std=c++11 -O3 -Wall
LDFLAGS = -lm


TARGET = projeto
SRC = projeto.cpp
EXAMPLE = tests/example1.in

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) < $(EXAMPLE)