#ifndef EDITGRPWINDW_H
#define EDITGRPWINDW_H

#include <Window.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class EditorGrpView;
class EditPolWindow;
class BFilePanel;

class EditGrpWindow : public BWindow 
{
public:
	Day				*_jour;
	Country 		**_country;	 
	Group			**_group;
	Politic 		**_politic;				
	BFilePanel 		*flag_load;
	EditorGrpView 	*ed_grp_view;
	EditPolWindow 	*polWin;	
		
	EditGrpWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id [MAX_POLITIC], Day *compteur);
	virtual	~EditGrpWindow();
	virtual void 	MessageReceived(BMessage *message);
};
#endif