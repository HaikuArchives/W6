#include "def_col.h"
#include "politic.h"

#include <stdio.h>

/**** Constructeurs Politic ****/
Politic::Politic(const char *name, unsigned char num)
{
	_name		= name;
	nb_pol		= num;
	active		= ON;
	repression	= 0;
	propaganda	= 0;

	//par défaut on est amis avec tout le monde (donc pas de combat)
	//on peut etre soit, FRIEND, ENNEMY, NEUTRAL
	//une fois qu'on a plus d'ennemi on attaque les neutral.

	for(int16 i=0;i<255;i++)
		relation[i]=FRIEND; //relation avec autres pays
}
