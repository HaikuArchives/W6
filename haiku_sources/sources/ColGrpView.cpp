#include "ColGrpView.h"
#include <Window.h>

ColGrpView::ColGrpView(BRect r)
: BView(r, "", B_FOLLOW_TOP, B_WILL_DRAW)
{
	hidden = true;
}

void ColGrpView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{

	if(transit==B_ENTERED_VIEW && hidden==true)
	{	
		point += BPoint(32,0);
		the_win->MoveTo(ConvertToScreen(point));
		the_win->Show(); hidden=false;
	}
	
	if(transit==B_EXITED_VIEW)   
	{
		the_win->Hide();
		hidden=true;
	}
}
