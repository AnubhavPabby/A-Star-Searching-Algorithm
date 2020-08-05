// A C++ Program to implement A* Search Algorithm 
#include<bits/stdc++.h>
#include"edgeCases2.h"
using namespace std;

void checkSuccessor(int grid[ROW][COL],cell cellDetails[ROW][COL],bool closedList[ROW][COL],set<pair<double, pair<int, int>>>& openList,int i,int j,pair<int, int>& loc,double& fNew,double& gNew,double& hNew,pair<int,int>& dest,bool& foundDest){
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
			gNew = cellDetails[i][j].g + 1.0; 
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

// A Function to find the shortest path between 
// a given source cell to a destination cell according 
// to A* Search Algorithm 
void aStarSearch(int grid[][COL],pair<int, int> src,pair<int, int> dest) 
{ 
	// If the source is out of range 
	if (isValid (src.first, src.second) == false) 
	{ 
		printf ("Source is invalid\n"); 
		return; 
	} 

	// If the destination is out of range 
	if (isValid (dest.first, dest.second) == false) 
	{ 
		printf ("Destination is invalid\n"); 
		return; 
	} 

	// Either the source or the destination is blocked 
	if (isUnBlocked(grid, src.first, src.second) == false || 
			isUnBlocked(grid, dest.first, dest.second) == false) 
	{ 
		printf ("Source or the destination is blocked\n"); 
		return; 
	} 

	// If the destination cell is the same as source cell 
	if (isDestination(src.first, src.second, dest) == true) 
	{ 
		printf ("We are already at the destination\n"); 
		return; 
	} 

	// Create a closed list and initialise it to false which means 
	// that no cell has been included yet 
	// This closed list is implemented as a boolean 2D array 
	bool closedList[ROW][COL]; 
	memset(closedList, false, sizeof (closedList)); 

	// Declare a 2D array of structure to hold the details 
	//of that cell 
	cell cellDetails[ROW][COL]; 

	int i, j; 

	for (i=0; i<ROW; i++) 
	{ 
		for (j=0; j<COL; j++) 
		{ 
			cellDetails[i][j].f = FLT_MAX; 
			cellDetails[i][j].g = FLT_MAX; 
			cellDetails[i][j].h = FLT_MAX; 
			cellDetails[i][j].parent_i = -1; 
			cellDetails[i][j].parent_j = -1; 
		} 
	} 

	// Initialising the parameters of the starting node 
	i = src.first, j = src.second; 
	cellDetails[i][j].f = 0.0; 
	cellDetails[i][j].g = 0.0; 
	cellDetails[i][j].h = 0.0; 
	cellDetails[i][j].parent_i = i; 
	cellDetails[i][j].parent_j = j; 

	/* 
	Create an open list having information as- 
	<f, <i, j>> 
	where f = g + h, 
	and i, j are the row and column index of that cell 
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	This open list is implenented as a set of pair of pair.*/
	set<pair<double, pair<int, int>>> openList; 

	// Put the starting cell on the open list and set its 
	// 'f' as 0 
	openList.insert(make_pair (0.0, make_pair (i, j))); 

	// We set this boolean value as false as initially 
	// the destination is not reached. 
	bool foundDest = false; 

	while (!openList.empty()) 
	{ 
		pair<double, pair<int, int>> p = *openList.begin(); 

		// Remove this vertex from the open list 
		openList.erase(openList.begin()); 

		// Add this vertex to the closed list 
		i = p.second.first; 
		j = p.second.second; 
		pair<int,int> loc = make_pair(i,j);
		closedList[i][j] = true; 

		// To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew; 

		//----------- 1st Successor (North) ------------
		if(foundDest == false) 
			checkSuccessor(grid,cellDetails,closedList,openList,i-1,j,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 2nd Successor (South) ------------
		if(foundDest == false)
			checkSuccessor(grid,cellDetails,closedList,openList,i+1,j,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 3rd Successor (East) ------------
		if(foundDest == false)
			checkSuccessor(grid,cellDetails,closedList,openList,i,j+1,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 4th Successor (West) ------------
		if(foundDest == false)
			checkSuccessor(grid,cellDetails,closedList,openList,i,j-1,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 5th Successor (North-East) ------------
		if(foundDest == false)
			checkSuccessorDiagonal(grid,cellDetails,closedList,openList,i-1,j+1,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 6th Successor (North-West) ------------
		if(foundDest == false)
			checkSuccessorDiagonal(grid,cellDetails,closedList,openList,i-1,j-1,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 7th Successor (South-East) ------------
		if(foundDest == false)
			checkSuccessorDiagonal(grid,cellDetails,closedList,openList,i+1,j+1,loc,fNew,gNew,hNew,dest,foundDest);
		//----------- 8th Successor (South-West) ------------
		if(foundDest == false)
			checkSuccessorDiagonal(grid,cellDetails,closedList,openList,i+1,j-1,loc,fNew,gNew,hNew,dest,foundDest);
	}


	// When the destination cell is not found and the open 
	// list is empty, then we conclude that we failed to 
	// reach the destiantion cell. This may happen when the 
	// there is no way to destination cell (due to blockages) 
	if (foundDest == false) 
		printf("Failed to find the Destination Cell\n"); 

	return; 
} 


// Driver program to test above function 
int main() 
{ 
	/* Description of the Grid- 
	1--> The cell is not blocked 
	0--> The cell is blocked */
	int grid[ROW][COL] = 
	{ 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
	}; 
    
    cout << "Enter details for Source Coordinates" << endl;
    int srcRow,srcColumn;
    cout << "Enter x-coordinate for Source" << endl;
    cin >> srcRow;
    cout << "Enter y-coordinate for Source" << endl;
    cin >> srcColumn;
    
    cout << "Enter details for Destination Coordinates" << endl;
    int destRow,destColumn;
    cout << "Enter x-coordinate for Destination" << endl;
    cin >> destRow;
    cout << "Enter y-coordinate for Destination" << endl;
    cin >> destColumn;
    
	// Source is the left-most bottom-most corner 
	pair<int,int> src = make_pair(srcRow, srcColumn); 

	// Destination is the left-most top-most corner 
	pair<int,int> dest = make_pair(destRow, destColumn); 

	aStarSearch(grid, src, dest); 

	return(0); 
}

