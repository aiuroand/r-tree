CXXFLAGS = -std=c++20 -Wall -pedantic
HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
LIBS=-lSDL2 -lSDL2_ttf

.PHONY: all
all: compile

.PHONY: run
run: compile
	./program

.PHONY: compile
compile: program

program: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@ $(LIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -rf username build/ debug/ doc/ 2>/dev/null
	rm program