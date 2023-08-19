#include "../headers/complexity.hpp"

Complexity_Game Complexity_Game::make(COMPLEXITY value) {
   Complexity_Game ans;
   switch ( value ) {
       case COMPLEXITY::EASY :
	   ans = Complexity_Game(9, 9, 10);
           break;
       case COMPLEXITY::NORMAL :
	   ans = Complexity_Game(16, 16, 40);
	   break;
       case COMPLEXITY::HARD :
	   ans = Complexity_Game(16, 30, 99);
	   break;
       default:
	   ans = Complexity_Game(0, 0, 0);
   }
   ans._type_complexity = value;
   return ans;
};

Complexity_Game::Complexity_Game(COMPLEXITY value) {
    *this = Complexity_Game::make(value);
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
