# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = GeneticRandomBoolean

# Source file(s)
SRC = main.c

# Build target
all: $(TARGET)

# Compile the source file into the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)
