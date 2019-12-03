// include guards
#include <iostream>
#include <stdio.h>
#include <string>

// include all header files 
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "View.h"
#include "Model.h" 
#include "GameCommand.h"

 class GameObject;


int main()
{
	Model mod; 
	mod.ShowStatus(); 
	//mod.Plot(); 

	View vi = View(); 

	int pokemon_id; 
	int x; 
	int y; 
	Model* modelPtr = &mod; 
	int gym_id; 
	int center_id; 
	unsigned int training_units;
	unsigned int stamina_points;  

	char command; 
	cout << "Enter command: " << endl; 
	cin >> command; 

	// run program in loop until quit command is given 
	while (command != 'q')
{

		// switch statment for commands
			// executes and calls functions depending on which command is given
		switch (command)
{
	case 'm': // move command
	{
		cout << "Enter pokemon ID, x and y coordinates: " << endl; 
		cin >> pokemon_id; 
		cin >> x; 
		cin >>  y ; 
		cout << "move" << endl; 
		DoMoveCommand(*modelPtr, pokemon_id, Point2D(x,y));
		break; 
	}

	case 'g': // move to gym command
	{
		cout << "Enter pokemon ID, gym ID" << endl; 
		cin >> pokemon_id ; 
		cin >>  gym_id ; 
		cout << "Move towards a Pokemon Gym" << endl;  
		DoMoveToGymCommand(*modelPtr, pokemon_id, gym_id); 
		break; 
	}

	case 'c': // move to center command
	{
		cout << "Enter pokemon ID, center ID" << endl; 
		cin >> pokemon_id ; 
		cin >> center_id ; 
		cout << "Move towards a Pokemon Center" << endl; 
		DoMoveToCenterCommand(*modelPtr, pokemon_id, center_id);
		break; 
	}

	case 's': // stop command
	{
		cout << "Enter pokemon ID" << endl; 
		cin >> pokemon_id ; 
		cout << "stop" << endl; 
		DoStopCommand(*modelPtr, pokemon_id);
		break; 
	}

	case 'r': // stamina amount
	{
		cin >> pokemon_id ; 
		cin >>  stamina_points;  
		cout << "recover at a Pokemon Center" << endl; 
		DoRecoverInCenterCommand(*modelPtr, pokemon_id, stamina_points); 
	}

	case 't': // unit amount
	{
		cin >> pokemon_id ; 
		cin >> training_units;  
		cout << "complete " << training_units << " training units at a Pokemon Gym" << endl; 
		DoTrainInGymCommand(*modelPtr, pokemon_id, training_units);
		break; 
	}

	case 'v': // go command
	{
		cout << "go" << endl; 
		//DoGoCommand(*modelPtr, *viewPtr);
		break; 
	}

	case 'x': // run command
	{
		cout << "run" << endl; 
		//DoRunCommand(*modelPtr, *viewPtr); // repeats loop 
		break; 
	} 


	} // ends switch statement  

} // ends while loop

	if (command == 'q') 
	{
		cout << "quit." << endl; 
	}
	cout << "Ending program" << endl;
	//View -> ~View(); // deconstructs view 
	//Model -> ~Model(); // deconstructs model 


	return 0; 
} // ends main function 

