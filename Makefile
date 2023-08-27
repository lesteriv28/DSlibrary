# List of source files and corresponding object files
SOURCES = test_myDSlibrary.c DSlibrary.c test_mystring.c test_list.c test_tracker.c
OBJECTS = $(SOURCES:.c=.o)

# Main target
all: test_myDSlibrary

# Compile all .c files into .o files
%.o : %.c
	$(CC) -c $(CCFLAGS) $< -o $@

# Build test_DSlibrary if necessary
test_myDSlibrary: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

# Clean up generated files
clean:
	rm -f $(OBJECTS) test_myDSlibrary


