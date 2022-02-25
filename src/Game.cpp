#include <iostream>

#include "Game.h"
#include "Board.h"

void game::playGame(){
    Board b; 

    int col(-1);

    std::cout << "NEW GAME" << std::endl;
    b.displayHumanReadable();
    while(b.getWinner() == -1){
        std::cout << "Player X, which column? (1-7) ";
        std::cin >> col;
        b.addToken(col-1);
        std::cout << std::endl;
        b.displayHumanReadable();
        if(b.getWinner() != -1)
            break;
        std::cout << "Player O, which column? (1-7) ";
        std::cin >> col;
        b.addToken(col-1);
        std::cout << std::endl;
        b.displayHumanReadable();
        if(b.getWinner() != -1)
            break;
    }
    if (b.getWinner() == 0)
        std::cout <<"Player X Wins!" << std::endl;
    else
        std::cout << "player O Wins!" << std::endl;
}