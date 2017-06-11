#include "EditWindow.h" 
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "EditorView.h"
#include "EditorGrpView.h"
#include "EditGrpWindow.h"
#include <ScrollView.h>
#include <Menu.h>
#include <Alert.h>
#include <Beep.h>
#include <Message.h>

EditWindow::EditWindow(BRect frame,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BWindow(frame, "Edit Country Data", B_FLOATING_WINDOW,B_NOT_H_RESIZABLE | B_ASYNCHRONOUS_CONTROLS) 
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id; 
	_politic = Politic_id;
	
	_jour->editWin=this; //pour pouvoir recevoir des messages
			
//-------------------------------------
	


	BRect rect;
	rect.Set(0,0,EDIT_X_SIZE-(2*B_V_SCROLL_BAR_WIDTH)-4,EDIT_Y_SIZE-B_V_SCROLL_BAR_WIDTH-2);
	ed_view = new EditorView(rect, B_FOLLOW_ALL |B_WILL_DRAW,
						  _country,_group,_politic,_jour);

	BScrollView *scroll_view=new BScrollView("", ed_view, B_FOLLOW_ALL, 0, false, true);
	AddChild(scroll_view);

//par défaut les scroll bars vont jusqu'à 1000 donc faut les setter
BScrollBar *verti = scroll_view->ScrollBar(B_VERTICAL);

//le range de scroll est égal à la taille de la pic moins la partie affichée
verti->SetRange(0, EDIT_Y_SIZE-110); 

_jour->infoWin->PostMessage(DRAW_INFO);
ed_view->SetEdit();


SetSizeLimits(EDIT_X_SIZE-B_V_SCROLL_BAR_WIDTH-3,EDIT_X_SIZE-B_V_SCROLL_BAR_WIDTH-3, //min max width 
         	  128, 2000);    //min max height

ed_view->SelectedCt(); 
 
}

EditWindow::~EditWindow()
{

if (_jour->edit_grp_win_exists==ON) 
	{	grpWin->Close();
		_jour->edit_grp_win_exists=OFF;
	}
	
_jour->edit_mode=OFF;
_jour->pause=OFF;
_jour->game_started=ON;
_jour->edit_menu->SetEnabled(false);
_jour->mainWin->PostMessage(UPDATE_TITLE);
		
//surtout pas faire un Close() ici! On est déjà en train de killer la win
}

void EditWindow::MessageReceived(BMessage *message)
{

	// Print the message to see its contents
	message->PrintToStream();

 	switch ( message->what )
 	{
 	
		case SET_GRP_LIST_EDIT:
		ed_view->UpdateGroups(); 
		break;
		 	
 		case SET_EDIT:	
		ed_view->SetEdit(); //affiche les valeurs actuelles dans les cases
		break;

 		case EDIT_UPDATE:
 		ed_view->UpdateEdit(); //update les données d'après les cases
 		_jour->infoWin->PostMessage(DRAW_INFO);
		//affiche le groupe actif dans edit grp win
		if (_jour->edit_grp_win_exists==ON) _jour->edit_grpWin->PostMessage(SET_GRP_EDIT);
  		break;
		
		case EDIT_CT_SELECT:
 		ed_view->SelectedCt();
 		break;
		
		case BUTTON_NEXT:
		if (_jour->active_country == _jour->country_last) _jour->active_country=_jour->country_first;
		else _jour->active_country++;
		ed_view->SetEdit();
		_jour->mainWin->PostMessage(SHOW_SELECT);
		_jour->infoWin->PostMessage(DRAW_INFO);
	    break; 

 		case BUTTON_PREV:
		if (_jour->active_country == _jour->country_first) _jour->active_country=_jour->country_last;
		else _jour->active_country--; //si on peut pas faire la suivante on recommence
		ed_view->SetEdit();
		_jour->mainWin->PostMessage(SHOW_SELECT);
		_jour->infoWin->PostMessage(DRAW_INFO);
	    break; 
	    
	    
 		case BUTTON_GEN: //genere une armée
 		_country[_jour->active_country]->set_army(); //génére valeurs par défaut
 		_country[_jour->active_country]->default_army(); //les mets...
 		ed_view->SetEdit();
		_jour->infoWin->PostMessage(DRAW_INFO);
 		break;


		case BUTTON_ADD_GRP:
		 if (_jour->group_last != MAX_GROUP) //min un grp
			{
				 rgb_color couleur= (rgb_color) {0,255,0,0}; //vert pétant
				 unsigned char nn=(_jour->group_last)+1;
				 _group[nn]  = new Group      (COMPUTER,"New Group",nn,couleur,PO_ANARCHY,NULL,_jour);

				 	_jour->group_last++;
		 			_country[_jour->active_country]->group = _jour->group_last;

				ed_view->UpdateGroups();

		if (_jour->edit_grp_win_exists==ON)
			{
			grpWin ->Lock();
			grpWin->ed_grp_view->SetGrpEdit();
			grpWin ->Unlock();
			}
		_jour->mainWin->PostMessage(DRAW_ACTIVE_COUNTRY);

  		  }
		 else
		 {BAlert *alert = new BAlert("","This would exceed maximum number of groups allowed!","Oompf!");alert->Go();}
		 
  		break;

		case BUTTON_EDT_GRP:
		ed_view->SetEdit();	  		 		

		if (_jour->edit_grp_win_exists==OFF) //si existe pas déja
		{
		_jour->edit_grp_win_exists=ON;
		grpWin = new EditGrpWindow(_country,_group,_politic,_jour);
		grpWin->ed_grp_view->SetGrpEdit();
		grpWin ->Lock();		
	    grpWin ->Show();		
 		grpWin ->Unlock();				
		}
		else beep();
		break;
		
		case BUTTON_DEL_GRP:
		
		if (_jour->group_first != _jour->group_last) //min un grp
						{
		char str[255];
		char str2[255];
		sprintf(str,"Confirm deletion of ");
		sprintf(str2,_group[_jour->active_group]->Name());
		strcat(str,str2);
		BAlert *alert = new BAlert("", str,"Cancel", "Go on"); 
		int32 button_index;
   
   			switch(button_index = alert->Go())
   					{
   					case 0:
   					//back to the jeu
   					break;
		
					case 1:
					//SUPPRESSION DU GROUPE
					//on copie le dernier groupe à la place du supprimé 
   					unsigned char grp     = _jour->active_group;
   					unsigned char new_grp = _jour->group_first; //pour l'instant
   					
   					
   					//pays du groupe détruits vers un autre groupe (new_grp)
   					unsigned char the_ctry = _jour->country_first; //pour pointer dans list pays
					while (the_ctry != _jour->country_last+1) 
						{
						 if (_country[the_ctry]->group==grp) _country[the_ctry]->group=new_grp;
						 the_ctry++;
						 }
   						//echange groupe avec le dernier groupe
   					
   					unsigned char keep_nb=_group[grp]->nb; //on garde le nb du groupe
   					*_group[grp]     = *_group[_jour->group_last]; 
   					_group[grp]->nb=keep_nb; //on remet le meme numéro de groupe
   					
   					//pays du groupe last au nouvel emplacement
   					the_ctry = _jour->country_first; //pour pointer dans list pays
					while (the_ctry != _jour->country_last+1) 
						{
						 if (_country[the_ctry]->group==_jour->group_last) _country[the_ctry]->group=keep_nb;
						 the_ctry++;
						 }
   					   					
					//mise à _jour liste
		 			if (_jour->group_last > _jour->group_first) _jour->group_last--;
		 			_country[_jour->active_country]->group = _jour->group_first;
					
					//TRes important de locker sinon crash
					ed_view->UpdateGroups();
					if (_jour->edit_grp_win_exists==ON)
					{
						grpWin ->Lock();
						grpWin->ed_grp_view->SetGrpEdit();
						grpWin ->Unlock();
					}
		 			
					_jour->mainWin->PostMessage(MENU_EDIT_REFRESH);
					break;
		
					}
			}//fin if min deux grp
			 else
		 {BAlert *alert = new BAlert("","You need at least one group!","Oompf!");alert->Go();}
		 
		break;//fin button DEL	
		

 		 		
		default:
   		// Call inherited if we didn't handle the message
   		BWindow::MessageReceived(message);
        break;
		}//end switch

}//fin message received

void EditWindow::NotImplemented()
{
   	  	BAlert *alert = new BAlert("","Sorry, still not Implemented","Oompf!");alert->Go();
 
}

void EditWindow::FrameResized(float width, float height)
{
//remet la taille possible des scrollbars au nécessaire
ed_view->ScrollBar(B_VERTICAL)->SetRange(0, (ed_view->Bounds().Height())-height);

}




