#ifndef COLGRPVIEW_H
#define COLGRPVIEW_H

#include <View.h>

class BWindow;

class ColGrpView : public BView
{
public:
	BWindow *the_win;
	bool	hidden;		

	ColGrpView(BRect r);

	virtual void	MouseMoved(BPoint point, uint32 transit, const BMessage *message);		
};
#endif