#ifndef CELL_HPP
#define CELL_HPP

#include <utility>

enum class TYPE_CELL {
    HIDDEN,
    VALUE,
    BOMB,
    FLAG,
    TRUE_FLAG,
    FALSE_FLAG,

};

struct Cell {
    Cell(TYPE_CELL state_user = TYPE_CELL::HIDDEN,
	 TYPE_CELL state_default = TYPE_CELL::VALUE, short value = 0);

    static Cell make(TYPE_CELL state_user, TYPE_CELL state_default, short value);

    TYPE_CELL state_user;
    TYPE_CELL state_default;
    short value; 
};

#endif
