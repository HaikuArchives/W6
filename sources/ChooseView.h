#ifndef CHOOSEVIEW_H
#define CHOOSEVIEW_H

#include <View.h>
#include "def_col.h"

class Day;
class Group;
class FlagView;

#define BUTTON_DONE 'btdn'

class ChooseView : public BView
{
public:
	FlagView	*le_fond_choose;
	BBitmap     *title;
	Day			*_jour;
	Group		**_group;	 //utilisé par les sous-fonctions type MouseDown

	ChooseView(BRect r, long flags,Group *Group_id[MAX_GROUP], Day *compteur);
	virtual	~ChooseView();
	
	virtual	void	Draw(BRect);
};
#endif