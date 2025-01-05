#include "GameBoard.h"
#include "ITest.h"
#include <iostream>

class GameBoardTest : public ITest{
    public:
    bool doTests() {
        GameBoard *board = GameBoard::getInstance("xyzzy");
        PlainDisplay display (*board); 
        board->addObserver(&display);
        try {
            display.display();
            return true;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            return false;
        }
        

    }
};

int main(int argc, char const *argv[])
{
    GameBoardTest test;
    
    std::cout << "Checking Display: \n" << std::boolalpha << test.doTests() << "\n";
    return 0;
}
