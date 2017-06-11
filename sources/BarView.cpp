#include "BarView.h"
#include <stdio.h>
#include <string.h>

BarView::BarView(BRect r, const char *nm,float lm, const char* l_text)
: BView(r, "", B_FOLLOW_TOP | B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW)
{
 	percentage = 100;
 	limit = lm;
 	sprintf(name,nm);
 	sprintf(limit_text,l_text);
}


void BarView::Draw(BRect update_rect)
{
	BRect r = Bounds();

	// fond
	SetHighColor(37,39,121);
	FillRect(r);

	// cadre
	SetHighColor(77,79,161);
	StrokeRect(r);
	
	// calcul pourcentage
	r.InsetBy(1,1);
	r.right = r.right * percentage / 100;

	// afficher que si on a un pourcentage correcte > 1
	if(r.right>1)
	{
		SetHighColor(189,190,255);
		StrokeLine(BPoint(r.left,r.top),BPoint(r.right,r.top));
		StrokeLine(BPoint(r.left,r.top),BPoint(r.left,r.bottom));
		SetHighColor(107,109,181);
		StrokeLine(BPoint(r.left,r.bottom),BPoint(r.right,r.bottom));
		StrokeLine(BPoint(r.right,r.top),BPoint(r.right,r.bottom));

		//affichage pourcentage
		r.InsetBy(1,1);
		SetHighColor(148,150,255); //couleur normale
		FillRect(r);
	}
	
	char str[255];
	char str2[255];
	sprintf(str,name);
	sprintf(str2,": %.3g %%",percentage);
	strcat(str,str2);
	
	SetFont(be_bold_font);
	SetFontSize(9);
	
	if (percentage <= limit)
		strcat(str,limit_text);

	float lg = StringWidth(str);
	BPoint pt((Bounds().Width()/2)-lg/2,(Bounds().Height()/2)+4);

	pt -= BPoint(1,1);
	if (percentage > limit)
	{
		SetLowColor(HighColor());
		SetHighColor(255,255,255); //couleur normale
	}
	else
	{
		SetLowColor(37,39,121);
		SetHighColor(255,30,0); //Couleur limite atteinte	
	}
	
	DrawString(str,pt);
}