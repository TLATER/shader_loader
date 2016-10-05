CC = g++
CFLAGS = -fpic -c -Wall -std=c++11 -pedantic
LDFLAGS = -lGLEW -lGL

_OBJ = shader.o shader_program.o
OBJ = $(addprefix obj/,$(_OBJ))

# Include libs
LDFLAGS +=

all: libshader.a libshader.so

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ -Iinclude

libshader.a: $(OBJ) $(LDFLAGS)
	ar -rcs $@ $^

libshader.so: $(OBJ) $(LDFLAGS)
	$(CC) -shared -o $@ $^

.PHONY: clean test

clean:
	rm libshader.a libshader.so obj/*
