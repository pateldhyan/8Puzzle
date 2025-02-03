#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;

// Struct to represent each node
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
    // I will put these in a vector: pos = [a1, a2, ..., c2, c3]

    vector<int> pos = vector<int>(9);

    int g; // Cost
    int h; // Heuristic
    int f; // g + h

    //Constructor
    Node() {}
    Node(vector<int> posVec, int gVal, int hVal) : pos(posVec), g(gVal), h(hVal), f(gVal+hVal) {}
};

// Function to easily output the board
void Puzzle_Output(vector<int> nums){
    cout << " ___________" << endl;
    cout << "|_" << nums.at(0) << "_|_" << nums.at(1) << "_|_" << nums.at(2) << "_|" << endl;
    cout << "|_" << nums.at(3) << "_|_" << nums.at(4) << "_|_" << nums.at(5) << "_|" << endl;
    cout << "|_" << nums.at(6) << "_|_" << nums.at(7) << "_|_" << nums.at(8) << "_|" << endl;
    cout << endl;
}

// Interface function to select or input a puzzle
Node SelectPuzzle(){
    int userInput;
    vector<int> initialVec = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

    Node initialState(initialVec, 0, 0);
    vector<int> easyPuzzle = {1, 2, 3, 4, 0, 6, 7, 5, 8};
    vector<int> mediumPuzzle = {2, 4, 3, 7, 1, 6, 0, 5, 8};
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
    else{
        vector<int> customPuzzle(9);
        cout << "Please enter your custom puzzle 3 numbers at a time with a space between each number. Enter 0 for the empty space. " << endl;
        cout << "First line:  "; cin >> customPuzzle.at(0) >> customPuzzle.at(1) >> customPuzzle.at(2); cout;
        cout << "Second line: "; cin >> customPuzzle.at(3) >> customPuzzle.at(4) >> customPuzzle.at(5); cout;
        cout << "Third line:  "; cin >> customPuzzle.at(6) >> customPuzzle.at(7) >> customPuzzle.at(8); cout;
        
        initialState.pos = customPuzzle;
    }
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
int MisplacedTileHeuristic(vector<int> currState){
    //SImply counting how many numbers are out of place
    int count = 0;
    for(int i = 0; i <= 7; i++){
        if (currState.at(i) != i + 1){
            count++;
        }
    }
    return count;
}
int ManhattanHeuristic(vector<int> currState){
    //Counting distance of each tile from goal state
    vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};
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

//Test to check if puzzle is solved
bool GoalTest(Node& node){
    vector<int> goalState = {1,2,3,4,5,6,7,8,0};
    if(node.pos == goalState)
        return true;
    else
        return false;
}

// Adds all possible moves to queue
void Expand(queue<Node>& nodes, Node& node, int searchType){

    //Find index of 0 (empty space)
    int index = -1;
    for(int i = 0; i < node.pos.size(); i++){
        if (node.pos.at(i) == 0){
            index = i;
        }
    }

    // Adding all possible moves to queue of nodes
    // Including heuristic calculations here while creating new nodes
    // Up operator
    if(index/3 != 0){
        vector<int> gameState = node.pos;
        int temp = gameState.at(index-3);
        gameState.at(index-3) = gameState.at(index);
        gameState.at(index) = temp;
        //Creating new node based on type of heuristic
        int h;
        if (searchType == 1)
            h = 0;
        else if (searchType == 2)
            h = MisplacedTileHeuristic(gameState);
        else if (searchType == 3)
            h = ManhattanHeuristic(gameState);

        Node newNode(gameState, node.g + 1 , h);
        nodes.push(newNode);
    }
    //Down operator
    if(index/3 != 2){
        vector<int> gameState = node.pos;
        int temp = gameState.at(index+3);
        gameState.at(index+3) = gameState.at(index);
        gameState.at(index) = temp;
        //Creating new node based on type of heuristic
        int h;
        if (searchType == 1)
            h = 0;
        else if (searchType == 2)
            h = MisplacedTileHeuristic(gameState);
        else if (searchType == 3)
            h = ManhattanHeuristic(gameState);

        Node newNode(gameState, node.g + 1 , h);
        nodes.push(newNode);
    }
    //Left operator
    if(index%3 != 0){
        vector<int> gameState = node.pos;
        int temp = gameState.at(index-1);
        gameState.at(index-1) = gameState.at(index);
        gameState.at(index) = temp;
        //Creating new node based on type of heuristic
        int h;
        if (searchType == 1)
            h = 0;
        else if (searchType == 2)
            h = MisplacedTileHeuristic(gameState);
        else if (searchType == 3)
            h = ManhattanHeuristic(gameState);

        Node newNode(gameState, node.g + 1 , h);
        nodes.push(newNode);
    }
    //Right operator
    if(index%3 != 2){
        vector<int> gameState = node.pos;
        int temp = gameState.at(index+1);
        gameState.at(index+1) = gameState.at(index);
        gameState.at(index) = temp;
        //Creating new node based on type of heuristic
        int h;
        if (searchType == 1)
            h = 0;
        else if (searchType == 2)
            h = MisplacedTileHeuristic(gameState);
        else if (searchType == 3)
            h = ManhattanHeuristic(gameState);

        Node newNode(gameState, node.g + 1 , h);
        nodes.push(newNode);
    }
}

//Driver function for search
Node SearchAlgorithm(Node& initialState, int searchType){
    // 1: Uniform Cost, 2: Misplaced Tile, 3: Manhattan
    
    // Start queue and insert initial state of puzzle
    queue<Node> nodes;
    nodes.push(initialState);
    cout << "Starting position: " << endl;
    Puzzle_Output(initialState.pos);
    cout << endl;

    bool timeOut = false;
    int count = 0;
    Node node;
    while(!timeOut){
        // No solution if the queue is empty
        if(nodes.empty()){
            cout << "No solution found. " << endl;
        }
        node = nodes.front();
        nodes.pop();

        if(GoalTest(node)){
            cout << "Goal State!" << endl;
            cout <<"Nodes Expanded: "<< count << endl;
            return node;
        }

        Expand(nodes, node, searchType);
        Queuing_Function(nodes);
        
        cout << "The move with the smallest f(n) is: " << endl;
        Puzzle_Output(nodes.front().pos);
        cout << "It has g(n) = " << nodes.front().g << " and h(n) = " << nodes.front().h << endl << endl;

        count++;
        if(count > 999)
            timeOut = true;
    }
    return nodes.front();
}

int main() {

    Node initialState = SelectPuzzle();

    cout << "Would you like to use: " << endl;
    cout << "1. Uniform Cost search" << endl;
    cout << "2. A* search with Misplaced Tile Heuristic" << endl;
    cout << "3. A* search with Manhattan Heuristic" << endl;
    int searchType;
    cin >> searchType;
    cout << endl << endl;

    Node finalNode = SearchAlgorithm(initialState, searchType);
    cout << "Depth: " << finalNode.g << endl;
    return 0;
}