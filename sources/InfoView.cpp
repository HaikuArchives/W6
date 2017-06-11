#include "InfoView.h"
#include "ColorWindow.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "TxtView.h"
#include "BarView.h"
#include "TopView.h"
#include "GroupView.h"
#include "ColGrpView.h"
#include "GroupWindow.h"
#include "WeatherView.h"
#include "StatusView.h"
#include <PictureButton.h>
#include <TranslationUtils.h>
#include <Bitmap.h>

InfoView::InfoView(BRect r, Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP],Politic *Politic_id[MAX_POLITIC], Day *compteur)
: BView(r, "", B_FOLLOW_ALL, B_WILL_DRAW | B_PULSE_NEEDED)
{
  
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;

 

//----AFFICHAGE DES INFOS
    SetViewColor(0,0,0);
//------------------------


BRect r;
r.Set(0,0,Bounds().Width()-2,100);
grpwin = new GroupWindow(r,_country,_group,_politic,_jour);
grporiwin = new GroupWindow(r,_country,_group,_politic,_jour);
grporiwin->Show();
grpwin->Show();

back_view = new TopView(BRect(0,0,Bounds().Width(),51), _country,_group,_politic,_jour);
AddChild(back_view);

BRect yy(0,0,32-1,32-1);
yy.OffsetBy(84,6);
stat_view = new StatusView(yy, _country,_group,_politic,_jour);

yy.OffsetBy(32+4,0);
wth_view = new WeatherView(yy, _country,_group,_politic,_jour);
   	
back_view->AddChild(wth_view);	
back_view->AddChild(stat_view);	


BRect rect;

rect.Set(0,0,32-1,32-1);
rect.OffsetBy(6,6);

CreateButton(53,54);
buy_button = new BPictureButton(rect,"",on, off, new BMessage(BUTTON_BUY),B_ONE_STATE_BUTTON);


rect.OffsetBy(32+4,0);
CreateButton(51,52);
set_button = new BPictureButton(rect,"",on, off, new BMessage(BUTTON_SET),B_ONE_STATE_BUTTON);

bb_help.SetHelp(buy_button,"Buy army (B)");
bb_help.SetHelp(set_button,"Country settings (T)");

CreateButton(55,56); //create the pictures
buy_button ->SetDisabledOn(on); 
buy_button ->SetDisabledOff(on);
set_button ->SetDisabledOn(off); 
set_button ->SetDisabledOff(off); 

back_view->AddChild(buy_button);
back_view->AddChild(set_button);

BRect raaa;
raaa.Set(160,8,185,13);
group_color_view = new ColGrpView(raaa);
group_color_view->SetViewColor(0,255,0);
group_color_view->the_win = grpwin;

raaa.InsetBy(0,1.5);
raaa.OffsetBy(0,11);

group_ori_color_view = new ColGrpView(raaa);
group_ori_color_view->SetViewColor(255,255,0);
group_ori_color_view->the_win = grporiwin;


back_view->AddChild(group_color_view);
back_view->AddChild(group_ori_color_view);

//-------------------------------------------------------------


#define TOP_TXT 0
#define INDENT 2 //bord gauche
#define BAR_INDENT 8 //bord gauche

unsigned char line_pos=0;
line_pos=4;


rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
pop_view = new TxtView(rect, "pop", "xxx");
AddChild(pop_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
money_view = new TxtView(rect, "money", "xxx");
AddChild(money_view);

line_pos++;
line_pos++;
rect.Set(BAR_INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-BAR_INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT-6);
moral_bar = new BarView(rect, "Moral",35," (Revolution Near!)"); //la rev est à 25
AddChild(moral_bar);

line_pos++;
rect.OffsetBy(0,16);
resist_bar = new BarView(rect, "Resistance",0," (free)");
AddChild(resist_bar);

line_pos++;
rect.OffsetBy(0,24);
agri_bar = new BarView(rect, "Agriculture",STARVE_LEVEL, " (starving!)");
AddChild(agri_bar);
    
line_pos++;
rect.OffsetBy(0,15);
indus_bar = new BarView(rect, "Industry",0,""); //pas de limite
AddChild(indus_bar);


///

line_pos++;
line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
tl_view = new TxtView(rect, "tech_level", "xxx");
AddChild(tl_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
infantry_view = new TxtView(rect, "infantry", "xxx");
AddChild(infantry_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
tank_view = new TxtView(rect, "tank", "xxx");
AddChild(tank_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
marine_view = new TxtView(rect, "marine", "xxx");
AddChild(marine_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
airforce_view = new TxtView(rect, "airforce", "xxx");
AddChild(airforce_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
dca_view = new TxtView(rect, "dca", "xxx");
AddChild(dca_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
missile_view = new TxtView(rect, "missile", "xxx");
AddChild(missile_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
nuke_view = new TxtView(rect, "nuke", "xxx");
AddChild(nuke_view);



///-------------------------------------------


line_pos++;
line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
engaged_view = new TxtView(rect, "eng1", "...");
AddChild(engaged_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
engaged2_view = new TxtView(rect, "eng2", "...");
AddChild(engaged2_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
engaged3_view = new TxtView(rect, "eng3", "...");
AddChild(engaged3_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
engaged4_view = new TxtView(rect, "eng4", "...");
AddChild(engaged4_view);

///

line_pos++;
line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
ennemy_view = new TxtView(rect, "enmy", "...");
AddChild(ennemy_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
ennemy2_view = new TxtView(rect, "enmy", "...");
AddChild(ennemy2_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
ennemy3_view = new TxtView(rect, "enmy", "...");
AddChild(ennemy3_view);

line_pos++;
rect.Set(INDENT,TOP_TXT+(_jour->interligne*line_pos),INFO_X_SIZE-1-INDENT, (_jour->interligne*(line_pos+1)) + TOP_TXT);
ennemy4_view = new TxtView(rect, "enmy", "...");
AddChild(ennemy4_view);



		

}

InfoView::~InfoView()
{
}

void InfoView::MouseDown(BPoint point)
{

if (_jour->edit_mode==ON && point.y<80) 
	{

		ColorWindow *colWindow = new ColorWindow(_group[_country[_jour->active_country]->group],_jour);
	    colWindow ->Lock();	
	    colWindow ->Show();	
	    colWindow ->Unlock();	
	}

}

void InfoView::AttachedToWindow()
{
	UpdateCountryInfo();
}


//--------------------------------------

void InfoView::UpdateCountryInfo()
{

	const char *tmp;
	
	int grp,base_grp;
	grp = _country[_jour->active_country]->group; //trouve le groupe à qui appartient le pays
	base_grp = _country[_jour->active_country]->base_group;
	
	rgb_color couleur_groupe = _group[grp]->grp_color;
	rgb_color couleur_ori_groupe = _group[base_grp]->grp_color;

	char str[255];
	char str2[255];
	
	sprintf(str,_country[_jour->active_country]->Name());

	//day !=month_counter (day=nb total de _jour)
	strcat(str," (");
	sprintf(str2,_jour->month_name);  	strcat(str,str2);
	sprintf(str2," %i, %i",_jour->month_counter, _jour->year);	strcat(str,str2);
	strcat(str,")");
	Window()->SetTitle(str);

	
	//A l'ancienne
	
	//------------------------

	if (grpwin!=NULL) grpwin->grp_view->UpdateGroupInfo(_country[_jour->active_country]->group);
	if (grporiwin!=NULL) grporiwin->grp_view->UpdateGroupInfo(_country[_jour->active_country]->base_group);
	group_color_view->SetViewColor(couleur_groupe);
	group_color_view->Invalidate();
    
    group_ori_color_view->SetViewColor(couleur_ori_groupe);
	group_ori_color_view->Invalidate();
    
//ON ACCEDE AUX PAYS qu'à partir de leur numero dans le tableau
//IDEM POUR LES GROUPES


	

	
	//POPULATION pas de virgule en %i
	sprintf(str,"Population: %u",(int)(_country[_jour->active_country]->population));
	pop_view->SetText(str);

	moral_bar->percentage = _country[_jour->active_country]->moral;
	resist_bar->percentage = _country[_jour->active_country]->resistance;
	agri_bar->percentage = _country[_jour->active_country]->agriculture;
	indus_bar->percentage = _country[_jour->active_country]->industry;

	moral_bar->Invalidate();
	resist_bar->Invalidate();
	agri_bar->Invalidate();
	indus_bar->Invalidate();

	
	
	//Money si le chiffre  %g pour les flottants, %i pour les entiers
	sprintf(str,"$ %i mio.",(int)(_country[_jour->active_country]->money));
	sprintf(str2,"   Tax: %.4g %%",_country[_jour->active_country]->tax);
	tmp=strcat(str,str2); //on joint les deux bouts après car types différents
	money_view->SetText(tmp);
	
	//tl_view->SetAlignment(B_ALIGN_LEFT);	
	//Tech_Level	
	sprintf(str,"Tech level: %.4g %% (%.4g %%)",
				_country[_jour->active_country]->tech_level,
				_country[_jour->active_country]->ennemy_tech_level);
	tmp=str;
	tl_view->SetText(tmp);

	//Infantry	
	sprintf(str,"Infantry: %u (%u)",(int)(_country[_jour->active_country]->infantry),(int)(_country[_jour->active_country]->ennemy_infantry));
	tmp=str;
	infantry_view->SetText(tmp);

	//Tank	
	sprintf(str,"Tank: %i (%i)",(int)(_country[_jour->active_country]->tank),(int)(_country[_jour->active_country]->ennemy_tank));
	tmp=str;
	tank_view->SetText(tmp);

	//Marine	
	sprintf(str,"Marine: %i (%i)",(int)(_country[_jour->active_country]->marine),(int)(_country[_jour->active_country]->ennemy_marine));
	tmp=str;
	marine_view->SetText(tmp);

	//Airforce
	sprintf(str,"Airforce: %i (%i)",(int)(_country[_jour->active_country]->airforce),(int)(_country[_jour->active_country]->ennemy_airforce));
	tmp=str;
	airforce_view->SetText(tmp);
		
	//Missile
	sprintf(str,"Missile: %i (%i)",(int)(_country[_jour->active_country]->missile),(int)(_country[_jour->active_country]->ennemy_missile));
	tmp=str;
	missile_view->SetText(tmp);	
	
	//DCA
	sprintf(str,"DCA: %i (-)",(int)(_country[_jour->active_country]->dca));
	tmp=str;
	dca_view->SetText(tmp);
	
	//Nuke
	sprintf(str,"Nuke: %i (%i)",(int)(_country[_jour->active_country]->nuke),(int)(_country[_jour->active_country]->ennemy_nuke));
	tmp=str;
	nuke_view->SetText(tmp);




	//Engaged 1
	sprintf(str," ");//par défaut rien
	engaged_view->SetHighColor(255,255,255,0); 
	//mais si il y a une victime...
	if(_country[_jour->active_country]->victim_01!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->victim_01->group]->grp_color;
	engaged_view->SetHighColor(col); 
		
		sprintf(str,"Attacking "); //partons du principe qu'on attaque un ennemi
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->victim_01->group)
		{sprintf(str,"Moving to ");}
		strcat(str,_country[_jour->active_country]->victim_01->Name());
		sprintf(str2," in %d day(s)",_country[_jour->active_country]->travel_01);
		if (_country[_jour->active_country]->move_01!=OFF)strcat(str,str2);
	}
	engaged_view->SetText(str);

	//Engaged 2
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->victim_02!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->victim_02->group]->grp_color;
    	engaged2_view->SetHighColor(col); 

		sprintf(str,"Attacking "); //partons du principe qu'on attaque un ennemi
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->victim_02->group)
		{sprintf(str,"Moving to ");}

		strcat(str,_country[_jour->active_country]->victim_02->Name());
		sprintf(str2," in %d day(s)",_country[_jour->active_country]->travel_02);
		if (_country[_jour->active_country]->move_02!=OFF)strcat(str,str2);
		}
	engaged2_view->SetText(str);



	//Engaged 3
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->victim_03!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->victim_03->group]->grp_color;
	engaged2_view->SetHighColor(col); 

		sprintf(str,"Attacking "); //partons du principe qu'on attaque un ennemi
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->victim_03->group)
		{sprintf(str,"Moving to ");}

		strcat(str,_country[_jour->active_country]->victim_03->Name());
		sprintf(str2," in %d day(s)",_country[_jour->active_country]->travel_03);
		if (_country[_jour->active_country]->move_03!=OFF)strcat(str,str2);
	}
	engaged3_view->SetText(str);


	//Engaged 4
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->victim_04!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->victim_04->group]->grp_color;
	engaged4_view->SetHighColor(col); 

		sprintf(str,"Attacking "); //partons du principe qu'on attaque un ennemi
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->victim_04->group)
		{sprintf(str,"Moving to ");}

		strcat(str,_country[_jour->active_country]->victim_04->Name());
		sprintf(str2," in %d day(s)",_country[_jour->active_country]->travel_04);
		if (_country[_jour->active_country]->move_04!=OFF)strcat(str,str2);
	}
	engaged4_view->SetText(str);
	

	//Ennemy 1
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->agressor_01!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->agressor_01->group]->grp_color;
	ennemy_view->SetHighColor(col); 
		sprintf(str,"Attacked by "); 
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->agressor_01->group)
		{sprintf(str,"Moving from ");}
	 	strcat(str,_country[_jour->active_country]->agressor_01->Name());
		if(_country[_jour->active_country]==_country[_jour->active_country]->agressor_01)
		sprintf(str,"Attacked by resistance!");     
	}
	ennemy_view->SetText(str);

	//Ennemy 2
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->agressor_02!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->agressor_02->group]->grp_color;
	ennemy2_view->SetHighColor(col); 
		sprintf(str,"Attacked by "); 
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->agressor_02->group)
		{sprintf(str,"Moving from ");}
	 	strcat(str,_country[_jour->active_country]->agressor_02->Name());
		if(_country[_jour->active_country]==_country[_jour->active_country]->agressor_02)
		sprintf(str,"Attacked by resistance!");     
	}
	ennemy2_view->SetText(str);

	//Ennemy 3
	sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->agressor_03!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->agressor_03->group]->grp_color;
	ennemy3_view->SetHighColor(col); 
		sprintf(str,"Attacked by "); 
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->agressor_03->group)
		{sprintf(str,"Moving from ");}
	 	strcat(str,_country[_jour->active_country]->agressor_02->Name());
		if(_country[_jour->active_country]==_country[_jour->active_country]->agressor_03)
		sprintf(str,"Attacked by resistance!");     
 
	}
	ennemy3_view->SetText(str);

	//Ennemy 4
		sprintf(str," ");//par défaut rien
	//mais si il y a une victime...
	if(_country[_jour->active_country]->agressor_04!=NULL)
	{rgb_color col;
	 col=_group[_country[_jour->active_country]->agressor_04->group]->grp_color;
	ennemy4_view->SetHighColor(col); 
		sprintf(str,"Attacked by "); 
		if (_country[_jour->active_country]->group==_country[_jour->active_country]->agressor_04->group)
		{sprintf(str,"Moving from ");}
	 	strcat(str,_country[_jour->active_country]->agressor_04->Name());
		if(_country[_jour->active_country]==_country[_jour->active_country]->agressor_04)
		sprintf(str,"Attacked by resistance!");     
 
	}
	ennemy4_view->SetText(str);

//desactive les boutons pour les autres pays
if (_group[_country[_jour->active_country]->group]->player==COMPUTER)
	{
		set_button->SetEnabled(false);
		buy_button->SetEnabled(false);	
	}
	
	else {
		set_button->SetEnabled(true);
		buy_button->SetEnabled(true);
		}
	


stat_view->Invalidate(); //pour le war-peace et autres		
wth_view->Invalidate(); //pour le war-peace et autres		


}//FIN FONCTION

void InfoView::CreateButton(int32 enabled_id ,int32 disabled_id)
{	
//	BWindow *tmp_win = new BWindow(BRect(0,0,32,32),"",B_DOCUMENT_WINDOW,Flags(),B_CURRENT_WORKSPACE);
			
			//fill bitmap
			downBitmap = BTranslationUtils::GetBitmap('RAWT', enabled_id, NULL);
			upBitmap = BTranslationUtils::GetBitmap('RAWT', disabled_id, NULL);
			
			//avoid crash if missing
			if (downBitmap==NULL) downBitmap = new BBitmap(BRect(0,0,15,15),B_RGB32);
			if (upBitmap==NULL) upBitmap = new BBitmap(BRect(0,0,15,15),B_RGB32);
			
			BRect rect = downBitmap->Bounds();

			//Faut un window pour le faire
			BWindow* x= new BWindow(rect,"", B_FLOATING_WINDOW, Flags(), B_CURRENT_WORKSPACE);
			
			//tempview for creating the picture
			BView *tempView = new BView( rect, "temp", B_FOLLOW_NONE, B_WILL_DRAW );
			x->AddChild(tempView);
			
			//create on picture
   			tempView->BeginPicture(new BPicture); 
   			tempView->DrawBitmap(upBitmap);
   			on = tempView->EndPicture();
   			//create off picture
   			tempView->BeginPicture(new BPicture); 
   			tempView->DrawBitmap(downBitmap);
   			off = tempView->EndPicture();
   			//get rid of tempview
   			
   			x->RemoveChild(tempView);
   			x->Close();
			delete upBitmap;
   			delete downBitmap;  			
}
