Using the provided code that can be downloaded from this github add a new class that inherits from game.cpp in the same way TicTacToe.cpp does and implement a working version of the game Connect 4. The game should be added as a fourth choice from the menu so the choices are Tic Tac Toe, Checkers, Othello and now Connect 4.

The game must be playable by both by 2 people and vs. an AI. Your implementation must check for the winning condition, and display that on the right hand side the same way the current setup does for tic-tac-toe. The stopGame() method is expected to clean up and delete any memory allocated.

Look at the new Grid.cpp class and see how it is used in Checkers.cpp for a good understanding about laying out a useable grid.

For extra credit, when a game piece is added to the board, make it animate into place instead of just appearing in it's final spot.

Graphic files are provided for the game pieces called yellow.png and red.png.

For the submission, create a new github based on the above code-base and provide a link to that along with a complete readme.md on how your implementation works.

Name: Jonathan Ng

This connect 4 program foolows a similar implementation as the tictactoe program, using the game class as a parent to it. It uses a 7x6 grid to store all the piece in the game. The main function of the base game is placing the piece. This program checks to see if it can place a piece by finding the column that is selected and starting from the bottom of the column, seeing if any of the rows are empty, when the lowest empty row is found, it then places the piece there. The game checks for a winner by using the functions provided in the grid class, starting form the last placed piece and checking to see if there are any horizontal or vertical rows that connect 4, or any diagonals that connect 4 of the same piece. The AI in this program uses negamax to create a tree of possbile possitions which then the evalutation function, scores those positions based an evaluation table. Alpha beta pruning is use to find branches of the tree in which the negamax algorithm would never selects and removes those branches.