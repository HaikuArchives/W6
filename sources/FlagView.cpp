#include "FlagView.h"
#include "day.h"
#include "group.h"
#include <Button.h>

FlagView::FlagView(BRect r, long flags,Group *Group_id[MAX_GROUP], Day *compteur)
: BView(r, "", flags, B_WILL_DRAW )
{
	_jour=compteur;
	_group = Group_id;
}

void	FlagView::Draw(BRect update_rect)
{
SetPenSize(1);
BRect rect, big_rect;
unsigned char i = _jour->group_first;
rect.Set(((150-FLAG_X_SIZE)/2), 8, ((150-FLAG_X_SIZE)/2)+FLAG_X_SIZE-1, 8+FLAG_Y_SIZE-1);

while (i!=_jour->group_last+1)
	{
	DrawBitmap(_group[i]->flag_ptr, rect);
	
	big_rect = rect; big_rect.InsetBy(-2,-2);
	if (_jour->active_group==i) { SetHighColor(_group[i]->grp_color);  StrokeRect(big_rect,B_SOLID_HIGH);}
					else	   { SetHighColor(0,0,0);  StrokeRect(big_rect,B_SOLID_HIGH);}
	
	rect.OffsetBy(0,FLAG_Y_SIZE+8);
	i++;
	}
	
}


void FlagView::MouseDown(BPoint point)
{

BRect rect;
rect.Set(((150-FLAG_X_SIZE)/2)-1, 8-1, ((150-FLAG_X_SIZE)/2)+FLAG_X_SIZE, 8+FLAG_Y_SIZE);
unsigned char i = _jour->group_first;

while (i!=_jour->group_last+1)
	{
	if (point.x >= rect.left 	 && point.x <= rect.right 
		&& point.y >= rect.top   && point.y <= rect.bottom  )	//si on est dans la zone du drapeau
  		{
		_jour->active_group=i;
		char str[255];
		char str2[255];
		sprintf(str,"Start as leader of ");
		sprintf(str2,_group[_jour->active_group]->Name());
		strcat(str,str2);
		_jour->button_Done->SetLabel(str);
		_jour->button_Done->SetEnabled(true);
		}
	rect.OffsetBy(0,FLAG_Y_SIZE+8);
	i++;
	}
	
	Draw(Bounds());
}//FIN FONCTION
