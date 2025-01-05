#include "ITest.h"
#include "BoardSquare.h"
#include <iostream>

class BoardSquareTest : public ITest{
    public: 
    bool doTests(){
        BoardSquare base;
        std::cout << "Checking default constructor: ";
        if(base.getColorSquare() == SquareColor::WHITE
        && base.robotDirection() == Direction::NORTH
        && base.getSquareType() == SquareType::EMPTY
        && base.blueRobotPresent() == false
        && base.redRobotPresent() == false){
            std::cout << "\tPASS\n";
        } else { std::cout << "\tFAIL\n"; return false;}

        BoardSquare construct {SquareColor::BLUE,
        SquareType::ROCK,
        Direction::EAST,
        true,
        false};
        std::cout << "Checking value constructor: ";
        if(construct.getColorSquare() == SquareColor::BLUE
        && construct.robotDirection() == Direction::EAST
        && construct.getSquareType() == SquareType::ROCK
        && construct.blueRobotPresent() == false
        && construct.redRobotPresent() == true){
            std::cout << "\tPASS\n";
        } else { std::cout << "\tFAIL\n"; return false;}

        BoardSquare copied(base);
        std::cout << "Checking copy constructor: ";
        if(copied.getColorSquare() == SquareColor::WHITE
        && copied.robotDirection() == Direction::NORTH
        && copied.getSquareType() == SquareType::EMPTY
        && copied.blueRobotPresent() == false
        && copied.redRobotPresent() == false){
            std::cout << "\tPASS\n";
        } else { std::cout << "\tFAIL\n"; return false;}

        copied = construct;
        std::cout << "Checking overload operator =: ";
        if(copied.getColorSquare() == construct.getColorSquare()
        && copied.robotDirection() == construct.robotDirection()
        && copied.getSquareType() == construct.getSquareType()
        && copied.blueRobotPresent() == construct.blueRobotPresent()
        && copied.redRobotPresent() == construct.redRobotPresent()){
            std::cout << "\tPASS\n";
        } else { std::cout << "\tFAIL\n"; return false; }

        return true;
    }
};

int main() {
    BoardSquareTest test;
    std::cout << "BoardSquareTest: \n" << test.doTests();
    return 0;
}