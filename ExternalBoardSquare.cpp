#include "ExternalBoardSquare.h"
#include "InternalBoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare& square)
    :   BoardSquare(square.getColorSquare(),
        square.getSquareType(),
        square.robotDirection(),
        square.blueRobotPresent(),
        square.redRobotPresent())
    {}

ExternalBoardSquare::ExternalBoardSquare() : BoardSquare() {}