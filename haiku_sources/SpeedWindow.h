#ifndef SPEED_WINDOW_H
#define SPEED_WINDOW_H

#include <Window.h>
#include <InterfaceDefs.h>


class Day;
class BStringView;
class BTextControl;
class BButton;
class BSlider;

#define SPEED_CHANGED 'spdc'	

class SpeedWindow : public BWindow 
{
public:
	BStringView *x_view,*y_view;
	BSlider *slider_speed;
	BSlider *slider_jump;
	Day *_jour;

	SpeedWindow(Day *compteur); 

	virtual void 	MessageReceived(BMessage *message);
};
#endif