#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Forward declaration
class SudokuSolver;

/**
 * Class representing the Sudoku grid and its data.
 */
class SudokuBoard {
private:
    int grid[9][9]; // 0 represents an empty cell
    string filename;
    int solutionsFoundCount;

public:
    SudokuBoard() : solutionsFoundCount(0) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                grid[i][j] = 0;
            }
        }
    }

    // Load puzzle from file
    bool loadFromFile(const string& fname) {
        filename = fname;
        ifstream file(fname);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << fname << endl;
            return false;
        }

        int r = 0, c = 0;
        string token;
        
        // Read tokens (separated by whitespace)
        while (r < 9 && file >> token) {
            if (token == "_") {
                grid[r][c] = 0;
            } else {
                try {
                    grid[r][c] = stoi(token);
                } catch (...) {
                    cerr << "Error parsing number in file." << endl;
                    return false;
                }
            }
            
            c++;
            if (c == 9) {
                c = 0;
                r++;
            }
        }
        
        file.close();
        return true;
    }

    // Print the current state of the board
    void printGrid() const {
        for (int i = 0; i < 9; ++i) {
            if (i == 3 || i == 6) cout << "+-------+-------+-------+" << endl;
            else if (i == 0) cout << "|-------+-------+-------|" << endl; // Top border
            
            for (int j = 0; j < 9; ++j) {
                if (j == 3 || j == 6) cout << "| ";
                
                if (grid[i][j] != 0) {
                    cout << grid[i][j];
                } else {
                    cout << "_";
                }
                cout << " ";
            }
            cout << "|" << endl;
        }
    }

    // Getters and Setters for the solver to use
    int getCell(int r, int c) const { return grid[r][c]; }
    void setCell(int r, int c, int val) { grid[r][c] = val; }
    
    string getFilename() const { return filename; }
    int getSolutionsCount() const { return solutionsFoundCount; }
    void incrementSolutionsCount() { solutionsFoundCount++; }

    // Check if placing num at (r, c) is valid according to Sudoku rules
    bool isValid(int r, int c, int num) const {
        // Check Row
        for (int x = 0; x < 9; ++x) {
            if (grid[r][x] == num) return false;
        }

        // Check Column
        for (int x = 0; x < 9; ++x) {
            if (grid[x][c] == num) return false;
        }

        // Check 3x3 Box
        int startRow = r - r % 3;
        int startCol = c - c % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }

        return true;
    }
};

/**
 * Class responsible for solving the SudokuBoard using backtracking.
 */
class SudokuSolver {
private:
    SudokuBoard& board; // Reference to the board being solved

public:
    SudokuSolver(SudokuBoard& b) : board(b) {}

    /**
     * Entry point for the solver. Finds all solutions.
     */
    void solve() {
        findSolution(0, 0);
    }

private:
    /**
     * Recursive helper function to fill cells.
     * Returns true if a solution was found (and printed), false otherwise.
     * Note: To print ALL solutions, we don't return immediately upon finding one;
     * we continue the search after printing.
     */
    bool findSolution(int r, int c) {
        // Base Case: If we have passed the last row, we found a valid solution
        if (r == 9) {
            cout << "Solution:" << endl;
            board.printGrid();
            cout << endl;
            return true;
        }

        // Calculate next cell coordinates
        int nextR = r;
        int nextC = c + 1;
        if (nextC == 9) {
            nextR = r + 1;
            nextC = 0;
        }

        // If current cell is already filled, move to next
        if (board.getCell(r, c) != 0) {
            return findSolution(nextR, nextC);
        }

        // Try digits 1-9 in the empty cell
        bool foundAny = false;
        for (int num = 1; num <= 9; ++num) {
            if (board.isValid(r, c, num)) {
                board.setCell(r, c, num); // Make a move
                
                // Recurse to next cell
                if (findSolution(nextR, nextC)) {
                    foundAny = true;
                    board.incrementSolutionsCount();
                    // We do NOT return false here. We want to find ALL solutions.
                    // However, we must backtrack after printing so the loop can try the next number.
                }

                // Backtrack: Remove the digit to try the next possibility
                board.setCell(r, c, 0); 
            }
        }

        return foundAny;
    }
};

int main() {
    // Loop through puzzle files 1 to 5
    for (int i = 1; i <= 5; ++i) {
        string filename = "puzzle" + to_string(i) + ".txt";
        
        cout << "Processing: " << filename << endl;
        cout << "Original Puzzle:" << endl;

        SudokuBoard board;
        if (board.loadFromFile(filename)) {
            board.printGrid();
            
            // Create solver object and solve
            SudokuSolver solver(board);
            solver.solve();
            
            cout << "Solutions found: " << board.getSolutionsCount() << endl;
        } else {
            cout << "Failed to load puzzle." << endl;
        }
        
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
