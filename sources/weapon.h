//*************************************//
//******* Classe WEAPON.h (alliance) *****//
//*************************************//

#ifndef WEAPON_H
#define WEAPON_H

#include <AppKit.h>
#include <String.h>

class Weapon
{
public:
	unsigned char wpn_nb;					//numero d'arme
	float cost;								//cout à l'unité en millions
	uint32 men_required;					//nb hommes nécessaires par arme
	uint32 strength;						//force pour le calcul des ratios
	uint32 kill_per_day;					//max d'hommes tués par _jour
	int16 max_per_day;
	int8 can_fight[MAX_WEAPON];	//quelles armes peuvent combattre lesquelles
	int8 defense,attack;

	Weapon(const char *name,unsigned char num,float price, uint32 how_many_men, uint32 force, uint32 kill,unsigned char attack, unsigned char defense, uint16 per_day);
	void Set(const char *name,float price, uint32 how_many_men, uint32 force, uint32 kill,unsigned char attack, unsigned char defense, uint16 per_day);

	inline	const char *Name()		{ return _name.String(); }

protected:
	BString	_name;							//name
};
#endif
