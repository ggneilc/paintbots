#pragma once

#include "Config.h"
#include "RobotTypes.h"
#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "ObserverPattern.h"

/* Would be more efficient as a Union */
class GameBoardNotification {
    public:
        enum class EventType { COLOR, SCORE, MOVE };

        static GameBoardNotification ScoreChanged(int newScore, bool red){
            GameBoardNotification notification;
            notification.event = EventType::SCORE;
            if (red) {
                notification.redScore = newScore;
                notification.robot = RobotColor::RED;
            }
            else {
                notification.blueScore = newScore;
                notification.robot = RobotColor::BLUE;
            }
            return notification;
        }

        static GameBoardNotification SquareColorChanged(SquareColor newColor, int x, int y){
            GameBoardNotification notification;
            notification.event = EventType::COLOR;
            notification.squareColor = newColor;
            notification.xCoord = x;
            notification.yCoord = y;
            return notification;
        }

        static GameBoardNotification RobotMoved(RobotMove moveType, RobotColor col, Direction dir, int fromX, int fromY, int toX, int toY){
            GameBoardNotification notification;
            notification.event = EventType::MOVE;
            notification.moveType = moveType;
            notification.fromXcoord = fromX;
            notification.fromYcoord = fromY;
            notification.toXcoord = toX;
            notification.toYcoord = toY;
            notification.dir = dir;
            notification.robot = col;
            return notification;
        }

        EventType getEventType() const { return event; }
        int getRedScore() const { return redScore; }
        int getBlueScore() const { return blueScore; }
        RobotColor getScoringRobot() const { return robot; }
        SquareColor getSquareColor() const { return squareColor; }
        int getXCoord() const { return xCoord; }
        int getYCoord() const { return yCoord; }
        RobotMove getMoveType() const { return moveType; }
        Direction getDirection() const { return dir; }
        int getFromXCoordinate() const { return fromXcoord; }
        int getFromYCoordinate() const { return fromYcoord; }
        int getToXCoordinate() const { return toXcoord; }
        int getToYCoordinate() const { return toYcoord; }
    private:
        GameBoardNotification() = default;
        EventType event;
        int redScore = 0;
        int blueScore = 0;
        RobotColor robot;
        SquareColor squareColor;
        int xCoord = -1;
        int yCoord = -1;
        RobotMove moveType;
        Direction dir; 
        int fromXcoord = -1;
        int fromYcoord = -1;
        int toXcoord = -1;
        int toYcoord = -1;
};

class GameBoard : public Observable<GameBoardNotification>{
    private:
        InternalBoardSquare grid[17][17];
        Config settings;
        Robot* redRobot;   // Add these member variables
        Robot* blueRobot;  // to store the robots
        static GameBoard* instance;
        GameBoard();
        GameBoard(const Config&);
    public:
        static GameBoard* getInstance(std::string);
        static GameBoard* getInstance(std::string, Config&);
        GameBoard(const GameBoard&) = delete;
        GameBoard& operator=(const GameBoard) = delete;

        InternalBoardSquare& getSquare(int row, int col);
        bool MoveRobot(RobotMoveRequest& mr);
        bool PaintBlobHit(RobotMoveRequest& mr);
        int redScore();
        int blueScore();
        void setSquareColor(int row, int col, SquareColor c);
        void setRobotPaintColor(RobotColor robot, SquareColor sc);
        ExternalBoardSquare** getLongRangeScan();
        ExternalBoardSquare** getShortRangeScan(RobotColor);
        InternalBoardSquare& findRobot(RobotColor);
};


class PlainDisplay : public Observer<GameBoardNotification> {
    private:
        InternalBoardSquare grid[17][17];
        int redscore;
        int bluescore;
    public:
        PlainDisplay(const GameBoard&);
        void display();
        void update(const GameBoardNotification&);
};