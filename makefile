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
        
# Build main (or main.app for clarity on macOS, though not required)
build:
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Player.cpp -o $(OUTPUT_FOLDER)/Player.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Farmers.cpp -o $(OUTPUT_FOLDER)/Farmers.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Petani.cpp -o $(OUTPUT_FOLDER)/Petani.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Peternak.cpp -o $(OUTPUT_FOLDER)/Peternak.o
	$(COMPILER) $(SOURCE_FOLDER)/$(PLAYER_FOLDER)/Walikota.cpp -o $(OUTPUT_FOLDER)/Walikota.o
	@$(LIN) $(OUTPUT_FOLDER)/*.o -o $(OUTPUT_FOLDER)/main

<<<<<<< Updated upstream
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

=======
run:
	./$(OUTPUT_FOLDER)/main
>>>>>>> Stashed changes

# Clean up main (no .exe)
.PHONY: clean
clean:
	rm -f $(OUTPUT_FOLDER)/main $(OUTPUT_FOLDER)/*.o
