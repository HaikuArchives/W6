#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <Window.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class EditorView;
class EditGrpWindow;

class EditWindow : public BWindow 
{
public:
	Day				*_jour;
	Country 		**_country;	 
	Group			**_group;
	Politic 		**_politic;
	EditorView 		*ed_view;
	EditGrpWindow 	*grpWin;

		
	EditWindow(BRect frame,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id [MAX_POLITIC], Day *compteur);
	virtual	~EditWindow();

	virtual void 	MessageReceived(BMessage *message);
	virtual void 	FrameResized(float width, float height);
			void 	NotImplemented();
};
#endif