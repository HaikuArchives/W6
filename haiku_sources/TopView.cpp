#include "TopView.h"

TopView::TopView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BView(r, "", B_FOLLOW_TOP, B_WILL_DRAW)
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
}
