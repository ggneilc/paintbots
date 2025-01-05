#include "ITest.h"
#include "InternalBoardSquare.h"
#include <iostream>
#include <type_traits>

class InternalBoardSquareTest : public ITest {
    public:
    bool doTests() {
        if(std::is_base_of<BoardSquare, InternalBoardSquare>::value){
            return true;
        }
        else { return false; }
    }
};

int main()
{
    InternalBoardSquareTest test;
    std::cout << "InternalBoardSquareTest: " << std::boolalpha << test.doTests() << "\n";
    return 0;
}
