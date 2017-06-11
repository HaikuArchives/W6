#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <TextView.h>

class Day;

class HistoryView : public BTextView
{
public:
	Day			*_jour;
	rgb_color	coul_a,coul_b;
		
	HistoryView(BRect frame, const char *name, BRect text, bool incoming,BFont *font, Day *ddd);
	virtual void		Pulse();
};
#endif