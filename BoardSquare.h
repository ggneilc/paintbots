#pragma once

enum class Direction { NORTH, SOUTH, EAST, WEST };
enum class SquareColor { WHITE, RED, BLUE };
enum class SquareType { EMPTY, ROCK, WALL, FOG };

class BoardSquare {
    private:
        SquareColor squareColor;
        Direction robotdir;
        SquareType squareType;
        bool redRobot;
        bool blueRobot;
    public:
        BoardSquare();
        BoardSquare(SquareColor, SquareType, Direction, bool, bool);
        BoardSquare(const BoardSquare&);
        BoardSquare& operator=(const BoardSquare&);
        virtual ~BoardSquare();
        inline bool redRobotPresent() const{
            return redRobot;
        }
        inline bool blueRobotPresent() const{
            return blueRobot;
        }
        inline Direction robotDirection() const{
            return robotdir;
        }
        inline SquareType getSquareType() const{
            return squareType;
        }
        inline SquareColor getColorSquare() const{
            return squareColor;
        }
        inline void setRedRobot(bool val) { redRobot = val; }
        inline void setBlueRobot(bool val) { blueRobot = val; }
        inline void setSquareColor(SquareColor c) { squareColor = c; }
        inline void setRobotDir(Direction d) { robotdir = d; }
        inline void setSquareType(SquareType s) { squareType = s; }
};