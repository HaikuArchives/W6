#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "def_col.h" //POUR GRP_X
#include <Window.h>
#include <FilePanel.h>

class Day;
class Country;
class Group;
class Politic;
class EditWindow;
class MainView;
class MapView;
class EditorView;
class PopWindow;
class HistoryView;
class PowerView;
class BuyWindow;
class OrderWindow;
class SpeedWindow;

#define ZOOM_200 'z200'
#define ZOOM_150 'z150'
#define ZOOM_100 'z100'
#define ZOOM_75 'zm75'
#define ZOOM_50 'zm50'
#define POWER_HEIGHT 10

class W6Window : public BWindow
{
public:
	EditorView		*e_view;
	BScrollView		*scroll_view;
	MapView			*inside_view; 
	HistoryView		*h_view; 
	PowerView 		*power_view;
	BView			*history_parent_view; 
	BScrollBar 		*history_v_scroll;
	BFilePanel 		*panneau_load;
	BFilePanel 		*panneau_save;
	float			mb_height; //pour taille menubar
	BuyWindow		*buyWindow;	
	OrderWindow		*setWindow;	
	SpeedWindow		*speedWindow;
	EditWindow		*editWindow;
	BMenuBar		*menubar; 
	BMenuItem 		*paintmode; //car le texte change pour celui-ci
	
	W6Window(BRect frame);

	virtual void 	MessageReceived(BMessage *message);
	virtual void	FrameResized(float width, float height);
			void	My_AboutBox();
			void	Restart();
			void	OpenHelp();
			void	ShortCuts(BMessage *msg);
			void	NotImplemented();

protected:
	Day				*_jour;
	Country 		**_country;	 
	Group			**_group;
	Politic			**_politic;
};


#endif //Main_WINDOW_H

