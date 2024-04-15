# Set the compiler executable
COMPILER = gcc
LIN = ld

# Source files
SRC_FILES = main.cpp

# Directory
SOURCE_FOLDER = src
OUTPUT_FOLDER = bin
PLAYER_FOLDER = Player
EXCEPTION_FOLDER = Exception
FIELD_OBJECT_FOLDER = FieldObject
GAME_MASTER_FOLDER = GameMaster
GAME_OBJECT_FOLDER = GameObject

ALLPLAYERFILE := $(wildcard src/Player/*.cpp)

# Build main.exe directly from source files
build:
	$(COMPILER) -o bin/main.o src/main.cpp ${ALLPLAYERFILE}

run :
	$(OUTPUT_FOLDER)/main.o


# Clean up main (no .exe)
.PHONY: clean
clean:
	rm -f $(OUTPUT_FOLDER)/main $(OUTPUT_FOLDER)/*.o
