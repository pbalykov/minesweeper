#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "cell.hpp"
#include "complexity.hpp"
#include <vector>

enum class USER_ACTION {
    OPEN,
    FLAG,
    DELETION,
};

class Minesweeper {
public:
    Minesweeper(COMPLEXITY value = COMPLEXITY::EASY);
    Minesweeper(Complexity_Game complexity);

    std::pair<int, int> size() const; 
    short get_number_bomb() const; 
    std::pair<TYPE_CELL, short> get_index(int i, int j) const; 
    bool get_end_game() const; 
    bool get_wing_game() const; 
    short get_number_flag() const; 
    COMPLEXITY get_complexity_game() const; 

    bool set_index(int i, int j, USER_ACTION other); 

    
private:
    int _first_index(int current_index, int first_index = 0) const;
    int _last_index(int current_index, int last_index) const; 
    void _increment_neighbors(std::pair<int, int> index); 
    void _field_generation();
    bool _open_cell(int i, int j);
    void _end_game_field();  
    

    Complexity_Game _complexity_game;
    short _number_flag;
    unsigned short _number_cell;
    bool _end_game;
    std::vector<std::vector<Cell> > _data;
};

#endif 
