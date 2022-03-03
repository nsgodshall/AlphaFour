#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Board;
class Player;

class Game{
public:
    Game(Board *b, Player *p1, Player *p2);
    void playGame();

private:
    Board *m_b;
    Player *m_p1, *m_p2;

    void interactiveMove(Player *p);
};

#endif //GAME_INCLUDED