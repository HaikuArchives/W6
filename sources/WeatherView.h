#ifndef WEATHERVIEW_H
#define WEATHERVIEW_H

#include <View.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class BBitmap;

class WeatherView : public BView
{
public:
	Day		*_jour;
	Country **_country;	 
	Group	**_group;
	Politic **_politic;	
	BBitmap *img_very_dry, *img_dry, *img_normal_hum, *img_rainy, *img_very_rainy;
	BBitmap *img_very_cold, *img_cold, *img_normal_temp, *img_hot, *img_very_hot;

	WeatherView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);

	virtual	void		Draw(BRect);
};
#endif