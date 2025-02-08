#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

struct Puzzle {
    vector<vector<int>> board;
    pair<int,int> emptyIndex;
    int depth = 0;
    int heuristicCost = -1;
    const Puzzle* parent;
};

struct ComparePuzzle {
    bool operator()(const Puzzle& p1, const Puzzle& p2) {
        return (p1.depth + p1.heuristicCost) > (p2.depth + p2.heuristicCost);
    }
};

vector<vector<int>> goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
vector<vector<int>> depth0 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
vector<vector<int>> depth2 = {{1, 2, 3}, {4, 5, 6}, {0, 7, 8}};
vector<vector<int>> depth4 = {{1, 2, 3}, {5, 0, 6}, {4, 7, 8}};
vector<vector<int>> depth8 = {{1, 3, 6}, {5, 0, 2}, {4, 7, 8}};
vector<vector<int>> depth12 = {{1, 3, 6}, {5, 0, 7}, {4, 8, 2}};
vector<vector<int>> depth16 = {{1, 6, 7}, {5, 0, 3}, {4, 8, 2}};
vector<vector<int>> depth20 = {{7, 1, 2}, {4, 8, 5}, {6, 3, 0}};
vector<vector<int>> depth24 = {{0, 7, 2}, {4, 6, 1}, {3, 5, 8}};

void generalSearch(vector<vector<int>>, int alg) ;
int misplacedTile(vector<vector<int>> puzzle);
int manhattanDistance(vector<vector<int>> puzzle);
pair<int,int> findEmptySpace(vector<vector<int>> puzzle);
vector<Puzzle> expand(const Puzzle* p, vector<Puzzle> visited);
void printPuzzle(vector<vector<int>> puzzle);

int main() {
    cout << "Welcome to my 8-Puzzle Solver. Type \'1\' to use a default puzzle, or \'2\' to create your own." << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "You chose to use a default puzzle." << endl;
    } else if (choice == 2) {
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. Enter the puzzle delimiting the numbers with a space. Type RETURN only when finished." << endl;
    } else {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    vector<vector<int>> puzzle(3, vector<int>(3));
    if(choice == 1) {
        generalSearch(depth24, 3);
        return 0;
    }

    if(choice == 2) {
        cout << "\nEnter the first row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[0][i];
        }
        cout << "\nEnter the second row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[1][i];
        }
        cout << "\nEnter the third row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[2][i];
        }
    }

    cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) for the Manhattan Distance Heuristic." << endl;
    
    int alg;
    cin >> alg;

    if(alg == 1) {
        cout << "You chose Uniform Cost Search." << endl;
        generalSearch(puzzle, alg);
    }
    else if(alg == 2) {
        cout << "You chose the Misplaced Tile Heuristic." << endl;
        generalSearch(puzzle, alg);
    }
    else if(alg == 3) {
        cout << "You chose the Manhattan Distance Heuristic." << endl;
        generalSearch(puzzle, alg);
    }
    else {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }


    return 0;
}

// general search algorithm
void generalSearch(vector<vector<int>> puzzleBoard, int alg) {
    int heuristic = -1;
    if(alg == 1) {
        heuristic = 0;
    }
    else if(alg == 2) {
        heuristic = misplacedTile(puzzleBoard);
    }
    else if(alg == 3) {
        heuristic = manhattanDistance(puzzleBoard);
    }

    priority_queue<Puzzle, vector<Puzzle>, ComparePuzzle> nodes;
    Puzzle *newPuzzle = new Puzzle;
    newPuzzle->board = puzzleBoard;
    newPuzzle->emptyIndex = findEmptySpace(puzzleBoard);
    newPuzzle->heuristicCost = heuristic;

    nodes.push(*newPuzzle);

    int nodesVisited = 0;
    int maxQueueSize = -1;
    vector<Puzzle> visited;

    visited.push_back(*newPuzzle);

    while(true) {
        if(nodes.empty()) {
            cout << "Failure" << endl;
            return;
        }

        Puzzle current = nodes.top();
        nodes.pop();

        if(current.board == goalState) {
            cout << "Goal state!" << endl << endl;
            cout << "Solution depth was " << current.depth << endl;
            cout << "Number of nodes expanded: " << nodesVisited << endl;
            cout << "Max queue size: " << maxQueueSize << endl;
            return;
        }

        nodesVisited++;

        cout << "The best state to expand with a g(n) = " << current.depth << " and h(n) = " << current.heuristicCost << " is..." << endl;
        printPuzzle(current.board);

        vector<Puzzle> children = expand(&current, visited);
        
        for(int i = 0; i < children.size(); ++i) {
            if(alg == 1) {
                children[i].heuristicCost = 0;
            }
            else if(alg == 2) {
                children[i].heuristicCost = misplacedTile(children[i].board);
            }
            else if(alg == 3) {
                children[i].heuristicCost = manhattanDistance(children[i].board);
            }
            nodes.push(children[i]);
            visited.push_back(children[i]);
        }
        maxQueueSize = max(maxQueueSize, (int)nodes.size());
    }
}

// misplaced tile heuristic
int misplacedTile(vector<vector<int>> puzzle) {
    int misplaced = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; j++) {
            if(puzzle[i][j] != goalState[i][j] && puzzle[i][j] != 0) {
                misplaced++;
            }
        }
    }
    return misplaced;
}

// manhattan distance heuristic
int manhattanDistance(vector<vector<int>> puzzle) {
    int distance = 0;
    for(int i = 0; i < 3; ++i) {    // horizontal of puzzle
        for(int j = 0; j < 3; ++j) {    // vertical of puzzle
            int val = puzzle[i][j];
            if(val != 0) {
                for(int k = 0; k < 3; ++k) {    // horizontal of goal state
                    for(int l = 0; l < 3; ++l) {    // vertical of goal state
                        if(val == goalState[k][l]) {
                            distance += abs(i - k) + abs(j - l);
                        }
                    }
                }
            }
        }
    }

    return distance;
}

pair<int,int> findEmptySpace(vector<vector<int>> puzzle) {
    int r = -1, c = -1;  // row and column of empty space
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(puzzle[i][j] == 0) {
                r = i;
                c = j;
                break;
            }
        }
        if(r != -1) {   // break out of outer loop when empty space is found
            break;
        }
    }
    return {r, c};
}

// generate children
vector<Puzzle> expand(const Puzzle* p, vector<Puzzle> visited) {
    vector<Puzzle> children;

    int r = p->emptyIndex.first;
    int c = p->emptyIndex.second;

    // move empty spce to the left
    if(c > 0) {
        Puzzle* child = new Puzzle;
        child->board = p->board;
        swap(child->board[r][c], child->board[r][c-1]);
        child->emptyIndex = {r, c -1};
        child->depth = p->depth + 1;
        child->parent = p;
        children.push_back(*child);
    }

    // move empty space to the right
    if(c < 2) {
        Puzzle* child = new Puzzle;
        child->board = p->board;
        swap(child->board[r][c], child->board[r][c+1]);
        child->emptyIndex = {r, c + 1};
        child->depth = p->depth + 1;
        child->parent = p;
        children.push_back(*child);
    }

    // move empty space up
    if(r > 0) {
        Puzzle* child = new Puzzle;
        child->board = p->board;
        swap(child->board[r][c], child->board[r-1][c]);
        child->emptyIndex = {r - 1, c};
        child->depth = p->depth + 1;
        child->parent = p;
        children.push_back(*child);
    }

    // move empty space down
    if(r < 2) {
        Puzzle* child = new Puzzle;
        child->board = p->board;
        swap(child->board[r][c], child->board[r+1][c]);
        child->emptyIndex = {r + 1, c};
        child->depth = p->depth + 1;
        child->parent = p;
        children.push_back(*child);
    }

    for(int i = 0; i < children.size(); ++i) {
        for(int j = 0; j < visited.size(); ++j) {
            if(children[i].board == visited[j].board) {
                children.erase(children.begin() + i);
                i--;
                break;
            }
        }
    }

    return children;
}

void printPuzzle(vector<vector<int>> puzzle) {
    for(int i = 0; i < 3; ++i) {
        cout << "[ ";
        for(int j = 0; j < 3; ++j) {
            cout << puzzle[i][j] << ", ";
        }
        cout << ']' << endl;
    }
    cout << endl;
}