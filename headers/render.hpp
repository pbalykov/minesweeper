#ifndef RENDER_HPP
#define RENDER_HPP

#include "color.hpp"
#include "game_minesweeper.hpp"
#include <ncurses.h>
#include <string_view>

class Render {
public:
    Render();

    int menu(const std::string_view* button, int size_y, int size_x, int cur = 0);
    int abaut_game(const std::string_view* value, int size_y, int size_x);
    int draw_game(const Game_Minesweeper& value);

private:
    void _size_terminal(int& y, int& x) const;
    void _draw_table(int begin_y, int begin_x, int y, int x, 
          int first_begin = ACS_ULCORNER, int second_begin = ACS_URCORNER, 
          int first_end = ACS_LLCORNER, int second_end = ACS_LRCORNER, 
          int center_x = ACS_HLINE, int center_y = ACS_VLINE) const;
    void _draw_flag_time(time_t time, short flag, int y, int first_x, int second_x);
    void _draw_field(const Game_Minesweeper& other, int y, int x);
    Color _color;
};

#endif
