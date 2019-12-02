// include guards 

#include <iostream> 
#include "Model.h" 

using namespace std; 


// constructors 

	//default constructor 
Model::Model()
{
	time = 0; 

	// sets nums equal to number of pointers initialized, correct num of objects
	num_objects = 6; 
	num_pokemon = 2; 
	num_centers = 2; 
	num_gyms = 2;

	// create pointers to Point2D vectors
	// create array of certain types to assign into array 
	Point2D point1 = Point2D(5,1); 
		Pokemon* ptrArray1 = new Pokemon(1, point1); 
		object_ptrs[0] = ptrArray1; 

	Point2D point2 = Point2D(10,1); 
		Pokemon* ptrArray2 = new Pokemon(2, point2); 
		object_ptrs[1] = ptrArray2; 

	Point2D point3 = Point2D(1,20); 
		PokemonCenter* ptrArray3 = new PokemonCenter(1, point3); 
		object_ptrs[2] = ptrArray3; 

	Point2D point4 = Point2D(10,20); 
		PokemonCenter* ptrArray4 = new PokemonCenter(2, point4); 
	 	object_ptrs[3] = ptrArray4;

		PokemonGym* ptrArray5 = new PokemonGym(); 
		object_ptrs[4] = ptrArray5; 

	Point2D point5 = Point2D(5,5);
		PokemonGym* ptrArray6 = new PokemonGym(2, point5); 
		object_ptrs[5] = ptrArray6; 

	cout << "Model default constructed" << endl; 
}

	// destructor
		// must also create destructors for GameObject, Pokemon, PokemonCenter, and PokemonGym
Model::~Model()
{
	for (int i = 0; i < 10; i++) // loop through array to delete pointers
	{
		delete object_ptrs[i]; // frees memory from heap to destruct pointer array 
	}
	cout << "Model destructed" << endl; 
}

// member functions 

Pokemon* Model::GetPokemonPtr(int id)
{
	for (int i = 0; i < num_pokemon; i++)
	{
		if (pokemon_ptrs[i] -> GetId() == id_num)
		{
			return pokemon_ptrs[i]; 
		}
	}
	return NULL; 
}

PokemonCenter* Model::GetPokemonCenterPtr(int id) 
{
	for (int i = 0; i < num_pokemon; i++) 
	{
		if (center_ptrs[i] -> GetId() == id_num)
		{
			return center_ptrs[i]; 
		}
	}
	return NULL; 
}

bool Model::Update()
/* provides service to main program: 
	increments time, iterates through object_ptrs array, 
	calls Update() for each object. Must update if game is over, 
	or if game has been won based on specific conditions */ 
{
	int count = 0; // track amount of objects updates
	bool output; 

	time += 1; // update time 
	for (int i = 0; i < num_objects; i++)
	{
		output= object_ptrs[i] -> Update(); // updates objects since virtual, access all objects, do not need to go into other arrays 
		if (output == true) 
		{
			count += 1; 
		}
	} // exit for loop 

	if (count > 0) // nonzero count, objects have been updated
	{
		return true; 
	} else {
		return false; 
	} // exit if statment

		
} // exit update function 



void Model::Display(View& view)
{
	cout << "Time: " << time << endl; 
	view.Clear(); // calls clear function to clear view
	for (int i = 0; i < num_objects; i++) 
	{
		view.Plot(object_ptrs[i]); // calls plot function
			// generates view display for all of the GameObjects
	} // exits for loop
	view.Draw(); // access DrawSelf function from view 

} // exit display function 

void Model::ShowStatus()
{
	for (int i = 0; i < num_objects; i++)
	{
		object_ptrs[i] ->ShowStatus(); 
	} // exit for loop
} // exit show status function 

Model:: Model(const Model &other)
{
	// empty copy constructor 
}







