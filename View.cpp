// include guards 

#include <iostream>
#include "View.h" 

using namespace std; 

// default constructor
View::View() 
{
	size = 11; 
	scale = 2; 
	origin = Point2D(0,0); 
}

// destructor 
View::~View()
{
	cout << "View destructed." << endl; 
}

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location) 
{
	// follow formula, set out_x and out_y to values accessed by location and origin 
		// serves as subscripts 
	out_x = (location.x - origin.x)/scale; // dot into location
	out_y = (location.y - origin.y) / scale; // dot into location
	if (out_x > view_maxsize || out_y > view_maxsize) // outside bounds of display
	{
		cout << "An object is outside the display" << endl; 
		return false; 
	} else {
		// return x and y subscripts 
			// already stored in out_x and out_y as true statement
		return true; 
	}
}

void View::Clear()
{
	// sets all cells of the grid to the background pattern shown 
	for (int i = 0; i < view_maxsize; i++)
	{
		for (int j = 0; j < view_maxsize; j++) // j loop to iterate through both dimensions of array 
		{
			grid[i][j][0] = '.'; 
			grid [i][j][1] = ' '; 
		} // exit j loop 
	} // exit i loop 
}

void View::Plot(GameObject* ptr)
{
	int out_x = 0;
	int out_y = 0;
	if (GetSubscripts(out_x, out_y, ptr -> GetLocation()))
	{
		ptr -> DrawSelf(grid[out_x][out_y]); 
	}
}

void View::Draw()
{
	// create arrays for outputs from x and y axis 
	int array[view_maxsize/2 + 1]; 

	// case 1: initializes x and y axis
	for (int i = 0; i < view_maxsize/2; i++)
	{
		array[i] = 2*i; 
	}

	array[view_maxsize/2] = view_maxsize; // new array setting 

	// case 2: prints y as blanks or from array (every other)
	for (int i = size -1 ; i >= 0; i--) // decrementing 
	{
		if (i%2 == 0) // every other line 
		{
			cout << array[i]; 
			if (array[i] < 10) // size - 1
			{
				cout << " " ; 
			} // exit nested if 
		} else {
			cout << " "; 
		} // exit if statement

	// print object grid 
	for (int j = 0; i < size; j++) // j loop 
	{
		cout << grid[j][i][0]; // array of objects pt 1
		cout << grid[j][i][1]; // array of objects pt 2 
	}
	cout << endl; 
	} // exit for loop 2 

cout << " " ; // spaces 

	// output for x axis 
	for (int k = 0; k <= size; k++) 
	{
		if (k%2 == 0) // every other line
		{
			cout << array[k];
			if (array[k] < 10)
			{
				cout << " " ; 
			}
		} else {
			cout << " " ; 
		}
	}
	cout << endl; 

}
