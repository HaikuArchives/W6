#ifndef EDITORGRPVIEW_H
#define EDITORGRPVIEW_H

#include <View.h>
#include "def_col.h"

class BListView;
class BTextControl;
class BColorControl;
class BButton;
class BStringView;
class BMenuField;
class Day;
class Country;
class Group;
class Politic;

#define ORI_Y_POS 64
#define ORI_X_POS 4
#define COL_H 64

#define BUTTON_ADD_POL 'adpl'
#define BUTTON_DEL_POL 'depl'
#define BUTTON_EDT_POL 'edpl'

#define FLAG_LOAD  'flgl'

#define SET_GRP_LIST_EDIT 	'stls'
#define SET_COMPUTER_PLAYER 'stcp'
#define SET_PLAYER_01 		'stp1'
#define SET_PLAYER_02 		'stp2'
#define SET_PLAYER_03 		'stp3'
#define SET_PLAYER_04 		'stp4'
#define SET_PLAYER_05 		'stp5'
#define SET_PLAYER_06 		'stp6'
#define SET_PLAYER_07 		'stp7'
#define SET_PLAYER_08 		'stp8'

class EditorGrpView : public BView
{
public:
	BListView 		*pol_list; //pour groupes
	Day				*_jour;
	Country 		**_country;	 //utilisé par les sous-fonctions type MouseDown
	Group   		**_group;	 //utilisé par les sous-fonctions type MouseDown
	Politic 		**_politic;	 //utilisé par les sous-fonctions type MouseDown		
	BTextControl 	*name_control;
	rgb_color 		coul;
	BColorControl 	*col_control;
	BButton 		*button_AddPol,*button_DelPol,*button_EdtPol;
	BStringView  	*nom_file;
	BMenuField 		*player;

	EditorGrpView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);
	
	virtual	void	Draw(BRect);
			void	UpdateGrpEdit();
			void	SetGrpEdit();
			void	UpdatePolitics();
};
#endif