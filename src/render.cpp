#include "../headers/render.hpp"
#include <ncurses.h>
#include <iostream>

namespace {
    void repeat(int value_char, int size) {
	    for (int i = 0; i < size; i++) {
	        addch(value_char);
        }
	    return ;
    }
}

void Render::_draw_table(int begin_y, int begin_x, int y, int x) const {
    move(begin_y, begin_x);
   	addch(ACS_ULCORNER);
    repeat(ACS_HLINE, x);
	addch(ACS_URCORNER);
	for (int i = 0; i < y; i++) {
	    move(begin_y + i + 1, begin_x);
	    addch(ACS_VLINE);
	    move(begin_y + i + 1, begin_x + x + 1);
	    addch(ACS_VLINE);
	}
    move(begin_y + y + 1, begin_x);
    addch(ACS_LLCORNER);
	repeat(ACS_HLINE, x);
	addch(ACS_LRCORNER);
    move(begin_y + y + 1, begin_x + x + 1);
    return ;
}

void Render::_size_terminal(int& y, int& x) const {
  	getmaxyx(stdscr, y, x);
  	return ;
}

Render::Render() {
    noecho(); 
    return ;
}

int Render::menu(const std::string_view* button, int size_y, int size_x, int cur) {
    int y, x;
    this->_size_terminal(y, x);
    y = y / 2 - (size_y  + 1 ) / 2;
    x = x / 2 - size_x / 2;
    this->_draw_table(y, x, size_y + 1, size_x);
    move(y, x + ((size_x - button[0].size()) / 2) + 1); 
    printw("%s", button[0].data());
    y += 2;
    for (int i = 1; i < size_y; i++) {
        move(y++, x + 1);
        if ( cur == i ) {
            this->_color.set_color(COLOR::GREY);
            repeat(' ', size_x);
            move(y - 1, x + ((size_x - button[i].size()) / 2 + 1));
            printw("%s", button[i].data());
            this->_color.set_color(COLOR::DEFAULT);
        } 
        else {
            move(y - 1, x + ((size_x - button[i].size()) / 2 + 1));
            printw("%s", button[i].data());
        }
    }
    return 0;
}

int Render::abaut_game(const std::string_view* value, int size_y, int size_x) {
    int y, x;
    this->_size_terminal(y, x);
    if ( y < size_y + 2 || x < size_x + 2) {
        return 1;
    }
    y = y / 2 - size_y / 2;
    x = x / 2 - size_x / 2;
    this->_draw_table(y, x - 1 , size_y, size_x);
    move(y, x + ((size_x - value[0].size()) / 2)); 
    printw("%s", value[0].data());
    y += 1;
    for (int i = 1; i < size_y; i++) {
        move(y++, x);
        printw("%s", value[i].data());
    }
    return 0;
}

int Render::draw_game(const Minesweeper& other, int y, int x) {
    std::pair<int, int> size_field = other.size();
    move(0, 0);
    this->_color.set_color(COLOR::DEFAULT_BLUE);
    for (int i = 0; i < size_field.first; i++) {
        for (int j = 0; j < size_field.second; j++) {
	        auto value = other.get_index(i, j);
	        switch ( value.first ) {
		        case TYPE_CELL::HIDDEN :
		            this->_color.set_color(COLOR::DEFAULT_BLUE);
                    addch(' ');
      		        break;
    		    case TYPE_CELL::VALUE :
                    this->_color.set_color(COLOR::BLACK_GREEN);
	                addch(value.second ? 48 + value.second : ' ');
		            break;
        		case TYPE_CELL::BOMB :
		            attron(A_BLINK | A_BOLD);
                    this->_color.set_color(COLOR::RED_BLUE);
        		    addch('*');
           	        attroff(A_BLINK | A_BOLD);
	                break;
        		case TYPE_CELL::FLAG :
		        case TYPE_CELL::TRUE_FLAG :
		            attron(A_BOLD);
	                this->_color.set_color(COLOR::YELLOW_BLUE);
      		        addch('F');
		            attroff(A_BOLD);
		            break;

		        case TYPE_CELL::FALSE_FLAG :
		           attron(A_BOLD);
                   this->_color.set_color(COLOR::RED_BLUE);
       		       addch('F');
		           attroff(A_BOLD);
	               break;
		        default:
		          addch(' ');
		          break;
	     } 
	 }
     move(i + 1, 0);
     }
     move(y, x);
     this->_color.set_color(COLOR::DEFAULT);
     return 0;
}
