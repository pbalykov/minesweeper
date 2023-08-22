#ifndef RENDER_HPP
#define RENDER_HPP

#include "minesweeper.hpp"

namespace {
    constexpr const char* WING = "YOU WON!!";
    constexpr const char* LOSE = "YOU LOSE!";
    constexpr const char* PRESS = "Press any key";
}

void printField(std::pair<int, int> begin_curses, const Minesweeper& other);
int printGame(const Minesweeper& other, std::pair<int, int> cursor_game, 
              int time);

#endif
