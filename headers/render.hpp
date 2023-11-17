#ifndef RENDER_HPP
#define RENDER_HPP

#include "color.hpp"
#include "minesweeper.hpp"
#include <string_view>

class Render {
public:
    Render();

    int menu(const std::string_view* button, int size_y, int size_x, int cur = 0);
    int abaut_game(const std::string_view* value, int size_y, int size_x);
    int draw_game(const Minesweeper& value, int y, int x);

private:
    void _size_terminal(int& y, int& x) const;
    void _draw_table(int begin_x, int begin_y, int x, int y) const;
    
    Color _color;
};

#endif
