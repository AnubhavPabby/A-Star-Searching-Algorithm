#include<bits/stdc++.h> 
using namespace std; 

#define ROW 9 
#define COL 10

// A structure to hold the neccesary parameters 
struct cell 
{ 
	// Row and Column index of its parent 
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i, parent_j; 
	// f = g + h 
	double f, g, h; 
}; 

bool isValid(int row, int col) 
{ 
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < ROW) && 
		(col >= 0) && (col < COL); 
} 

// A Utility Function to check whether the given cell is 
// blocked or not 
bool isUnBlocked(int grid[][COL], int row, int col) 
{ 
	// Returns true if the cell is not blocked  
	if (grid[row][col] == 1) 
	{
		return (true); 
	}
	// Returns False if the cell is not blocked
	else
	{

		return (false); 
	}

}

// A Utility Function to trace the path from the source 
// to destination 
void tracePath(cell cellDetails[][COL],pair<int, int> dest) 
{ 
	printf ("\nThe Path is "); 
	int row = dest.first; 
	int col = dest.second; 

	// Making Stack for storing row and column variables
	stack<pair<int, int>> Path; 

	while (!(cellDetails[row][col].parent_i == row 
			&& cellDetails[row][col].parent_j == col )) 
	{ 
		Path.push (make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i; 
		int temp_col = cellDetails[row][col].parent_j; 
		row = temp_row; 
		col = temp_col; 
	} 

	Path.push (make_pair (row, col));

	// Running While loop if the stack is not empty 
	while (!Path.empty()) 
	{ 
		pair<int,int> p = Path.top(); 
		Path.pop(); 
		printf("-> (%d,%d) ",p.first,p.second); 
	} 

	return; 
} 