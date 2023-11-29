#ifndef GAME_MINESWEEPER_CPP
#define GAME_MINESWEEPER_CPP

#include "minesweeper.hpp"
#include "timer.hpp"

enum class TYPE_END_GAME {
    WING = 1,
    NONE = 0,
    LOSS = -1,
    END_TIME = -2,
};

class Game_Minesweeper {
public:
    enum class TYPE_STEP {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        OPEN,
        FLAG, 
        DELETE,
    };

    Game_Minesweeper(time_t max_time = 1000);
    void start(const Complexity_Game& value);
    void pause();
    bool get_end_game() const;
    const Minesweeper& get_minesweeper() const;
    time_t get_time() const;
    std::pair<int, int> size() const;
    void set_cell(TYPE_STEP other);
    std::pair<TYPE_CELL, short> get_cell(int i, int j) const;
    int get_cursor_x() const;
    int get_cursor_y() const;
    short get_flag() const;

private:
    int _cursor_x;
    int _cursor_y;
    time_t _max_time;
    Timer _time;
    Minesweeper _game;
};

#endif
