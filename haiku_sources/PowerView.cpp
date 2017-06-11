#include "PowerView.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "politic.h"
#include "W6.h"
#include <InterfaceDefs.h>

/**** Constructeur ****/
PowerView::PowerView(BRect frame)
: BView(frame, "PowerView", B_FOLLOW_BOTTOM | B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW)
{
	_jour		= ((W6Application *)be_app)->_jour;
	_country	= ((W6Application *)be_app)->_country;
	_group		= ((W6Application *)be_app)->_group;
	_politic	= ((W6Application *)be_app)->_politic;	

	// AFFICHAGE DES INFOS
    SetViewColor(0,0,0);
}

/**** dessin de la vue ****/
void PowerView::Draw(BRect update_rect)
{
	//DESSIN DU RECTANGLE en dernier
	float		pos  = 0;
	float		sizeGroup = 0;
	float		viewHeight = Bounds().Height()-1;
	rgb_color	groupColor;
	BRect		groupFrame;

	//pour pointer dans list pays
	unsigned char	compteur;

    for(compteur = _jour->group_first;compteur<(_jour->group_last+1);compteur++)
    {
		// recuperer la couleur du groupe
		groupColor = _group[compteur]->grp_color;
		
		sizeGroup = (Bounds().Width()/100 * _group[compteur]->power_percent);
		sizeGroup += pos;
		groupFrame.Set(pos,4,sizeGroup-1,viewHeight);

		//SetHighColor(groupColor);
		SetHighColor(tint_color(groupColor,B_LIGHTEN_2_TINT));
		StrokeLine(BPoint(groupFrame.left,groupFrame.top),BPoint(groupFrame.right,groupFrame.top));	
		StrokeLine(BPoint(groupFrame.left,groupFrame.top),BPoint(groupFrame.left,groupFrame.bottom));	

		SetHighColor(tint_color(groupColor,B_DARKEN_2_TINT));
		StrokeLine(BPoint(groupFrame.left,groupFrame.bottom),BPoint(groupFrame.right,groupFrame.bottom));	
		StrokeLine(BPoint(groupFrame.right,groupFrame.top+1),BPoint(groupFrame.right,groupFrame.bottom));	
	
		SetHighColor(tint_color(groupColor,B_DARKEN_1_TINT));
		StrokeLine(BPoint(groupFrame.left+1,groupFrame.bottom-1),BPoint(groupFrame.right-1,groupFrame.bottom-1));	

		SetHighColor(groupColor);
		groupFrame.InsetBy(1,1);
		FillRect(groupFrame);

		pos = sizeGroup;
	}
}

/**** mise a _jour de la barre ****/
void PowerView::UpdateBar()
{
	Invalidate();
}