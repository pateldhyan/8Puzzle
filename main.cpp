#include <iostream>
#include <queue>
using namespace std;

int main() {

    queue<int> myQueue;

    return 0;
}

//Need to replace ints with structs or something to represent the puzzle space
int Uniform_Search(problem, QUEUING_FUNCTION){
    queue<int> nodes;
    bool temp = true;

    while (temp){
        if (nodes.empty()){
            return 1; // Failure, no solution
        }
        node = nodes.pop();
        if problem.GoalTest(node){
            return node;
        }
        nodes = QUEUING_FUNCTION(nodes, EXPAND(node,problem.OPERATORS))
        return 0;
    }
}
