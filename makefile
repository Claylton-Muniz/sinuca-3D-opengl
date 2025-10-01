CC = gcc
SRC = src/*.c src/*/*.c
EXEC = build/sinuca3D

# Detecta o sistema
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    FLAGS = -lGL -lGLU -lglut -lm
endif

ifeq ($(OS), Windows_NT)
    FLAGS = -lopengl32 -lglu32 -lfreeglut -lm
endif

all:
	$(CC) $(SRC) -o $(EXEC) $(FLAGS) && ./$(EXEC)

clean:
	rm -f $(EXEC)