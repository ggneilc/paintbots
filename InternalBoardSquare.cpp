#include "InternalBoardSquare.h"

InternalBoardSquare::InternalBoardSquare()
    : BoardSquare()
    {}

// Board square constructor. 
InternalBoardSquare::InternalBoardSquare(SquareColor c, SquareType s)
    : BoardSquare(c, s, Direction::NORTH, false, false)
    {}

void InternalBoardSquare::setPaintBot(Robot* p){
    paintbot = p;
}

int InternalBoardSquare::getPaintBotRow() const{
    return paintbot->getRow();
}

int InternalBoardSquare::getPaintBotCol() const{
    return paintbot->getCol();
}

Robot* InternalBoardSquare::getPaintBot() const {
    return paintbot;
}
