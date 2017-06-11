#ifndef W6_H
#define W6_H

#include <Application.h>
#include "def_col.h"       //creation des pays
#include <String.h>
#include <Bitmap.h>

class Country;
class Politic;
class Group;
class Day;
class Weapon;
class Running;
class BWindow;
class W6Window;
class InfoWindow;

class W6Application : public BApplication
{
public:
	Day			*_jour;
	Country	 	*_country[MAX_COUNTRY];	 //utilisé par les sous-fonctions type MouseDown
	Group		*_group[MAX_GROUP];  	 //CA MERDE SANS deux ** car c'est un tableau de pointeurs
	Politic		*_politic[MAX_POLITIC];   //CA MERDE SANS deux **
	Weapon  	*_weapon[MAX_WEAPON]; 
	Running 	*run_me;
	BWindow 	*runWin;
	W6Window	*mainWindow;
	InfoWindow	*infoWindow;

	W6Application();
	

	virtual	bool	QuitRequested();
	virtual void	MessageReceived(BMessage *message);
	virtual void	RefsReceived(BMessage *message);
			void	InitWeapon();
			void	InitGroup();
			void	Init();
   			BString	app_dir();
			
	// gestion image
	BBitmap			*LoadBitmap(const char *filename);
};


#endif //Main_H

