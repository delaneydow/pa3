// include guards 

#ifndef MODEL_H
#define MODEL_H 

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 


using namespace std; 

#include "GameObject.h" 
#include "Pokemon.h" 
#include "building.h" 
#include "View.h" 
#include "PokemonGym.h" 
#include "PokemonCenter.h" 

// implement class
class Model 
{
private: 
	int time; // simulation time 
	GameObject* object_ptrs[10]; 
	int num_objects; 
	Pokemon* pokemon_ptrs[10]; 
	int num_pokemon; 
	PokemonCenter* center_ptrs[10]; 
	int num_centers; 
	PokemonGym* gym_ptrs[10]; 
	int num_gyms; 
		
	Model(const Model &other); // copy constructor, cannot be used 

public: 
	Model(); //default constructor
	~Model(); //destructor 
	Pokemon* GetPokemonPtr(int id_num); 
	PokemonCenter* GetPokemonCenterPtr(int id_num); 
	PokemonGym* GetPOkemonGymPtr(int id_num ); 
	bool Update(); 
	void Display(View& view) ; 
	void ShowStatus(); 
	int id_num;

};



#endif
