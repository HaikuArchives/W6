#include "ChooseView.h"
#include "day.h"
#include "FlagView.h"
#include "W6.h"
#include <Bitmap.h>
#include <ScrollView.h>
#include <Window.h>
#include <Button.h>

ChooseView::ChooseView(BRect r, long flags,Group *Group_id[MAX_GROUP], Day *compteur)
: BView(r, "", flags, B_WILL_DRAW )
{
	_jour=compteur;
	_group = Group_id;
	BRect	bitmap_rect; //tous les drapeaux sont créés à la meme position c'est draw qui les place après
	BRect rect;
	bitmap_rect.Set(0,0,320-1,240-1);
	BString	name;
//	title = new BBitmap(bitmap_rect, B_RGB_32_BIT);

   	name = ((W6Application *)be_app)->app_dir(); //trouve le dir actuel de l'application (a ne pas appeler avant de créer la win)
   	name << "title.png"; //et le nom du fichier
   	title = ((W6Application *)be_app)->LoadBitmap(name.String()); 
   
   if(title==NULL)
		title = new BBitmap(BRect(0,0,320-1,240-1), B_RGB32); //sécurité
	
   	SetViewColor(0,0,0);

	rect.Set(8,8,8+150,Bounds().Height()-8);
	le_fond_choose = new FlagView(rect, B_FOLLOW_TOP |B_WILL_DRAW| B_NOT_RESIZABLE, _group,_jour);

	le_fond_choose->SetViewColor(0,0,0);   
	BScrollView *sc_view = new BScrollView("", le_fond_choose, B_FOLLOW_ALL, 0, false, true);
	AddChild(sc_view);

	//barre scroll à la taille nécessaire
	sc_view->ScrollBar(B_VERTICAL)->SetRange(0, ((_jour->group_last+1)*(FLAG_Y_SIZE+8)+8)-(sc_view->Bounds().Height()) );
	
	rect.Set(224,252,224+320,252+32);
	_jour->button_Done = new BButton( rect,"",	"Select a group first",new BMessage(BUTTON_DONE)  );          								 				 									 	
	_jour->button_Done->SetEnabled(false);
	AddChild(_jour->button_Done);
}

ChooseView::~ChooseView()
{
	delete title; //Bitmaps
	delete _jour->button_Done;
}

void ChooseView::Draw(BRect update_rect)
{
	DrawBitmap(title, BPoint(224,8) );
}
