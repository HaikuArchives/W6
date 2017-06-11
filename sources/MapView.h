#ifndef Map_VIEW_H
#define Map_VIEW_H

#include <View.h>
#include <String.h>
#include "def_col.h"

class Country;
class Politic;
class Group;
class Day;
class BBitmap;
class SendWindow;

#define		NO_COUNTRY_SELECTED		-1

class MapView : public BView
{
public:
	BString		_DestName;
	BString		_SrcName;
	BPoint		_startPoint;
	BPoint		_destPoint;
	BPoint		_oldDestPoint;
	int16		_currentCountry;
//--------------------------------------	
	BBitmap		*final_bitmap;
	BBitmap		*frontier_bitmap;
	BBitmap		*bump_bitmap;
	BRect		selection;
	uchar		frontier_palette[256*3]; //couleurs des pays frontier_bitmap
	uchar		bump_palette[256*3]; //couleurs du bump (gris
	//TxtView	*pos_view;
	float		pause_angle;
	SendWindow	*sendWindow;
	BRect		v_rect;
	BRect		old_line_rect;
	BPoint		delta;
	uint8		previous_ct; 
	uint16 		result;
	uint8 		agressor,victim; 
	bool 		country_selected;
	uint8 		tab_multiply[256][256];
	bool 		dragging;
	bool		_scrollView;

	MapView(BRect r, long flags);
	virtual	~MapView();

	virtual	void	Pulse();
	virtual	void	Draw(BRect);
	virtual void	MouseMoved(BPoint point, uint32 transit, const BMessage *message);
	virtual void	MouseDown(BPoint where);
	virtual void 	MouseUp(BPoint point);
			void	UpdateTitle();
			void	MultiplyCountrySelected();
			void 	Multiply(BRect la_zone);
			void 	MultiplyAll();
			void	Init();
			void 	ShowTroops();
			void	ErasePlayerLine();
			void	CountriesChosen();
			int16	SelectCountry(BPoint pix);
			BRect	SelectedFrameCountry();
			void	update_map_palette();
			void	set_gray_palette(); //celui-là on le fait qu'une fois au début et fertig
			void	set_frontier_palette(unsigned char which_color,unsigned char rval, unsigned char gval,unsigned char bval); 

protected:
	Day			*_jour;
	Country 	**_country;	  
	Group		**_group; 
	Politic 	**_politic;
	
			bool	PointOfCountry(BPoint point);
};
#endif
