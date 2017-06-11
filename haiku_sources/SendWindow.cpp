#include "SendWindow.h"
#include "country.h"
#include "day.h"
#include <Button.h>
#include <StringView.h>
#include <TextControl.h>
#include <View.h>

//J'ai remplacé tous les "" par des "0"
//pour éviter d'avoir des cases vides...
//dans certains cas c'était le nom de l'objet mais on s'en tape

//SendWindow==pOUR L'attaque sendtroops
SendWindow::SendWindow(Country *ct1,Country *ct2,Day *compteur)
: BWindow(compteur->find_win_pos(256,224), "                             ", B_FLOATING_WINDOW, B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	Ctry_a=ct1;
	Ctry_b=ct2;
	BRect rect;	  //variable de rectangle utilisée pour les diverses créations d'objets

	BView *la_vue_du_fond = new BView(Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);
	la_vue_du_fond->SetViewColor(216,216,216);
	AddChild(la_vue_du_fond);

	//Bouton SEND
	rect.Set( 176-2, 96-2+64+32, 176+80-2, 96+32-2+64+32 );
	button_A = new BButton( rect,"BTA",	"Send", new BMessage( BUTTON_AGREE ) );          								 				 									 	

	//Bouton CANCEL
	rect.Set( 0+2, 96-2+64+32, 0+80+2, 96+32-2+64+32 );
	button_B = new BButton( rect,"BTB",	"Cancel", new BMessage( BUTTON_CANCEL ) );          								 				 									 	
	
	SetDefaultButton(button_A);
	la_vue_du_fond->AddChild(button_A); //ajoute le bouton à la window
	la_vue_du_fond->AddChild(button_B); //ajoute le bouton à la window

	const char *tmp;
	char str[100];
	char str2[100];

	rect.Set( 0, 0, 256, 18);
	x_view = new BStringView(rect, "Title", Ctry_a->Name());
	x_view->SetFont(be_bold_font);
	x_view->SetFontSize(12);
	x_view->SetHighColor(0,0,64);
	x_view->SetAlignment(B_ALIGN_CENTER);	

	rect.Set( 0, 18, 256, 18+18);
	y_view = new BStringView(rect, "Titleb", "yy");
	y_view->SetFont(be_plain_font);
	y_view->SetFontSize(12);
	y_view->SetHighColor(0,0,0);
	y_view->SetAlignment(B_ALIGN_CENTER);	
	sprintf(str,"Send troops to ");
	sprintf(str2,Ctry_b->Name());
	tmp=strcat(str,str2); //on joint les deux bouts après car types différents
	y_view->SetText(tmp);
	
	la_vue_du_fond->AddChild(x_view);
	la_vue_du_fond->AddChild(y_view);
	
	//ATTENTION FAUT METTRE DES ZEROS PAS DU VIDE!!!
	//SINON LE ATOI DE LA LECTURE=CATASTROPHE AND CRASH
	rect.Set( 4, 64-22+6, 4+120, 64+6);
	infantry_control = new BTextControl(rect, "0", "Infantry", "1000", NULL);
	rect.OffsetBy(0,22);
	tank_control = new BTextControl(rect, "0", "Tanks", "0", NULL);
	rect.OffsetBy(0,22);
	marine_control = new BTextControl(rect, "0", "Marine", "0", NULL);
	rect.OffsetBy(0,22);
	airforce_control = new BTextControl(rect, "0", "Airforce", "0", NULL);
	rect.OffsetBy(0,22);
	missile_control = new BTextControl(rect, "0", "Missile", "0", NULL);
	rect.OffsetBy(0,22);
	nuke_control = new BTextControl(rect, "0", "Nukes", "0", NULL);

	rect.OffsetBy(128,(-5*22)-3);
	sprintf(str,"%ld",Ctry_a->infantry);
	a_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	sprintf(str,"%d",(int)Ctry_a->tank);
	b_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	sprintf(str,"%i",(int)Ctry_a->marine);
	c_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	sprintf(str,"%i",(int)Ctry_a->airforce);
	d_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	sprintf(str,"%i",(int)Ctry_a->missile);
	e_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	sprintf(str,"%i",(int)Ctry_a->nuke);
	f_view = new BStringView(rect, "0", str );	

	//Bouton ADD 10%
	rect.Set( 94,192,94+32, 192+16);
	BButton* button_x = new BButton( rect,"0",	" + ", new BMessage( SET_PLUS_MSG ) );
	la_vue_du_fond->AddChild(button_x);	

	//Bouton SUB 10%
	rect.Set( 94+32,192,94+32+32, 192+16);
	BButton* button_y = new BButton( rect,"0",	" - ", new BMessage( SET_MINUS_MSG ) );
	la_vue_du_fond->AddChild(button_y);	
		
	la_vue_du_fond->AddChild(infantry_control);
	la_vue_du_fond->AddChild(tank_control);
	la_vue_du_fond->AddChild(marine_control);
	la_vue_du_fond->AddChild(airforce_control);
	la_vue_du_fond->AddChild(missile_control);
	la_vue_du_fond->AddChild(nuke_control);
	
	la_vue_du_fond->AddChild(a_view);
	la_vue_du_fond->AddChild(b_view);
	la_vue_du_fond->AddChild(c_view);
	la_vue_du_fond->AddChild(d_view);
	la_vue_du_fond->AddChild(e_view);
	la_vue_du_fond->AddChild(f_view);
	
	if (Ctry_a->access_nuke==OFF)
		nuke_control->SetEnabled(false);
	else
		nuke_control->SetEnabled(true);

	if(Ctry_a->access_sea==OFF)
		marine_control->SetEnabled(false);
	else
		marine_control->SetEnabled(true);	
}

//POUR LA GESTION DES MESSAGES ARRIVANT	
void SendWindow::MessageReceived(BMessage *message)
{

	// Print the message to see its contents
	message->PrintToStream();

 	switch(message->what)
 	{
	case BUTTON_AGREE:			//attention, très important de checker ça!!
		if(button_A->IsEnabled()==true)
		{
			unsigned long inf,tnk,mar,air,mis,nuke;
  	 		inf= atoi(infantry_control->Text());
  	 		tnk= atoi(tank_control->Text());
 	  		mar= atoi(marine_control->Text());
 	  		air= atoi(airforce_control->Text());
	   		mis= atoi(missile_control->Text());
	   		nuke= atoi(nuke_control->Text());
	        Ctry_a->send_troops(Ctry_b,inf,tnk,mar,air,mis,nuke);
			Lock();
			Close();
		}
		break;
	case SET_PLUS_MSG:
   		char str[100];
   		sprintf(str,"%i",(int)Ctry_a->infantry-1000);
   		infantry_control->SetText(str);
   		sprintf(str,"%i",(int)Ctry_a->tank);
   		tank_control->SetText(str);
   		sprintf(str,"%i",(int)Ctry_a->airforce);
   		airforce_control->SetText(str);
		
		//si l'ennemi est au milieu du continent faudrait éviter ;-)
		if (Ctry_b->access_sea==ON)
		{
   			sprintf(str,"%i",(int)Ctry_a->marine);
   			marine_control->SetText(str);
   		}
   		sprintf(str,"%i",(int)Ctry_a->missile);
   		missile_control->SetText(str);
   		//faudrait pas attacker avec des nukes a moins de le vouloir vraiment
   		//sprintf(str,"%i",Ctry_a->nuke);
   		//nuke_control->SetText(str);
   		break;
	case SET_MINUS_MSG:
   		sprintf(str,"%i",1000);
   		infantry_control->SetText(str);
   		sprintf(str,"%i",0);
   		tank_control->SetText(str);
   		sprintf(str,"%i",0);
   		airforce_control->SetText(str);
   		sprintf(str,"%i",0);
   		missile_control->SetText(str);
   		sprintf(str,"%i",0);
   		nuke_control->SetText(str);
   		break;
	case BUTTON_CANCEL:
		Lock();
		Close();
		break;
   	default:
		// Call inherited if we didn't handle the message
		BWindow::MessageReceived(message);
	}//fin switch;
}
