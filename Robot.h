#pragma once

#include "BoardSquare.h"
#include "RobotTypes.h"

/* Forward Declaration */
class IRobotAgent;

class Robot {
    public:
        /* Strategy pattern */
        void setColor(RobotColor);
        void setPaintColor(SquareColor);
        RobotColor getRobotColor();
        void setRobotAgent(IRobotAgent*);
        IRobotAgent* getRobotAgent();
        Robot();

        /* Methods to make part b still work ok */
        Robot(RobotColor c, int row, int col)
            : color(c), row(row), col(col) {};
        int getRow() const { return row; }
        int getCol() const { return col; }
        void setRow(int r) { row = r; }
        void setCol(int c) { col = c; }
    private:
        IRobotAgent* strategy;

        RobotColor color;
        SquareColor paintcolor;
        int row; 
        int col;
};