#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

int main() {
    cout << "Welcome to my 8-Puzzle Solver. Type \'1\' to use a default puzzle, or \'2\' to create your own." << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "You chose to use a default puzzle." << endl;
    } else if (choice == 2) {
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. Enter the puzzle demilimiting the numbers with a space. Type RETURN only when finished." << endl;
    } else {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    vector<vector<int>> puzzle(3, vector<int>(3));

    if(choice == 2) {
        cout << "\n Enter the first row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[0][i];
        }
        cout << "\n Enter the second row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[1][i];
        }
        cout << "\n Enter the third row: ";
        for(int i = 0; i < 3; ++i) {
            cin >> puzzle[2][i];
        }
    }

    cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) for the Manhattan Distance Heuristic." << endl;
    
    int alg;
    cin >> alg;


    return 0;
}

// general search algorithm

// misplaced tile heuristic
int misplacedTile(vector<vector<int>> puzzle) {
    int misplaced = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; j++) {
            if(puzzle[i][j] != goalState[i][j]) {
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
            for(int k = 0; k < 3; ++k) {    // horizontal of goal state
                for(int l = 0; l < 3; ++l) {    // vertical of goal state
                    if(val == goalState[k][l]) {
                        distance += abs(i - k) + abs(j - l);
                    }
                }
            }
        }
    }

    return distance;
}