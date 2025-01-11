#include "GameBoard.h"
#include <random>
#include <iostream>


GameBoard::GameBoard() 
    : GameBoard(Config())
    { }

GameBoard::GameBoard(const Config& settings)
    : settings(settings), redRobot(nullptr), blueRobot(nullptr)
    {
        /* place walls */
        for (int row=0; row < 17; row++){
            for (int col=0; col < 17; col++){
                if (row == 0 || col == 0 || row == 16 || col == 16){
                    grid[row][col] = InternalBoardSquare(SquareColor::WHITE,SquareType::WALL);
                }
            }
        }
        /* Utilize settings to spread fog & rocks */
        /* Generate random indices to place objects */
        std::random_device rd;
        std::mt19937 engine(rd());

        //Rocks
        std::uniform_int_distribution<int> RockDist(settings.getRockLowerBound(), settings.getRockUpperBound());
        int num_rocks = RockDist(engine);
        std::uniform_int_distribution<int> FogDist(settings.getFogLowerBound(), settings.getFogUpperBound());
        int num_fog = FogDist(engine);

        int rocks_placed = 0;
        int fog_placed = 0;

        std::uniform_int_distribution<int> dist(1,15);
        while (rocks_placed != num_rocks){
            int row = dist(engine);
            int col = dist(engine);
            if (grid[row][col].getSquareType() != SquareType::EMPTY){
                continue;
            } else {
                grid[row][col] = InternalBoardSquare(grid[row][col].getColorSquare(), SquareType::ROCK);
                rocks_placed++;
            }
        }
        while (fog_placed != num_fog){
            int row = dist(engine);
            int col = dist(engine);
            if (grid[row][col].getSquareType() != SquareType::EMPTY){
                continue;
            } else {
                grid[row][col] = InternalBoardSquare(grid[row][col].getColorSquare(), SquareType::FOG);
                fog_placed++;
            }
        }

        /* Place Robots */
        int red_placed = 0;
        int blue_placed = 0;
        while(red_placed == 0){
            int row = dist(engine);
            int col = dist(engine);
            if (grid[row][col].getSquareType() != SquareType::EMPTY) continue;
            else{
                redRobot = new Robot(RobotColor::RED, row, col);
                grid[row][col].setPaintBot(redRobot);
                grid[row][col].setRedRobot(true);
                printf("Placed red robot at %d,%d\n", row, col);
                red_placed = 1;
            }
        }
        while(blue_placed == 0){
            int row = dist(engine);
            int col = dist(engine);
            if (grid[row][col].getSquareType() != SquareType::EMPTY) continue;
            else{
                blueRobot = new Robot(RobotColor::BLUE, row, col);
                grid[row][col].setPaintBot(blueRobot);
                grid[row][col].setBlueRobot(true);
                printf("Placed blue robot at %d,%d\n", row, col);
                blue_placed = 1;
            }
        }
    }

GameBoard* GameBoard::getInstance(std::string pass){
    if (instance == nullptr && pass == "xyzzy") {
            instance = new GameBoard();
    }
    return (pass == "xyzzy") ? instance : nullptr;
}

GameBoard* GameBoard::getInstance(std::string pass, Config& settings){
    if (instance == nullptr && pass == "xyzzy") {
            instance = new GameBoard(settings);
    }
    return (pass == "xyzzy") ? instance : nullptr;
}

InternalBoardSquare& GameBoard::getSquare(int row, int col){
    return grid[row][col];
}

InternalBoardSquare& GameBoard::findRobot(RobotColor color){
    if (color == RobotColor::RED){
        for (int i = 0; i < 17; i++){
            for (int j = 0; j < 17; j++){
                if(grid[i][j].redRobotPresent())
                    return grid[i][j];
                else continue;
            }
        }
    } else {
        for (int i = 0; i < 17; i++){
            for (int j = 0; j < 17; j++){
                if(grid[i][j].blueRobotPresent())
                    return grid[i][j];
                else continue;
            }
        }
    }
    /* Should never happen - for compiler */
    return grid[0][0];
}

GameBoard* GameBoard::instance = nullptr;

bool GameBoard::MoveRobot(RobotMoveRequest& mr){
    /* Find the robot */
    InternalBoardSquare& robotSquare = (mr.robot == RobotColor::RED) ? findRobot(RobotColor::RED) : findRobot(RobotColor::BLUE);

    switch (mr.move)
    {
    case RobotMove::ROTATELEFT:
        if (robotSquare.robotDirection() == Direction::NORTH) robotSquare.setRobotDir(Direction::WEST);
        if (robotSquare.robotDirection() == Direction::WEST) robotSquare.setRobotDir(Direction::SOUTH);
        if (robotSquare.robotDirection() == Direction::SOUTH) robotSquare.setRobotDir(Direction::EAST);
        if (robotSquare.robotDirection() == Direction::EAST) robotSquare.setRobotDir(Direction::NORTH);
        notifyObservers(GameBoardNotification::RobotMoved(RobotMove::ROTATELEFT, mr.robot, robotSquare.robotDirection(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()));
        break;
    case RobotMove::ROTATERIGHT:
        if (robotSquare.robotDirection() == Direction::NORTH) robotSquare.setRobotDir(Direction::EAST);
        if (robotSquare.robotDirection() == Direction::WEST) robotSquare.setRobotDir(Direction::NORTH);
        if (robotSquare.robotDirection() == Direction::SOUTH) robotSquare.setRobotDir(Direction::WEST);
        if (robotSquare.robotDirection() == Direction::EAST) robotSquare.setRobotDir(Direction::SOUTH);
        notifyObservers(GameBoardNotification::RobotMoved(RobotMove::ROTATERIGHT, mr.robot, robotSquare.robotDirection(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()));
        break;
    case RobotMove::FORWARD:
        if (robotSquare.robotDirection() == Direction::NORTH) {
            setSquareColor(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), (robotSquare.blueRobotPresent() ? SquareColor::BLUE : SquareColor::RED));
            InternalBoardSquare next = getSquare(robotSquare.getPaintBotRow()-1, robotSquare.getPaintBotCol());
            notifyObservers(GameBoardNotification::RobotMoved(RobotMove::FORWARD, mr.robot, Direction::NORTH, robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow()-1, robotSquare.getPaintBotCol()));
            next.setPaintBot((robotSquare.getPaintBot()));
            robotSquare.setPaintBot(nullptr);
            robotSquare.getPaintBot()->setRow(robotSquare.getPaintBot()->getRow()-1);
        }
        if (robotSquare.robotDirection() == Direction::WEST) {
            setSquareColor(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), (robotSquare.blueRobotPresent() ? SquareColor::BLUE : SquareColor::RED));
            InternalBoardSquare next = getSquare(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()-1);
            notifyObservers(GameBoardNotification::RobotMoved(RobotMove::FORWARD, mr.robot, Direction::WEST, robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()-1));
            next.setPaintBot((robotSquare.getPaintBot()));
            robotSquare.setPaintBot(nullptr);
            robotSquare.getPaintBot()->setRow(robotSquare.getPaintBot()->getCol()-1);
        }
        if (robotSquare.robotDirection() == Direction::SOUTH) {
            setSquareColor(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), (robotSquare.blueRobotPresent() ? SquareColor::BLUE : SquareColor::RED));
            InternalBoardSquare next = getSquare(robotSquare.getPaintBotRow()+1, robotSquare.getPaintBotCol());
            notifyObservers(GameBoardNotification::RobotMoved(RobotMove::FORWARD, mr.robot, Direction::SOUTH, robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow()+1, robotSquare.getPaintBotCol()));
            next.setPaintBot((robotSquare.getPaintBot()));
            robotSquare.setPaintBot(nullptr);
            robotSquare.getPaintBot()->setRow(robotSquare.getPaintBot()->getRow()+1);
        }
        if (robotSquare.robotDirection() == Direction::EAST) {
            setSquareColor(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), (robotSquare.blueRobotPresent() ? SquareColor::BLUE : SquareColor::RED));
            InternalBoardSquare next = getSquare(robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()+1);
            notifyObservers(GameBoardNotification::RobotMoved(RobotMove::FORWARD, mr.robot, Direction::EAST,  robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol(), robotSquare.getPaintBotRow(), robotSquare.getPaintBotCol()+1));
            next.setPaintBot((robotSquare.getPaintBot()));
            robotSquare.setPaintBot(nullptr);
            robotSquare.getPaintBot()->setRow(robotSquare.getPaintBot()->getCol()+1);
        }
        break;
    case RobotMove::NONE:
        break;
    }
    return true;
}

bool GameBoard::PaintBlobHit(RobotMoveRequest& mr){
    /* Find the robot */
    InternalBoardSquare& robotSquare = (mr.robot == RobotColor::RED) 
        ? findRobot(RobotColor::RED)
        : findRobot(RobotColor::BLUE);

    switch(robotSquare.robotDirection()){
        case Direction::NORTH:
            for(int i = 0; i + robotSquare.getPaintBotRow() > 0; i++){
                InternalBoardSquare tmp = grid[robotSquare.getPaintBotRow()-i][robotSquare.getPaintBotCol()];
                if (mr.robot == RobotColor::RED){
                    if (tmp.blueRobotPresent()) return true;
                    else continue; 
                }
                else {
                    if (tmp.redRobotPresent()) return true;
                    else continue; 
                }
            }
            return false;
            break;
        case Direction::WEST:
            for(int i = 0; i + robotSquare.getPaintBotCol() > 0; i++){
                InternalBoardSquare tmp = grid[robotSquare.getPaintBotRow()][robotSquare.getPaintBotCol()-i];
                if (mr.robot == RobotColor::RED){
                    if (tmp.blueRobotPresent()) return true;
                    else continue; 
                }
                else {
                    if (tmp.redRobotPresent()) return true;
                    else continue; 
                }
            }
            return false;
            break;
        case Direction::SOUTH:
            for(int i = 0; i + robotSquare.getPaintBotRow() < 17; i++){
                InternalBoardSquare tmp = grid[robotSquare.getPaintBotRow()+i][robotSquare.getPaintBotCol()];
                if (mr.robot == RobotColor::RED){
                    if (tmp.blueRobotPresent()) return true;
                    else continue; 
                }
                else {
                    if (tmp.redRobotPresent()) return true;
                    else continue; 
                }
            }
            return false;
            break;
        case Direction::EAST:
            for(int i = 0; i + robotSquare.getPaintBotCol() < 17; i++){
                InternalBoardSquare tmp = grid[robotSquare.getPaintBotRow()][robotSquare.getPaintBotCol()+i];
                if (mr.robot == RobotColor::RED){
                    if (tmp.blueRobotPresent()) return true;
                    else continue; 
                }
                else {
                    if (tmp.redRobotPresent()) return true;
                    else continue; 
                }
            }
            return false;
            break;
    }
    return false;
}

int GameBoard::redScore() {
    int redscore = 0;
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 17; j++){
            redscore += (grid[i][j].getColorSquare() == SquareColor::RED) ? 1 : 0;
        }
    }
    notifyObservers(GameBoardNotification::ScoreChanged(redscore, true));
    return redscore;
}

int GameBoard::blueScore() {
    int bluescore = 0;
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 17; j++){
            bluescore += (grid[i][j].getColorSquare() == SquareColor::BLUE) ? 1 : 0;
        }
    }
    notifyObservers(GameBoardNotification::ScoreChanged(bluescore, false));
    return bluescore;

}

void GameBoard::setSquareColor(int row, int col, SquareColor c){
    InternalBoardSquare square = getSquare(row, col);
    square.setSquareColor(c);
    notifyObservers(GameBoardNotification::SquareColorChanged(c, row, col));
}

void GameBoard::setRobotPaintColor(RobotColor robot, SquareColor sc){
    InternalBoardSquare square = findRobot(robot);
    Robot* r = square.getPaintBot();
    r->setPaintColor(sc == SquareColor::RED ? SquareColor::RED : SquareColor::BLUE);
}

ExternalBoardSquare** GameBoard::getLongRangeScan(){
    ExternalBoardSquare** externalgrid = new ExternalBoardSquare*[17];
    for (int i = 0; i < 17; i++){
        externalgrid[i] = new ExternalBoardSquare[17];
        for (int j = 0; j < 17; j++){
            externalgrid[i][j] = ExternalBoardSquare(grid[i][j]);
        }
    }
    return externalgrid;
}

/**
 * Robot is always centered at the grid
 * Whatever direction the robot is facing is consider 'up'
 * the grid is 5x5
 */
ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc){
    /* Find the robot */
    InternalBoardSquare robotSquare;
    if (rc == RobotColor::RED){
        robotSquare = findRobot(RobotColor::RED);
    }
    else {
        robotSquare = findRobot(RobotColor::BLUE);
    }    

    ExternalBoardSquare** shortGrid = new ExternalBoardSquare*[5];
    for (int i = 0; i < 5; i++){
        shortGrid[i] = new ExternalBoardSquare[5];
    }

    int row = 0;
    int col = 0;
    switch (robotSquare.robotDirection()){
        case Direction::NORTH:
            for (int i = -2; i < 3; i++){
                col = 0;
                for (int j = -2; j < 3; j++){
                    if (robotSquare.getPaintBotRow() + i > 16 
                    || robotSquare.getPaintBotRow() + i < 0
                    || robotSquare.getPaintBotCol() + j > 16
                    || robotSquare.getPaintBotCol() + j < 0){
                        /* [0][0] is a wall, therefore just make oob walls*/
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(0,0));
                    } else{
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(robotSquare.getPaintBotRow()+i, robotSquare.getPaintBotCol()+j));
                    }
                    col++;
                }
                row++;
            }
            break;
        case Direction::SOUTH:
            for (int i = 2; i > -3; i--){
                col = 0;
                for (int j = 2; j > -3; j--){
                    if (robotSquare.getPaintBotRow() + i > 16 
                    || robotSquare.getPaintBotRow() + i < 0
                    || robotSquare.getPaintBotCol() + j > 16
                    || robotSquare.getPaintBotCol() + j < 0){
                        /* [0][0] is a wall, therefore just make oob walls*/
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(0,0));
                    } else{
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(robotSquare.getPaintBotRow()+i, robotSquare.getPaintBotCol()+j));
                    }
                    col++;
                }
                row++;
            }
            break;
        case Direction::EAST:
            for (int i = 2; i > -3; i--){ // Column
                col = 0;
                for (int j = -2; j < 3; j++){ // Row
                    if (robotSquare.getPaintBotRow() + i > 16 
                    || robotSquare.getPaintBotRow() + i < 0
                    || robotSquare.getPaintBotCol() + j > 16
                    || robotSquare.getPaintBotCol() + j < 0){
                        /* [0][0] is a wall, therefore just make oob walls*/
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(0,0));
                    } else{
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(robotSquare.getPaintBotRow()+j, robotSquare.getPaintBotCol()+i));
                    }
                    col++;
                }
                row++;
            }
            break;
        case Direction::WEST:
            for (int i = -2; i < 3; i++){ // Column
                col = 0;
                for (int j = -2; j < 3; j++){ // Row
                    if (robotSquare.getPaintBotRow() + i > 16 
                    || robotSquare.getPaintBotRow() + i < 0
                    || robotSquare.getPaintBotCol() + j > 16
                    || robotSquare.getPaintBotCol() + j < 0){
                        /* [0][0] is a wall, therefore just make oob walls*/
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(0,0));
                    } else{
                        shortGrid[row][col] = ExternalBoardSquare(getSquare(robotSquare.getPaintBotRow()+j, robotSquare.getPaintBotCol()+i));
                    }
                    col++;
                }
                row++;
            }
            break;
    }

    return shortGrid;
}

void PlainDisplay::display() {
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 17; j++){
            if (grid[i][j].getSquareType() == SquareType::WALL){
                std::cout << "WWWW ";
                continue;
            }
            /* first character: square color*/
            switch(grid[i][j].getColorSquare()){
                case SquareColor::RED:
                    std::cout<< "R";
                    break;
                case SquareColor::BLUE:
                    std::cout<< "B";
                    break;
                case SquareColor::WHITE:
                    std::cout<< "W";
                    break;
            }

            /* Second Character: robot present*/
            if (grid[i][j].blueRobotPresent()) std::cout << "B";
            else if (grid[i][j].redRobotPresent()) std::cout << "R";
            else { std::cout << "-"; }

            std::cout << (grid[i][j].getSquareType() == SquareType::ROCK ? "X" : "-");
            std::cout << (grid[i][j].getSquareType() == SquareType::FOG ? "X" : "-");
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

PlainDisplay::PlainDisplay(const GameBoard& initial){
    GameBoard *instance = initial.getInstance("xyzzy");
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 17; j++){
            grid[i][j] = instance->getSquare(i,j);
        }
    }
    instance->addObserver(this);
}

void PlainDisplay::update(const GameBoardNotification& notif) {
    switch(notif.getEventType()){
        case GameBoardNotification::EventType::COLOR:
            printf("Updated Display: Color, %d %d", notif.getXCoord(), notif.getYCoord());
            grid[notif.getXCoord()][notif.getYCoord()].setSquareColor(notif.getSquareColor());
            break;
        case GameBoardNotification::EventType::MOVE:
            // Only clear robot from source if actually moving
            if (notif.getMoveType() == RobotMove::FORWARD) {
                // Create new robot state in destination
                grid[notif.getToXCoordinate()][notif.getToYCoordinate()].setPaintBot(
                    grid[notif.getFromXCoordinate()][notif.getFromYCoordinate()].getPaintBot()
                );

                grid[notif.getFromXCoordinate()][notif.getFromYCoordinate()].setPaintBot(nullptr);
            } else {
                // For rotation, just update the direction
                grid[notif.getFromXCoordinate()][notif.getFromYCoordinate()].setRobotDir(
                    notif.getDirection()
                );
            }
            break;
        case GameBoardNotification::EventType::SCORE:
            printf("Updated Display: Score");
            if (notif.getScoringRobot() == RobotColor::RED){
                redscore = notif.getRedScore();
            } else {
                bluescore = notif.getBlueScore();
            }
            break;
    }
    printf(": %s\n",
    notif.getSquareColor() == SquareColor::RED 
    ? "RED" 
    : notif.getSquareColor() == SquareColor::BLUE ? "BLUE" : "WHITE");
}