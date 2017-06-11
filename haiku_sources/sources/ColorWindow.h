#ifndef COLOR_WINDOW_H
#define COLOR_WINDOW_H

#include "Window.h"

class Day;
class Country;
class Group;
class BColorControl;

#define BUTTON_BUY 'buyt'
#define BUTTON_SET 'btor'
#define GROUP_COLOR_CHANGED    'grpc'

class ColorWindow : public BWindow 
{
public:
	rgb_color		coul;
	BColorControl	*col_control;
	Group			*grp;
	Day				*_jour;

	ColorWindow(Group *grp_x,Day *compteur); 
	virtual void 	MessageReceived(BMessage *message);
};
#endif
