#ifndef RUNNING_H
#define RUNNING_H

#include <View.h>
#include "def_col.h"       //creation des pays

class Country;
class Politic;
class Group;
class Day;
class Weapon;

//La classe qui tourne en permanence et fait passer les _jours tout en calculant...
class Running : public BView
{
public:
	Day			*_jour;
	Country 	**_country;	  
	Group		**_group; 
	Politic		**_politic; 
	Weapon		**_weapon; 

	Running(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC],Weapon *Weapon_id[MAX_WEAPON], Day *compteur);
	virtual	void Pulse();
};
#endif