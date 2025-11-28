CC = g++
CFLAGS = -std=c++11 -O3 -Wall
LDFLAGS = -lm


TARGET = projeto.bin
SRC = projeto.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)