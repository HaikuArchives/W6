#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <View.h>
#include <PictureButton.h>

#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class TxtView;
class BarView;
class TopView;
class ColGrpView;
class GroupWindow;
class WeatherView;
class StatusView;

class InfoView : public BView
{
public:
		Day			*_jour;
		Country 	**_country;	 //utilisé par les sous-fonctions type MouseDown
		Group   	**_group;	 //utilisé par les sous-fonctions type MouseDown
		Politic 	**_politic;	 //utilisé par les sous-fonctions type MouseDown
		float		size_x,size_y;	
		ColGrpView* group_color_view;
		ColGrpView* group_ori_color_view;
		TopView 	*back_view; 	
		TxtView		*pop_view,*money_view;	
		BarView 	*moral_bar, *resist_bar, *agri_bar,*indus_bar;	
		TxtView 	*tl_view; //techlevel	
		TxtView 	*infantry_view, *tank_view, *marine_view;
		TxtView		*airforce_view, *dca_view, *missile_view,*nuke_view;
		TxtView 	*engaged_view,*engaged2_view,*engaged3_view,*engaged4_view;
		TxtView 	*ennemy_view,*ennemy2_view,*ennemy3_view,*ennemy4_view;
		BBitmap		*downBitmap;
		BBitmap		*upBitmap;
   		BPicture 	*on,*off;   	
   		BPictureButton 	*buy_button, *set_button;
   		GroupWindow 	*grpwin,*grporiwin; 	
   		WeatherView 	*wth_view;
   		StatusView 		*stat_view;
	
		InfoView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur);
		virtual	~InfoView();

		void	CreateButton(int32 enabled_id ,int32 disabled_id);
		void	MouseDown(BPoint where);
		void	UpdateCountryInfo();
};

#endif