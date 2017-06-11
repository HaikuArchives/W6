#include "EditorPolView.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "politic.h"
#include <MenuField.h>
#include <MenuItem.h>
#include <ScrollView.h>
#include <TextControl.h>
#include <Slider.h>
#include <Window.h>

EditorPolView::EditorPolView(BRect r, long flags,Country *Country_id[MAX_COUNTRY],Group *Group_id[MAX_GROUP], Politic *Politic_id[MAX_POLITIC],Day *compteur)
: BView(r, "", flags, B_WILL_DRAW )
{
	_jour=compteur;
	_country = Country_id;
	_group = Group_id;
	_politic = Politic_id;
	_jour->active_group=_country[_jour->active_country]->group;
	Group *grp=_group[_jour->active_group];
	_jour->active_politic=grp->politic;
	BRect rect;

	SetViewColor(216,216,216);   

	rect.Set(4,4,Bounds().Width()-8,4+10);
	pol_name_control = new BTextControl(rect, "", "Politic Name", "X", new BMessage(UPDATE_RELATIONS)); //Le nom update aussi le nom des relations pour son propre nom!
	AddChild(pol_name_control);

	//AJOUTER ADD et del politic
	rect.OffsetBy(0,48);
	rect.left  = 4 ;
	rect.right = Bounds().Width()-4;
	rect.bottom +=24;	
	slider_repression = new BSlider(rect, " ", "Repression level", new BMessage(UPDATE_POL_EDIT),0,100,B_TRIANGLE_THUMB,B_FOLLOW_TOP,B_WILL_DRAW);
	rect.OffsetBy(0,56);
	slider_propaganda = new BSlider(rect, "", "Propaganda level", new BMessage(UPDATE_POL_EDIT),0,100,B_TRIANGLE_THUMB,B_FOLLOW_TOP,B_WILL_DRAW);    
    slider_repression->SetLimitLabels("0 %", "100 %");
    slider_propaganda->SetLimitLabels("0 %", "100 %");
	AddChild(slider_repression);
	AddChild(slider_propaganda);

	rect.Set(4,170,Bounds().Width()-4-B_V_SCROLL_BAR_WIDTH,Bounds().Height()-4);
	le_fond_pol = new BView(rect, "", B_FOLLOW_ALL, B_WILL_DRAW); 
	le_fond_pol->SetViewColor(216,216,216);   
	sc_view = new BScrollView("", le_fond_pol, B_FOLLOW_ALL, 0, false, true);
	AddChild(sc_view);

	SetPolitic();
}

void EditorPolView::SetPolEdit() //Lorsque l'on a changé de Pol ont met les valeurs actuelles la pol à l'écran
{
	pol_name_control->SetText(_politic[_jour->active_politic]->Name());
	slider_propaganda->SetValue(_politic[_jour->active_politic]->propaganda);      
	slider_repression->SetValue(_politic[_jour->active_politic]->repression);      

	unsigned char i = _jour->politic_first;
	while (i!=_jour->politic_last+1)
	{	
		//ItemAt marche tant qu'on change pas ça: dans def_col.h!!!
		//vu que le item 0 doit être friend etc.
		//#define FRIEND 0   #define ENNEMY 1    #define NEUTRAL 2
		switch (_politic[_jour->active_politic]->relation[i])
		{
		case FRIEND:
			pol_relation[i]->Menu()->ItemAt(FRIEND)->SetMarked(true);
			break;
		case ENNEMY:
			pol_relation[i]->Menu()->ItemAt(ENNEMY)->SetMarked(true);
			break;
		case NEUTRAL:
			pol_relation[i]->Menu()->ItemAt(NEUTRAL)->SetMarked(true);
			break;
		}
		i++;
	}
}


void EditorPolView::SetPolitic() //recrée les politics
{
	while (le_fond_pol->ChildAt(0)!=NULL)
		le_fond_pol->ChildAt(0)->RemoveSelf();
	
	//ON RECREE LES NOUVEAUX
	BRect rect;
	unsigned char i = _jour->politic_first;
	rect.Set(4,4,le_fond_pol->Bounds().Width()-4,4+100);
	//BView *vue_pol_relation[MAX_POL];
	while (i!=_jour->politic_last+1)
	{
		//oui, il faut recréer le menu à chaque fois, sinon le menu s'affiche qu'une fois pour tous les pols!
		BMenu *relation = new BMenu("Relation");

		BMessage *msg_friend  = new BMessage(BECOMES_FRIEND);
		BMessage *msg_ennemy  = new BMessage(BECOMES_ENNEMY);
		BMessage *msg_neutral = new BMessage(BECOMES_NEUTRAL);
		msg_friend->AddInt8("val",i); //lequel devient ami du pays actif
		msg_ennemy->AddInt8("val",i); //lequel devient ennemy du pays actif
		msg_neutral->AddInt8("val",i); //lequel devient neutre du pays actif

		//FAUT AJOUTER LES rubrique DANS l'ordre selon ceci qui est dans def_col.h
		//#define FRIEND 0    #define ENNEMY 1   #define NEUTRAL 2

		relation->AddItem(new BMenuItem("Friend", msg_friend));
		relation->AddItem(new BMenuItem("Ennemy", msg_ennemy));
		relation->AddItem(new BMenuItem("Neutral", msg_neutral));
		relation->SetLabelFromMarked(true); //pour mettre nom actif en titre

		pol_relation[i]=  new BMenuField(rect,"",_politic[i]->Name(),relation,B_FOLLOW_TOP,B_WILL_DRAW);

		le_fond_pol->AddChild(pol_relation[i]);
		rect.OffsetBy(0,20);
		i++;
	}

	//normalement ça devrait mettre la scrollbar à la bonne taille mais on dirait pas...
	sc_view->ScrollBar(B_VERTICAL)->SetRange(0, (_jour->politic_last*20)+8 -(le_fond_pol->Bounds().Height()) );	
}

void EditorPolView::UpdatePolEdit() //met les valeurs de l'écran dans le group
{
	_jour->active_group=_country[_jour->active_country]->group;
	Group *grp=_group[_jour->active_group];
	_jour->active_politic=grp->politic;

	_politic[_jour->active_politic]->SetName(pol_name_control->Text());

	_politic[_jour->active_politic]->repression = slider_repression->Value();
	_politic[_jour->active_politic]->propaganda = slider_propaganda->Value();

	BMessage	message(DRAW_INFO);
	_jour->infoWin->PostMessage(&message);    //Draw InfoView
}

