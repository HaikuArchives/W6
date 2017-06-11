#ifndef ORDER_WINDOW_H
#define ORDER_WINDOW_H

#include "Window.h"

class Day;
class Country;
class BStringView;
class BSlider;
class BButton;

#define TEMP_CHANGED    'tmpc'	
#define WEATHER_CHANGED 'wthc'	
#define TAX_CHANGED 	'taxc'

class OrderWindow : public BWindow 
{
public:
	BStringView *x_view;
	BTextControl *tax_control;
	BSlider *slider_temp,*slider_weather;
	Country *Ctry_a;

	OrderWindow(Country *ct1,Day *compteur); 

	virtual void 	MessageReceived(BMessage *message);
};
#endif
