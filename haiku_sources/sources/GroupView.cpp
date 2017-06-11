#include "GroupView.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "TxtView.h"
#include <Window.h>
#include <Application.h>

GroupView::GroupView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BView(r, "", B_FOLLOW_TOP, B_WILL_DRAW)
{
  
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	


//----AFFICHAGE DES INFOS
    SetViewColor(0,0,0);
//------------------------


#define TOP_TXT 65
#define INDENT 2 //bord gauche
unsigned char line_pos=0;

BRect rect;

line_pos=0;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
grp_name_view = new TxtView(rect, "grp", "xxx");
AddChild(grp_name_view);

line_pos=1;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
player_view = new TxtView(rect, "player_view", "xxx");
AddChild(player_view);



}

void GroupView::Draw(BRect update_rect)
{
if (_group[grp]->flag_ptr != NULL)
DrawBitmap(_group[grp]->flag_ptr, BPoint(54,11));
else 
     {SetHighColor(100,100,100);
     FillRect(BRect(54,16,54+FLAG_X_SIZE-1,16+FLAG_Y_SIZE-1),B_SOLID_HIGH);
     }
}

void GroupView::UpdateGroupInfo(uint8 which_grp)
{
grp = which_grp;

Window()->Lock();
be_app->Lock();

	char str[255];
	char str2[255];
	
	
	rgb_color couleur_groupe = _group[grp]->grp_color; //non il y pas de gestionnaire de café installé ;-)

//-------------------------------------------------------------------------------------
	//RVBA
	grp_name_view->SetHighColor(couleur_groupe); 
	//%G affiche que les virgules nécessaires
	sprintf(str,_group[grp]->Name());
	sprintf(str2," (%.3g %%)",_group[grp]->power_percent);
	strcat(str,str2);
	//pour arrondir vers le bas: floor(xxx)
	grp_name_view->SetText(str);

	sprintf(str,_politic[_group[grp]->politic]->Name());
	
	switch(_group[grp]->player)
	{
	case COMPUTER:	sprintf(str2,", (Computer)");	break;
	case PLAYER_01:	sprintf(str2,", (Player 1)");	break;
	case PLAYER_02:	sprintf(str2,", (Player 2)");	break;
	case PLAYER_03:	sprintf(str2,", (Player 3)");	break;
	case PLAYER_04:	sprintf(str2,", (Player 4)");	break;
	case PLAYER_05:	sprintf(str2,", (Player 5)");	break;
	case PLAYER_06:	sprintf(str2,", (Player 6)");	break;
	case PLAYER_07:	sprintf(str2,", (Player 7)");	break;
	case PLAYER_08:	sprintf(str2,", (Player 8)");	break;

	}
	strcat(str,str2);
	player_view->SetText(str);

	
	Draw(Bounds()); //pour le drapeau
//---------------------------------------------

Window()->Unlock();
be_app->Unlock();

}
