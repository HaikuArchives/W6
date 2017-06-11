#include "GroupWindow.h"
#include "GroupView.h"
#include "day.h"

GroupWindow::GroupWindow(BRect frame,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BWindow(frame, "Group Infos", B_BORDERED_WINDOW, B_NOT_ZOOMABLE | B_NOT_CLOSABLE | B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS | B_NO_BORDER) 
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id; 
	_politic = Politic_id;
	
	_jour->info_win_exists = ON;
	
	grp_view = new GroupView(Bounds(), _country,_group,_politic,compteur);
	AddChild(grp_view); 
	
	SetFeel(B_FLOATING_APP_WINDOW_FEEL);
}
