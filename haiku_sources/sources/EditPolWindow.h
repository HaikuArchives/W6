#ifndef EDITPOLWINDOW_H
#define EDITPOLWINDOW_H

#include <Window.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class EditorPolView;

class EditPolWindow : public BWindow 
{
public:
	Day				*_jour;
	Country 		**_country;	 
	Group			**_group;
	Politic 		**_politic;	
	EditorPolView 	*ed_pol_view;

	EditPolWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id [MAX_POLITIC], Day *compteur);
	virtual	~EditPolWindow();
	
	virtual void 	MessageReceived(BMessage *message);
};
#endif
