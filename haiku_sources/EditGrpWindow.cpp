#include "EditGrpWindow.h"
#include "W6.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "EditorGrpView.h"
#include "EditorView.h"
#include "EditorPolView.h"
#include "EditPolWindow.h"
#include <View.h>
#include <FilePanel.h>
#include <Alert.h>
#include <Beep.h>


EditGrpWindow::EditGrpWindow(Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BWindow(_jour->find_win_pos(EDIT_GRP_X_SIZE,EDIT_GRP_Y_SIZE),"Edit Group", B_FLOATING_WINDOW,  B_NOT_RESIZABLE | B_NOT_ZOOMABLE) 
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	
	_jour->edit_grpWin=this; //pour pouvoir recevoir des messages
	ed_grp_view = new EditorGrpView(Bounds(), B_FOLLOW_ALL |B_WILL_DRAW,_country,_group,_politic,_jour);
	AddChild(ed_grp_view);

    ed_grp_view->SetGrpEdit(); //met les valeurs actuelles dans les cases
	_jour->edit_grp_win_exists=ON;
	
	
}

EditGrpWindow::~EditGrpWindow()
{
_jour->edit_grp_win_exists=OFF;

if (_jour->edit_pol_win_exists==ON) 
	{	polWin->Close();
		_jour->edit_pol_win_exists=OFF;
	}
	

}


void EditGrpWindow::MessageReceived(BMessage *message)
{


	// Print the message to see its contents
	message->PrintToStream();

 	switch ( message->what )
 	{
	
		case SET_COMPUTER_PLAYER: 	_group[_jour->active_group]->player = COMPUTER; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_01: 		_group[_jour->active_group]->player = PLAYER_01; 
		_jour->player_group = _jour->active_group;		
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_02: 		_group[_jour->active_group]->player = PLAYER_02; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_03: 		_group[_jour->active_group]->player = PLAYER_03; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_04: 		_group[_jour->active_group]->player = PLAYER_04; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_05: 		_group[_jour->active_group]->player = PLAYER_05; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_06: 		_group[_jour->active_group]->player = PLAYER_06; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_PLAYER_07: 		_group[_jour->active_group]->player = PLAYER_07; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
	
		case SET_PLAYER_08: 		_group[_jour->active_group]->player = PLAYER_08; 
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
		
		case SET_GRP_EDIT:	
		ed_grp_view->SetGrpEdit(); //affiche les valeurs actuelles dans les cases
		break;

		case UPDATE_GRP_EDIT:	
		ed_grp_view->UpdateGrpEdit();
		break;
		
		case GRP_COLOR_CHANGED:
		ed_grp_view->UpdateGrpEdit(); //FAUT UPDATER LES DATAS SI ON VEUT VOIR L'effet!
		_jour->mainWin->PostMessage(new BMessage (MULTIPLY_ALL));
		_jour->infoWin->PostMessage(new BMessage (DRAW_INFO));
		break;
	
		case SET_GRP_LIST_EDIT:
		ed_grp_view->UpdateGrpEdit(); //FAUT UPDATER LES DATAS SI ON VEUT VOIR L'effet!
		ed_grp_view->SetGrpEdit(); 
		_jour->editWin->PostMessage(SET_GRP_LIST_EDIT);
  		break;

		case SET_POL_LIST_EDIT:
		ed_grp_view->UpdatePolitics(); 
		break;

 		case EDIT_GRP_UPDATE:
  		ed_grp_view->UpdateGrpEdit(); //met valeurs de l'écran dans le grp
		_jour->infoWin->PostMessage(DRAW_INFO);
		//affiche le groupe actif dans edit grp win
		if (_jour->edit_pol_win_exists==ON) _jour->edit_polWin->PostMessage(SET_POL_EDIT);
  		break;
		
		break;
		
		case FLAG_LOAD:
 				 ((W6Application *)be_app)->app_dir();
				 flag_load = new BFilePanel(B_OPEN_PANEL,NULL,NULL,B_FILE_NODE,false,NULL,NULL,false,true);
				 flag_load->Window()->SetTitle("Choose a flag file (80 x 40)");
				 flag_load->Window()->SetFeel(B_FLOATING_APP_WINDOW_FEEL);//DEVANT TOUT
				 char str[2048];
				 sprintf(str,_jour->dossier_app);
				 strcat(str,_jour->dossier_scenario);
				 flag_load->SetPanelDirectory(str);
				_jour->is_flag_load = ON; //sinon refsreceived le prend pour une backup

				 flag_load->Show();
 		 break;
 		 

		//------------------------------------
		
		case BUTTON_ADD_POL:
		 if (_jour->politic_last != MAX_POLITIC) 
			{
				 unsigned char nn=(_jour->politic_last)+1;
				 _politic[nn]  = new Politic ("New Politic",nn);
   			 	 _jour->politic_last++;
		 		 _group[_jour->active_group]->politic = _jour->politic_last;
 
				 ed_grp_view->UpdatePolitics();

		if (_jour->edit_pol_win_exists==ON)
			{
			polWin ->Lock();
			polWin->ed_pol_view->SetPolitic();
			polWin->ed_pol_view->SetPolEdit();
			polWin ->Unlock();
			}

  		  }
		 else
		 {BAlert *alert = new BAlert("","This would exceed maximum number of politics allowed!","Oompf!");alert->Go();}
		 
  		break;

		case BUTTON_EDT_POL:
		ed_grp_view->SetGrpEdit();	  		 		

		if (_jour->edit_pol_win_exists==OFF) //si existe pas déja
		{
		_jour->edit_pol_win_exists=ON;
		polWin = new EditPolWindow(_country,_group,_politic,_jour);
		polWin->ed_pol_view->SetPolEdit();
		polWin ->Lock();		
	    polWin ->Show();		
 		polWin ->Unlock();				
		}
		else beep();
		break;
		
		case BUTTON_DEL_POL:
		
		if (_jour->politic_first != _jour->politic_last) //min un grp
						{
		char str[255];
		char str2[255];
		sprintf(str,"Confirm deletion of ");
		sprintf(str2,_politic[_jour->active_politic]->Name());
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
					//on copie le dernier pol à la place du supprimé 
   					unsigned char pol     = _jour->active_politic;
   					unsigned char new_pol = _jour->politic_first; //pour l'instant
   					
   					
   					//groupe de la pol détruits vers un autre politic (new_pol)
   					unsigned char the_grp = _jour->group_first; //pour pointer dans list pays
					while (the_grp != _jour->group_last+1) 
						{
						 if (_group[the_grp]->politic==pol) _group[the_grp]->politic=new_pol;
						 the_grp++;
						 }
   						//echange groupe avec le dernier groupe
   					
   					unsigned char keep_nb = _politic[pol]->nb_pol; //on garde le nb du groupe
   					*_politic[pol]     = *_politic[_jour->politic_last]; 
   					_politic[pol]->nb_pol=keep_nb; //on remet le meme numéro de groupe
   					
   					//pays du groupe last au nouvel emplacement
   					the_grp = _jour->group_first; //pour pointer dans list pays
					while (the_grp != _jour->group_last+1) 
						{
						 if (_group[the_grp]->politic==_jour->politic_last) _group[the_grp]->politic=keep_nb;
						 the_grp++;
						 }
   					   					
					//mise à _jour liste
		 			if (_jour->politic_last > _jour->politic_first) _jour->politic_last--;
		 			_group[_jour->active_group]->politic = _jour->politic_first;
					
					//TRes important de locker sinon crash
					ed_grp_view->UpdatePolitics();
					if (_jour->edit_pol_win_exists==ON)
					{
						polWin ->Lock();
						polWin->ed_pol_view->SetPolitic();
						polWin->ed_pol_view->SetPolEdit();
						polWin ->Unlock();
					}
					break;
		
					}
			}//fin if min deux grp
			 else
		 {BAlert *alert = new BAlert("","You need at least one politic!","Oompf!");alert->Go();}
		 
		break;//fin button DEL	
		
		
 		 		
		default:
   		// Call inherited if we didn't handle the message
   		BWindow::MessageReceived(message);
        break;
		}//end switch

}//fin message received
