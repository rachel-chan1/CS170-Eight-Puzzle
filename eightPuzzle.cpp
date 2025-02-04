#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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
        for(int i = 0; i < 3; i++) {
            cin >> puzzle[0][i];
        }
        cout << "\n Enter the second row: ";
        for(int i = 0; i < 3; i++) {
            cin >> puzzle[1][i];
        }
        cout << "\n Enter the third row: ";
        for(int i = 0; i < 3; i++) {
            cin >> puzzle[2][i];
        }
    }

    cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) the Manhattan Distance Heuristic." << endl;

    int alg;
    cin >> alg;


    return 0;
}

// general search algorithm
