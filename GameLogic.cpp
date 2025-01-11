#include "GameLogic.h"
#include "Config.h"
#include "GameBoard.h"
#include "RobotTypes.h"
#include "IRobotAgent.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string boardconfig;
    std::string robotconfig;
    if (argc != 3){ 
        std::cout << "Usage: ./paintbots boardconfig.txt robotconfig.txt\n";
        return 1; 
    } else {
        boardconfig = argv[1];
        robotconfig = argv[2];
    }

    GameLogic game;
    game.playGame(boardconfig, robotconfig);
    return 0;
}

GameLogic::GameLogic() 
    : pause(true), iterations(300)  
    { }

void GameLogic::playGame(std::string boardconfig, std::string robotconfig){
    Config settings(boardconfig);
    GameBoard* board = GameBoard::getInstance("xyzzy", settings);
    PlainDisplay display(*board);
    

    std::ifstream robotConfiguration(robotconfig);
    if (!robotConfiguration.is_open()){
        throw std::invalid_argument("Error opening robot config file\n");
    }

    std::string line; 
    /* Red Robot Strategy */
    std::getline(robotConfiguration, line);
    Robot* red = board->findRobot(RobotColor::RED).getPaintBot();
//    red.setColor(RobotColor::RED);   // already happened in GameBoard but sanity check
    IRobotAgent* redstrategy = nullptr;
    if (line == "Lazy") { redstrategy = new lazyRobot();} 
    else { redstrategy = new randomRobot();} 
    red->setRobotAgent(redstrategy);

    /* Blue Robot Strategy */
    std::getline(robotConfiguration, line);
    Robot* blue = board->findRobot(RobotColor::BLUE).getPaintBot();
//    blue.setColor(RobotColor::BLUE);   // already happened in GameBoard but sanity check
    IRobotAgent* bluestrategy = nullptr;
    if (line == "Lazy") { bluestrategy = new lazyRobot();} 
    else { bluestrategy = new randomRobot();} 
    blue->setRobotAgent(bluestrategy);

    /* Game Loop */
    for (int i = 0; i < iterations; i++){
        printf("%d\n", i);
        printf("RED  %d, %d\n", board->findRobot(RobotColor::RED).getPaintBotRow(), board->findRobot(RobotColor::RED).getPaintBotCol());
        printf("BLUE %d, %d\n", board->findRobot(RobotColor::BLUE).getPaintBotRow(), board->findRobot(RobotColor::BLUE).getPaintBotCol());
        /* Game Ending Checks */
        // Red bumps into rock or wall
        if (board->findRobot(RobotColor::RED).getSquareType() == SquareType::ROCK
        || board->findRobot(RobotColor::RED).getSquareType() == SquareType::WALL){
            winner = RobotColor::BLUE;
            break;
        }
        // Blue bumps into rock or wall 
        else if (board->findRobot(RobotColor::BLUE).getSquareType() == SquareType::ROCK
        || board->findRobot(RobotColor::BLUE).getSquareType() == SquareType::WALL){
            winner = RobotColor::RED;
            break;
        }
        // they bump into each other
        else if (board->findRobot(RobotColor::BLUE).getPaintBotRow() == board->findRobot(RobotColor::RED).getPaintBotRow()
        && board->findRobot(RobotColor::BLUE).getPaintBotCol() == board->findRobot(RobotColor::RED).getPaintBotCol()){
            break;  // get out of the loop -> count the tiles 
        }

        ExternalBoardSquare** redsrs = board->getShortRangeScan(RobotColor::RED);
        ExternalBoardSquare** bluesrs = board->getShortRangeScan(RobotColor::BLUE);

        IRobotAgent* redstrat = red->getRobotAgent();
        RobotMoveRequest* redMove = redstrat->getMove(nullptr, redsrs);

        printf("RED MOVE: %s\n", redMove->move == RobotMove::FORWARD ? "FORWARD"
        : redMove->move == RobotMove::ROTATELEFT ? "ROTATELEFT" 
        : redMove->move == RobotMove::ROTATERIGHT ? "ROTATERIGHT"
        : "NONE");

        IRobotAgent* bluestrat = blue->getRobotAgent();
        RobotMoveRequest* blueMove = bluestrat->getMove(nullptr, bluesrs);

        printf("BLUE MOVE: %s\n", blueMove->move == RobotMove::FORWARD ? "FORWARD"
        : blueMove->move == RobotMove::ROTATELEFT ? "ROTATELEFT" 
        : blueMove->move == RobotMove::ROTATERIGHT ? "ROTATERIGHT"
        : "NONE");

        board->MoveRobot(*redMove);
        board->MoveRobot(*blueMove);
        display.display();
         // Properly delete 2D arrays
        for (int j = 0; j < 5; j++) {  // Assuming 5x5 scan area
            delete[] redsrs[j];
            delete[] bluesrs[j];
        }
        delete[] redsrs;
        delete[] bluesrs;
        
        delete redMove;
        delete blueMove;
        
        if (pause) {
            std::cin.get();
        }
    }
    if (winner != RobotColor::RED || winner != RobotColor::BLUE){
        winner = (board->redScore() > board->blueScore()) ? RobotColor::RED : RobotColor::BLUE;
    }
    std::cout << "Winner! : " << ((GameLogic::winner == RobotColor::RED) ? "RED" : "BLUE") << "\n";
    delete redstrategy;
    delete bluestrategy;
}


void GameLogic::setPause(bool pausemode) { pause = pausemode; }