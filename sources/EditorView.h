#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

#include <View.h>
#include "def_col.h"

class BListView;
class BTextControl;
class BButton;
class BStringView;
class BCheckBox;
class Day;
class Country;
class Group;
class Politic;

#define BUTTON_ADD_GRP 'adgr'
#define BUTTON_DEL_GRP 'degr'
#define BUTTON_EDT_GRP 'edtr'
#define BUTTON_GEN 'gnar'
#define SET_POL_LIST_EDIT 'sple'
#define BUTTON_NEXT 'btnx'
#define BUTTON_PREV 'btpv'
#define ESPACE 8 //pour les drapeaux
#define X_ORI 54
#define Y_ORI 16
#define XX_ORI 8
#define YY_ORI 16
#define MARGE 2
#define OFFSET_X 108
#define OFFSET_Y 22

class EditorView : public BView
{
public:
	BListView 		*list,*ct_list; //pour groupes
	Day				*_jour;
	Country 		**_country;	 //utilisé par les sous-fonctions type MouseDown
	Group 			**_group;	 //utilisé par les sous-fonctions type MouseDown
	Politic 		**_politic;	 //utilisé par les sous-fonctions type MouseDown
	BStringView  	*numero;
	BTextControl 	*money_control, *birth_rate_control, *tech_level_control;
	BTextControl 	*pnb_control;
	BCheckBox   	*sea_check,*nuke_check;
	BTextControl	*name_control,*group_name_control,*population_control;
	BTextControl	*infantry_control, *tank_control, *marine_control;
	BTextControl	*airforce_control, *missile_control,*nuke_control,*dca_control; 
	BButton			*button_AddGrp,*button_DelGrp,*button_EdtGrp;
	BButton			*button_Next, *button_Prev, *button_Gen;		
		
	EditorView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);
	virtual	~EditorView();

		void	MouseDown(BPoint where);
		void	SetEdit();    //met les valeurs actuelles dans les cases
		void	UpdateEdit(); //update les valeurs avec celles des cases
		void	UpdateGroups();
		void	SelectedCt();
};
#endif
