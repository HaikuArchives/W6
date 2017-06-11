#include "def_col.h"
#include "group.h"
#include "day.h"
#include "W6.h"

#include <Rect.h>
#include <Bitmap.h>
#include <File.h>
#include <Alert.h>
#include <stdio.h>

#include <iostream.h>

/**** Constructeurs Groupe ****/
Group::Group(unsigned char pl,const char *name, unsigned char numero, rgb_color col, unsigned char polit,char fname[255], Day *compteur)
{
	_name = name;
	_jour=compteur;
	nb=numero;
	grp_color=col; 
	politic=polit;
	player=pl;
	sprintf(flag_file_name,fname); //nom de fichier utilisé plus tard
	grp_power=0; 
	power_percent=0; 
	active=ON;

	BRect bitmap_rect;
	bitmap_rect.Set(0,0,FLAG_X_SIZE-1,FLAG_Y_SIZE-1);
	flag_ptr = new BBitmap(bitmap_rect, B_RGB_32_BIT);

	//par défaut rempli gris sombre
	unsigned char *bits;
	bits = (unsigned char *)flag_ptr->Bits(); 
	unsigned int t=0;
	
	while(t!=FLAG_X_SIZE*FLAG_Y_SIZE*4)
	{
		bits++;
		*bits=100;
		t++;
	} 
	
	load_bmp();
}

//---------------- Fonctions Groupe ----------------//



void Group::load_bmp()
{ 
  	BAlert* alert;	 
	BString	alertMessage;
	BString	app_path;
 	BFile fich;

	app_path = ((W6Application *)be_app)->app_dir();
	
   	//on rajoute le dossier
   	app_path << "flags/";
   	app_path << flag_file_name;
	
  	if(fich.SetTo(app_path.String(),B_READ_ONLY)!=B_NO_ERROR)
  	{ 
  		alertMessage = "For some reason, I could not load bitmap named:\n";
		alertMessage << app_path.String();
		alert = new BAlert("",alertMessage.String(),"oops..."); 
		alert->Go();
	}
  	else
  	{  
  	 	alertMessage = "Attempting to load bitmap named : ";
		alertMessage << app_path.String();
		
		// info
	//	cout << alertMessage.String() << endl;
		
		flag_ptr = ((W6Application *)be_app)->LoadBitmap(app_path.String());
	}
  	
  	if(flag_ptr==NULL)
  		flag_ptr = new BBitmap(BRect(0,0,FLAG_X_SIZE-1,FLAG_Y_SIZE-1), B_RGB32);
}