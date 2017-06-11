#include "HistoryView.h"
#include "day.h"

/**** constructeur ****/
HistoryView::HistoryView(BRect frame, const char *name, BRect text,bool incoming, BFont *font, Day *ddd)
: BTextView(frame, "", text, B_PULSE_NEEDED | B_FOLLOW_BOTTOM | B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW | B_NAVIGABLE)
{	
	_jour = ddd;
	rgb_color x = {0,190,0};
	rgb_color y = {0,220,0};
	coul_a = x;
	coul_b = y;

	MakeEditable(false);
	MakeSelectable(false);
	SetViewColor(0,32,0); 
	SetFontAndColor(be_plain_font, B_FONT_ALL, &coul_b);
}

/**** pulse ****/
void HistoryView::Pulse()
{
	//égal à zéro si identique
	if (strcmp(_jour->history_text, "stop_it")!=0  )
	{
		char str[255];
		char str2[255];

		Insert("\n");	
		sprintf(str," %i, %i",_jour->month_counter, _jour->year);
		sprintf(str2,_jour->month_name);
		strcat(str2,str); //on joint les deux bouts après car types différents
		Insert(str2);
		Insert("  \t\t");
		Insert(_jour->history_text);
		sprintf(_jour->history_text,"stop_it"); //on remet à zéro
	
		ScrollToOffset(OffsetAt(CurrentLine()-1 ) );
	}
} 
