#ifndef _APPLICATION_H
#include <Application.h>
#endif	

#include "W6Window.h"
#include "W6.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "PowerView.h"
#include "MapView.h"
#include "HistoryView.h"
#include "EditorView.h"
#include "EditWindow.h"
#include "BuyWindow.h"
#include "ColorWindow.h"
#include "OrderWindow.h"
#include "SpeedWindow.h"
#include <MenuBar.h>
#include <MenuItem.h>
#include <Menu.h>
#include <ScrollView.h>
#include <Beep.h>
#include <FilePanel.h>
#include <Alert.h>
#include <Roster.h>

W6Window::W6Window(BRect frame)
: BWindow(frame, "What Went Wrong? It's a World Wide War!",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) 
{
	_jour		= ((W6Application *)be_app)->_jour;
	_country	= ((W6Application *)be_app)->_country;
	_group		= ((W6Application *)be_app)->_group;
	_politic	= ((W6Application *)be_app)->_politic;	

	BRect rect;	  //variable de rectangle utilisée pour les diverses créations d'objets

	SetPulseRate (DEFAULT_PULSE_RATE);

///////////******************************************************
/// BARRE DE MENUS
/////////*******************************************************

	
	BMenu		*a_menu;  //objet sous-menu utilisé plusieurs fois pour la création des différents menus.
	BMenuItem	*item;    //utilisé par item coché par défaut (Options)
	//menubar et a_menu sont créés dans le .h pour utilisation (si on veut changer le menu
	Lock();

	menubar = new BMenuBar(rect, "MB");
	
	a_menu = new BMenu("Game");
	a_menu->AddItem(new BMenuItem("Start a new Game", new BMessage(MENU_GAME_RESTART)));
	a_menu->AddItem(new BMenuItem("Load Game", new BMessage(MENU_LOAD)));
	a_menu->AddItem(new BMenuItem("Save Game", new BMessage(MENU_SAVE)));
	
	a_menu->AddSeparatorItem();
	a_menu->AddItem(new BMenuItem("Set game speed", new BMessage(MENU_GAME_SET_DAY_RATE)));
	a_menu->AddItem(new BMenuItem("Edit Game", new BMessage(MENU_GAME_EDIT)));
	a_menu->AddItem(new BMenuItem("Pause", new BMessage(MENU_GAME_PAUSE)));
	a_menu->AddItem(new BMenuItem("Quit WW6", new BMessage(MENU_GAME_QUIT)));
	menubar->AddItem(a_menu);
	
	a_menu = new BMenu("Level");
	a_menu->AddItem(new BMenuItem("Easy", new BMessage(MENU_LEVEL_EASY)));
	a_menu->AddItem(item = new BMenuItem("Normal", new BMessage(MENU_LEVEL_NORMAL)));
	a_menu->AddItem(new BMenuItem("Hard", new BMessage(MENU_LEVEL_HARD)));
	a_menu->AddItem(new BMenuItem("Really, really, really, really, really too HARD", new BMessage(MENU_LEVEL_TOO_HARD)));
	a_menu->SetRadioMode(TRUE);//pour avoir un menu d'options à choix (coche)
	item->SetMarked(TRUE);//met la coche sur celui par défaut
	menubar->AddItem(a_menu); //rajoute le menu à la barre

//----------------------------------------

	_jour->edit_menu = new BMenu("Edit");
	_jour->edit_menu->AddItem(new BMenuItem("Scenario settings", new BMessage(MENU_SCENARIO)));
	_jour->edit_menu->AddItem(paintmode = new BMenuItem("Paint Mode", new BMessage(MENU_PAINT_MODE)));
	_jour->edit_menu->AddItem(new BMenuItem("Edit politics", new BMessage(MENU_POLITIC)));
	_jour->edit_menu->AddSeparatorItem();
	_jour->edit_menu->AddItem(new BMenuItem("Refresh Map (Multiply)", new BMessage(MENU_EDIT_REFRESH)));
	menubar->AddItem(_jour->edit_menu);
	_jour->edit_menu->SetEnabled(false);

	a_menu = new BMenu("Options");
	a_menu->AddItem(new BMenuItem("Don't log resistance attacks", new BMessage(LOG_IMPORTANT_MESSAGES)));
	a_menu->SetRadioMode(TRUE);//pour avoir un menu d'options à choix (coche)
	menubar->AddItem(a_menu); //rajoute le menu à la barre

	a_menu = new BMenu("Zoom");
	a_menu->AddItem(new BMenuItem("200%", new BMessage(ZOOM_200)));
	a_menu->AddItem(new BMenuItem("150%", new BMessage(ZOOM_150)));
	a_menu->AddItem(new BMenuItem("100%", new BMessage(ZOOM_100)));
	a_menu->AddItem(new BMenuItem("75%", new BMessage(ZOOM_75)));
	a_menu->AddItem(new BMenuItem("50%", new BMessage(ZOOM_50)));
	
	a_menu->SetRadioMode(TRUE);//pour avoir un menu d'options à choix (coche)
	menubar->AddItem(a_menu); //rajoute le menu à la barre

	a_menu = new BMenu("Help");
	a_menu->AddItem(item = new BMenuItem("Documentation...", new BMessage(MENU_DOC)));
	a_menu->AddSeparatorItem();
	a_menu->AddItem(item = new BMenuItem("About", new BMessage(MENU_ABOUT)));
	menubar->AddItem(a_menu); //rajoute le menu à la barre

	AddChild(menubar); //ajoute la barre de menus complète à la fenêtre
	Unlock();//Lock nécessaire que pour barre menus

	//CONSTRUCTIONS DES VUES
	mb_height = menubar->Bounds().Height();
	rect.Set(0,mb_height+1,WIN_X_SIZE,WIN_Y_SIZE-HISTORY_Y_SIZE-POWER_HEIGHT-3);
	inside_view = new MapView(BRect(rect), B_FOLLOW_ALL | B_WILL_DRAW| B_PULSE_NEEDED);
	scroll_view = new BScrollView("scroll view", inside_view, B_FOLLOW_ALL, B_WILL_DRAW,false,false);
	scroll_view->SetViewColor(0,0,0);//pour pas trop flasher les yeux avant que le premier full multiply ait pu avoir eu lieu
								//ouais... faudrait surtout que la pic vide soit noire et pas blanche...	

	rect.top = rect.bottom;
	rect.bottom = rect.top +POWER_HEIGHT+1;
	power_view = new PowerView(BRect(rect));

	//j'utilise pas les scrollbar de la scrollviews car je veux pas les afficher..
	//Or, même si je fais Hide, la barre du bas, voit son contour redessiné de temps en temps, ça fait buggé									
	_jour->scroll_hori  = new BScrollBar(BRect(inside_view->Bounds().Width(),0,B_V_SCROLL_BAR_WIDTH,0),"",inside_view,0,1000,B_HORIZONTAL);
	_jour->scroll_verti  = new BScrollBar(BRect(0,inside_view->Bounds().Height(),0,B_V_SCROLL_BAR_WIDTH),"",inside_view,0,1000,B_VERTICAL);

	//le range de scroll est égal à la taille de la pic moins la partie affichée
	//cette routine est refaite dans FrameResized à chaque modif de taille
	_jour->scroll_hori->SetRange(0, DEF_PIC_X_SIZE-(WIN_X_SIZE)); 
	_jour->scroll_verti->SetRange(0, DEF_PIC_Y_SIZE-(WIN_Y_SIZE-mb_height-HISTORY_Y_SIZE)); 

	AddChild(scroll_view); //ajoute la vue du texte à la window  
	AddChild(power_view);

	//-----------------------------------------------------------------------------------------------------------
	rect.Set(0,WIN_Y_SIZE-HISTORY_Y_SIZE,1280,WIN_Y_SIZE); //1280 pour être sûr
			 
	//history_parent_view englobe le texte et la barre de scroll vert			 
	history_parent_view = new BView(rect,"",B_FOLLOW_BOTTOM | B_FOLLOW_LEFT_RIGHT,B_WILL_DRAW);
	history_parent_view->SetViewColor(216,216,216);
	AddChild(history_parent_view); //ajoute la vue du texte à la window

	BRect text_rect;
	//Creation vue History

	rect.Set(0,0, WIN_X_SIZE-B_V_SCROLL_BAR_WIDTH,HISTORY_Y_SIZE);	
	text_rect=rect;
	text_rect.InsetBy(16,16); //même rect en plus petit de 16
	h_view = new HistoryView(rect,"",text_rect,true, (BFont*) be_bold_font, _jour);
	history_parent_view->AddChild(h_view); //ajoute la vue du texte à la window
	
	//Création barre vertical de HistoryView
	rect.Set(WIN_X_SIZE-B_V_SCROLL_BAR_WIDTH+1,0, WIN_X_SIZE,HISTORY_Y_SIZE);	
    history_v_scroll= new BScrollBar(rect, "", h_view, 0, HISTORY_Y_SIZE-B_V_SCROLL_BAR_WIDTH, B_VERTICAL); 
   	history_parent_view->AddChild(history_v_scroll);
}

//POUR LA GESTION DES MESSAGES ARRIVANT	
//Ca doit etre dans la main window... si c'est dans les view, seulement les views répondent
void W6Window::MessageReceived(BMessage *message)
{
	BRect la_zone;
	// Print the message to see its contents
	message->PrintToStream();
	BAlert *xalert;
		
 	switch(message->what)
 	{
	case UPDATE_TITLE:
		inside_view->UpdateTitle();
		break;
	case UPDATE_POWER_BAR:
		power_view->UpdateBar();
		break;
	case ZOOM_200:
		_jour->zoom_level = 2;
		inside_view->SetScale(2);
		inside_view->ResizeTo(DEF_PIC_X_SIZE * _jour->zoom_level,DEF_PIC_X_SIZE *_jour->zoom_level );
		PostMessage(REDRAW_ME);
		break;
	case ZOOM_150:
		_jour->zoom_level = 1.5;
		inside_view->SetScale(1.5);
		inside_view->ResizeTo(DEF_PIC_X_SIZE * _jour->zoom_level,DEF_PIC_X_SIZE *_jour->zoom_level );
		PostMessage(REDRAW_ME);
 		break;
	case ZOOM_100:
		_jour->zoom_level = 1;
		inside_view->SetScale(1);
		inside_view->ResizeTo(DEF_PIC_X_SIZE * _jour->zoom_level,DEF_PIC_X_SIZE *_jour->zoom_level );
		PostMessage(REDRAW_ME);
 		break;
	case ZOOM_75:
		_jour->zoom_level = 0.75;
		inside_view->SetScale(0.75);
		inside_view->ResizeTo(DEF_PIC_X_SIZE * _jour->zoom_level,DEF_PIC_X_SIZE *_jour->zoom_level );
		PostMessage(REDRAW_ME);
 		break;
	case ZOOM_50:
		_jour->zoom_level = 0.5;
		inside_view->SetScale(0.5);
		inside_view->ResizeTo(DEF_PIC_X_SIZE * _jour->zoom_level,DEF_PIC_X_SIZE *_jour->zoom_level );
		PostMessage(REDRAW_ME);
 		break;
	case REDRAW_ME:
 		inside_view->Invalidate(inside_view->Bounds());
 		break;
	case DRAW_ACTIVE_COUNTRY:
 		la_zone = 	_country[_jour->active_country]->limit;
   	  	inside_view->Multiply(la_zone); //multiplie la zone séléectionée par _jour->zone
		inside_view->Invalidate(la_zone);
		break;
	case CT_NEXT:
		if (_jour->active_country == _jour->country_last)
			_jour->active_country=_jour->country_first;
		else
			_jour->active_country++;
		_jour->mainWin->PostMessage(SHOW_SELECT);
		_jour->infoWin->PostMessage(DRAW_INFO);
	    break; 
	case CT_PREV:
		if (_jour->active_country == _jour->country_first)
			_jour->active_country=_jour->country_last;
		else
			_jour->active_country--; //si on peut pas faire la suivante on recommence
		_jour->mainWin->PostMessage(SHOW_SELECT);
		_jour->infoWin->PostMessage(DRAW_INFO);
	    break; 
	case MENU_EDIT_REFRESH:
		inside_view->MultiplyAll();
		break;		
	case MENU_POLITIC:
		//afficher fenetre edit politique
		NotImplemented();
		break;		
 	case MENU_GAME_EDIT:
		if (_jour->edit_mode==OFF)
		{
			_jour->edit_mode=ON;
			_jour->pause=ON;
			_jour->game_started=OFF;
			_jour->jump_days=1; //sinon ça merde quand on ressort
			_jour->edit_menu->SetEnabled(true);
		
			//CREER fenetre edit
			BRect rect;
			rect.Set(16,16,EDIT_X_SIZE-1, EDIT_Y_SIZE-1);
			editWindow = new EditWindow(rect,_country,_group,_politic,_jour);
	    
	   		editWindow ->Lock();		
			editWindow ->Show();		
			editWindow ->Unlock();		
			_jour->mainWin->PostMessage(UPDATE_TITLE);
		}
		else
			PostMessage(UPDATE_TITLE);
		break; 
	case BUTTON_BUY:
		if(_group[_country[_jour->active_country]->group]->player==COMPUTER) 
			beep();
		else
		{
			buyWindow = new BuyWindow(_country[_jour->active_country],_jour);
	    
		    buyWindow ->Lock();		
			buyWindow ->Show();		
			buyWindow ->Unlock();		
		}
		PostMessage(new BMessage(SHOW_SELECT));
		break;	
	case BUTTON_SET:
  		if(_group[_country[_jour->active_country]->group]->player==COMPUTER) 
			beep();
		else
		{
			setWindow = new OrderWindow(_country[_jour->active_country],_jour);
	    	setWindow ->Lock();		
	    	setWindow ->Show();		
	    	setWindow ->Unlock();	
	    }	
	   	PostMessage(new BMessage(SHOW_SELECT));
		break;	
	case SHOW_SELECT:
 		inside_view->Invalidate(_jour->rect_update_select);
 		break;
	case MENU_GAME_RESTART:	//MENUS GAME
		Restart();
		break;   
  	case MENU_LOAD:
   	  	if(panneau_load==NULL) 
   	  	{
   	  		((W6Application *)be_app)->app_dir();
				
		  	panneau_load = new BFilePanel(B_OPEN_PANEL,NULL,NULL,B_FILE_NODE,false,NULL,NULL,false,true);
			panneau_load->SetPanelDirectory(_jour->dossier_app);
		}
  		panneau_load->Show();
   	  	break;
	case MENU_SAVE:
   	  	if(panneau_save==NULL)
   	  	{
   	  		((W6Application *)be_app)->app_dir();
		  	panneau_save = new BFilePanel(B_SAVE_PANEL,NULL,NULL,B_FILE_NODE,false,NULL,NULL,false,true);
			panneau_save->SetPanelDirectory(_jour->dossier_app);
  	 	}
  	 	panneau_save->Show();
  		break;
	case MENU_GAME_SET_DAY_RATE:
		speedWindow = new SpeedWindow(_jour);
	    speedWindow ->Lock();	
	    speedWindow ->Show();	
	    speedWindow ->Unlock();	
		break;   
	case B_QUIT_REQUESTED:
	case MENU_GAME_QUIT:
		be_app->Lock();
		be_app->PostMessage(B_QUIT_REQUESTED);
		be_app->Unlock(); //sinon ça plante	
		break;   
	case MENU_GAME_PAUSE:
   		if(_jour->pause==OFF)
   			_jour->pause=ON;
   		else
   			_jour->pause=OFF; 
   		PostMessage(REDRAW_ME);
		break;   
	case MENU_LEVEL_EASY:	//MENUS LEVEL
   	  	_jour->game_level=EASY;
   		break;   
	case MENU_LEVEL_NORMAL:
   	  	_jour->game_level=NORMAL;
   		break;   
	case MENU_LEVEL_HARD:
   	  	_jour->game_level=HARD;
   	   	break;   
   	case MENU_LEVEL_TOO_HARD:
   		xalert = new BAlert("","YOU LOSE.\nSorry but you knew it was going to be hard!", "Exit!"); 
   		xalert->Go();
   	  	Restart();
   	  	break;
   	case MENU_SCENARIO:
   	   	NotImplemented();
   	  	break;
	case MENU_PAINT_MODE:
		if(_jour->paint_mode==OFF)
		{
			_jour->paint_mode=ON;
			paintmode->SetLabel("BACK TO SELECT MODE");
		}
		else
		{
			_jour->paint_mode=ON;
			paintmode->SetLabel("Paint mode");
			_jour->paint_mode=OFF;
		}
   	  	break;	
  	case LOG_IMPORTANT_MESSAGES:
   	 	if(_jour->full_log == OFF)
   	 		_jour->full_log=ON;
 	  	else
 	  		_jour->full_log =OFF;  	
   	  	break;
  	case MENU_ABOUT:
   	  	My_AboutBox();
  		break;   
  	case MENU_DOC: //on lance netpositive
   	  	OpenHelp();
   	  	break;   
	case MULTIPLY_RECT:
		{
   	  		if(message->FindRect("zone",&la_zone)!=B_OK)
   	  			return;
   	  		
   	  		//multiplie la zone séléectionée par _jour->zone
   	  		inside_view->Multiply(la_zone);
		}
		break;
	case MULTIPLY_ALL:
		inside_view->MultiplyAll();
		break;
	case B_KEY_DOWN:
		ShortCuts(message);
		break;
   	default:
		// Call inherited if we didn't handle the message
		BWindow::MessageReceived(message);
	}//fin switch;
//SI ON A UN ILLEGAL JUMP PAST INITIALIZER c'est à cause de case MENU_DOC
//be_roster->Launch... faut qu'il soit dans une fonction externe (c'est le cas maintenant)
}

//--------------------------------------


void W6Window::My_AboutBox()
{
   BAlert *alert = new BAlert("WW6","What Went Wrong? it's a World Wide War! V1.7\n\n© 1998-1999 by Santiago Lema\nsantiago.lema@cryogen.ch\n http://www.beoscentral.com/home/free/","Sucks!"); 
   alert->Go();
}

void W6Window::NotImplemented()
{
	BAlert *alert = new BAlert("","Sorry, still not Implemented","Oompf!");
	alert->Go();
}

void W6Window::OpenHelp()
{
	//si tu as envoies un message depuis le message received
	//tu as un warning à la compilation (past initializer)
	//donc faut une fonction, comme ici.
	((W6Application *)be_app)->app_dir(); //met le dossier de l'app dans _jour->dossier_app
	char name[255];
	char filename[255];
	sprintf(name,_jour->dossier_app); //recupere le nom en string ;-)pour le modifier
  	sprintf(filename,"file://%s/help/index.html",name);

   	BMessage urlmsg( B_ARGV_RECEIVED );
   	urlmsg.AddString( "argv", "" );
   	urlmsg.AddString( "argv",filename );
   	urlmsg.AddInt32(  "argc", 2 );
   	be_roster->Launch("application/x-vnd.Be-NPOS", &urlmsg );  	
}


void W6Window::FrameResized(float width, float height)
{
	//set le v_rect pour le scroll
	inside_view->v_rect = Bounds();
	inside_view->v_rect.right-= 0;
	inside_view->v_rect.bottom-= HISTORY_Y_SIZE;

	//remet la taille possible des scrollbars au nécessaire
	_jour->scroll_hori->SetRange(0,DEF_PIC_X_SIZE-(width)); 
	_jour->scroll_verti->SetRange(0,DEF_PIC_Y_SIZE-(height-mb_height-HISTORY_Y_SIZE));

	//-70 c'est la taille du toptxt dans infoview
	_jour->interligne = (uint16) ((height-70)/36);
	_jour->infoWin->PostMessage(DRAW_INFO);
}

void W6Window::Restart()
{
	BAlert *alert = new BAlert("","Are you sure you wish to start it all again?","Cancel", "Do it"); 
	int32 button_index;
 
	//les boutons ont tou_jours les valeurs 0,1,2 (trois boutons max)
	switch(button_index = alert->Go())
	{
    case 1:
    	alert = new BAlert("","Sorry, to start a new game you'll have to reload","Oompf!");
    	alert->Go();
 		break;
	}
}

void W6Window::ShortCuts(BMessage *msg)
 {
	int8 bytes[3];
    int32 key;
    int32 modi;
    
    msg->FindInt32 ("modifiers", &modi); 
    msg->FindInt32 ("key", &key); 
    msg->FindInt8  ("byte", &bytes[0]); 
	//POUR KEYS SIMPLES
	if(modifiers() & B_SHIFT_KEY) 
	{
		switch(bytes[0])
		{
		case B_TAB & B_SHIFT_KEY:
			PostMessage(CT_PREV);//en arrière
			break;
		}
		//sinon il fait les autres après
		return;
	}		
			
	switch(bytes[0])
    {
    //ON AVANCE de 10 à 100 %
    case B_TAB:
		PostMessage(CT_NEXT);	//en avant
        break;        
    case 'b': 
		PostMessage(BUTTON_BUY);	
        break;        
	case 't': 
		PostMessage(BUTTON_SET);	
        break;        
	case 's': 
		PostMessage(MENU_GAME_SET_DAY_RATE);	
        break;        
	case 'p': 
		PostMessage(MENU_GAME_PAUSE);	
        break;        
    }//fin switch 

	switch(key)
    { 
    case B_F1_KEY: 
		PostMessage(MENU_DOC);
        break;      
 	}//fin switch 
 }