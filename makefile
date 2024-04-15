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
        

# Build main.exe directly from source files
build:
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Player.cpp -o $(OUTPUT_FOLDER)/Player.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Farmers.cpp -o $(OUTPUT_FOLDER)/Farmers.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Petani.cpp -o $(OUTPUT_FOLDER)/Petani.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Peternak.cpp -o $(OUTPUT_FOLDER)/Peternak.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Walikota.cpp -o $(OUTPUT_FOLDER)/Walikota.o
	@$(LIN) bin/*.o -o $(OUTPUT_FOLDER)/main

run :
	./main


# Clean up main.exe
.PHONY: clean
clean:
	rm -f main.exe