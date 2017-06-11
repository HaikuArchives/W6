#include "EditPolWindow.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "EditorPolView.h"
#include "EditorView.h"
#include <Message.h>

EditPolWindow::EditPolWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BWindow(_jour->find_win_pos(EDIT_POL_X_SIZE,EDIT_POL_Y_SIZE),"Edit Politic", B_FLOATING_WINDOW, B_NOT_H_RESIZABLE | B_NOT_ZOOMABLE) 
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	
	_jour->edit_polWin=this; //pour pouvoir recevoir des messages
	ed_pol_view = new EditorPolView(Bounds(), B_FOLLOW_ALL |B_WILL_DRAW,
						  _country,_group,_politic,_jour);
	AddChild(ed_pol_view);

    ed_pol_view->SetPolEdit(); //met les valeurs actuelles dans les cases
	_jour->edit_pol_win_exists=ON;
	
	
}

EditPolWindow::~EditPolWindow()
{
_jour->edit_pol_win_exists=OFF;

}


void EditPolWindow::MessageReceived(BMessage *message)
{


	// Print the message to see its contents
	message->PrintToStream();

 	switch ( message->what )
	{
		int8 val;		

		case SET_POL_EDIT:	
		ed_pol_view->SetPolEdit(); //affiche les valeurs actuelles dans les cases
		break;

		case UPDATE_RELATIONS:	
		ed_pol_view->SetPolitic(); 
		ed_pol_view->UpdatePolEdit();
		_jour->edit_grpWin->PostMessage(new BMessage(SET_POL_LIST_EDIT));
		break;

		case UPDATE_POL_EDIT:	
		ed_pol_view->UpdatePolEdit();
		_jour->edit_grpWin->PostMessage(new BMessage(SET_POL_LIST_EDIT));
		break;
	
		case BECOMES_FRIEND:
		message->FindInt8("val",&val);
		_politic[_jour->active_politic]->relation[val] = FRIEND;
		break;	
		
		case BECOMES_NEUTRAL:
		message->FindInt8("val",&val);
		_politic[_jour->active_politic]->relation[val] = NEUTRAL;
		break;	
		
		case BECOMES_ENNEMY:
		message->FindInt8("val",&val);
		_politic[_jour->active_politic]->relation[val] = ENNEMY;
		break;	
		
		default:
   		// Call inherited if we didn't handle the message
   		BWindow::MessageReceived(message);
        break;
		}//end switch

}//fin message received
