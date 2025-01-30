#include "../headers/render.hpp"

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
        printw("%*c", x, ' ');
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

int Render::_draw_name(int y, int x, const std::string_view* name, int size_name) {
    move(y, x);
    for (int i = 0; i < size_name; i++) {
        printw("%s", name[i].data());
        move(y + 1 + i, x);
    }
    return 0;
}

void Render::_draw_menu(int y, int x, const std::string_view* button, 
                         int size_y, int size_x, int cur) {
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
    return ;
}

int Render::main_menu(const std::string_view* arr_button, int size_y, int size_x, 
               int cur, const std::string_view* arr_name, int size_arr) {
    int y, x;
    this->_size_terminal(y, x);
    int begin_y = y / 2 - (size_y  + 1 ) / 2;
    int begin_x = x / 2 - size_x / 2;
    if ( begin_y < 0 || begin_x < 0 ) {
        return 1;
    }
    this->_draw_menu(begin_y, begin_x, arr_button, size_y, size_x, cur);
    begin_y -= size_arr;
    begin_x = x / 2 - arr_name[0].size() / 2;
    if ( begin_y < 0 || begin_x < 0 ) {
        return 1;
    }
    this->_draw_name(begin_y, begin_x, arr_name, size_arr);   
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

int Render::draw_game(const Game_Minesweeper& other, const std::string_view* button,
                      int button_size) {
    this->_draw_bar(button, button_size);
    this->draw_game(other);
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
    if ( other.get_end_game() ) {
        this->_draw_message_end(other, begin_y_folder - 4, x);
    }
    this->_draw_flag_time(time, flag, begin_y_folder - 3, begin_x_folder - 3,
                          begin_x_folder + size_field.second - 2);
    this->_draw_field(other, begin_y_folder, begin_x_folder);
    return 0;
}


int Render::menu(const std::string_view* button, int button_y, int button_x, 
                 int cur) {
    int y, x;
    this->_size_terminal(y, x);
    y = y / 2 - (button_y  + 1 ) / 2;
    x = x / 2 - button_x / 2;
    this->_draw_menu(y, x, button, button_y, button_x, cur);
    return 0;
}

int Render::meny_YES_NO(const std::string_view NAME, int currsor) {
    int y, x;
    this->_size_terminal(y, x); 
    y = y / 2 - 1;
    x = x / 2 - (NAME.size() + 2) / 2;
    this->_draw_table(y, x, 2, NAME.size());
    move(y, x + 1);
    printw("%s", NAME.data());
    move(y + 2, x + 1);    
    this->_color.set_color(!currsor? COLOR::GREY : COLOR::DEFAULT);
    printw(" Yes ");
    this->_color.set_color(!currsor ? COLOR::DEFAULT : COLOR::GREY);
    move(y + 2, x + NAME.size() - 3);
    printw(" No ");
    this->_color.set_color(COLOR::DEFAULT);
    return 0;
}

void Render::_draw_bar(const std::string_view* button, int size) {
    int y, x;
    this->_size_terminal(y, x);
    move(y - 1, 0);
    int m_size = 0;
    for (int i = 0; i < size; i+=2) {
        printw("%s ", button[i].data());
        this->_color.set_color(COLOR::GREY);
        printw("%s ", button[i + 1].data());
        m_size += button[i + 1].size() + button[i].size() + 2;
        this->_color.set_color(COLOR::DEFAULT);
    }
    this->_color.set_color(COLOR::GREY);
    repeat(' ', x - m_size);
    this->_color.set_color(COLOR::DEFAULT);
    return ;
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

void Render::_draw_message_end(const Game_Minesweeper& other, int y, int x) {
    std::string_view value = other.message_end_game();
    move(y,  x / 2 - value.size() / 2);
    attron(A_BOLD);
    switch ( other.type_end_game() ) {
        case Game_Minesweeper::TYPE_END_GAME::WON : 
            this->_color.set_color(COLOR::GREEN);
            printw("%s", value.data());
            this->_color.set_color(COLOR::DEFAULT);
            break;
        default:
            this->_color.set_color(COLOR::RED);
            printw("%s", value.data());
            this->_color.set_color(COLOR::DEFAULT);
            break;
    }
   	attroff(A_BOLD);
    return ;
}


void Render::_draw_field(const Game_Minesweeper& other, int y, int x) {
    move(y, x);
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
        move(y + i + 1, x);
    }
    move(y + other.get_cursor_y(), x + other.get_cursor_x());
    return ;
}
