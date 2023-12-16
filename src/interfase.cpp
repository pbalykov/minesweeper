#include "../headers/interfase.hpp"
#include <cstdlib>
#include <ctime>

#include <iostream>

#include <ncurses.h>
#include <string.h>

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
    cbreak();
    curs_set(0);
    std::srand(std::time(nullptr));
    return ;
}

int Interfase::exec() {
    this->menu();
    return 0;
}

Interfase::~Interfase() { 
    curs_set(1);
    endwin();
    if ( this->_error ) {
       fprintf(stderr, "Error: %s\n", this->_error);
       free(this->_error);
    }
    delete this->_render;
    return ;
}

int Interfase::menu() {
    int cursor = 0;
    int size_menu_y = sizeof(Interfase::MENU) / sizeof(std::string_view);
    int size_menu_x = this->_max_button_size(Interfase::MENU, size_menu_y);
    int size_name = sizeof(Interfase::NAME_PROGMA) / sizeof(std::string_view);
    int size_menu = size_menu_y - 1;
    for ( ; ;) {
        wclear(stdscr);
        int error = this->_render->main_menu(Interfase::MENU, size_menu_y, size_menu_x, 
                                 cursor + 1, Interfase::NAME_PROGMA, size_name);
        if ( error ) {
            this->_error = strdup("size terminal!");
            return 1;
        }
      	auto key = getch();
        switch (key) {
            case KEY_UP :
                cursor = ( (cursor - 1) % size_menu + size_menu) % size_menu; 
                break;
    	    case KEY_DOWN :
                cursor = ( (cursor + 1) % size_menu + size_menu) % size_menu;
	            break;
            case '\n' : 
            {
                switch ( cursor ) {
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
    } 
    return 0;
}

int Interfase::game() {
    Complexity_Game complexity;
    this->_choice_complexity(complexity);
    this->_game.start(complexity);
    auto len_game = this->_game.size();
    int size_bar = sizeof(Interfase::BAR_CONTROL) / sizeof(std::string_view);
    curs_set(1);
    timeout(500);
    while ( !this->_game.get_end_game() ) {
        wclear(stdscr);
        this->_render->draw_game(this->_game, Interfase::BAR_CONTROL, size_bar);
      	auto key = getch();
        switch ( key ) {
    	    case KEY_UP :
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::UP);
                break;
    	    case KEY_DOWN :
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::DOWN);
    	        break;
    	    case KEY_LEFT :
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::LEFT);
        		break;
    	    case KEY_RIGHT :
	            this->_game.set_cell(Game_Minesweeper::TYPE_STEP::RIGHT);
    	        break;
    	    case 'f':
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::FLAG);
        		break;
    	    case KEY_BACKSPACE :
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::DELETE);
       		    break;
	        case '\n':
                this->_game.set_cell(Game_Minesweeper::TYPE_STEP::OPEN);
       		    break;
            default :
                break;
        }
    }
    timeout(-1);
    wclear(stdscr);
    this->_render->draw_game(this->_game, Interfase::BAR_CONTROL, size_bar);
    getch();
    curs_set(0);
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
                break ;
        }
    }
    return 0;
}
