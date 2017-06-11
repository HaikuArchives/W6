#ifndef EDITORPOLVIEW_H
#define EDITORPOLVIEW_H

#include <View.h>
#include "def_col.h"

class Day;
class Country;
class Group;
class Politic;
class BMenuField;
class BScrollView;
class BTextControl;
class BSlider;

class EditorPolView : public BView
{
public:
	Day				*_jour;
	Country 		**_country;	 //utilisé par les sous-fonctions type MouseDown
	Group   		**_group;	 //utilisé par les sous-fonctions type MouseDown
	Politic 		**_politic;	 //utilisé par les sous-fonctions type MouseDown
	BMenuField 		*pol_relation[MAX_POLITIC];
	BView			*le_fond_pol;
	BScrollView 	*sc_view;
	BTextControl 	*pol_name_control;
	BSlider 		*slider_repression,*slider_propaganda; 

	EditorPolView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);

	void	UpdatePolEdit();
	void	SetPolEdit();
	void    SetPolitic();
};
#endif