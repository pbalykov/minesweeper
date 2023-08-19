#include "../headers/color_game.hpp"

COLOR Color::color_current = COLOR::DEFAULT;

Color::Color() {
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
    return ;
}

COLOR Color::get_color() {
    return Color::color_current;
}

void Color::set_color(const COLOR value) {
    if ( value == COLOR::DEFAULT ) {
	attroff(COLOR_PAIR(static_cast<int>(Color::color_current)));
    }
    else {
	 attron(COLOR_PAIR(static_cast<int>(value)));
    }
    Color::color_current = value;
    return ;
}
