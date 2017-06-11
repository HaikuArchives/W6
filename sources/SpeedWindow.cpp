#include "SpeedWindow.h"
#include "day.h"
#include <Slider.h>
#include <StringView.h>
#include <TextControl.h>
#include <Button.h>

SpeedWindow::SpeedWindow(Day *compteur)
: BWindow(_jour->find_win_pos(264,118), "Set game speed                    ", B_FLOATING_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	BView *la_vue_du_fond = new BView(this->Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);
	AddChild(la_vue_du_fond);

	la_vue_du_fond->SetViewColor(216,216,216);  

	BRect rect;

	_jour=compteur;
	rect.Set(4,4,256-4,4+24+10); 
    slider_speed = new BSlider(rect, "0", "How many seconds for a day?", new BMessage(SPEED_CHANGED), 1,10); 
	slider_speed->SetHashMarks(B_HASH_MARKS_BOTTOM); 
	slider_speed->SetHashMarkCount(10);
	slider_speed->SetLimitLabels("1", "10");
	slider_speed->SetStyle(B_TRIANGLE_THUMB);

	rect.OffsetBy(0,64); 
    slider_jump = new BSlider(rect, "0", "Speed up (reduces playability!)", new BMessage(SPEED_CHANGED), 1,100); 
	slider_jump->SetHashMarks(B_HASH_MARKS_BOTTOM); 
	slider_jump->SetHashMarkCount(100);
	slider_jump->SetLimitLabels("1", "100");
	slider_jump->SetStyle(B_TRIANGLE_THUMB);

	slider_speed->SetValue(_jour->day_step);      
	slider_jump->SetValue(_jour->jump_days);      
	la_vue_du_fond->AddChild(slider_speed);
	la_vue_du_fond->AddChild(slider_jump);

	slider_speed->SetViewColor(216,216,216); 
	slider_speed->SetViewColor(216,216,216); 
}
	
void SpeedWindow::MessageReceived(BMessage *message)
{
	// Print the message to see its contents
	message->PrintToStream();

 	switch(message->what)
 	{
	case SPEED_CHANGED:
		_jour->day_step  = slider_speed->Value();
		_jour->jump_days = slider_jump->Value()-1; //faut 0 pour 1 day par _jour donc moins 1
		break;				 
   	default:
		BWindow::MessageReceived(message);
	}//fin switch
}
