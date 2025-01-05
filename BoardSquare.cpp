#include "BoardSquare.h"

BoardSquare::BoardSquare()
    : squareColor(SquareColor::WHITE),
    robotdir(Direction::NORTH),
    squareType(SquareType::EMPTY),
    redRobot(false),
    blueRobot(false)
    {}

BoardSquare::BoardSquare(SquareColor c, SquareType t, Direction d, bool red, bool blue)
    : squareColor(c), squareType(t), robotdir(d), redRobot(red), blueRobot(blue)
    {}

BoardSquare::BoardSquare(const BoardSquare& other)
    : squareColor(other.getColorSquare()),
    squareType(other.getSquareType()),
    robotdir(other.robotDirection()),
    blueRobot(other.blueRobotPresent()),
    redRobot(other.redRobotPresent())
    {}

BoardSquare& BoardSquare::operator=(const BoardSquare& other){
    if (this != &other){
        squareColor = other.getColorSquare();
        squareType = other.getSquareType();
        robotdir = other.robotDirection();
        blueRobot = other.blueRobotPresent();
        redRobot = other.redRobotPresent();
    }
    return *this;
}

BoardSquare::~BoardSquare(){}