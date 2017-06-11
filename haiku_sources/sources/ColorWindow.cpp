#include "ColorWindow.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include <ColorControl.h>
#include <View.h>

ColorWindow::ColorWindow(Group *grp_x, Day *compteur)
: BWindow(_jour->find_win_pos(304,128), "Change active group's color", B_FLOATING_WINDOW, B_NOT_ZOOMABLE )
{
	_jour=compteur;
	grp=grp_x;

	BView *la_vue_du_fond = new BView(Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);
	la_vue_du_fond->SetViewColor(216,216,216);
	AddChild(la_vue_du_fond);

	col_control = new BColorControl(BPoint(10,10), B_CELLS_32x8, 4, "cc", new BMessage(GROUP_COLOR_CHANGED), false); 
	la_vue_du_fond->AddChild(col_control);
	col_control->SetValue(grp->grp_color);	
}

void ColorWindow::MessageReceived(BMessage *message)
{
	message->PrintToStream();

 	switch ( message->what )
 	{
   	case GROUP_COLOR_CHANGED:
   		{
   			coul = col_control->ValueAsColor();
			grp->grp_color = coul;		
			_jour->mainWin->PostMessage(MULTIPLY_ALL);
		}
		break;
   	default:
		BWindow::MessageReceived(message);
   	}
}
