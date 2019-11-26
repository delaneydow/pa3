// include guards 

#ifndef POKEMON_H
#define POKEMON_H 

#include <iostream> 
#include <stdio.h> 

#include "GameObject.h"
#include "Vector2D.h"
#include "building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h" 

class Point2D; 
class Vector2D; 
class Building; 
class PokemonGym; 
class PokemonCenter; 

enum PokemonStates 
{
	STOPPED = 0,
	MOVING = 1,
	EXHAUSTED = 2,
	IN_GYM = 3,
	IN_CENTER = 4,
	MOVING_TO_GYM = 5,
	MOVING_TO_CENTER = 6,
	TRAINING_IN_GYM = 7,
	RECOVERING_STAMINA = 8
};


class Pokemon : public GameObject
{
protected: 
	bool UpdateLocation(); 
	void SetupDestination(Point2D dest); 

private: 
	double speed; 
	bool is_in_gym; 
	bool is_in_center; 
	unsigned int stamina; 
	unsigned int experience_points; 
	double pokemon_dollars; 
	unsigned int training_units_to_buy;
	unsigned int stamina_points_to_buy;  
	string name; 
	PokemonCenter* current_center; 
	PokemonGym* current_gym; 
	Point2D destination; // initialized to (0.0, 0.0) by Point2D default constructor
	Vector2D delta; 

	// public members
public: 
	Pokemon(); 
	Pokemon(char in_code); 

	~Pokemon(); 

	Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc); 
	void StartMoving(Point2D dest); 
	void StartMovingToCenter(PokemonCenter* center); 
	void StartMovingToGym(PokemonGym* gym); 
	void StartTraining(unsigned int num_training_units); 
	void StartRecoveringStamina(unsigned int num_stamina_points); 
	void Stop(); 
	bool IsExhausted(); 
	bool ShouldBeVisible(); 
	void ShowStatus(); 
	bool CheckLocation(); 
	bool Update(); 
	void SetUpDestination(Point2D dest); 


	// getters
	double GetSpeed(); 
	bool GetGym(); 
	bool GetCenter(); 
	unsigned int GetStamina(); 
	unsigned int GetExperiencePoints(); 
	double GetPokemonDollars(); 
	unsigned int GetTrainingUnitsToBuy(); 


}; 

// Non-Members (static) 
double GetRandomAmountOfPokemonDollars(); 

#endif 