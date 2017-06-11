#include "OrderWindow.h"
#include "BuyWindow.h"
#include "country.h"
#include "day.h"
#include <View.h>
#include <StringView.h>
#include <Slider.h>
#include <TextControl.h>

OrderWindow::OrderWindow(Country *ct1,Day *compteur)
: BWindow(compteur->find_win_pos(256,256), "Set parameters                         ", B_FLOATING_WINDOW, B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	BView *la_vue_du_fond = new BView(Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);
	la_vue_du_fond->SetViewColor(216,216,216);
	AddChild(la_vue_du_fond);

	BRect rect;
	Ctry_a=ct1;

	rect.Set( 0, 4, 256, 4+18);
	x_view = new BStringView(rect, "Title", Ctry_a->Name());
	x_view->SetFont(be_bold_font);
	x_view->SetFontSize(12);
	x_view->SetHighColor(0,0,64);
	x_view->SetAlignment(B_ALIGN_CENTER);	
	la_vue_du_fond->AddChild(x_view);

	rect.Set(4,24+24,256-4,24+24+10); 
    slider_temp = new BSlider(rect, "0", "Expected temperature", new BMessage(TEMP_CHANGED), 1, 5);
	rect.OffsetBy(0,64); 
    slider_weather = new BSlider(rect, "0", "Expected weather", new BMessage(WEATHER_CHANGED),1, 5);
	slider_temp->SetHashMarks(B_HASH_MARKS_BOTTOM); 
	slider_temp->SetHashMarkCount(5);
	slider_temp->SetLimitLabels("Cold", "Hot");

	slider_weather->SetHashMarks(B_HASH_MARKS_BOTTOM); 
	slider_weather->SetHashMarkCount(5);
	slider_weather->SetLimitLabels("Dry", "Rainy");

	rgb_color temp_col = {0,0,150,0};
	slider_temp->SetBarColor(temp_col);

	rgb_color wt_col = {200,0,0,0};
	slider_weather->SetBarColor(wt_col);

	slider_temp->SetValue(Ctry_a->expected_temperature);      
	slider_weather->SetValue(Ctry_a->expected_weather);      

	la_vue_du_fond->AddChild(slider_temp);
	la_vue_du_fond->AddChild(slider_weather);

	rect.OffsetBy(0,64); 
	char str[32];
	sprintf(str,"%g",Ctry_a->tax);
	tax_control = new BTextControl(rect, "0", "Army tax %", str, new BMessage(TAX_CHANGED) );
	tax_control->SetAlignment(B_ALIGN_LEFT,B_ALIGN_CENTER);
	la_vue_du_fond->AddChild(tax_control);
}

//POUR LA GESTION DES MESSAGES ARRIVANT	
void OrderWindow::MessageReceived(BMessage *message)
{
	// Print the message to see its contents
	message->PrintToStream();

 	switch(message->what)
 	{
	case BUTTON_BUY_OK:
		Lock();
		Close();
		break;
   	case TAX_CHANGED:
		Ctry_a->set_tax(atoi(tax_control->Text()) );
		break;
   	case TEMP_CHANGED:
		Ctry_a->expected_temperature=slider_temp->Value();
		break;
   	case WEATHER_CHANGED:
		Ctry_a->expected_weather=slider_weather->Value();
		break;
   	default:
		BWindow::MessageReceived(message);
	}//fin switch
}
