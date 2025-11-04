#pragma once
#include "Game.h"

class Connect4 : public Game
{
    public:
    Connect4();
    ~Connect4();

    void setUpBoard() override;

    Player*     checkForWinner() override;
    bool        checkForDraw() override;
    std::string initialStateString() override;
    std::string stateString() override;
    void        setStateString(const std::string &s) override;
    bool        actionForEmptyHolder(BitHolder &holder) override;
    int         getLowest(int y);
    int         getLowest(int y, std::string& state);
    bool        canBitMoveFrom(Bit &bit, BitHolder &src) override;
    bool        canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) override;
    void        stopGame() override;
    
    bool        isAIBoardFull(const std::string&);
    int         evaluateBoard(const std::string&, char player);
    void        updateAI() override;
    bool        gameHasAI() override;
    void        setAI() override;
    Grid*       getGrid() override { return _grid; }

private:
    Bit *       PieceForPlayer(const int playerNumber);
    Player*     ownerAt(int index ) const;
    Player*     ownerAt(int x, int y);
    int         negamax(std::string& state, int depth, int playerColor, int alpha, int beta);

    Grid*       _grid;
};