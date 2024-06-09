# Compiler and flags
TARGET_CC = aarch64-none-linux-gnu-gcc
HOST_CC = gcc
CFLAGS = -Wall
TARGET_CFLAGS = $(CFLAGS)
HOST_CFLAGS = $(CFLAGS)

# Source files
SRC = writer.c

# Object files
TARGET_OBJ = writer.o
HOST_OBJ = writer.o

# Targets
TARGET_EXEC = writer
HOST_EXEC = writer

.PHONY: all clean

all: host

#target: $(TARGET_EXEC)

host: $(HOST_EXEC)

# Link target executable
#$(TARGET_EXEC): $(TARGET_OBJ)
#	$(TARGET_CC) $^ -o $@

# Link host executable
$(HOST_EXEC): $(HOST_OBJ)
	$(HOST_CC) $^ -o $@

# Compile target object
#%.o: %.c
#	$(TARGET_CC) $(TARGET_CFLAGS) -c $< -o $@

# Compile host object
writer_host.o: writer.c
	$(HOST_CC) $(HOST_CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(TARGET_OBJ) $(HOST_OBJ) $(TARGET_EXEC) $(HOST_EXEC)
