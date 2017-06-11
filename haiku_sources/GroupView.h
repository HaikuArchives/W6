#ifndef GROUPVIEW_H
#define GROUPVIEW_H

#include <View.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class TxtView;

class GroupView : public BView
{
public:
	Day		*_jour;
	Country **_country;	 //utilisé par les sous-fonctions type MouseDown
	Group   **_group;	 //utilisé par les sous-fonctions type MouseDown
	Politic **_politic;	 //utilisé par les sous-fonctions type MouseDown
	TxtView *grp_name_view,*player_view;
	uint8 	grp;
	
	GroupView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);

	virtual	void	Draw(BRect);
	//virtual void	MouseDown(BPoint where);

			void	UpdateGroupInfo(uint8 which_grp);
};
#endif