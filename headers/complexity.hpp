#ifndef COMPLEXITY_HPP
#define COMPLEXITY_HPP

#include <cstddef>

enum class COMPLEXITY {
    EASY = 1,
    NORMAL = 2,
    HARD = 3,
    NONE = 0,
};

class Complexity_Game {
public:
    Complexity_Game() = default;
    Complexity_Game(COMPLEXITY value) ;
    Complexity_Game(int rows, int cols, short number_bomb);
    
    int get_rows() const;
    int get_cols() const;
    short get_number_bomb() const;
    COMPLEXITY get_complexity() const;

    static Complexity_Game make(COMPLEXITY value = COMPLEXITY::EASY);   
private:
    COMPLEXITY _type_complexity;
    int _rows;
    int _cols;
    short _number_bomb;
};

#endif
