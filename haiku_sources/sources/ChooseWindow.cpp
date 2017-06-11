#include "ChooseWindow.h"
#include "country.h"
#include "ChooseView.h"
#include "group.h"
#include "day.h"

#include <Message.h>
#include <iostream.h>

ChooseWindow::ChooseWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Day *compteur)
: BWindow(_jour->find_win_pos(584,300),"Choose-Window", B_MODAL_WINDOW, B_NOT_ZOOMABLE | B_NOT_RESIZABLE )
{
	_country=Country_id;
	_group=Group_id;
	_jour=compteur;

	ch_view = new ChooseView(Bounds(), B_FOLLOW_TOP |B_WILL_DRAW| B_NOT_RESIZABLE| B_NO_BORDER , _group,_jour);
	AddChild(ch_view); //ajoute la vue du texte à la window


}	
//-----------------------------------------------------------------
void ChooseWindow::MessageReceived(BMessage *message)
{
	unsigned char found,tmp_ct; //unsigned char tmp_ct=_jour->country_first
	// Print the message to see its contents
	message->PrintToStream();

 	switch(message->what)
 	{
	case BUTTON_DONE:
		{
			_group[_jour->active_group]->player = PLAYER_01;
			//trouve le premier pays du groupe en question et l'active
			found = OFF;
			tmp_ct = _jour->country_first; //unsigned char tmp_ct=_jour->country_first
			while(tmp_ct!=_jour->country_last+1 && found==OFF)
			{
				// atention de ne pas depasser
				if(tmp_ct == MAX_COUNTRY)
					found = ON;

				if(_country[tmp_ct]->group == _jour->active_group) 
				{
					_jour->active_country = tmp_ct;
					found = ON;
				}
				tmp_ct++;
			}	
			_jour->player_group =_jour->active_group;
//			_jour->mainWin->PostMessage(REDRAW_ME);
			_jour->game_started=ON;
			_jour->pause=OFF;
			_jour->mainWin->PostMessage(UPDATE_TITLE);

			PostMessage(B_QUIT_REQUESTED);
		}
		break;
	default:
		BWindow::MessageReceived(message);
	}
}

