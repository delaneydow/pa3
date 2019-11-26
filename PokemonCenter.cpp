//include guards 
#include <iostream> 
#include <math.h>

#include "PokemonCenter.h"

using namespace std; 

double dollar_cost_per_stamina_point; 
unsigned int num_stamina_points_remaining; 
unsigned int stamina_capacity;

// inherits from building, which inherits from GameObject 

// constructors
PokemonCenter::PokemonCenter() : Building::Building()
{
	display_code = 'C'; 
	stamina_capacity = 100; 
	num_stamina_points_remaining = stamina_capacity; 
	dollar_cost_per_stamina_point = 5; 
	state = (char) STAMINA_POINTS_AVAILABLE; 
	cout << "PokemonCenter default constructed" << endl; 	
}


PokemonCenter::PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_cap, Point2D in_loc): Building(display_code, in_id, in_loc)
	{
		display_code = 'C'; 
		location =  in_loc; 
		dollar_cost_per_stamina_point = stamina_cost; 
		stamina_capacity = stamina_cap; 
		// rest of variables assigned default values 
		stamina_capacity = 100; 
		num_stamina_points_remaining = stamina_capacity; 
		dollar_cost_per_stamina_point = 5; 
			// state is STAMINA_POINTS_AVAILABLE 
		state = (char) STAMINA_POINTS_AVAILABLE; // "default" value 
		cout << "PokemonCenter constructed" << endl; 		
	}

PokemonCenter::~PokemonCenter()
{
	cout << "PokemonCenter destructed." << endl; 
}


// public member functions 
	bool PokemonCenter::HasStaminaPoints() 
	{
		// true if PokemonCenter has at least one stamina point 
		if (num_stamina_points_remaining >= 1)
			return true; 
		else 
			return false; 
	}

	unsigned int PokemonCenter::GetNumStaminaPointsRemaining() 
	{
		// get number of stamina points remaining 
		return num_stamina_points_remaining; 
	}


	bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
	 {
		// returns true if pokemon can afford to purchase stamina points from budget 
		if (budget >= (stamina_points * dollar_cost_per_stamina_point)) {
			return true ; 
		} else 
			return false; 
	}
 
	double PokemonCenter::GetDollarCost(unsigned int points_needed) 
	{
		double cost = points_needed * 5; 
		return cost; 
	}


	unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed) {
		// series of if statements 
		if (num_stamina_points_remaining >= points_needed) {
			// subtract points_needed from PokemonCenter amount
			points_needed = (num_stamina_points_remaining - points_needed); 
			return points_needed; 
		} else if (num_stamina_points_remaining < points_needed) {
			// stamina amount set to zero 
			return num_stamina_points_remaining; 
			unsigned int stamina_cap = 0; 
		}
	}

	bool PokemonCenter::Update() {
		if ((num_stamina_points_remaining == 0) && (state == (char) STAMINA_POINTS_AVAILABLE)){
			state = (char) NO_STAMINA_POINTS_AVAILABLE; 
			display_code = 'c'; 
			cout << "PokemonCenter " << GetId() << " has run out of stamina points." << endl; 
			return true; // returns true if stamina is depleted
		} else {
			return false; 
		}
	}

	void PokemonCenter::ShowStatus() 
	{
		cout << "Pokemon Center Status: " << endl; 
		Building::ShowStatus(); 
		cout << "Pokemon dollars per stamina point: " << dollar_cost_per_stamina_point << " has " << num_stamina_points_remaining << "stamina point(s) remaining. " << endl; 
	}

	




