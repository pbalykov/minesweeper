#ifndef GAME_MINESWEEPER_HPP
#define GAME_MINESWEEPER_HPP

#include "minesweeper.hpp"
#include "timer.hpp"

enum class END_GAME {
    LOSE = -1,
    NONE = 0,
    WIN = 1,
    STOP_TIME = 2,
};

enum class STEP {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    OPEN,
    FLAG,
};    

class Game_Minesweeper {
public:
    Game_Minesweeper(COMPLEXITY value = COMPLEXITY::EASY, int time = 1000);

    END_GAME get_end() const;
    int get_time() const;
    

private:
    void _mod_curses();
 
//    Timer _time;
    int _max_time;
    END_GAME _end;
    Minesweeper _game; 
    std::pair<int, int> _cursor;

};

#endif
