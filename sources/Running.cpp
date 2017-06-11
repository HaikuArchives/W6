#include "Running.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include <Window.h>

Running::Running(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC],Weapon *Weapon_id[MAX_WEAPON], Day *compteur)
: BView(BRect(0,0,0,0),"Running Pseudo View", Flags() | B_PULSE_NEEDED,B_WILL_DRAW)
{
	//Cette classe est dérivée de running juste pour avoir le pulse...
	//rien ici cette classe n'est là que pour pulser...
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	_weapon = Weapon_id;
	_jour=compteur;
}

void Running::Pulse()
{
	if (_jour->pause != ON) 
	{
		if (_jour->step-- ==0)
		{
			//PAs mettre directement jump_days dans la boucle
			//car s'il est change en plus petit pendant la boucle crash puisque s'arrete plus
			uint32 to_reach=_jour->jump_days;
			uint32 i=0;
				
			do
			{  			
				//DAY PASSED A INTERVALLE REGULIER
				_jour->next();
				unsigned char temp_ctry = _jour->country_first;
  				
  				while (temp_ctry != _jour->country_last+1) 
  				{
  					_country[temp_ctry]->day_passed();
  					temp_ctry++;}
			 	}
			 	
			 	while (i++!=to_reach)
			 		;	
				
				_jour->step=_jour->day_step; //on recommence dans x pulses...
				_jour->infoWin->PostMessage(DRAW_INFO);
		}
	}
}//fin pulse infoview
