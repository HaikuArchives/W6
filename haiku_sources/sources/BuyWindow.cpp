#include "BuyWindow.h"
#include "day.h"
#include "country.h"
#include <View.h>
#include <StringView.h>
#include <TextControl.h>
#include <Button.h>

BuyWindow::BuyWindow(Country *ct1,Day *compteur)
: BWindow(compteur->find_win_pos(256,256), "                             ",  B_FLOATING_WINDOW, B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
BView *la_vue_du_fond = new BView(Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);
la_vue_du_fond->SetViewColor(216,216,216);
AddChild(la_vue_du_fond);


Ctry_a=ct1;


BRect rect;	  //variable de rectangle utilisée pour les diverses créations d'objets

		//Bouton BUY
		rect.Set( 176-2, 96-2+64+32+32, 176+80-2, 96+32-2+64+32 +32);
		BMessage *button_A_msg = new BMessage( BUTTON_BUY_OK );
		button_A_msg->AddString("text", "BUY");
		button_A = new BButton( rect,"BTA",	"BUY", button_A_msg );          								 				 									 	

		//Bouton CANCEL
		rect.Set( 0+2, 96-2+64+32+32, 0+80+2, 96+32-2+64+32+32 );
		BMessage *button_B_msg = new BMessage( BT_BUY_CANCEL );
		button_B_msg->AddString("text", "BCC");
		button_B = new BButton( rect,"BTB",	"Cancel", button_B_msg );          								 				 									 	

	
	SetDefaultButton(button_A);
	la_vue_du_fond->AddChild(button_A); //ajoute le bouton à la window
	la_vue_du_fond->AddChild(button_B); //ajoute le bouton à la window
	
//------------------------------------------------------------
//------------------------------------------------------------

	char str[100];


	rect.Set( 0, 0, 256, 18);
	x_view = new BStringView(rect, "Title", Ctry_a->Name());
	x_view->SetFont(be_bold_font);
	x_view->SetFontSize(12);
	x_view->SetHighColor(0,0,64);
	x_view->SetAlignment(B_ALIGN_CENTER);	

	rect.Set( 0, 18, 256, 18+18);
	y_view = new BStringView(rect, "Titleb", "Buy troops");
	y_view->SetFont(be_plain_font);
	y_view->SetFontSize(12);
	y_view->SetHighColor(0,0,0);
	y_view->SetAlignment(B_ALIGN_CENTER);	
	
	la_vue_du_fond->AddChild(x_view);
	la_vue_du_fond->AddChild(y_view);
	
	//ATTENTION FAUT METTRE DES ZEROS PAS DU VIDE!!!
	//SINON LE ATOI DE LA LECTURE=CATASTROPHE AND CRASH	
	rect.Set( 4, 64-22+6, 4+120, 64+6);
	infantry_control = new BTextControl(rect, "0", "Infantry", "100", new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	tank_control = new BTextControl(rect, "0", "Tanks", "0",new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	marine_control = new BTextControl(rect, "0", "Marine", "0",new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	airforce_control = new BTextControl(rect, "0", "Airforce", "0",new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	missile_control = new BTextControl(rect, "0", "Missile", "0", new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	nuke_control = new BTextControl(rect, "0", "Nukes", "0",new BMessage(FIELD_UPDATE) );
	rect.OffsetBy(0,22);
	dca_control = new BTextControl(rect, "0", "dca", "0", new BMessage(FIELD_UPDATE) );
	
	if (Ctry_a->access_sea==OFF) marine_control->SetEnabled(false);
//----------------------------------------------------------

	rect.OffsetBy(128,(-5*22)-3-22);


 	a_view = new BStringView(rect, "0", str );	
	
	rect.OffsetBy(0,22);
	b_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	c_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	d_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	e_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	f_view = new BStringView(rect, "0", str );	

	rect.OffsetBy(0,22);
	g_view = new BStringView(rect, "0", str );	

	la_vue_du_fond->AddChild(infantry_control);
	la_vue_du_fond->AddChild(tank_control);
	la_vue_du_fond->AddChild(marine_control);
	la_vue_du_fond->AddChild(airforce_control);
	la_vue_du_fond->AddChild(missile_control);
	la_vue_du_fond->AddChild(nuke_control);
	la_vue_du_fond->AddChild(dca_control);
	
	la_vue_du_fond->AddChild(a_view);
	la_vue_du_fond->AddChild(b_view);
	la_vue_du_fond->AddChild(c_view);
	la_vue_du_fond->AddChild(d_view);
	la_vue_du_fond->AddChild(e_view);
	la_vue_du_fond->AddChild(f_view);
	la_vue_du_fond->AddChild(g_view);
	
	
	if (Ctry_a->access_nuke==OFF)	{	nuke_control->SetEnabled(false);	}
	else {	nuke_control->SetEnabled(true);	}

	if (Ctry_a->access_sea==OFF)	{	marine_control->SetEnabled(false);	}
	else {	marine_control->SetEnabled(true);	}
		
	UpdateFields();
	
}



//POUR LA GESTION DES MESSAGES ARRIVANT	
void BuyWindow::MessageReceived(BMessage *message)
{

	// Print the message to see its contents
	message->PrintToStream();

 	switch(message->what)
 	{
	case BUTTON_BUY_OK:
  		UpdateFields(); //important sinon si le mec valide pas le champ, il passe
		if(button_A->IsEnabled()==true)
		{//Très important de checker parce-que si on fait	
		 //Updatefields avant, ça peut disabler (à raison)
			Ctry_a->buy(atoi(infantry_control->Text() ),
					atoi(tank_control->Text() ),
					atoi(marine_control->Text() ),
					atoi(airforce_control->Text() ),
					atoi(missile_control->Text() ),
					atoi(nuke_control->Text() ),
					atoi(dca_control->Text() )
					);
		PostMessage(B_QUIT_REQUESTED);
		}
		break;
	case FIELD_UPDATE:
		UpdateFields();
		break;
	case BT_BUY_CANCEL:
		UpdateFields();
		break;
   	default:
		BWindow::MessageReceived(message);
	}//fin switch;
}

void BuyWindow::UpdateFields()
{


	const char *tmp;
	char str[32];
	char str2[32];
	uint64 calca,calcb,calcc,calcd,calce,calcf,calcg, total;
	
	sprintf(str,"x %g = ",COST_INFANTRY); //seul à virgule 
	calca=atoi(infantry_control->Text() );
	calca = (uint64)(calca*(float)COST_INFANTRY);
	sprintf(str2,"%d",(int)calca);
	tmp=strcat(str,str2); 
	a_view->SetText(tmp);		

	sprintf(str,"x %d = ",COST_TANK);
	calcb=atoi(tank_control->Text() );
	calcb*=COST_TANK;
	sprintf(str2,"%d",(int)calcb);
	tmp=strcat(str,str2); 
	b_view->SetText(tmp);		

	sprintf(str,"x %d = ",COST_MARINE);
	calcc=atoi(marine_control->Text() );
	calcc*=COST_MARINE;
	sprintf(str2,"%d",(int)calcc);
	tmp=strcat(str,str2); 
	c_view->SetText(tmp);		

	sprintf(str,"x %d = ",COST_AIRFORCE);
	calcd=atoi(airforce_control->Text() );
	calcd*=COST_AIRFORCE;
	sprintf(str2,"%d",(int)calcd);
	tmp=strcat(str,str2); 
	d_view->SetText(tmp);		

	sprintf(str,"x %d = ",COST_MISSILE);
	calce=atoi(missile_control->Text() );
	calce*=COST_MISSILE;
	sprintf(str2,"%d",(int)calce);
	tmp=strcat(str,str2); 
	e_view->SetText(tmp);		


	sprintf(str,"x %d = ",COST_NUKE);
	calcf=atoi(nuke_control->Text() );
	calcf*=COST_NUKE;
	sprintf(str2,"%d",(int)calcf);
	tmp=strcat(str,str2); 
	f_view->SetText(tmp);		

	sprintf(str,"x %d = ",COST_DCA);
	calcg=atoi(dca_control->Text() );
	calcg*=COST_DCA;
	sprintf(str2,"%d",(int)calcg);
	tmp=strcat(str,str2); 
	g_view->SetText(tmp);		

	total=calca+calcb+calcc+calcd+calce+calcf+calcg;
	sprintf(str2,"%d",(int)total);
	sprintf(str,"Total in mio. $: ");
	tmp=strcat(str,str2); 
	
	if ( (Ctry_a->money) <= total)	
	{	button_A->SetEnabled(false);
		y_view->SetHighColor(200,0,0);
		}
	else	
	{button_A->SetEnabled(true);
	y_view->SetHighColor(0,0,0); //normalement en noir
		}
	y_view->SetText(tmp);		

}
