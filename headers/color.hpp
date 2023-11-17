#ifndef COLOR_HPP
#define COLOR_HPP

enum class COLOR {
    DEFAULT = 0,
    DEFAULT_BLUE = 1,
    BLACK_GREEN = 2,
    RED_BLUE = 3,
    YELLOW_BLUE = 4,
    RED = 5,
    GREEN = 6,
    GREY = 7,
};

class Color {
public:
    Color();
    COLOR get_color() const;
    void set_color(const COLOR value);

private:
    COLOR color_current;
};

#endif
