#include<bits/stdc++.h> 
#include"edgeCases1.h"
using namespace std; 

// A Utility Function to check whether destination cell has 
// been reached or not 
bool isDestination(int row, int col,pair<int, int> dest) 
{ 
	if (row == dest.first && col == dest.second) 
		return (true); 
	else
		return (false); 
} 

// A Utility Function to calculate the 'h' heuristics. 
double calculateHValue(int row, int col,pair<int, int> dest) 
{ 
	// Return using the distance formula 
	return ((double)sqrt ((row-dest.first)*(row-dest.first) 
						+ (col-dest.second)*(col-dest.second))); 
} 


void checkSuccessorDiagonal(int grid[ROW][COL],cell cellDetails[ROW][COL],bool closedList[ROW][COL],set<pair<double, pair<int, int>>>& openList,int i,int j,pair<int,int>& loc,double& fNew,double& gNew,double& hNew,pair<int,int>& dest,bool& foundDest){
	if (isValid(i, j) == true) 
	{ 
		// If the destination cell is the same as the 
		// current successor 
		if (isDestination(i, j, dest) == true) 
		{ 
			// Set the Parent of the destination cell 
			cellDetails[i][j].parent_i = loc.first; 
			cellDetails[i][j].parent_j = loc.second;  
			printf ("The destination cell is found\n"); 
			tracePath (cellDetails, dest); 
			foundDest = true; 
			return; 
		} 
		// If the successor is already on the closed 
		// list or if it is blocked, then ignore it. 
		// Else do the following 
		else if (closedList[i][j] == false && 
				isUnBlocked(grid, i, j) == true) 
		{ 
			gNew = cellDetails[i][j].g + 1.414; 
			hNew = calculateHValue (i, j, dest); 
			fNew = gNew + hNew; 

			// If it isn’t on the open list, add it to 
			// the open list. Make the current square 
			// the parent of this square. Record the 
			// f, g, and h costs of the square cell 
			//			 OR 
			// If it is on the open list already, check 
			// to see if this path to that square is better, 
			// using 'f' cost as the measure. 
			if (cellDetails[i][j].f == FLT_MAX || 
					cellDetails[i][j].f > fNew) 
			{ 
				openList.insert(make_pair(fNew,make_pair(i, j))); 

				// Update the details of this cell 
				cellDetails[i][j].f = fNew; 
				cellDetails[i][j].g = gNew; 
				cellDetails[i][j].h = hNew; 
				cellDetails[i][j].parent_i = loc.first; 
				cellDetails[i][j].parent_j = loc.second;  
			} 
		} 
	}
}