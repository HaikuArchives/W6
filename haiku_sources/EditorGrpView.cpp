#include "EditorGrpView.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "politic.h"
#include <StringView.h>
#include <ListView.h>
#include <Button.h>
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <ScrollView.h>
#include <ColorControl.h>
#include <TextControl.h>
#include <Window.h>

EditorGrpView::EditorGrpView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id[MAX_POLITIC],Day *compteur)
: BView(r, "", flags, B_WILL_DRAW )
{

	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	SetViewColor(216,216,216);   

	BRect rect;
    nom_file  = new BStringView	(BRect(100,4+12,250,4+12+12), "","xxx.raw");

	AddChild (nom_file);
	
	rect.Set( 100, 30, 100+100, 30+8);
	BButton* button_load_flag = new BButton( rect,"",	"Load flag...", new BMessage(FLAG_LOAD) );          								 				 									 	
	AddChild(button_load_flag);

	BMenu *player_menu = new BMenu("Player");
	player_menu->AddItem(new BMenuItem("Computer", new BMessage(SET_COMPUTER_PLAYER)));
	player_menu->AddItem(new BMenuItem("Player 01", new BMessage(SET_PLAYER_01)));
	player_menu->AddItem(new BMenuItem("Player 02", new BMessage(SET_PLAYER_02)));
	player_menu->AddItem(new BMenuItem("Player 03", new BMessage(SET_PLAYER_03)));
	player_menu->AddItem(new BMenuItem("Player 04", new BMessage(SET_PLAYER_04)));
	player_menu->AddItem(new BMenuItem("Player 05", new BMessage(SET_PLAYER_05)));
	player_menu->AddItem(new BMenuItem("Player 06", new BMessage(SET_PLAYER_06)));
	player_menu->AddItem(new BMenuItem("Player 07", new BMessage(SET_PLAYER_07)));
	player_menu->AddItem(new BMenuItem("Player 08", new BMessage(SET_PLAYER_08)));

	rect.OffsetBy(110,0);
	player_menu->SetLabelFromMarked(true); //pour mettre nom actif en titre
	player = new BMenuField(rect,"",NULL,player_menu,B_FOLLOW_ALL,B_WILL_DRAW);
	player_menu->SetLabelFromMarked(true); //pour mettre nom actif en titre
	AddChild(player);

	
	col_control = new BColorControl(BPoint(ORI_X_POS,ORI_Y_POS), B_CELLS_32x8, 4, "cc", new BMessage(GRP_COLOR_CHANGED), false); 
	col_control->SetValue(_group[_jour->active_group]->grp_color);	
	AddChild(col_control);
	
	rect.Set(ORI_X_POS,ORI_Y_POS+COL_H,EDIT_GRP_X_SIZE-ORI_X_POS,ORI_X_POS+6+COL_H);
	name_control = new BTextControl(rect, "", "Group Name", _group[_jour->active_group]->Name(),new BMessage(SET_GRP_LIST_EDIT) );
    AddChild(name_control);
	
	rect.OffsetBy(0,32);
  	rect.bottom+=200;
  	rect.right-=B_V_SCROLL_BAR_WIDTH;

 	pol_list = new BListView(rect, "", B_SINGLE_SELECTION_LIST); 
  	AddChild(new BScrollView("", pol_list, B_FOLLOW_LEFT | B_FOLLOW_TOP_BOTTOM, 0, false, true));
  	pol_list->SetSelectionMessage(new BMessage(EDIT_GRP_UPDATE));

	//ADD
	rect.Set( 5, 312, 5+70, 312+10);
	button_AddPol = new BButton( rect,"",	"Add Pol", new BMessage( BUTTON_ADD_POL ) );          								 				 									 	

	//ADD
	rect.OffsetBy(70,0);
	button_EdtPol = new BButton( rect,"",	"Edit", new BMessage( BUTTON_EDT_POL ) );          								 				 									 	

	//DEL
	rect.OffsetBy(70,0);
	button_DelPol = new BButton( rect,"",	"Delete", new BMessage( BUTTON_DEL_POL) );    

	AddChild(button_AddPol);
	AddChild(button_DelPol);
	AddChild(button_EdtPol);
}

void EditorGrpView::UpdateGrpEdit() //met les valeurs de l'écran dans le group
{
	uint32 index;

	_jour->active_group=_country[_jour->active_country]->group;
	Group *grp=_group[_jour->active_group];
	_jour->active_politic=grp->politic;

	grp->grp_color=col_control->ValueAsColor();
	grp->SetName(name_control->Text());

	//active politic
	index = pol_list->CurrentSelection(); //index dans la liste ctry
	
	//test si valide et on change les datas 
	//seulement si quelque chose est sélectionné
	//sinon crash quand on selecte un autre élément (par ex. player)
	if((index+(_jour->politic_first) >= _jour->politic_first)	&& (index+(_jour->politic_first) <= _jour->politic_last) )
	{
		_jour->active_politic = index+(_jour->politic_first);
		grp->politic = _jour->active_politic;	
	}
	else
	{//sinon on reselect le juste
		pol_list->Select(_jour->active_politic-(_jour->politic_first));
		pol_list->ScrollToSelection();
	}
	
	sprintf(grp->flag_file_name,nom_file->Text());
	_jour->mainWin->PostMessage(new BMessage(DRAW_ACTIVE_COUNTRY)); //Draw active country
	_jour->infoWin->PostMessage(new BMessage(DRAW_INFO));    //Draw InfoView
}

void EditorGrpView::SetGrpEdit() //met les valeurs du group à l'écran
{
	_jour->active_group   = _country[_jour->active_country]->group;
	_jour->active_politic = _group[_jour->active_group]->politic;

	//_group[_country[_jour->active_country]->group]->politic = _jour->active_politic;	
    Group *grp=_group[_jour->active_group];
	
	col_control->SetValue(grp->grp_color);
	name_control->SetText(grp->Name());

	nom_file->SetText(grp->flag_file_name);
	
	UpdatePolitics();

	//liste des politics
	pol_list->Select(_jour->active_politic-(_jour->politic_first));
	pol_list->ScrollToSelection();

	_jour->infoWin->PostMessage(new BMessage(DRAW_INFO));    //Draw InfoView
	Draw(Bounds()); //pour le drapeau
}



void EditorGrpView::Draw(BRect update_rect)
{
	if(_group[_country[_jour->active_country]->group]->flag_ptr != NULL)
		DrawBitmap(_group[_country[_jour->active_country]->group]->flag_ptr, BPoint(4,4));
	else 
    {
    	SetHighColor(100,100,100);
     	FillRect(BRect(4,4,4+FLAG_X_SIZE-1,4+FLAG_Y_SIZE-1),B_SOLID_HIGH);
    }
}



void EditorGrpView::UpdatePolitics()
{
	//si il y a aucune select crash!
	int32 old_set = pol_list->CurrentSelection(); //index dans la liste ctry
	pol_list->RemoveItems(0,pol_list->CountItems()); //efface tout

	//on trouve les groupes et on les met dans la liste
	unsigned char temp_pol = _jour->politic_first;
    while (temp_pol != _jour->politic_last+1)
    {
 		pol_list->AddItem(new BStringItem(_politic[temp_pol]->Name()));
		temp_pol++;    
    }

	if (pol_list->CountItems()-1 < old_set)
		old_set = pol_list->CountItems()-1;
	pol_list->Select(old_set);
}
