#pragma once

#include "RobotTypes.h"
#include "ExternalBoardSquare.h"

#include <string>
#include <random>
#include <vector>
#include <algorithm>

class IRobotAgent {
    public:
    virtual std::string getRobotName() = 0;
    virtual std::string getRobotCreator() = 0;
    virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) = 0;
    virtual void setRobotColor(RobotColor) = 0;
};

class randomRobot : public IRobotAgent {
    private:
        std::string robotName = "RANDOM";
        std::string robotCreator = "DEFAULT";
        RobotMoveRequest move;
        RobotColor color;
    public:
        std::string getRobotName() { return robotName; };
        std::string getRobotCreator() { return robotCreator; };
        RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs){
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<int> dist(0,3);
            RobotMove rmove;
            switch (dist(engine)) {
            case 0:
                rmove = RobotMove::ROTATELEFT;
                break;
            case 1:
                rmove = RobotMove::ROTATERIGHT;
                break;
            case 2:
                rmove = RobotMove::FORWARD;
                break;
            case 3:
                rmove = RobotMove::NONE;
                break;
            }
            RobotMoveRequest* move = new RobotMoveRequest{color, rmove, false};
            return move;
        }
        void setRobotColor(RobotColor c) { color = c; }
};

class lazyRobot : public IRobotAgent {
    private:
        std::string robotName = "LAZY";
        std::string robotCreator = "DEFAULT";
        RobotMoveRequest move;
        RobotColor color;
    public:
        std::string getRobotName() {return robotName;}
        std::string getRobotCreator() {return robotCreator;}
        RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs){
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<int> dist(0,1);
            RobotMove decision = (dist(engine)) ? RobotMove::ROTATELEFT : RobotMove::ROTATERIGHT;
            RobotMoveRequest *move = new RobotMoveRequest{ color, decision, true };
            return move;
        }
        void setRobotColor(RobotColor c) {color = c;}
};


class RobotAgentRoster {
    private:
        std::vector<IRobotAgent*> agents;
        static inline RobotAgentRoster* instance = nullptr;  // inline declaration
        RobotAgentRoster() = default;  // can be defaulted if no special initialization needed
        void initialize(){
            IRobotAgent* lazy = new lazyRobot(); 
            IRobotAgent* random = new randomRobot(); 
            agents.push_back(lazy);
            agents.push_back(random);
        }; 
    public:
        static RobotAgentRoster* getInstance(){
            if (!instance){
                instance = new RobotAgentRoster();
                instance->initialize();
            }
            return instance;
        };
        RobotAgentRoster(const RobotAgentRoster&) = delete;
        RobotAgentRoster& operator=(const RobotAgentRoster) = delete;

        void add(IRobotAgent* agent) {
            if (std::find(agents.begin(), agents.end(), agent) == agents.end()){
                agents.push_back(agent);
            }
        }
        IRobotAgent* operator[](int i){
            return agents.at(i);
        };
        IRobotAgent* operator[](std::string name){
            IRobotAgent* ret = nullptr; 
            for (int i = 0; i < agents.size(); i++){
                if (agents.at(i)->getRobotName() == name){
                    ret = agents.at(i);
                }
            }
            return ret;
        };
};

template<typename T>
class Pair{
    private:
        T* items = new T[2];
    public:
        Pair(T* a, T* b){
            items[0] = a;
            items[1] = b;
        }
        T* getFirst() const {
            return items[0];
        }
        T* getSeconds() const {
            return items[1];
        }

        /* needs to return T* instead of T& 
        because of possible nullity */
        T* operator[](int idx){
            if (idx == 1) return items[0];
            else if (idx == 2) return items[1];
            else return nullptr;
        }
};