CC = g++
SRC = src/*.cpp src/*/*.cpp
EXEC = build/sinuca3D

# Detecta o sistema
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    FLAGS = -lGL -lGLU -lglut -lm -lassimp -lSOIL
endif

ifeq ($(OS), Windows_NT)
    FLAGS = -lopengl32 -lglu32 -lfreeglut -lm -lassimp -lSOIL
endif

# Adicione flags do compilador
CFLAGS = -std=c++11 -I./include

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(FLAGS) && ./$(EXEC)

clean:
	rm -f $(EXEC)