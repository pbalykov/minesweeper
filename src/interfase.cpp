#include "../headers/interfase.hpp"
#include <cstdlib>
#include <ctime>

#include <iostream>

#include <ncurses.h>
#include <cstring>

int Interfase::_max_button_size(const std::string_view* value, int size_v) {
    int max = 0;
    for (int i = 0; i < size_v; i++) {
        max = (value[i].size() > max ? value[i].size() : max);
    }
    return max;
}

Interfase::Interfase() : _error(nullptr), _render(nullptr) {
    initscr();
    noecho();
    this->_render = new Render;
    keypad(stdscr, true);  
    std::srand(std::time(nullptr));
    return ;
}

int Interfase::exec() {
    this->_main_menu();
    return 0;
}

Interfase::~Interfase() { 
    endwin();
    if ( this->_error ) {
       fprintf(stderr, "Error: %s\n", this->_error);
       std::free(this->_error);
    }
    delete this->_render;
    return ;
}

int Interfase::_main_menu() {
    int cursor = 0;
    int size_y = sizeof(Interfase::MENU) / sizeof(std::string_view) - 1;
    int size_x = this->_max_button_size(Interfase::MENU, size_y);
    do {
        wclear(stdscr);
        this->_render->menu(Interfase::MENU, size_y + 1, size_x, cursor + 1);
      	auto key = getch();
        switch (key) {
            case KEY_UP :
                cursor = ( (cursor - 1) % size_y + size_y) % size_y;
                break;
    	    case KEY_DOWN :
                cursor = ( (cursor + 1) % size_y + size_y) % size_y;
	            break;
            case '\n' : 
            {
                switch (cursor ) {
                    case 0:
                        this->game();
                        break;
                    case 1:
                        if (this->abaut_game() ) {
                            return 1;
                        }
                        break;
                    case 2:
                        return 0;
                }
            }
        }
    } while (true);
    return 0;
}

int Interfase::game() {
    Complexity_Game complexity;
    this->_choice_complexity(complexity);
    this->_game = Minesweeper(complexity);
    auto len_game = this->_game.size();
    int cursor_x = 0, cursor_y = 0;
    while ( !this->_game.get_end_game() ) {
        this->_render->draw_game(this->_game, cursor_y, cursor_x);
      	auto key = getch();
        switch ( key ) {
    	    case KEY_UP :
                cursor_y = ( (cursor_y - 1) % len_game.first + len_game.first);
                cursor_y %= len_game.first;
                break;
    	    case KEY_DOWN :
    	        cursor_y = (cursor_y + 1) % len_game.first;
    	        break;
    	    case KEY_LEFT :
		        cursor_x = (cursor_x - 1) % len_game.second + len_game.second;
                cursor_x %= len_game.second;
        		break;
    	    case KEY_RIGHT :
	        	cursor_x = (cursor_x + 1) % len_game.second;
    	        break;
    	    case 'f':
	        	this->_game.set_index(cursor_y, cursor_x, USER_ACTION::FLAG);
        		break;
    	    case KEY_BACKSPACE :
    	    	this->_game.set_index(cursor_y, cursor_x, USER_ACTION::DELETION);
        		break;
	        case '\n':
        		this->_game.set_index(cursor_y, cursor_x, USER_ACTION::OPEN);
        		break;
        }
    }
    return 0;
}

int Interfase::abaut_game() {
    int size_y = sizeof(Interfase::ABAUT_GAME) / sizeof(std::string_view);
    int size_x = this->_max_button_size(Interfase::ABAUT_GAME, size_y);
    bool end_abaut_game = true;
    for ( ; end_abaut_game ; ) {
        wclear(stdscr);
        if ( this->_render->abaut_game(Interfase::ABAUT_GAME, 
                                       size_y, size_x) ) {
            return 1;
        }
        auto key = getch();
        if ( key != KEY_RESIZE ) {
             end_abaut_game = false;
        } 
    } 
    return 0;
}

int Interfase::_choice_complexity(Complexity_Game& value) {
    int size_y = sizeof(Interfase::COMPLEXITY) / sizeof(std::string_view) - 1;
    int size_x = this->_max_button_size(Interfase::COMPLEXITY, size_y);
    int cursor = 0;
    bool end_choice_comp = true;
    for ( ; end_choice_comp; ) {
        wclear(stdscr);
        this->_render->menu(Interfase::COMPLEXITY, size_y + 1, size_x, cursor + 1);
        auto key = getch();
        switch ( key ) {
            case KEY_UP :
                cursor = ( (cursor - 1) % size_y + size_y) % size_y;
                break;
    	    case KEY_DOWN :
                cursor = ( (cursor + 1) % size_y + size_y) % size_y;
	            break;
            case '\n':
                end_choice_comp = false;
                value = Complexity_Game(static_cast<enum COMPLEXITY>(cursor + 1));
        }
    }
    return 0;
}
