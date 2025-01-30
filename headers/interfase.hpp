#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include <string_view>
#include "game_minesweeper.hpp"
#include "render.hpp"


class Interfase {
public:
    Interfase();
    ~Interfase();
    int exec();

protected:
    int menu();
    int game();
    int abaut_game();

    static constexpr std::string_view NAME_PROGMA[] = {
    " __  __ _                                                   ",
    "|  \\/  (_)_ __   ___  _____      _____  ___ _ __   ___  ___ ",
    "| |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\/ __|",
    "| |  | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/\\__ \\",
    "|_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___||___/",
    "                                           |_|              "
    };

    static constexpr std::string_view MENU[] = {" MENU ",
    "Game", "About the game", "Exit"};
    
    static constexpr std::string_view ABAUT_GAME[] = {" ABAUT GAME ", 
    "Minesweeper is a classic single-player puzzle game where the", 
    "player uncovers hidden mines on a grid by strategically clicking", 
    "on squares. The numbers revealed indicate the proximity of mines.",
    "The goal is to clear the entire grid without detonating a mine.",
    "Minesweeper requires logic, deduction, and a bit of luck to win."};

    static constexpr std::string_view COMPLEXITY[] = {" COMPLEXITY ",
    "Easy", "Normal", "Hard"};

    static constexpr std::string_view BAR_CONTROL[] = {"Enter", "Choice", "f", 
    "Setting the flag", "SPACE", "del the flag", "q", "exit"};

    static constexpr std::string_view PLAY_AGAIN = " PLAY AGAIN? ";
    
private:    
    int _max_button_size(const std::string_view* value, int size_v);
    int _choice_complexity(Complexity_Game& value);
    
    bool _play_again();

    char* _error;
    Render* _render;
    Game_Minesweeper _game;
};

#endif
