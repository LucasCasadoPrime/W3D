SRC_DIR = src
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDES_PATH = -I./include -I./include/interface -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBS_PATH = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
COMPILER_FLAGS = -std=c++11 -Wall -g -O0 -v
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDES_PATH) $(LIBS_PATH) $(SRC_FILES) -o $(OBJ_NAME)

clean:
	rm -f $(OBJ_NAME)

run:
	./$(OBJ_NAME)
