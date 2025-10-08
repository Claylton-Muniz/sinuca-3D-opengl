CC = gcc
SRC = src/*.c src/*/*.c
EXEC = build/sinuca3D

# Detecta o sistema
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	FLAGS = -lGL -lGLU -lglut -lm
else
ifeq ($(UNAME_S), Darwin)
	# Flags para macOS (Darwin)
	FLAGS = -framework OpenGL -lglut -lm
else
	# Assume que é Windows ou outro sistema que precise destas libs
	FLAGS = -lopengl32 -lglu32 -lfreeglut -lm -IC:\SOIL2-master\src\SOIL2 -LC:\SOIL2-master\src\SOIL2 -lSOIL2
endif
endif

all:
	$(CC) $(SRC) -o $(EXEC) $(FLAGS) && ./$(EXEC)

clean:
	rm -f $(EXEC)