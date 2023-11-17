#include "../headers/color.hpp"
#include <ncurses.h>
#include <iostream>

Color::Color() : color_current(COLOR::DEFAULT) {
    if ( has_colors() ) {
 	    start_color();
    }
    use_default_colors();
    init_pair(static_cast<int>(COLOR::DEFAULT_BLUE), -1, COLOR_BLUE);
    init_pair(static_cast<int>(COLOR::BLACK_GREEN), COLOR_BLACK, COLOR_GREEN);
    init_pair(static_cast<int>(COLOR::RED_BLUE), COLOR_RED, COLOR_BLUE);
    init_pair(static_cast<int>(COLOR::YELLOW_BLUE), COLOR_YELLOW, COLOR_BLUE);
    init_pair(static_cast<int>(COLOR::RED), COLOR_RED, -1);
    init_pair(static_cast<int>(COLOR::GREEN), COLOR_GREEN, -1);
    init_pair(static_cast<int>(COLOR::GREY), COLOR_BLACK, COLOR_WHITE);
    return ;
}

COLOR Color::get_color() const {
    return this->color_current;
}

void Color::set_color(const COLOR value) {
    if ( value == COLOR::DEFAULT ) {
        attroff(COLOR_PAIR(static_cast<int>(this->color_current)));
    }
    else {
        attron(COLOR_PAIR(static_cast<int>(value)));
    }
    this->color_current = value;
    return ;
}
