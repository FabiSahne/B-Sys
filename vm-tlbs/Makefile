TARGET = tlb
CC = gcc
CFLAGS = -Wall -Wextra -O0 -Wpedantic

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)