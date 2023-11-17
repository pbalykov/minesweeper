.PHONY:  all run clean

NAME = minesweepes
NCURSES_HEADER = `pkg-config --cflags ncurses`
NCURSES_LD = `pkg-config --libs ncurses`
SRC = src/
OBJ = obj/
SANITIZE = -fsanitize=address -fsanitize=undefined 

all: bin obj main

bin: 
	mkdir -p bin
obj:
	mkdir -p obj

main: $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(wildcard $(SRC)*.cpp))
	c++ $^ -o bin/$(NAME) $(NCURSES_LD) $(SANITIZE) -g 

$(OBJ)interface.o: $(SRC)interface.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(SANITIZE) -g

$(OBJ)render.o: $(SRC)render.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(SANITIZE) -g

$(OBJ)color_game.o: $(SRC)color_game.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(SANITIZE) -g


$(OBJ)%.o: $(SRC)%.cpp
	c++ -c $^ -o $@ -g $(SANITIZE)

run: all
	./bin/$(NAME) 2> error
	cat error

clean:
	rm -rf bin obj 
