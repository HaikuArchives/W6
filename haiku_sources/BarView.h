#ifndef BARVIEW_H
#define BARVIEW_H

#include <View.h>

class BarView : public BView 
{
public:
		BarView(BRect r,const char *name,float limit, const char* limit_text);
		char name[255];
		char limit_text[255];
		virtual	void Draw(BRect);
		float percentage,limit;
};
#endif