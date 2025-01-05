all: PaintBots GameBoardTest ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest

BoardSquare.o: BoardSquare.cpp
	g++ -c $^ -o $@

InternalBoardSquare.o: InternalBoardSquare.cpp 
	g++ -c $^ -o $@

ExternalBoardSquare.o: ExternalBoardSquare.cpp
	g++ -c $^ -o $@

GameBoard.o: GameBoard.cpp 
	g++ -c $^ -o $@

GameBoardTest.o: GameBoardTest.cpp
	g++ -c $^ -o $@

Config.o: Config.cpp
	g++ -c $^ -o $@

ConfigTest.o: ConfigTest.cpp
	g++ -c $^ -o $@

ExternalBoardSquareTest.o: ExternalBoardSquareTest.cpp
	g++ -c $^ -o $@

InternalBoardSquareTest.o: InternalBoardSquareTest.cpp
	g++ -c $^ -o $@

BoardSquareTest.o: BoardSquareTest.cpp
	g++ -c $^ -o $@

Robot.o: Robot.cpp
	g++ -c $^ -o $@

GameLogic.o: GameLogic.cpp
	g++ -c $^ -o $@

ConfigTest: Config.o ConfigTest.o
	g++ $^ -o $@

BoardSquareTest: BoardSquare.o BoardSquareTest.o
	g++ $^ -o $@

ExternalBoardSquareTest: BoardSquare.o ExternalBoardSquare.o ExternalBoardSquareTest.o
	g++ $^ -o $@

InternalBoardSquareTest: BoardSquare.o InternalBoardSquare.o InternalBoardSquareTest.o
	g++ $^ -o $@

GameBoardTest: GameBoardTest.o GameBoard.o Config.o BoardSquare.o InternalBoardSquare.o ExternalBoardSquare.o Robot.o
	g++ $^ -o $@

PaintBots: GameLogic.o GameBoard.o Config.o BoardSquare.o InternalBoardSquare.o ExternalBoardSquare.o Robot.o 
	g++ $^ -o $@

clean:
	rm PaintBots GameBoardTest ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest *.o