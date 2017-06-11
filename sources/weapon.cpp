#include "def_col.h"
#include "weapon.h"


/**** constructeur ****/
Weapon::Weapon(const char *name,unsigned char num,float price, uint32 how_many_men, uint32 force, uint32 kill,unsigned char attk, unsigned char def, uint16 per_day)
{
	wpn_nb=num;
	Set(name, price, how_many_men, force, kill, attk, def, per_day);

	for(int16 i=0;i<MAX_WEAPON;i++)
		can_fight[i]=ON; //par défaut la nouvelle arme peut attacker toutes les autres
}

/**** modifier l'arme ****/
void Weapon::Set(const char *name,float price, uint32 how_many_men, uint32 force, uint32 kill,unsigned char attk, unsigned char def, uint16 per_day)
{ 
	cost = price;
	men_required = how_many_men;		 
	strength     = force;			 
	kill_per_day = kill;	
	attack       = attk;
	defense      = def;
	max_per_day  = per_day; //pour missiles et nukes et trucs du style
}
