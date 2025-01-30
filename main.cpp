#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    queue<int> myQueue;

    return 0;
}

struct Node {
    // I will write a struct that represents the 8 puzzle for each node. 
    // I will represent the position of each number with a1, a2, ..., c3
    //
    //    1  2  3
    // a  #  #  #
    // b  #  #  #
    // c  #  #  #
    //
    // I will put these in a vector: positions = [a1, a2, ..., c3]

    vector<int> pos = vector<int>(9);

    int g; // Cost
    int h; // Heuristic
    int f; // g + h
};

// Node Uniform_Search(problem, QUEUING_FUNCTION){
//     queue<Node> nodes;
//     bool temp = true;

//     while (temp){
//         if (nodes.empty()){
//             return 1; // Failure, no solution
//         }
//         node = nodes.pop();

//         if problem.GoalTest(node){
//             return node;
//         }
//         nodes = QUEUING_FUNCTION(nodes, EXPAND(node,problem.OPERATORS))
//         return 0;
//     }
// }

int MisplacedTileHeuristic(Node& node){
    int count = 0;

    if (node.pos.at(0) != 1){
        count++;
    }
    if (node.pos.at(1) != 2){
        count++;
    }
    if (node.pos.at(2) != 3){
        count++;
    }
    if (node.pos.at(3) != 4){
        count++;
    }
    if (node.pos.at(4) != 5){
        count++;
    }
    if (node.pos.at(5) != 6){
        count++;
    }
    if (node.pos.at(6) != 7){
        count++;
    }
    if (node.pos.at(7) != 8){
        count++;
    }

    return count;
}
