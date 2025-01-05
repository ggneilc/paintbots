#include "ITest.h"
#include "ExternalBoardSquare.h"
#include <iostream>
#include <type_traits>

class ExternalBoardSquareTest : public ITest {
    public:
    bool doTests(){
        if(std::is_base_of<BoardSquare, ExternalBoardSquare>::value){
            return true;
        }
        else { return false; }
    }
};


int main()
{
    ExternalBoardSquareTest test;
    std::cout << "ExternalBoardSquareTest: "<< std::boolalpha << test.doTests() << "\n";
    return 0;
}
