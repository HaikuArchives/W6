#ifndef BUY_WINDOW_H
#define BUY_WINDOW_H

#include "Window.h"

class Country;
class Day;
class BStringView;
class BTextControl;
class BButton;

#define BUTTON_BUY_OK 'buya' //ATENTION !=BUTTON_BUY
#define BT_BUY_CANCEL 'buyc'	
#define FIELD_UPDATE  'upda'	

class BuyWindow : public BWindow 
{
public:
		BStringView *x_view,*y_view,*a_view,*b_view,*c_view,*d_view,*e_view,*f_view;
		BStringView *g_view;
		BTextControl *infantry_control, *tank_control, *marine_control;
		BTextControl *airforce_control, *dca_control, *missile_control,*nuke_control;
		BButton *button_A,*button_B;
		Country *Ctry_a;

		BuyWindow(Country *ct1,Day *compteur); 

		virtual void 	MessageReceived(BMessage *message);		
				void	UpdateFields(); //calcule prix
};
#endif
