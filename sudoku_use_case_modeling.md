# UML Use Case Modeling: Sudoku Solver

## a. Identify/Discover a Use Case

**Use Case Name:** Run Sudoku Solver on Five Puzzle Files

**Primary Actor:** Operator (the person running the program)

**Goal:** Solve the five provided Sudoku puzzle files and display all
solutions found or indicate when no solution exists.

The use case was identified from the assignment requirements, which
specify that the program must read five puzzle files, solve each puzzle
using recursive depth-first search with backtracking, and display the
results.

## b. Brief Description of the Use Case

The operator runs the Sudoku Solver Application, which processes five
predefined puzzle files (`puzzle1.txt` through `puzzle5.txt`). For each
file, the system checks whether it can be opened and whether its
contents are properly formatted. It then validates the initial Sudoku
board and attempts to solve it using recursive depth-first search with
backtracking. The system prints the initial puzzle, all solutions found,
or an appropriate error or no-solution message.

## c. Step-by-Step Flow (Outline) of Events

### Main Flow

1.  The operator starts the Sudoku Solver Application.
2.  The system begins processing the five predefined puzzle files.
3.  The system displays the name of the current puzzle file.
4.  The system attempts to open the file.
5.  The system reads the puzzle and checks that it contains 81 valid
    cell values, using digits `1`--`9` and underscores (`_`) for empty
    cells.
6.  The system prints the initial Sudoku puzzle.
7.  The system checks whether the initial board contains duplicate
    digits in any row, column, or 3×3 block.
8.  If the initial board is valid, the system begins solving the puzzle
    using recursive depth-first search with backtracking.
9.  The system finds an empty cell and determines which digits can
    legally occupy it.
10. The system tries each candidate digit and recursively searches for a
    solution.
11. If a candidate leads to a dead end, the system removes that digit
    and tries another candidate.
12. When a complete solution is found, the system prints the solution
    and continues searching for additional solutions.
13. When the search finishes, the system prints the total number of
    solutions or displays `No solution found`.
14. The system repeats the process for the remaining puzzle files.
15. The application finishes after attempting all five files.

### Alternative Flows

-   **File cannot be opened:** The system displays an error message
    indicating that the file could not be opened and proceeds to the
    next file.
-   **Invalid file formatting:** The system reports bad file formatting
    if the file contains invalid characters, fewer than 81 cells, or
    extra non-whitespace data.
-   **Invalid initial board:** If the initial puzzle contains duplicate
    digits in a row, column, or block, the system displays
    `No solution found`.
-   **No solution exists:** If the solver exhausts all candidate
    possibilities without finding a valid solution, the system displays
    `No solution found`.
-   **Multiple solutions exist:** The system prints every solution found
    and reports the total number of solutions.

## d. Detailed Description for the Use Case

**Use Case ID:** UC-01

**Use Case Name:** Run Sudoku Solver

**Primary Actor:** Operator

**System:** Sudoku Solver Application

**Trigger:** The operator starts the application.

**Preconditions:** - The program has been compiled and is ready to
run. - The five puzzle filenames are configured in the application. -
The program expects the puzzle files to be available in its working
directory.

**Postconditions:** - The system has attempted to process all five
puzzle files. - For each file, the system displays the solutions found,
a no-solution message, or an appropriate file error.

### Detailed Flow of Events

1.  The operator starts the Sudoku Solver Application.
2.  The `SudokuApplication` class iterates through the five predefined
    puzzle filenames.
3.  For each file, the system displays its name and attempts to load its
    contents.
4.  If the file cannot be opened, the system displays an error message
    and moves to the next file.
5.  If the file opens successfully, the system checks the input for
    valid characters and the expected number of cell values. If the file
    is improperly formatted, the system reports a formatting error and
    skips that puzzle.
6.  The system prints the initial puzzle and checks its pre-filled
    digits for duplicates in rows, columns, and 3×3 blocks.
7.  If the initial board is invalid, the system displays
    `No solution found`.
8.  If the board is valid, the `SudokuSolver` begins recursive
    depth-first search with backtracking.
9.  The solver identifies an empty cell and uses the `SudokuBoard` class
    to determine the valid candidate digits.
10. The solver places a candidate digit into the empty cell and
    recursively attempts to solve the remaining puzzle.
11. If the candidate leads to a dead end, the solver clears the cell and
    tries the next candidate.
12. When all cells are filled without violating Sudoku constraints, the
    solver prints the completed board as a solution.
13. The solver continues exploring other candidates to find any
    additional solutions.
14. Once all possibilities have been explored, the system prints the
    total number of solutions or displays `No solution found` if no
    solution was found.
15. The application repeats this process until all five puzzle files
    have been attempted, then terminates.

### Classes Involved

  -----------------------------------------------------------------------
  Class                               Responsibility
  ----------------------------------- -----------------------------------
  `SudokuApplication`                 Manages the list of five puzzle
                                      files and starts the processing of
                                      each file.

  `SudokuBoard`                       Loads, stores, validates, and
                                      prints the Sudoku board; finds
                                      empty cells and determines valid
                                      candidates.

  `SudokuSolver`                      Performs recursive depth-first
                                      search and backtracking, counts
                                      solutions, and prints the solutions
                                      found.
  -----------------------------------------------------------------------

**Note:** The implementation checks the total number of cell tokens and
their values, but does not strictly enforce exactly nine values per text
line. The detailed description reflects the implemented behavior rather
than assuming stricter validation.
