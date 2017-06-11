#ifndef CHOOSE_WINDOW_H
#define CHOOSE_WINDOW_H

#include "Window.h"
#include "def_col.h"

class Day;
class Country;
class Group;
class ChooseView;

class ChooseWindow : public BWindow 
{
public:
	ChooseView	*ch_view;
	Country		**_country;
	Group		**_group;
	Day 		*_jour;		

	ChooseWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Day *compteur); 
	virtual void 	MessageReceived(BMessage *message);
};
#endif