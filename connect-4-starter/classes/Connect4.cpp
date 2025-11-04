#include "Connect4.h"
#include <iostream>

ImVec2 *lastPos = nullptr;
Player *lastPlayer = nullptr;
bool hasAI = true;
bool firstMove = false;

static int AIFirst = 1;

Connect4::Connect4()
{
    _grid = new Grid(7, 6);

}

Connect4::~Connect4()
{
    delete _grid;
}

Bit* Connect4::PieceForPlayer(const int playerNumber)
{
    Bit *bit = new Bit();
    bit->LoadTextureFromFile(playerNumber == AI_PLAYER ? "yellow.png" : "red.png");
    bit->setOwner(getPlayerAt(playerNumber == AI_PLAYER ? 1 : 0));
    return bit;
}

void Connect4::setUpBoard()
{
    setNumberOfPlayers(2);
    _gameOptions.rowX = 7;
    _gameOptions.rowY = 6;
    _grid->initializeSquares(80, "square.png");

    if (gameHasAI()) {
        setAIPlayer(AIFirst);
    }

    startGame();
}

bool Connect4::actionForEmptyHolder(BitHolder &holder)
{
    if (holder.bit()) {
        return false;
    }
    Bit *bit = PieceForPlayer(getCurrentPlayer()->playerNumber() == 0 ? HUMAN_PLAYER : AI_PLAYER);
    if (bit) {
        ImVec2 position = holder.getPosition();
        int x = (position.x-40)/80;
        int y = 5;

        int index = y * 7 + x;
        for (y = 5; y > -1; y--)
        {
            if(ownerAt(x,y) == nullptr)
            {
                float newX = 80 * x+40;
                float newY = y * 80 + 40;
                bit->setPosition(newX, newY);
                _grid->getSquare(x,y)->setBit(bit);
                lastPos = new ImVec2(x, y);
                lastPlayer = getCurrentPlayer();
                endTurn();
                return true;
            }
        }
    }   
    return false;
}

bool Connect4::canBitMoveFrom(Bit &bit, BitHolder &src)
{
    return false;
}

bool Connect4::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst)
{
    return false;
}

void Connect4::stopGame()
{
    _grid->forEachSquare([](ChessSquare* square, int x, int y) {
        square->destroyBit();
    });
}

Player* Connect4::ownerAt(int index ) const
{
    auto square = _grid->getSquare(index % 7, index / 6);
    if (!square || !square->bit()) {
        return nullptr;
    }
    return square->bit()->getOwner();
}

Player* Connect4::ownerAt(int x, int y)
{
    auto square = _grid->getSquare(x, y);
    if (!square || !square->bit()) {
        return nullptr;
    }
    return square->bit()->getOwner();
}

Player* Connect4::checkForWinner()
{   
    bool isWin = true;
    int x = lastPos->x;
    int y = lastPos->y;
    // based on the last placed thing, check to see if any winners
    
    if(x == NULL)
    {
        return nullptr;
    }
    if(y <=2)
    {
        // vertical win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getS(x,y+i);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }
     
    if(x <=3)
    {
        // Right win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getE(x+i,y);
            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    if(x >=3)
    {
        // Left win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getW(x-i,y);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    if(x >=3 && y >= 3)
    {
        // right digagonal up win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getFL(x-i,y-i);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    if(x <= 3 && y <= 2)
    {
        // right digagonal down win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getBR(x+i,y+i);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    if(x >= 3 && y <= 2)
    {
        // left digagonal down win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getBL(x-i,y+i);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    if(x <=3 && y >= 3)
    {
        // left digagonal up win
        for (int i = 0; i < 3; i++)
        {
            auto nextPos = _grid->getFR(x+i,y-i);

            if (!nextPos->bit())
            {
                isWin = false;
                break;
            }
            if(nextPos->bit()->getOwner() != lastPlayer)
            {
                isWin = false;
                break;
            }
        }
        if (isWin)
        {
            return lastPlayer;
        }
        
        isWin = true;
    }

    return nullptr;

}

bool Connect4::checkForDraw()
{
    bool isDraw = true;
    // check to see if the board is full
    _grid->forEachSquare([&isDraw](ChessSquare* square, int x, int y) {
        if (!square->bit()) {
            isDraw = false;
        }
    });
    return isDraw;
}

std::string Connect4::initialStateString()
{
    return "000000000000000000000000000000000000000000";
}

std::string Connect4::stateString()
{
    std::string s = "000000000000000000000000000000000000000000";
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
        Bit *bit = square->bit();
        if (bit) {
            s[y * 7 + x] = std::to_string(bit->getOwner()->playerNumber()+1)[0];
        }
    });
    return s;
}

void Connect4::setStateString(const std::string &s)
{
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
        int index = y*7 + x;
        int playerNumber = s[index] - '0';
        if (playerNumber) {
            square->setBit( PieceForPlayer(playerNumber-1) );
        } else {
            square->setBit( nullptr );
        }
    });
}



bool Connect4::isAIBoardFull(const std::string& state)
{
    return state.find('0') == std::string::npos;
}

int CoordsToIndex(int x, int y)
{
    return y * 7 + x;
}

ImVec2 IndexToCoords(int index)
{
    ImVec2 coords;
    coords.y = index / 7;
    coords.x = index % 7;

    return coords;
}

int Connect4::evaluateBoard(const std::string& state, char player)
{
    int evaluationTable[6][7] = {{3, 4, 5, 7, 5, 4, 3}, 
                                {4, 6, 8, 10, 8, 6, 4},
                                {5, 8, 11, 13, 11, 8, 5}, 
                                {5, 8, 11, 13, 11, 8, 5},
                                {4, 6, 8, 10, 8, 6, 4},
                                {3, 4, 5, 7, 5, 4, 3}};

    int val = 0;

    for (int i = 0; i < 42; i++)
    {
        //iterate through to find all the placed piece and change the score based on if they are there
        
        if(state[i] == player)
        {
            ImVec2 coords = IndexToCoords(i);
            val += evaluationTable[(int)coords.y][(int)coords.x];
        }
        else if(state[i] != '0')
        {
            ImVec2 coords = IndexToCoords(i);
            val -= evaluationTable[(int)coords.y][(int)coords.x];
        }
    }
 
    return val;
}

void Connect4::updateAI()
{
    int bestVal = -1000;
    BitHolder *bestMove = nullptr;
    std::string state = stateString();

    for (int x = 0; x < _grid->getWidth(); x++)
    {
        int y = getLowest(x);
        auto square = _grid->getSquare(x,y);
        int index = CoordsToIndex(x,y);

        if (state[index] == '0') {
            // Make the move
            state[index] = '2'; 
            int moveVal = -negamax(state, 0, HUMAN_PLAYER, -290, 290);
            // Undo the move for backtracking
            state[index] = '0';
            if (moveVal > bestVal) {
                bestMove = square;
                bestVal = moveVal;
            }
        }
    }

    // Make the best move
    if(bestMove) {
        if (actionForEmptyHolder(*bestMove)) {
        }
    }
}

int Connect4::negamax(std::string& state, int depth, int player, int alpha, int beta)
{
    int whichPlayer;
    int score = evaluateBoard(state, whichPlayer = player == HUMAN_PLAYER ? '1' : '2');

    if(lastPos != nullptr)
    {
        // check if can win next turn
        for (int x = 0; x < _grid->getWidth(); x++)
        {
            int y = getLowest(x, state);

            int index = CoordsToIndex(x,y);

            if(y == -1)
            {
                break;
            }
            if (state[index] == '0') 
            {
                // Make the move
                state[index] = player == HUMAN_PLAYER ? '1' : '2';
                Player *tempPlayer = lastPlayer;
                ImVec2 *tempPos = lastPos;

                lastPlayer = getPlayerAt(player == HUMAN_PLAYER ? 0 : 1);
                lastPos = new ImVec2(IndexToCoords(index));

                if(checkForWinner())
                {
                    return score;
                }

                lastPlayer = tempPlayer;
                lastPos = tempPos;
                state[index] = '0';
            }
        }
    }

    if (depth > 11)
    {
        return score;
    }



    if (isAIBoardFull(state))
    {
        return 0;
    }
    
    int bestVal = -1000;
    int max = 300;
    if (beta >  max)
    {
        beta = max;
        if (alpha >= beta) 
        {
            return beta;
        }
    }
    
    // get possible moves
    for (int x = 0; x < _grid->getWidth(); x++)
    {
        int y = getLowest(x, state);

        int index = CoordsToIndex(x,y);

        if(y == -1)
        {
            break;
        }
        if (state[index] == '0') {
            // Make the move
            state[index] = player == HUMAN_PLAYER ? '1' : '2';
            bestVal = std::max(bestVal, -negamax(state, depth + 1, -player, -alpha, -beta));
            // Undo the move for backtracking
            state[index] = '0';

            if (bestVal >= beta)
            {
                // prune this branch
                return bestVal;
            }

            if (bestVal > alpha)
            {
                // update alpha if needed
                alpha = bestVal;
            }
        }
    }
    return bestVal;
}

bool Connect4::gameHasAI()
{
    return hasAI;
}

void Connect4::setAI()
{
    if(hasAI)
    {
        hasAI = false;
        return;
    }
    if(!hasAI)
    {
        hasAI = true;
        return;
    }

}

// returns lowest empty y level in the grid
int Connect4::getLowest(int x)
{
    for(int y = 5; y > 0; y--)
    {
        if(ownerAt(x,y) == nullptr)
        {
            return y;
        }
    }
}

int Connect4::getLowest(int x, std::string& state)
{
    for (int y = 5; y > 0; y--)
    {
        int index = CoordsToIndex(x,y);
        if(state[index] == '0')
        {
            return y;
        }
    }
    return -1;
}
