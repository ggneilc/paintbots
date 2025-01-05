#pragma once

#include "BoardSquare.h"
#include "Robot.h"

class InternalBoardSquare : public BoardSquare {
    private:
        Robot* paintbot;       
    public:
        InternalBoardSquare();
        InternalBoardSquare(SquareColor, SquareType);
        void setPaintBot(Robot*);
        Direction getPaintBotDir() const;
        void setPaintBotDir(Direction);
        Robot& getPaintBot() const;
        int getPaintBotRow() const;
        int getPaintBotCol() const;
};