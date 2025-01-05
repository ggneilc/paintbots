#include "Robot.h"
#include "IRobotAgent.h"

void Robot::setRobotAgent(IRobotAgent* strat){
    strategy = strat;
}

IRobotAgent* Robot::getRobotAgent() {
    return strategy;
}

void Robot::setColor(RobotColor col){
    color = col;
    strategy->setRobotColor(col);
}

void Robot::setPaintColor(SquareColor col){
    paintcolor = col;
}

RobotColor Robot::getRobotColor() {
    return color;
}

Robot::Robot()
    : color(RobotColor::RED)
    {
        strategy = new lazyRobot();
        RobotAgentRoster* instance = RobotAgentRoster::getInstance();
        instance->add(strategy);
    }