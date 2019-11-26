// include guards 
#include <iostream>
#include <math.h> 

#include "GameObject.h"
#include "building.h" 
#include "PokemonGym.h"

using namespace std; 

unsigned int num_training_units_remaining; 
unsigned int max_number_of_training_units; 
unsigned int stamina_cost_per_training_unit; 
unsigned int dollar_cost_per_training_unit; 
unsigned int experience_points_per_training_unit; 

// constructors 
	// default constructor 
PokemonGym::PokemonGym() : Building::Building()
{
	display_code = 'G'; 
	state = (char) NOT_BEATEN; 
	max_number_of_training_units = 10; 
	num_training_units_remaining = max_number_of_training_units; 
	stamina_cost_per_training_unit = 1; 
	dollar_cost_per_training_unit = 1.0; 
	experience_points_per_training_unit = 2; 
	cout << "PokemonGym default constructed." << endl; 
}

PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc): Building::Building(display_code, in_id, in_loc) 
{
	display_code = 'G'; 
	state = (char) NOT_BEATEN; 
	max_number_of_training_units = 10; 
	max_number_of_training_units = num_training_units_remaining; 
	stamina_cost_per_training_unit = 1.0; 
	experience_points_per_training_unit = 2; 
	// initialize remainder to default values 

	max_number_of_training_units = max_training_units; 
	stamina_cost_per_training_unit = stamina_cost; 
	experience_points_per_training_unit = exp_points_per_unit; 
	dollar_cost_per_training_unit = dollar_cost; 
	location = in_loc; 
	
	cout << "PokemonGym constructed." << endl;
} 

PokemonGym::~PokemonGym()
{
	cout << "PokemonGym deconstructed." << endl; 
}

// public member functions 
 
double PokemonGym::GetDollarCost (unsigned int unit_qty) 
{
	// returns cost of purchasing training units
	double cost = unit_qty * dollar_cost_per_training_unit; 
	return cost; 
}

unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty) 
{
	// returns amount of stamina required
	unsigned int stamina = unit_qty * stamina_cost_per_training_unit; 
	return stamina; 
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining() 
{
	return num_training_units_remaining;
}

bool PokemonGym::IsAbletoTrain(unsigned int unit_qty, double budget, unsigned int stamina) 
{
	if (stamina * unit_qty <= budget) 
	{
		return true; 
	} else {
		return false; 
	}
}


unsigned int PokemonGym::TrainPokemon(unsigned int training_units) 
{
	if (num_training_units_remaining > 0) 
	{
		num_training_units_remaining = num_training_units_remaining - training_units; 
		return num_training_units_remaining; 
	} 
	else if ( num_training_units_remaining >= max_number_of_training_units) 
	{
		return num_training_units_remaining; 
	}
}

bool PokemonGym::Update() 
{
	if (num_training_units_remaining == 0)
	{
		state = (char) BEATEN; 
		display_code = 'g'; 
		cout << display_code << GetId() << " has been beaten" << endl; 
		return true; 
	} else if (num_training_units_remaining > 0) 
	{
		if (state == (char) NOT_BEATEN)
		{
			display_code = 'G'; 
			state = (char) NOT_BEATEN;
			return false;
		} else {
			return false; 
		}
	}
	return false; 
}


bool PokemonGym::IsBeaten() 
{
	if (num_training_units_remaining == 0) 
	{
		return true; 
	} else {
		return false; 
	} 
}


void PokemonGym::ShowStatus() 
{
	cout << "Pokemon Gym Status: " << endl; 
	Building::ShowStatus();  
	cout << "Max number of training units: " << max_number_of_training_units << endl; 
	cout << "Stamina cost per training unit: " << stamina_cost_per_training_unit << endl; 
	cout << "Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl; 
	cout << "Expereince points per training unit: " << experience_points_per_training_unit << endl; 
	cout << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl; 
}


