#ifndef GROUP_H
#define GROUP_H
//*************************************//
//******* Classe Group.h (alliance) *****//
//*************************************//

#include <InterfaceDefs.h>
#include <String.h>

class Day;
class BBitmap;

class Group
{
public:
	unsigned char nb, politic;		//numero de groupe, politique
	rgb_color grp_color;
	char flag_file_name[255];
	BBitmap *flag_ptr;
	Day		*_jour;
	uint64 grp_power;
	float power_percent;
    unsigned char player;
    unsigned char active; //pour savoir si on doit attaquer les autres
    					 //le communisme attaque pas la democracy avant
    					 //que le fascisme soit OFF
	
	Group(unsigned char who_plays_it,const char *name,unsigned char nb, rgb_color,unsigned char politic,char fname[255], Day *compteur);	// constructeur nb + col RGB + politic

	void load_bmp();

	inline	const char *Name()						{ return _name.String(); }
	inline	void		SetName(const char *name)	{ _name = name; }

protected:
	BString		_name;
};
#endif