// include guards 
#include "Pokemon.h" 
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "GameObject.h"
 
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>  

using namespace std; 

Pokemon::Pokemon() : GameObject('P') 
{
	state = char (STOPPED); 
	speed = 5; // speed changes, everything else default 
	bool is_in_gym = false; 
	bool is_in_center = false; 
	unsigned int stamina = 20; 
	unsigned int experience_points = 0; 
	double pokemon_dollars = 0.0; 
	unsigned int training_units_to_buy = 0; 
	unsigned int stamina_points_to_buy = 0; 
	PokemonCenter* current_center = NULL; 
	PokemonGym* current_gym = NULL; 
	string name; 
	Vector2D delta; 
	Point2D destination; 
	cout << "Pokemon default constructed" << endl; 

}

Pokemon::Pokemon(char in_code) : GameObject('P')  
{
	 
	state = char (STOPPED); 
	speed = 5; 
	bool is_in_gym = false; 
	bool is_in_center = false; 
	unsigned int stamina = 20; 
	unsigned int experience_points = 0; 
	double pokemon_dollars = 0; 
	unsigned int training_units_to_buy = 0; 
	unsigned int stamina_points_to_buy = 0; 
	PokemonCenter* current_center = NULL; 
	PokemonGym* current_gym = NULL; 
	string name; 
	Vector2D delta; 
	Point2D destination; 
	cout << "Pokemon constructed." << endl;
	 
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject::GameObject(in_loc, in_id, 'P')
{
	speed = in_speed; 
	name = in_name; 
	cout << "Pokemon constructed." << endl; 
}

// destructor 
Pokemon:: ~Pokemon()
{
	cout << "Pokemon destructed." << endl; 
}

void Pokemon::SetUpDestination(Point2D dest)
{
	destination = dest; 
	Vector2D vec = destination - location; 
	delta = vec* (speed/GetDistanceBetween(destination, location));  
}


void Pokemon:: StartMoving(Point2D dest) 
{
	if (state == (char) EXHAUSTED) {
		cout << display_code << GetId() <<": I am exhauted. I may move but you cannot see me." << endl; 
	} else if (dest.x == location.x && dest.y == location.y)
	{
		cout << display_code << GetId() << ": I'm already there. See?" << endl; 
	} else {
		SetUpDestination(dest); 
		state = (char) MOVING; 
		cout << display_code << GetId() << ": On my way" << endl; 
	}
}

void Pokemon:: StartMovingToCenter(PokemonCenter* center) 
{
	if (state == (char) EXHAUSTED) 
	{
		cout << display_code << GetId() << ": I am exhausted so I can't move to recover stamina..." << endl; 
	} else if ((location.x == center ->GetLocation().x) and (location.y == center->GetLocation().y)){
		cout << "I am already at the Pokemon Center!" << endl; 
	} else {
		state = (char) MOVING_TO_CENTER; 
		SetupDestination(center->GetLocation()); 
		//output statement 
		cout << display_code << this->GetId()<< ": On my way to Center " << center->GetId() << endl; 
	}

}

void Pokemon:: StartMovingToGym(PokemonGym* gym) 
{
	if (state == (char) EXHAUSTED) 
	{
		cout << display_code << this -> GetId() << ": I am exhauted so I shouldn't be going to the gym..." << endl; 
	} else if ((gym-> GetLocation().x == location.x) and (gym -> GetLocation().y == location.y)) {
		cout << "I am already at the Pokemon Gym!" << endl; 
	} else {
		state = (char) MOVING_TO_GYM;
		SetupDestination(gym -> GetLocation());
		// output statements
		cout << display_code << GetId() << ": On my way to Gym" << gym ->GetId() << endl; 
	} 
	
}


void Pokemon::StartTraining(unsigned int num_training_units) 
{
	//cout << display_code << ": Started to train at Pokemon Gym " << gym_id << " with " << num_training_units << " training units" << endl; 
	if (this -> is_in_gym)  
	{
		cout << this -> display_code << this -> GetId() << ": I am exhausted so no more training for me..." << endl; 
	} else {
		if (this -> current_gym -> IsBeaten()) 
		{
			cout << this -> display_code << this -> GetId() << ": I can only train in Pokemon Gym!" << endl; 
		}// exit nested if 
		else {
			if (this -> IsExhausted()) 
			{
				cout << this -> display_code << this -> GetId() << ": I am exhausted so no more training for me..." << endl; 
			} else if (! this -> current_gym -> IsAbletoTrain(num_training_units, this -> pokemon_dollars, this -> stamina))
			{
				cout << this -> display_code << this -> GetId() << ": Not enough stamin and/or money for training." << endl; 
			} else {
				this -> state = (char) TRAINING_IN_GYM;
				this -> training_units_to_buy = min(this -> current_gym -> GetNumTrainingUnitsRemaining(), num_training_units); 
				//cout << this -> display_code << this -> GetId() << ": Started to train at Pokemon Gym" << this -> current_gym -> GetId() << "with" << this -> num_training_units << "training units" << endl;
			}
		}
	} // exit if
	

}// exit function 

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) 
{
	if (current_center -> CanAffordStaminaPoints(num_stamina_points, pokemon_dollars))
	{
		cout << display_code << this -> GetId() << ": started recovering" << endl; 
	} else {
		cout << display_code << this -> GetId() << ": not enough money to recover stamina" << endl; 
	} // first if statement 

	if (current_center -> HasStaminaPoints()) 
	{
		cout << display_code << this -> GetId() << ": started recovering" << num_stamina_points << " stamina points at Pokemon Center" << current_center -> GetId() << endl; 
	} else {
		cout << display_code << this -> GetId() << ": cannot recover! no stamina points remaining in this Pokemon Center" << endl; 
	} // second if statement 

	if (is_in_center) // bool 
	{
		cout << display_code << this -> GetId() << ": started recovering" << num_stamina_points << "stamina points at Pokemon Center" << current_center -> GetId() << endl;
	} else {
		cout << display_code << this -> GetId() << ": I can only recover stamina at a pokemon center!" << endl; 
	}// third condition

	if (num_stamina_points > current_center -> GetNumStaminaPointsRemaining())
	{
		stamina_points_to_buy = current_center -> GetNumStaminaPointsRemaining(); 
	} else {
		stamina_points_to_buy = num_stamina_points; 
	}

}

void Pokemon:: Stop() 
{
	state = (char) STOPPED; 
	cout << display_code << GetId() << ": Stopping.." << endl; 

}


bool Pokemon:: IsExhausted() 
{
	if (this -> stamina == 0) 
	{
		return true; 
	} else 
		return false; 
}

bool Pokemon:: ShouldBeVisible() 
{
	if (this -> IsExhausted())
	{
		return true;
	} else {
		return false; 
	}
}

void Pokemon:: ShowStatus() 
{
	cout << name << " status: " << endl; 
	GameObject::ShowStatus(); 
	// prints statements depending on specific states 
	switch (state)
	{
		case (char) STOPPED: 
		{
			cout << "stopped" << endl; 
			break; 
		}
		case (char) MOVING: 
		{
			cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl; 
			break; 
		}
		case (char) IN_GYM: 
		{
			cout << " inside Pokemon Gym " << GetLocation() << endl; 
			break; 
		}
		case (char) IN_CENTER: 
		{
			cout << " inside Pokemon Center " << GetLocation() << endl;
			break; 
		}
		case (char) MOVING_TO_GYM: 
		{
			//cout << " heading to Pokemon Gym " << GetLocation() << " at a speed of " speed << " at each step of " << delta << endl; 
			break; 
		}
		case (char) MOVING_TO_CENTER: 
		{
			cout <<" heading to Pokemon Center " << GetLocation() << " at a speed of " << speed << " at each step of " << delta; 
			break; 
		}
		case (char) TRAINING_IN_GYM: 
		{
			cout << " training in Pokemon Gym " << GetLocation() << endl; 
			break; 
		}
		case (char) RECOVERING_STAMINA: 
		{ 
			cout << " recovering stamina in Pokemon Center " << GetLocation() << endl; 
			break; 
		}
	}
}

bool Pokemon:: CheckLocation()
// checks if Pokemon is within one step of destination
{
	if ((fabs(destination.x - GetLocation().x) <= fabs(delta.x)) && (fabs(destination.y - GetLocation().y) <= fabs(delta.y)))
	{
		location = destination; 
		cout << display_code << GetId() << " : I'm there!" << endl; 
		return true; 
	} else {
		location = location + delta; 

		// output if Pokemon is moving 
		if (delta.x != 0)
		{
			cout << display_code << GetId() << ": On my way." << endl; 
		}
	}

}

bool Pokemon:: Update()
 // update location is object is moving
{
	switch (state) 
	{
		bool okay; 
		case (char) STOPPED: 
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			return false; 
			break; 
		case (char) MOVING: 
		{
			okay = UpdateLocation(); 
			if (okay == UpdateLocation()) 
			{
				this -> state = (char) STOPPED; 
				return true; 
				break;
			} else {
				return false; 
				break; 
			}
		} 

		case (char) MOVING_TO_CENTER: 
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			okay = UpdateLocation(); 
			if (okay == true) 
			{
				this -> state = (char) IN_CENTER; 
				return true; 
				break; 
			} else {
			return false; 
			break;
		}
		}

		case (char) IN_GYM: 
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			return false; 
			break;
		}

		case (char) IN_CENTER: 
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			return false; 
			break; 
		}

		case (char) MOVING_TO_GYM:
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			okay = UpdateLocation(); 
			if (okay == true) 
			{
				this -> state = (char) IN_GYM; 
				return true; 
				break; 
			} else {
			return false; 
			break; 
		}
		}


		case (char) TRAINING_IN_GYM:   
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			this -> state = (char) IN_GYM; 
			unsigned int num_train_points = this -> current_gym -> TrainPokemon(training_units_to_buy); 
			this -> stamina = this -> stamina - this -> current_gym -> GetStaminaCost(this -> training_units_to_buy); 
			this -> pokemon_dollars = this -> pokemon_dollars - this -> current_gym -> GetDollarCost(this -> training_units_to_buy); 
			this -> experience_points = this -> experience_points + num_train_points; 
			return true; 
			break; 
		}
		

		case (char) RECOVERING_STAMINA: 
		{
			cout << "Stamina: " << stamina << endl; 
			cout << "Pokemon Dollars: " << pokemon_dollars << endl; 
			cout << "Experience Points: " << experience_points << endl; 
			this -> ShowStatus(); 
			stamina = stamina + current_center -> DistributeStamina(current_center -> GetNumStaminaPointsRemaining()); 
			pokemon_dollars = pokemon_dollars - current_center -> GetDollarCost(current_center -> GetNumStaminaPointsRemaining());  
			// reduce pokemon dollars by total cost of stamina points
			cout << " ** " << name << "recovered " << stamina << "stamina point(s)!" << endl; 
			this -> state = (char) IN_CENTER; 
			return true; 
			break; 
		}
	}
}

/*
bool Pokemon::UpdateLocation() 
{
	Vector2D updateDist = destination - location; 
	updateDist.x = fabs(updateDist.x); 
	updateDist.y = fabs(updateDist.y); 

	if (updateDist.x <= fabs(delta.x) && updateDist.y <= fabs(delta.y)) 
	{
		location = destination; 
		cout << display_code << GetId() << ": I'm there!" << endl; 
		return true; 
	} else {
		location = location + delta; 
		cout << display_code << GetId(); << ": step..." << endl; 
		return false; 
	}
}


// non-member function
double Pokemon::GetRandomAmountofPokemonDollars()
{
	srand(time(0)); //seed 
	float random_dollars = static_cast<float>(rand())/static_cast<float>(RAND_MAX/2.0); 
	return random_dollars; 
}

// getters 

double Pokemon:: GetSpeed()
{
	return speed; 
}

bool Pokemon:: GetGym()
{
	return is_in_gym; 
}

bool Pokemon:: GetCenter()
{
	return is_in_center; 
}

unsigned int Pokemon:: GetStamina()
{
	return stamina; 
}

unsigned int Pokemon:: GetExperiencePoints()
{
	return experience_points; 
}

double Pokemon:: GetPokemonDollars()
{
	return pokemon_dollars; 
}

unsigned int Pokemon:: GetTrainingUnitsToBuy()
{
	return training_units_to_buy; 
}

*/ 
} 
