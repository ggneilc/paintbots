#pragma once

enum class RobotColor {
    RED,
    BLUE
};

enum class RobotMove {
    ROTATELEFT,
    ROTATERIGHT,
    FORWARD,
    NONE
};

struct RobotMoveRequest {
    RobotColor robot;
    RobotMove move;
    bool shoot;
    bool lrs; 
};