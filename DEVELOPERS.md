# Project 2 : PaintBots 

This end of the project is for creating the Robot Agents that take place inside of the GameBoard, and then write the GameLogic to simulate the playing of the game. 

## Robots

Currently, there is 1 known issue:
- Random Robot does not first check if the move is valid before randomly selecting a move

There is also many issues relating to potential dependecy problems, but the error codes are hard to read. This issue stems from how I handled robots in Part B, and the transition to Part C and the refactor to the robot made it hard to keep track of everywhere where robots are being handled, and I think I resolved the majority of the circular dependency issues, but I reckon that some are persist and causing the majority of errors. 

## GameLogic 

The GameLogic works *in theory* if the robots would correctly compile, but there is also probably some issues stemming from here as well. 

The main reason that I think my program got so messed up from the refactor stems from how InternalBoardSquare keeps a pointer to a robot, and I was being very liberal with just adding variables and methods to the temporary robot class to have it work, that when it came time to *actually write the robot class* there may be logic that doesn't fully work with the new setups.

## The Good

All header files are correctly written and represetative of their structures.
The Pair() template has no errors. 
The flow of reading file inputs from the command line, creating the corresponding objects, and starting the game loop in theory work fine if the code would compile. 


## Custom Robot: AntiRandom

I also did not have time to write my own version of beating the random robot, however I am currently enrolled in CS4720 so I can explain many ways to efficiently dismantly the random algorithm. A naive approach is to simply move towards empty squares, and if you get stuck against a wall or surrounding squares of your color, take a long range scan and move towards the next open square.

An agent that would completely destory the AntiRandom would be a MonteCarloTreeSearch robot which simulates random playouts of each robot given the current state of the board, and updates the state tree corresponding to the outcome of the random playout, and the robot takes the move that is most likely to lead them to victory. This robot could verifiably beat the robot in a fixed percentage due to the probabilistic nature of MCTS. 

I still intend to fix this code and implement these robots for my own well-being over winter break. 