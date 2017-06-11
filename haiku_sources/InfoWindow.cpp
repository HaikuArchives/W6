#include "InfoWindow.h" 
#include "ColorWindow.h"
#include "day.h"
#include "country.h"
#include "InfoView.h"
#include "GroupWindow.h"
#include <TranslationUtils.h>
#include <Message.h>

InfoWindow::InfoWindow(BRect frame,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BWindow(frame, "Country Infos", B_FLOATING_WINDOW, B_NOT_ZOOMABLE | B_NOT_CLOSABLE | B_NOT_H_RESIZABLE | B_ASYNCHRONOUS_CONTROLS) 
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id; 
	_politic = Politic_id;
	_jour->info_win_exists = ON;
	
	i_view = new InfoView(Bounds(), _country,_group,_politic,compteur);
	AddChild(i_view); 
	
	//on peut pas le faire à l'intérieur!!! donc après le addchild
	i_view->ChildAt(0)->SetViewBitmap(BTranslationUtils::GetBitmap('RAWT', 50, NULL));

	i_view->grpwin->Hide();
	i_view->grporiwin->Hide();
}

InfoWindow::~InfoWindow()
{
	_jour->info_win_exists=OFF;
	//surtout pas faire un Close() ici! On est déjà en train de killer la win
}

void InfoWindow::MessageReceived(BMessage *message)
{
	// Print the message to see its contents
	//message->PrintToStream();
 	switch ( message->what )
 	{
 		case BUTTON_BUY: 	
 			_jour->mainWin->PostMessage(BUTTON_BUY);
 			break;
 		case BUTTON_SET: 	
 			_jour->mainWin->PostMessage(BUTTON_SET);
 			break;
		case DRAW_INFO:
			i_view->UpdateCountryInfo();
			_jour->mainWin->PostMessage(UPDATE_POWER_BAR);
			break;
		default:
   			// Call inherited if we didn't handle the message
   			BWindow::MessageReceived(message);
	}//end switch
}//fin message received


