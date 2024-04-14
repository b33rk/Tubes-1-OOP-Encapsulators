# Set the compiler executable
COMPILER = g++

# Source files
SRC_FILES = main.cpp	\
        

# Build main.exe directly from source files
main.exe: $(SRC_FILES)
	$(COMPILER) -o $@ $^

# Clean up main.exe
.PHONY: clean
clean:
	rm -f main.exe