#ifndef INFOWINDW_H
#define INFOWINDW_H

#include <Window.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class InfoView;

class InfoWindow : public BWindow 
{
public:
		Day			*_jour;
		Country 	**_country;	 
		Group		**_group;
		Politic 	**_politic;				
		InfoView	*i_view; 
		
		InfoWindow(BRect frame, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id [MAX_POLITIC], Day *compteur);
		virtual	~InfoWindow();

		virtual void 	MessageReceived(BMessage *message);
};
#endif
