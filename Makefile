.PHONY:  all run clean

NAME = minesweepes
NCURSES_HEADER = `pkg-config --cflags ncurses`
NCURSES_LD = `pkg-config --libs ncurses`
SRC = src/
OBJ = obj/


all: bin obj main

bin: 
	mkdir -p bin
obj:
	mkdir -p obj

main: $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(wildcard $(SRC)*.cpp))
	c++ $^ -o bin/$(NAME) $(NCURSES_LD) -O3 -std=c++17

$(OBJ)interface.o: $(SRC)interface.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) -O3 -std=c++17

$(OBJ)render.o: $(SRC)render.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) -O3 -std=c++17

$(OBJ)color_game.o: $(SRC)color_game.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) -O3 -std=c++17


$(OBJ)%.o: $(SRC)%.cpp
	c++ -c $^ -o $@ -O3 -std=c++17

run: all
	./bin/$(NAME)

clean:
	rm -rf bin obj 
