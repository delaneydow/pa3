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

		// create objects using new, store pointers to them in arrays 
	this -> center_ptrs = new PokemonCenter*[2]; 
	this -> gym_ptrs = new PokemonGym*[2]; 
	this -> pokemon_ptrs = new Pokemon*[2];
	this -> object_ptrs = new GameObject*[6]; 

	// setting object type, id number, initial location to another array 
	// assigns to game object pointer array as well after declaring new space on heap
		// Pokemon 1
	this -> pokemon_ptrs[0] = new Pokemon(1, Point2D(5,1)); 
	this -> object_ptrs[0] = pokemon_ptrs[0]; 
		// Pokemon 2
	this -> pokemon_ptrs[1] = new Pokemon(2, Point2D(10,1)); 
	this -> object_ptrs[1] = pokemon_ptrs[1]; 
		// PokemonCenter 1 
	this -> center_ptrs[0] = new PokemonCenter(1, Point2D(1, 20)); 
	this -> object_ptrs[2] = center_ptrs[0]; 
		// PokemonCenter 2 
	this -> center_ptrs[1] = new PokemonCenter(2, Point2D(10,20)); 
	this -> object_ptrs[3] = center_ptrs[1]; 
		// PokemonGym1
			// default constructed 
	this -> gym_ptrs[0] = new PokemonGym(); // default constructor 
	this -> object_ptrs[4] = gym_ptrs[0]; 
	this -> gym_ptrs[1] = new PokemonGym(2, Point2D(5,5)); 
	this -> object_ptrs[5] = gym_ptrs[1]; 

 
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
		if (pokemon_ptrs[i] -> getId() == id_num)
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
		if (center_ptrs[i] -> getId() == id_num)
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
		view.plot(object_ptrs[i]); // calls plot function
			// generates view display for all of the GameObjects
	} // exits for loop
	view.DrawSelf(); // access DrawSelf function from view 

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







