#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <View.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class BBitmap;

class StatusView : public BView
{
public:
		Day		*_jour;
		Country **_country;	 
		Group	**_group;
		Politic **_politic;				
		BBitmap *img_war, *img_peace;

		StatusView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);
		virtual	void		Draw(BRect);
};
#endif