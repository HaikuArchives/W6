#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <Window.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class GroupView;

class GroupWindow : public BWindow 
{
public:
	Day			*_jour;
	Country 	**_country;	 
	Group		**_group;
	Politic 	**_politic;		
	GroupView	*grp_view; 
		
	GroupWindow(BRect frame, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id [MAX_POLITIC], Day *compteur);
};
#endif