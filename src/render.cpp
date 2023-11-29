#include "../headers/render.hpp"

namespace {
    void repeat(int value_char, int size) {
	    for (int i = 0; i < size; i++) {
	        addch(value_char);
        }
	    return ;
    }
}

void Render::_draw_table(int begin_y, int begin_x, int y, int x,
        int first_begin, int second_begin, int first_end, int second_end, 
        int center_x, int center_y) const {
    move(begin_y, begin_x);
   	addch(first_begin);
    repeat(center_x, x);
	addch(second_begin);
	for (int i = 0; i < y; i++) {
	    move(begin_y + i + 1, begin_x);
	    addch(center_y);
	    move(begin_y + i + 1, begin_x + x + 1);
	    addch(center_y);
	}
    move(begin_y + y + 1, begin_x);
    addch(first_end);
	repeat(center_x, x);
	addch(second_end);
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

int Render::draw_game(const Game_Minesweeper& other) {
    auto size_field = other.size();
    int y, x;
    this->_size_terminal(y, x);
    int begin_y_folder = y / 2 - size_field.first / 2 ;
    int begin_x_folder = x / 2 - size_field.second / 2;
    time_t time = other.get_time();
    short flag = other.get_flag();
    this->_draw_flag_time(time, flag, begin_y_folder - 3, begin_x_folder - 3,
                          begin_x_folder + size_field.second);
//    this->_draw_table(begin_y_folder, begin_x_folder, 
//            size_field.first, size_field.second, '#', '#', '#', 
//            '#', '#', '#');

    this->_draw_field(other, begin_y_folder, begin_x_folder);

    return 0;
}


void Render::_draw_flag_time(time_t time, short flag, 
                             int y, int first_x, int second_x) {
    this->_draw_table(y, first_x, 1, 3);
    this->_draw_table(y, second_x, 1, 3);
    move(y + 1, first_x + 1);
    printw("%03d", time);
    move(y + 1, second_x + 1);
    printw("%03d", flag);
    return ;
}

void Render::_draw_field(const Game_Minesweeper& other, int y, int x) {
    move(y + 1, x + 1);
    this->_color.set_color(COLOR::DEFAULT_BLUE);
    auto size = other.size();
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
       	    auto value = other.get_cell(i, j);
            switch (value.first) {
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
        this->_color.set_color(COLOR::DEFAULT);
        move(y + i + 2, x + 1);
    }
    move(y + 1 + other.get_cursor_y(), x + 1 + other.get_cursor_x());
    return ;
}
