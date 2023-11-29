#include "../headers/game_minesweeper.hpp"

Game_Minesweeper::Game_Minesweeper(time_t max_time) 
    : _max_time(max_time), _cursor_x(0), _cursor_y(0) {
    return ;
}

void Game_Minesweeper::start(const Complexity_Game& value) {
    this->_game = Minesweeper(value);
    this->_cursor_x = 0;
    this->_cursor_y = 0;
    this->_time.reset();
    return ;
}

void Game_Minesweeper::pause() {
    this->_time.stop();
    return ;
}

bool Game_Minesweeper::get_end_game() const {
    return this->_game.get_end_game(); 
}

const Minesweeper& Game_Minesweeper::get_minesweeper() const {
    return this->_game;
}

time_t Game_Minesweeper::get_time() const {
    bool com_time = this->_max_time <= this->_time.get_time();
    return com_time ? this->_max_time - 1 : this->_time.get_time();
}

std::pair<int, int> Game_Minesweeper::size() const {
    return this->_game.size();
}

void Game_Minesweeper::set_cell(TYPE_STEP other) {
    switch ( other ) {
        case TYPE_STEP::LEFT : 
            this->_cursor_x -= 1;
            break;
        case TYPE_STEP::RIGHT :
            this->_cursor_x += 1;
            break;
        case TYPE_STEP::UP :
            this->_cursor_y -= 1;
            break;
        case TYPE_STEP::DOWN :
            this->_cursor_y += 1;
            break;
        case TYPE_STEP::OPEN :
            this->_time.start();
            this->_game.set_index(this->_cursor_y, this->_cursor_x, 
                                  USER_ACTION::OPEN);
            break;
        case TYPE_STEP::FLAG :
            this->_time.start();
            this->_game.set_index(this->_cursor_y, this->_cursor_x, 
                                  USER_ACTION::FLAG);
            break;
        case TYPE_STEP::DELETE :
            this->_time.start();
            this->_game.set_index(this->_cursor_y, this->_cursor_x, 
                                  USER_ACTION::DELETE);
            break;
    }
    auto size = this->size();
    this->_cursor_y = (this->_cursor_y % size.first + size.first) % size.first;
    this->_cursor_x = (this->_cursor_x % size.second + size.second) % size.second;
    return ;           
}

int Game_Minesweeper::get_cursor_x() const {
    return this->_cursor_x;
}

int Game_Minesweeper::get_cursor_y() const {
    return this->_cursor_y;
}

std::pair<TYPE_CELL, short> Game_Minesweeper::get_cell(int i, int j) const {
    return this->_game.get_index(i, j);
}

short Game_Minesweeper::get_flag() const {
    return this->_game.get_number_flag();
}
