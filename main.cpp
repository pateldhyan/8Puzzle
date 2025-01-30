#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int main() {

    queue<int> myQueue;

    return 0;
}

struct Node {
    // I will write a struct that represents the 8 puzzle for each node. 
    // I will represent the position of each number with a1, a2, ..., c3
    //
    //    1   2   3
    //    _1____2____3__
    // a |_a1_|_a2_|_a3_|
    // b |_b1_|_b2_|_b3_| 
    // c |_c1_|_c2_|_c3_|
    //
    // I will put these in a vector: pos = [a1, a2, ..., c3]

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

//Next three function will be for the sorting algorithm
//They are referenced from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
int minIndex(queue<Node> &q, int sortedIndex) 
{ 
    int min_index = -1; 
    int min_val = INT_MAX; 
    int n = q.size(); 
    for (int i=0; i<n; i++) { 
        Node curr = q.front(); 
        q.pop();  
        if (curr.f <= min_val && i <= sortedIndex) 
        { 
            min_index = i; 
            min_val = curr.f; 
        } 
        q.push(curr);
    } 
    return min_index; 
} 
void insertMinToRear(queue<Node> &q, int min_index) 
{ 
    Node min_Node; 
    int n = q.size(); 
    for (int i = 0; i < n; i++) { 
        Node curr = q.front(); 
        q.pop(); 
        if (i != min_index) 
            q.push(curr); 
        else
            min_Node = curr; 
    } 
    q.push(min_Node); 
} 
queue<Node> Queuing_Function(queue<Node> &q){
    for (int i = 1; i <= q.size(); i++) { 
        int min_index = minIndex(q, q.size() - i); 
        insertMinToRear(q, min_index); 
    } 
}

int MisplacedTileHeuristic(Node& node){
    
    //SImply counting how many numbers are out of place
    int count = 0;

    if(node.pos.at(0) != 1){
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


int ManhattanHeuristic(Node& node){
    
    //Need to calculate the total distance (up and sideways) each tile has to move
    for(int i = 0; i < 9; i++){
        //Iterate through each tile and determine where it should be
        int currNum = node.pos.at(i);
        if(currNum != 0){       //Skip 0 (empty) tile
            
        }
    }
}