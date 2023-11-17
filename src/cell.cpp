#include "../headers/cell.hpp"

Cell::Cell(TYPE_CELL state_user, TYPE_CELL state_default, short value)
    : state_user(state_user), state_default(state_default), value(value) {}
