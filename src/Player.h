#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Board;

class Player(){
    public: 
        virtual bool isInteractive() const { return false; }
        virtual int chooseMove(Board &b);
};

class HumanPlayer : public Player {
    public:
        virtual bool isInteractive() const { return true; }
        
};

#endif // PLAYER_INCLUDED