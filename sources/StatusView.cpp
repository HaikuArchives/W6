#include "StatusView.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include <Bitmap.h>
#include <TranslationUtils.h>

StatusView::StatusView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BView(r, "", B_FOLLOW_TOP, B_WILL_DRAW )
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;		
	img_war 	= BTranslationUtils::GetBitmap('RAWT', 60, NULL);
	img_peace 	= BTranslationUtils::GetBitmap('RAWT', 61, NULL);
}

void StatusView::Draw(BRect update_rect)
{
	if (_country[_jour->active_country]->war==ON) 
	{ 
		DrawBitmap(img_war,  BPoint(0,0)); 
		if (_country[_jour->active_country]->status!=FREE)
			 bb_help.SetHelp(this,"Status: war / occupied");
		else bb_help.SetHelp(this,"Status: war / free");
		
	}
	else
	{
		DrawBitmap(img_peace,  BPoint(0,0));
		if (_country[_jour->active_country]->status!=FREE)
			bb_help.SetHelp(this,"Status: peace / occupied");
			else bb_help.SetHelp(this,"Status: peace / free");
	}

}
