#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;

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

// Function to easily output the board
void Puzzle_Output(vector<int> nums){
    cout << " ___________" << endl;
    cout << "|_" << nums.at(0) << "_|_" << nums.at(1) << "_|_" << nums.at(2) << "_|" << endl;
    cout << "|_" << nums.at(3) << "_|_" << nums.at(4) << "_|_" << nums.at(5) << "_|" << endl;
    cout << "|_" << nums.at(6) << "_|_" << nums.at(7) << "_|_" << nums.at(8) << "_|" << endl;
    cout << endl;
}

Node SelectPuzzle(){
    int userInput;
    Node initialState;
    vector<int> easyPuzzle = {1, 2, 3, 4, 0, 6, 7, 5, 8};
    vector<int> mediumPuzzle = {0, 2, 5, 1, 4, 8, 6, 7, 3};
    vector<int> hardPuzzle = {1, 6, 7, 5, 0, 3, 4, 8, 2};

    cout << "Would you like to use an example you input your own puzzle?" << endl;
    cout << "1: Use an example: " << endl;
    cout << "2: Input a new puzzle: " <<  endl;

    bool temp = true;
    while (temp){
        cin >> userInput;
        if(userInput != 1 && userInput != 2){
            cout << endl << "Please enter either 1 or 2" << endl;
        }
        else{
            temp = false;
        } 
    }

    //Premade puzzles
    if (userInput == 1){
        cout << "1. Easy: " << endl;
        Puzzle_Output(easyPuzzle);
        cout << endl;
        cout << "2. Meduium: " << endl;
        Puzzle_Output(mediumPuzzle);
        cout << endl;
        cout << "3 Hard: " << endl;
        Puzzle_Output(hardPuzzle);
        cout << endl;

        cout << "Which number would you like to solve: " << endl;
        temp = true;
        while (temp){
            cin >> userInput;
            if(userInput != 1 && userInput != 2 && userInput != 3 ){
                cout << endl << "Please enter either 1, 2, or 3" << endl;
            }
            else{
                temp = false;
            } 
        }
        if (userInput == 1){
            initialState.pos = easyPuzzle;
        }
        else if(userInput == 2){
            initialState.pos = mediumPuzzle;
        }
        else if(userInput == 3){
            initialState.pos = hardPuzzle;
        }
    }
    
    //Custom puzzles

    return initialState;
}

// Next three function will be for the sorting algorithm
// They are referenced from https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
// Tested with https://www.programiz.com/cpp-programming/online-compiler/
int minIndex(queue<Node> &q, int sortedIndex) { 
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
void insertMinToRear(queue<Node> &q, int min_index){ 
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
void Queuing_Function(queue<Node> &q){
    for (int i = 1; i <= q.size(); i++) { 
        int min_index = minIndex(q, q.size() - i); 
        insertMinToRear(q, min_index); 
    } 
}

// Heuristic Functions
int MisplacedTileHeuristic(Node& node){
    //SImply counting how many numbers are out of place
    int count = 0;
    for(int i = 0; i <= 7; i++){
        if (node.pos.at(0) != i + 1){
            count++;
        }
    }
    return count;
}
int ManhattanHeuristic(Node& node){
    //Counting distance of each tile from goal state
    vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    vector<int> currState = node.pos;
    int count = 0;
    int currX, currY, goalX, goalY = -99;

    //Need to calculate the total distance (up and sideways) each tile has to move
    for(int i = 0; i <= 8; i++){
        //Iterate through each tile and determine where it should be
        if(currState.at(i) != 0){       //Skip 0 (empty) tile
            if (currState.at(i) != goalState.at(i)){    //Only need to add if number not at goal state
                //Current position of i (0,0 is top left corner)
                currX = i % 3;
                currY = i / 3;
                //Where the number should be
                goalX = (currState.at(i) - 1) % 3;
                goalY = (currState.at(i) - 1) / 3;
                //Adding difference to heuristic
                count += abs(currX - goalX) + abs(currY - goalY);
            }
        }
    }

    return count;
}

int main() {

    // queue<Node> nodes;
    // bool temp = true;

    // while (temp){
    //     if (nodes.empty()){
    //         cout << "Failure. No solution" << endl;
    //         return 0; // Failure, no solution
    //     }
    //     Node node = nodes.pop();

    //     if (problem.GoalTest(node)){
    //         return node;
    //     }

    //     nodes = QUEUING_FUNCTION(nodes, EXPAND(node,problem.OPERATORS))
    //     return 0;
    // }
    Node puzzle = SelectPuzzle();
    for (auto i : puzzle.pos)
        cout << i << " ";

    return 0;
}