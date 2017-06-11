#include "day.h"
#include "def_col.h"
#include "W6.h"
#include "classSoundMaster.h"

#include <Alert.h>
#include <BitmapStream.h>
#include <TranslationUtils.h>
#include <File.h>
#include <Entry.h>

#include <iostream.h>

BubbleHelper bb_help; //en extern


Day::Day(int start_me) //CONSTRUCTEUR DAY
{
	
	zoom_level =1;
	days_per_month=31; //valeur pour janvier
	day_id=1;
	month_name="January";
	month_counter=1;
	year_counter=0;
	month_id=1;           //janvier
	start_year=start_me;
	year=start_year+year_counter;
	is_flag_load=OFF;

	//Ceci n'a rien à voir avec le Day mais bon je vais pas chier une classe exprès
	//et me faire chier à passer les paramètres pour une ou deux valeur globales.
	interligne = 16; //pour text
	full_log= ON;
	game_started = OFF;
	step=0;
	
	//nb de pulse a sauter avant d'agir...
	day_step=DEFAULT_DAY_STEP;
	jump_days=0;
	game_level=NORMAL;
	
	//avant de commencer faut choisir le joueur
	pause=ON;
	sprintf(history_text,"The Day it all started...");
	edit_mode=OFF; 
	paint_mode=OFF;
	rect_update_select.Set(0,0,DEF_PIC_X_SIZE-1,DEF_PIC_Y_SIZE-1);

	//taille du carré clignotant
	sq_size=6; 
	
	country_first = DEF_FIRST_COUNTRY;
	country_last  = DEF_LAST_COUNTRY;
	group_first   = DEF_FIRST_GROUP;
	group_last    = DEF_LAST_GROUP;
	politic_first   = DEF_FIRST_POLITIC;
	politic_last    = DEF_LAST_POLITIC;
	
	active_country = country_first;  
	active_group = GRP_G; //pour edit_mode et select du début
	active_politic = politic_first;

	sprintf(dossier_scenario,DEFAULT_SCENARIO_FOLDER);

	edit_grp_win_exists=OFF;
	edit_pol_win_exists=OFF;
}

//-----------------------------------------

void Day::next() //bon, ca fait pas les annees bissextiles mais faut pas deconner non plus
{
	day_id++;
	if(month_counter++ == days_per_month)
	{
		month_id++;
		month_counter=1;
	}

	switch(month_id) //d'apres defines.h
	{
	case  JANUARY:   days_per_month=31;   break; //NB de _jours par mois
	case  FEBRUARY:  days_per_month=28;   break;
    case  MARCH:     days_per_month=31;   break;
    case  APRIL:     days_per_month=30;   break;
    case  MAY:       days_per_month=31;   break;
    case  JUNE:      days_per_month=30;   break;
    case  JULY:      days_per_month=31;   break;
    case  AUGUST:    days_per_month=31;   break;
    case  SEPTEMBER: days_per_month=30;   break;
    case  OCTOBER:   days_per_month=31;   break;
    case  NOVEMBER:  days_per_month=30;   break;
    case  DECEMBER:  days_per_month=31;   break;
    }

	if(month_id > 12)
	{
		month_id=1;
		year_counter++;
	}

	switch(month_id)
   {
   case  1:   month_name = "January" ;  break;
   case  2:   month_name = "February" ;  break;
   case  3:   month_name = "March" ;  break;
   case  4:   month_name = "April" ;  break;
   case  5:   month_name = "May" ;  break;
   case  6:   month_name = "June" ;  break;
   case  7:   month_name = "July" ;  break;
   case  8:   month_name = "August" ;  break;
   case  9:   month_name = "September" ;  break;
   case 10:   month_name = "October" ;  break;
   case 11:   month_name = "November" ;  break;
   case 12:   month_name = "December" ;  break;
   }//fin de switch pour nom du _jour

	year=start_year+year_counter;
}//end of next_Day function

void Day::time_warp(int Days_to_advance)
{
	int ttt=0;
	while(ttt++!=Days_to_advance)
	{
		month_name="warping";
 		next();
 	}
}

/**** pour ajouter une chaine au texte ****/
void Day::add_history(char str_received[255])
{
	//si c'est pas le premier événement du _jour 
	if (strcmp(history_text, "stop_it")!=0)
	{
		strcat(history_text,"\n\t\t\t\t");
		strcat(history_text,str_received);
	}
	else
	{
		//si c'est le seul ou premier événément du _jour
		sprintf(history_text,str_received);
	}
}


void Day::StoreTranslatorBitmap(BBitmap *bitmap, char *filename, uint32 type) 
{ 
	//BTranslatorRoster *roster = BTranslatorRoster::Default(); 
    //BBitmapStream stream(bitmap); // init with contents of bitmap 
    //BFile file(filename, B_CREATE_FILE | B_WRITE_ONLY); 
   
   	//roster->Translate(&stream, NULL, NULL, &file, type); 
}



BBitmap* Day::load_bmp(const char *name)
{
	//tou_jours dans le dossier du scenar en cours et avec error check
	BAlert* alert;	 
	BString	fileName;
	BString	alertMessage;
	
	fileName = ((W6Application *)be_app)->app_dir();
	fileName << name;
	
  	BFile fich;
  	if (fich.SetTo(name,B_READ_ONLY)!=B_NO_ERROR)
  	{ 
  		alertMessage = "For some reason, I could not load bitmap named:\n";
		alertMessage << fileName.String();
	    alert = new BAlert("",alertMessage.String(),"oops..."); 
    	alert->Go();
	}
  	else
		return ((W6Application *)be_app)->LoadBitmap(fileName.String()) ;

	//si ça a merdé 	
 	return NULL;
}

BRect Day::find_win_pos(float width, float height)
{
	//trouve le point idéal pour poser la win
	BAlert *tmp;
	BPoint pt = tmp->AlertPosition(width, height); 
	BRect r;
	
	r.Set(pt.x, pt.y, pt.x+width, pt.y+height);
	
	return r;
}


void Day::PlaySoundFile(const char *name)
{
	BString				songName;

	// definir le chemin du son
	songName = ((W6Application *)be_app)->app_dir(); //trouve le dir actuel de l'application (a ne pas appeler avant de créer la win)
	songName << "sounds/";
	songName << name;			//et le nom du fichier

	BSound	*sound;
	entry_ref ref;
	BEntry entry(songName.String());
	BSoundPlayer::play_id id;

	if (entry.InitCheck() == B_OK && entry.GetRef(&ref) == B_OK)
	{
		sound = new BSound(&ref);  // Actually load the sound file into memory
		if(sound->InitCheck() == B_OK)
		{
			media_raw_audio_format fmt = sound->Format();
			
			BSoundPlayer	player(&fmt);
			player.Start();  // Init the player object and get it all ready to go.
			player.SetVolume(1.0);
			id = player.StartPlaying(sound);
			sound->ReleaseRef();
			player.WaitForSound(id);
		}
	}
}