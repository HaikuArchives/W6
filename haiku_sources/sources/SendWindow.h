#ifndef SEND_WINDOW_H
#define SEND_WINDOW_H

#include "Window.h"
#include "def_col.h"

class Day;
class Country;
class BStringView;
class BTextControl;
class BButton;

#define BUTTON_CANCEL 'canc'	
#define SET_PLUS_MSG  'setp'	
#define SET_MINUS_MSG 'setm'	
#define BUTTON_AGREE 'agre'

class SendWindow : public BWindow 
{
public:
	BStringView		*x_view,*y_view,*a_view,*b_view,*c_view,*d_view,*e_view,*f_view;
	BTextControl	*infantry_control, *tank_control, *marine_control;
	BTextControl	*airforce_control, *missile_control,*nuke_control;
	BButton			*button_A,*button_B;			
	Country			*Ctry_a,*Ctry_b;

	SendWindow(Country *ct1,Country *ct2,Day *compteur);
		
	virtual void 	MessageReceived(BMessage *message);
};
#endif