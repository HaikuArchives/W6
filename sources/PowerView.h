#ifndef POWERVIEW_H
#define POWERVIEW_H

#include <View.h>
#include "def_col.h"

class Day;
class Country;
class Group;
class Politic;

class PowerView : public BView
{
public:
		PowerView(BRect frame);
	
		void UpdateBar();
		virtual void Draw(BRect r);

protected:
		Day		*_jour;
		Country **_country;	 //utilisé par les sous-fonctions type MouseDown
		Group   **_group;	 //utilisé par les sous-fonctions type MouseDown
		Politic **_politic;	 //utilisé par les sous-fonctions type MouseDown
};
#endif


