#ifndef COLOR_GAME_HPP
#define COLOR_GAME_HPP

#include <ncurses.h>

enum class COLOR {
    DEFAULT = 0, 
    DEFAULT_BLUE = 1,
    BLACK_GREEN = 2,
    RED_BLUE = 3,
    YELLOW_BLUE = 4,
    RED = 5,
    GREEN = 6,
};

class Color {
public:
    Color();

    static COLOR get_color();
    static void set_color(const COLOR value);

private:
    static COLOR color_current;

};

#endif
