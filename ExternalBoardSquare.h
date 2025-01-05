#pragma once

#include "BoardSquare.h"

//Forward declaration of IBS to use in constructor
class InternalBoardSquare;

class ExternalBoardSquare : public BoardSquare{
    private:
    public:
        ExternalBoardSquare();
        ExternalBoardSquare(const InternalBoardSquare& square);
};