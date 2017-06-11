#ifndef TXTVIEW_H
#define TXTVIEW_H

#include <StringView.h>

class TxtView : public BStringView 
{ 
	public: 
	TxtView(BRect frame, const char *name, const char *text);  
};
#endif