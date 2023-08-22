#include "../headers/minesweeper.hpp"
#include <cstdlib>
#include <stdexcept>

int Minesweeper::_first_index(int current_index, int first_index) const {
    return std::max<ptrdiff_t>(current_index - 1, first_index);
}

int Minesweeper::_last_index(int current_index, int last_index) const {
    return std::min<ptrdiff_t>(current_index + 1, last_index);
}

void Minesweeper::_increment_neighbors(std::pair<int, int> index) {
    int begin_heigh = this->_first_index(index.first);
    int end_heigh = this->_last_index(index.first, this->size().first - 1);
    int begin_width = this->_first_index(index.second);
    int end_width = this->_last_index(index.second, this->size().second - 1);

    for (int i = begin_heigh; i < end_heigh + 1; i++) {
	for (int j = begin_width; j < end_width + 1; j++) {
	    if ( this->_data[i][j].state_default == TYPE_CELL::VALUE ) {
		 this->_data[i][j].value += 1;
	    }
	}
    }
    return ;
}

void Minesweeper::_field_generation() {
    if ( this->size().first * this->size().second <= this->get_number_bomb() ) {
	throw std::length_error("Error: all bombs don't fit in the field");
    }
    std::vector<std::pair<int, int> > all_index;
    for (int i = 0; i < this->_complexity_game.get_rows(); i++) {
	for (int j = 0; j < this->_complexity_game.get_cols(); j++) {
	    all_index.push_back({i, j});
	}
    }
    for (int i = 0; i < this->_complexity_game.get_number_bomb(); i++) {
	int rand_index = std::rand() % (all_index.size() - i) + i;
	std::swap(all_index[rand_index], all_index[i]);
	auto value = all_index[i];
	auto other = Cell::make(TYPE_CELL::HIDDEN, TYPE_CELL::BOMB, -1);
	this->_data[value.first][value.second] = other;
	this->_increment_neighbors(value);
    }
    return ;
}

bool Minesweeper::_open_cell(int i, int j) {
    if ( this->_data[i][j].state_default == TYPE_CELL::BOMB ) {
	 this->_end_game_field();
	 return true;
    }
    this->_number_cell += 1;
    this->_data[i][j].state_user = TYPE_CELL::VALUE;
    if ( this->_data[i][j].value != 0 ) {
	return false;
    }
    int begin_heigh = this->_first_index(i);
    int end_heigh = this->_last_index(i, this->size().first - 1);
    int begin_width = this->_first_index(j);
    int end_width = this->_last_index(j, this->size().second - 1);

    for (int i1 = begin_heigh; i1 < end_heigh + 1; i1++) {
	for (int j1 = begin_width; j1 < end_width + 1; j1++) {
	     if ( this->_data[i1][j1].state_default == TYPE_CELL::VALUE &&
	          this->_data[i1][j1].state_user == TYPE_CELL::HIDDEN) {
		  this->_open_cell(i1, j1);
	     }
	}
    }
    return false;
}

void Minesweeper::_end_game_field() {
    for (int i = 0; i < this->size().first; i++) {
	for (int j = 0; j < this->size().second; j++) {
	    if ( this->_data[i][j].state_user == TYPE_CELL::FLAG ) {
		 bool bomb = this->_data[i][j].state_default == TYPE_CELL::BOMB;
		 this->_data[i][j].state_user = bomb ? TYPE_CELL::TRUE_FLAG : 
			                               TYPE_CELL::FALSE_FLAG;
	    }
	    else if ( this->_data[i][j].state_default == TYPE_CELL::BOMB) {
		 this->_data[i][j].state_user = TYPE_CELL::BOMB;
	    }
	}
    }
    return ;
}			                               

Minesweeper::Minesweeper(COMPLEXITY value) 
    : _complexity_game(value), 
      _number_flag(this->_complexity_game.get_number_bomb()), _number_cell(0),
      _end_game(false), _data(_complexity_game.get_rows(), 
                              std::vector<Cell>(_complexity_game.get_cols())) {
    this->_field_generation();
    return ;
}

std::pair<int, int> Minesweeper::size() const {
     return {this->_complexity_game.get_rows(), this->_complexity_game.get_cols()};
}

short Minesweeper::get_number_bomb() const {
     return this->_complexity_game.get_number_bomb();
}

std::pair<TYPE_CELL, short> Minesweeper::get_index(int i, int j) const {
     if ( i >= this->size().first || j >= this->size().second ) {
	 throw std::out_of_range("Error: going beyond the size of the matrix");
     }
     short value = this->_data[i][j].value;
     value = this->_data[i][j].state_user != TYPE_CELL::VALUE ? -1 : value;
     return {this->_data[i][j].state_user, value };
}

bool Minesweeper::get_end_game() const {
    return this->_end_game;
}

bool Minesweeper::get_wing_game() const {
    int number_free_cell = this->size().first * this->size().second;
    number_free_cell -= this->_complexity_game.get_number_bomb(); 
    return this->_end_game && this->_number_cell == number_free_cell;
}

short Minesweeper::get_number_flag() const {
    return this->_number_flag;
}

COMPLEXITY Minesweeper::get_complexity_game() const {
    return this->_complexity_game.get_complexity();
}

bool Minesweeper::set_index(int i, int j, USER_ACTION other) {
    if ( this->_end_game ) {
	return this->_end_game;
    }
    if ( other == USER_ACTION::FLAG && 
            this->_data[i][j].state_user == TYPE_CELL::HIDDEN ) {
	bool value_flag =  this->_data[i][j].state_user == TYPE_CELL::FLAG;
	this->_number_flag -= value_flag ? 0 : 1;
	this->_data[i][j].state_user = TYPE_CELL::FLAG;
    }
    else if ( other == USER_ACTION::DELETION && 
	       this->_data[i][j].state_user == TYPE_CELL::FLAG ) { 
	bool value_flag = this->_data[i][j].state_user == TYPE_CELL::FLAG;
	this->_number_flag += value_flag ? 1 : 0;
	this->_data[i][j].state_user = TYPE_CELL::HIDDEN;
    }
    else if (other == USER_ACTION::OPEN ) {
	this->_end_game = this->_open_cell(i, j);

    }
    int number_free_cell = this->size().first * this->size().second;
    number_free_cell -= this->_complexity_game.get_number_bomb(); 
    this->_end_game = this->_number_cell == number_free_cell && 
		      !this->_number_flag ? true : this->_end_game;
    return this->_end_game;
}
