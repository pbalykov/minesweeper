#include "../headers/complexity.hpp"

Complexity_Game::Complexity_Game(COMPLEXITY value) {
    switch ( value ) {
        case COMPLEXITY::EASY :
	    *this = Complexity_Game(9, 9, 10);
            break;
        case COMPLEXITY::NORMAL :
	    *this = Complexity_Game(16, 16, 40);
	    break;
        case COMPLEXITY::HARD :
	    *this = Complexity_Game(16, 30, 99);
	    break;
        default:
	    *this = Complexity_Game(0, 0, 0);
    }
    this->_type_complexity = value;
    return ;
}

Complexity_Game::Complexity_Game(int rows, int cols, short number_bomb) 
    : _rows(rows), _cols(cols), _number_bomb(number_bomb), 
    _type_complexity(COMPLEXITY::NONE) {}

int Complexity_Game::get_rows() const {
    return this->_rows;
}

int Complexity_Game::get_cols() const {
    return this->_cols;
}

short Complexity_Game::get_number_bomb() const {
    return this->_number_bomb;
}

COMPLEXITY Complexity_Game::get_complexity() const {
    return this->_type_complexity;
}
