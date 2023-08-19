#include "../headers/render.hpp"
#include "../headers/color_game.hpp"
#include <ncurses.h>
#include <cstring>

namespace {
    void repeat(int value_char, int size) {
	for (int i = 0; i < size; i++) {
	    addch(value_char);
	}
	return ;
    }

    void tableBorder(std::pair<int, int> begin_curses, 
		                         std::pair<int, int> size) {
	move(begin_curses.first, begin_curses.second);
	addch(ACS_ULCORNER);
	repeat(ACS_HLINE, size.second);
	addch(ACS_URCORNER);

	for (int i = 0; i < size.first; i++) {
	    move(begin_curses.first + i + 1, begin_curses.second);
	    addch(ACS_VLINE);
	    move(begin_curses.first + i + 1, begin_curses.second + size.second + 1);
	    addch(ACS_VLINE);
	}

	move(begin_curses.first + size.first + 1, begin_curses.second);
        addch(ACS_LLCORNER);
	repeat(ACS_HLINE, size.second);
	addch(ACS_LRCORNER);
        move(begin_curses.first + 1, begin_curses.second + 1);
	return ;
    }

    void tableFolder(std::pair<int, int> begin_curses,
		                         std::pair<int, int> size) {

	move(begin_curses.first, begin_curses.second);
	repeat('#', size.second + 2);
        for (int i = 0; i < size.first; i++) {
	    move(begin_curses.first + i + 1, begin_curses.second);
	    addch('#');
	    move(begin_curses.first + i + 1, begin_curses.second + size.second + 1);
	    addch('#');
	}
	move(begin_curses.first + size.first + 1, begin_curses.second);
	repeat('#', size.second + 2);
	move(begin_curses.first + 1, begin_curses.second + 1);
	return ;
    }
    
    std::pair<int, int> size_terminal() {
	int a, b;
	getmaxyx(stdscr, a, b);
	return std::make_pair(a, b);
    }

    void printEnd(std::pair<int, int> begin_curses, const char* message, 
		  COLOR color_message, int curses_x_press) {

	move(begin_curses.first, begin_curses.second);
        attron(A_BOLD);
	Color::set_color(color_message);
	printw(message);
	Color::set_color(COLOR::DEFAULT);
	attroff(A_BOLD);

	move(begin_curses.first + 1, curses_x_press);
	Color::set_color(COLOR::RED);
	printw(PRESS);
	Color::set_color(COLOR::DEFAULT);

	return ;
    }   	
}


int printGame(const Minesweeper& other, std::pair<int, int> cursor_game) {
   std::pair<int, int> size_term(size_terminal()); 
   std::pair<int, int> size_field(other.size());
   int characters_height = size_field.first + 7;
   int characters_width = size_field.second + 2;

   if (size_term.first < characters_height || 
        size_term.second < characters_width ) {
       return 1;
   }
   std::pair<int, int> cursor(0, 0);
   cursor.first = size_term.first / 2 - characters_height / 2; 
   if ( other.get_end_game() ) {
       const char* mess = other.get_wing_game() ? WING : LOSE;
       COLOR color_mess = other.get_wing_game() ? COLOR::GREEN : COLOR::RED;
       cursor.second = size_term.second / 2 - std::strlen(mess) / 2;
       int cursor_x_press = size_term.second / 2 - std::strlen(PRESS) / 2;
       printEnd(cursor, mess, color_mess, cursor_x_press);
   }
   cursor.first += 2;
   cursor.second = size_term.second / 2 - size_field.second / 2 - 3 ; 
   tableBorder(cursor, std::make_pair(1, 3));
   printw("%03d", other.get_number_flag());
   cursor.second = size_term.second / 2 - size_field.second / 2 ;
   cursor.second += size_field.second - 2 ; 
   tableBorder(cursor, std::make_pair(1, 3));
   printw("000");

   cursor.first += 3;
   cursor.second = size_term.second / 2 - (size_field.second + 2) / 2; 
   printField(cursor, other);
   move(cursor.first + 1 + cursor_game.first, 
        cursor.second + 1 + cursor_game.second);

   return 0;
}
      

void printField(std::pair<int, int> begin_curses, const Minesweeper& OTHER) {

     std::pair<int, int> size_field = OTHER.size();
     Color::set_color(COLOR::DEFAULT_BLUE);
     tableFolder(begin_curses, size_field);
     for (int i = 0; i < size_field.first; i++) {
	 for (int j = 0; j < size_field.second; j++) {
	     auto value = OTHER.get_index(i, j);
	     switch ( value.first ) {
		 case TYPE_CELL::HIDDEN :
		     Color::set_color(COLOR::DEFAULT_BLUE);
		     addch(' ');
		     break;
		 case TYPE_CELL::VALUE :
                     Color::set_color(COLOR::BLACK_GREEN);
	             addch(value.second ? 48 + value.second : ' ');
		     break;
		 case TYPE_CELL::BOMB :
		     attron(A_BLINK | A_BOLD);
                     Color::set_color(COLOR::RED_BLUE);
		     addch('*');
		     attroff(A_BLINK | A_BOLD);
	             break;
		 case TYPE_CELL::FLAG :
		 case TYPE_CELL::TRUE_FLAG :
		     attron(A_BOLD);
	             Color::set_color(COLOR::YELLOW_BLUE);
		     addch('F');
		     attroff(A_BOLD);
		     break;

		 case TYPE_CELL::FALSE_FLAG :
		     attron(A_BOLD);
                     Color::set_color(COLOR::RED_BLUE);
		     addch('F');
		     attroff(A_BOLD);
	             break;


		 default:
		     addch(' ');
		     break;
	     } 
	 }
         move(begin_curses.first + 2 + i, begin_curses.second + 1);
     }
     move(begin_curses.first + 1, begin_curses.second + 1);
     Color::set_color(COLOR::DEFAULT);
     return ;
}
