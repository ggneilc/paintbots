#pragma once

#include <string>
#include "RobotTypes.h"

class GameLogic {
    private:
        bool pause;
        int iterations;
        int redLRL; 
        int blueLRL;
        int redIsHitCounter;
        int blueIsHitCounter;
        int redAmmo;
        int blueAmmo;
        RobotColor winner;
    public:
        GameLogic();
        void playGame(std::string boardconfig, std::string robotconfig);
        void setPause(bool pausemode);
};