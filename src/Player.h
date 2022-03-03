#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Board;

class Player{
    public:
        bool m_firstPlayer;

        Player();
        inline bool isFirstPlayer() const {return m_firstPlayer;}
        void setAsFirstPlayer();
};

class HumanPlayer : public Player {
    public:
        HumanPlayer();

};

#endif // PLAYER_INCLUDED