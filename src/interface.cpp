#include "../headers/interface.hpp"
#include "../headers/render.hpp"
#include "../headers/color_game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>

Interface::Interface() {
    initscr();
    noecho();
    keypad(stdscr, true);  
    std::srand(std::time(nullptr));
    Color tmp;
    return ;
}

int Interface::exec() {
    int value = this->game();
    endwin();
    if ( value ) {
        std::cerr << "The game does not fit in the window size!" << std::endl;
    }
    return value;
}

int Interface::game() {
    Minesweeper game;
    std::pair<int, int> cursor(0, 0);
    auto size_field = game.size();
    if ( printGame(game, cursor, 0) ) {
        return 1;
    }
    auto start = time(NULL);
    timeout(500);
    while ( !game.get_end_game() ) {
	auto key = getch();
	switch ( key ) {
	    case ERR :
		break;
	    case KEY_UP :
                cursor.first = ( (cursor.first - 1) % size_field.first + size_field.first) % size_field.first; 
                break;
	    case KEY_DOWN :
	        cursor.first = (cursor.first + 1) % size_field.first;
	        break;
	    case KEY_LEFT :
		cursor.second = ( (cursor.second - 1)  % size_field.second + size_field.second) % size_field.second;
		break;
	    case KEY_RIGHT :
		cursor.second = (cursor.second + 1) % size_field.second;
	        break;
	    case 'f':
		game.set_index(cursor.first, cursor.second, USER_ACTION::FLAG);
		break;
	    case KEY_BACKSPACE :
		game.set_index(cursor.first, cursor.second, USER_ACTION::DELETION);
		break;
	    case '\n':
		game.set_index(cursor.first, cursor.second, USER_ACTION::OPEN);
		break;
	    case KEY_RESIZE:
		clear();
		break;
        }
	auto finish = time(NULL); 
	int elapsed_time = finish - start; 
	if ( printGame(game, cursor, elapsed_time) ) {
	    return 1;
	}
    }
    timeout(-1);
    getch();
    return 0;
}
