#ifndef FLAGVIEW_H
#define FLAGVIEW_H

#include <View.h>
#include "def_col.h"

class Day;
class Group;

class FlagView : public BView
{
public:
	Day		*_jour;
	Group 	**_group;	 //utilisé par les sous-fonctions type MouseDown

	FlagView(BRect r, long flags,Group *Group_id[MAX_GROUP], Day *compteur);

	virtual	void	Draw(BRect);
			void	MouseDown(BPoint point);
};
#endif