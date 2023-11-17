#include "../headers/game_minesweeper.hpp"

void Game_Minesweeper::_mod_curses() {
    auto size_game = this->_game.size();
    this->_cursor.first = this->_cursor.first % size_game.first;
    this->_cursor.first += size_game.first;
    this->_cursor.first %= size_game.first;

    this->_cursor.second = this->_cursor.second % size_game.second;
    this->_cursor.second += size_game.second;
    this->_cursor.second %= size_game.second;
    return ;
}

Game_Minesweeper::Game_Minesweeper(COMPLEXITY value, int time) : _max_time(time), 
    _end(END_GAME::NONE), _cursor(0, 0) {
    switch ( value ) {
	case COMPLEXITY::EASY :
	case COMPLEXITY::NORMAL :
	     this->_game = Minesweeper(value);
	     break;
	case COMPLEXITY::HARD :
	     this->_game = Minesweeper(Complexity_Game(16, 16, 100));
	     break;
    }
    return ;
}

END_GAME Game_Minesweeper::get_end() const {
    return this->_end;
}

/*int Game_Minesweeper::get_time() const {
    return this->_time.get_time();
}*/
