#include "TxtView.h"

TxtView::TxtView(BRect rect, const char *name, const char *text)
: BStringView(rect, name, text, B_FOLLOW_TOP | B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW)
{
	SetFont(be_bold_font);
	SetFontSize(12);
	SetHighColor(255,255,255);
	SetAlignment(B_ALIGN_CENTER);
}
