#ifndef GAME_MINESWEEPER_CPP
#define GAME_MINESWEEPER_CPP

#include "minesweeper.hpp"
#include "timer.hpp"

#include <string_view>

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

    enum class TYPE_END_GAME {
        WON,
        LOSE,
        NONE,
        TIMES,
    };

    Game_Minesweeper(time_t max_time = 1000);
    void start(const Complexity_Game& value);
    void pause();
    const Minesweeper& get_minesweeper() const;
    time_t get_time() const;
    std::pair<int, int> size() const;
    void set_cell(TYPE_STEP other);
    std::pair<TYPE_CELL, short> get_cell(int i, int j) const;
    int get_cursor_x() const;
    int get_cursor_y() const;
    short get_flag() const;

    bool get_end_game();
    bool get_end_game() const;
    TYPE_END_GAME type_end_game() const;
    std::string_view message_end_game() const;

private:
    static constexpr std::string_view MESSAGE_END_GAME_WON = "You Won!!";
    static constexpr std::string_view MESSAGE_END_GAME_LOSE = "You Lose!";
    static constexpr std::string_view MESSAGE_END_GAME_TIMES = "Time has run out!";
    int _cursor_x;
    int _cursor_y;
    time_t _max_time;
    Timer _time;
    Minesweeper _game;
};

#endif
