#include "EditorView.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "politic.h"
#include <ListView.h>
#include <TextControl.h>
#include <Button.h>
#include <StringView.h>
#include <ScrollView.h>
#include <CheckBox.h>
#include <Window.h>

EditorView::EditorView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id[MAX_POLITIC],Day *compteur)
: BView(r, "", flags, B_WILL_DRAW | B_FOLLOW_TOP_BOTTOM)
{

	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
    BRect rect;

	SetViewColor(216,216,216);   
   	numero = new BStringView(BRect(100,188,120,204), "","");
	numero->SetAlignment(B_ALIGN_CENTER);
	AddChild(numero);

   	rect.Set( 8, 8, 4+210-B_V_SCROLL_BAR_WIDTH, 8+120);
   
   	list = new BListView(rect, "", B_SINGLE_SELECTION_LIST); 
   	AddChild(new BScrollView("", list, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true));
   	list->SetSelectionMessage(new BMessage(EDIT_UPDATE));
	//ADD
	rect.Set( 5, 134, 5+70, 148);
	button_AddGrp = new BButton( rect,"",	"Add Group", new BMessage( BUTTON_ADD_GRP ) );          								 				 									 	

	//ADD
	rect.OffsetBy(70,0);
	button_EdtGrp = new BButton( rect,"",	"Edit", new BMessage( BUTTON_EDT_GRP ) );          								 				 									 	

	//DEL
	rect.OffsetBy(70,0);
	button_DelGrp = new BButton( rect,"",	"Delete", new BMessage( BUTTON_DEL_GRP) );    

	//NeXt
	rect.OffsetBy(-140,OFFSET_Y*2);
	button_Prev = new BButton( rect,"",	"Prev", new BMessage( BUTTON_PREV ) );          								 				 									 	

	//previous
	rect.OffsetBy(132,0);
	button_Next = new BButton( rect,"",	"Next", new BMessage( BUTTON_NEXT) );          								 				 									 	

	numero = new BStringView(BRect(100,188,120,204), "","222");
	numero->SetAlignment(B_ALIGN_CENTER);

	AddChild(numero);
	AddChild(button_Next);
	AddChild(button_Prev);
	AddChild(button_AddGrp);
	AddChild(button_DelGrp);
	AddChild(button_EdtGrp);

	rect.Set( 4, 220, 4+210, 220+6);
	name_control = new BTextControl(rect, "", "Name", "XXX", new BMessage(EDIT_UPDATE) );
	AddChild(name_control);

	//DONNEES GENERALES
	rect.OffsetBy(0,OFFSET_Y);
	rect.OffsetBy(0,OFFSET_Y);
	population_control = new BTextControl(rect, "", "Population", "0", new BMessage(EDIT_UPDATE) );
	AddChild(population_control);
		
	rect.OffsetBy(0,OFFSET_Y);
	money_control = new BTextControl(rect, "", "Money in mio", "0", new BMessage(EDIT_UPDATE) );
	AddChild(money_control);

	rect.OffsetBy(0,OFFSET_Y);
	birth_rate_control = new BTextControl(rect, "", "Birth rate (0..5)", "0", new BMessage(EDIT_UPDATE) );
	AddChild(birth_rate_control);

	rect.OffsetBy(0,OFFSET_Y);
	tech_level_control = new BTextControl(rect, "", "Tech. level (0..100)", "0", new BMessage(EDIT_UPDATE) );
	AddChild(tech_level_control);

	rect.OffsetBy(0,OFFSET_Y);
	pnb_control = new BTextControl(rect, "", "PNB in $", "0", new BMessage(EDIT_UPDATE) );
	AddChild(pnb_control);

    BRect xrect=rect; //histoire de pas trop foutre le bordel on préserve l'ancien
    
	xrect.OffsetBy(0,OFFSET_Y*1.5);
	xrect.right-=(OFFSET_X);
	xrect.left+=2;
	
	sea_check= new BCheckBox(xrect, "name", "Access sea",  new BMessage(EDIT_UPDATE),B_FOLLOW_TOP, B_WILL_DRAW);
	AddChild(sea_check);		
	
	xrect.OffsetBy(OFFSET_X,0);
	nuke_check= new BCheckBox(xrect, "name", "Access nukes",  new BMessage(EDIT_UPDATE),B_FOLLOW_TOP, B_WILL_DRAW);
	AddChild(nuke_check);							
         		
	//ARMEE
	rect.OffsetBy(0,OFFSET_Y);	
	rect.OffsetBy(0,OFFSET_Y);
	rect.OffsetBy(0,OFFSET_Y);	
	rect.OffsetBy(0,OFFSET_Y*0.5);
	
	//Genarmy
	button_Gen = new BButton( rect,"",	"Auto generate army", new BMessage( BUTTON_GEN) );          								 				 									 	
	AddChild(button_Gen);
		
	rect.OffsetBy(0,OFFSET_Y);
	rect.OffsetBy(0,OFFSET_Y);	
	infantry_control = new BTextControl(rect, "", "Infantry", "0", new BMessage(EDIT_UPDATE) );
	AddChild(infantry_control);
	
	rect.OffsetBy(0,OFFSET_Y);
	tank_control = new BTextControl(rect, "", "Tanks", "0", new BMessage(EDIT_UPDATE) );
	AddChild(tank_control);

	rect.OffsetBy(0,OFFSET_Y);
	marine_control = new BTextControl(rect, "", "Marine", "0", new BMessage(EDIT_UPDATE) );
	AddChild(marine_control);

	rect.OffsetBy(0,OFFSET_Y);
	airforce_control = new BTextControl(rect, "", "Airforce", "0", new BMessage(EDIT_UPDATE) );
	AddChild(airforce_control);

	rect.OffsetBy(0,OFFSET_Y);
	dca_control = new BTextControl(rect, "", "DCA", "0", new BMessage(EDIT_UPDATE) );
	AddChild(dca_control);

	rect.OffsetBy(0,OFFSET_Y);
	missile_control = new BTextControl(rect, "", "Missile", "0", new BMessage(EDIT_UPDATE) );
	AddChild(missile_control);

	rect.OffsetBy(0,OFFSET_Y);
	nuke_control = new BTextControl(rect, "", "Nuke", "0", new BMessage(EDIT_UPDATE) );
	AddChild(nuke_control);

		
	//Country List
	rect=Bounds();	
 	rect.left+=224;
    rect.right-=B_V_SCROLL_BAR_WIDTH;
 	rect.bottom-=4;

	ct_list = new BListView(rect, "", B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL); 
   
   	AddChild(new BScrollView("", ct_list, B_FOLLOW_ALL, 0, false, true));
   	ct_list->SetSelectionMessage(new BMessage(EDIT_CT_SELECT));
	
	//on trouve les pays et on les mets dans la liste
	unsigned char temp_ct = _jour->country_first;
    while (temp_ct != _jour->country_last+1)
    {
 		ct_list->AddItem(new BStringItem(_country[temp_ct]->Name()));
		temp_ct++;    
    }
	
	SetEdit(); //affiche les valeurs actuelles du pays dans les cases
}


//------------------------------------------------------------

EditorView::~EditorView()
{
}

//------------------------------------------------------------
void EditorView::MouseDown(BPoint point)
{
	//pas besoin de remettre update_info à OFF, c'est fait dans infoview
}//FIN FONCTION
	
//------------------------------------------------------------
void EditorView::SelectedCt()
{
	uint32 index;

	//active country
	index = ct_list->CurrentSelection(); //index dans la liste ctry
	_jour->active_country = index+(_jour->country_first);
	_jour->active_group 	 = _country[_jour->active_country]->group;
	_jour->active_politic = _group[_jour->active_group]->politic;
	SetEdit();

}

void EditorView::UpdateEdit()
{

	uint32 index;
	uint32 chiffre;
	unsigned int mini;
	float fl;	
	Country *ctry;


	ctry = _country[_jour->active_country];
	
	//active group
    index=list->CurrentSelection(); //index dans la liste groupe 
   	
	//test si valide et on change les datas 
	//seulement si quelque chose est sélectionné
	//sinon crash quand on modif un autre élément et que tout est updaté y compris ça
	if((index+(_jour->group_first) >= _jour->group_first)	&& (index+(_jour->group_first) <= _jour->group_last))
		_jour->active_group  = index+_jour->group_first; //idem
	else
	{//sinon on reselect le juste
		list->Select(_jour->active_group-(_jour->group_first));
		list->ScrollToSelection();
	}	
	
	ctry->base_group	= 	ctry->group	    = _jour->active_group;
	_group[_jour->active_group]->active=ON; //pour pouvoir réssuciter un grp en lui assignant de nouveaux pays
	_politic[_group[_jour->active_group]->politic]->active=ON; //pour pouvoir réssuciter la politique aussi
	
    ctry->SetName(name_control->Text());
	
	//Données générales
	chiffre=atoi(population_control->Text());
	ctry->set_population(chiffre);

	chiffre=atoi(money_control->Text());
	ctry->set_money(chiffre);

	mini=atoi(pnb_control->Text());
	ctry->set_pnb(mini);

	fl=atof(birth_rate_control->Text());
	ctry->set_birth_rate(fl);

	fl=atof(tech_level_control->Text());
	ctry->set_tech_level(fl);

	ctry->access_nuke=OFF;//par défaut
	ctry->access_sea=OFF ;

	if (nuke_check->Value()==B_CONTROL_ON) ctry->access_nuke=ON;
	if (sea_check->Value()==B_CONTROL_ON) ctry->access_sea=ON;
		
	//army
	chiffre=atoi(infantry_control->Text());
	ctry->set_infantry(chiffre);
	
	mini=atoi(tank_control->Text());
	ctry->set_tank(mini);
	
	mini=atoi(marine_control->Text());
	ctry->set_marine(mini);
	
	mini=atoi(airforce_control->Text());
	ctry->set_airforce(mini);
	
	mini=atoi(missile_control->Text());
	ctry->set_missile(mini);
	
	mini=atoi(nuke_control->Text());
	ctry->set_nuke(mini);
	
	mini=atoi(dca_control->Text());
	ctry->set_dca(mini);

  	_jour->mainWin->PostMessage(new BMessage(DRAW_ACTIVE_COUNTRY)); //Draw active country
	_jour->infoWin->PostMessage(new BMessage(DRAW_INFO));    //Draw InfoView
  	
  	Window()->PostMessage(new BMessage(EDIT_GRP_UPDATE));
}

void EditorView::SetEdit() //copie les valeurs réelles dans les cases
{
	UpdateGroups();
	
	Country *ctry=_country[_jour->active_country];
	char str[255];

	sprintf(str,"%i",ctry->nb_in_pal);
	numero->SetText(str);
	
	
	//liste des groupes
	list->Select(ctry->group-(_jour->group_first));
	list->ScrollToSelection();
	
	//liste des pays
	ct_list->Select(ctry->nb_in_pal-(_jour->country_first));
	ct_list->ScrollToSelection();
	
	
	//texte
	sprintf(str,ctry->Name());
	name_control->SetText(str);

	//Données générales
	sprintf(str,"%d",(int)(ctry->population));
	population_control->SetText(str);
	
	sprintf(str,"%d",(int)(ctry->money));
	money_control->SetText(str);

	sprintf(str,"%d",ctry->pnb);
	pnb_control->SetText(str);

	sprintf(str,"%G",ctry->birth_rate);
	birth_rate_control->SetText(str);

	sprintf(str,"%G",ctry->tech_level);
	tech_level_control->SetText(str);

	nuke_check->SetValue(B_CONTROL_OFF); //par défaut
	sea_check->SetValue(B_CONTROL_OFF);

	if (_country[_jour->active_country]->access_nuke==ON) nuke_check->SetValue(B_CONTROL_ON);
	if (_country[_jour->active_country]->access_sea==ON) sea_check->SetValue(B_CONTROL_ON);

	//Arméé
	sprintf(str,"%ld",ctry->infantry);
	infantry_control->SetText(str);

	sprintf(str,"%d",(int)(ctry->marine));
	marine_control->SetText(str);
	
	sprintf(str,"%u",(unsigned int)(ctry->tank));
	tank_control->SetText(str);
	
	sprintf(str,"%u",(unsigned int)(ctry->airforce));
	airforce_control->SetText(str);
	
	sprintf(str,"%u",(unsigned int)(ctry->dca));
	dca_control->SetText(str);
	
	sprintf(str,"%u",(unsigned int)(ctry->missile));
	missile_control->SetText(str);
	
	sprintf(str,"%u",(unsigned int)(ctry->nuke));
	nuke_control->SetText(str);
		

	button_Next->SetEnabled(true);
	button_Prev->SetEnabled(true);
	if(_jour->active_country == _jour->country_last) button_Next->SetEnabled(false);
	if(_jour->active_country == _jour->country_first) button_Prev->SetEnabled(false);
	
	_jour->mainWin->PostMessage(new BMessage(DRAW_ACTIVE_COUNTRY)); //Draw active country
}

void EditorView::UpdateGroups()
{
	//si il y a aucune select crash!
	int32 old_set = list->CurrentSelection(); //index dans la liste ctry
	//list->RemoveItems(0,(_jour->group_last+1)-_jour->group_first); //efface tout
	list->RemoveItems(0,list->CountItems()); //efface tout

	//on trouve les groupes et on les met dans la liste
	unsigned char temp_grp = _jour->group_first;
    while (temp_grp != _jour->group_last+1)
    {
 		list->AddItem(new BStringItem(_group[temp_grp]->Name()));
		temp_grp++;    
    }

	if(list->CountItems()-1 < old_set)
		old_set = list->CountItems()-1;
	list->Select(old_set);
}
