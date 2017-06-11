#ifndef DAY_H
#define DAY_H

#include "def_col.h"

#define JANUARY     1
#define FEBRUARY    2
#define MARCH       3
#define APRIL       4
#define MAY         5
#define JUNE        6
#define JULY        7
#define AUGUST      8
#define SEPTEMBER   9
#define OCTOBER    10
#define NOVEMBER   11
#define DECEMBER   12


//TOUS CES INCLUDES SONT LA POUR LES AUTRES FILES QUI UTILISENT TOUS DAY.H
//je vais pas m'amuser à les remettre partout pour ce jeu à la con...
//merci release 4 et GNUC...
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

#include "BubbleHelper.h"
#include <InterfaceDefs.h>
#include <Rect.h>
#include <Menu.h> 
#include <Alert.h> 

class BWindow;

extern BubbleHelper bb_help;

class Day
{
public:
   	long 				day_id;
   	int 				days_per_month,month_counter, year_counter, month_id, start_year, year;
   	const char 			*month_name;
   	unsigned int 		day_step,step;
   	unsigned char 		country_first,country_last;
   	unsigned char 		group_first,group_last;
   	unsigned char 		politic_first,politic_last;
   	BRect 				rect_update_select;
   	BRect 				rect_update_troops;
   	char 				dossier_app[2048];
   	char 				dossier_scenario[255];
   	BMenu				*edit_menu;
   	unsigned char 		edit_grp_win_exists;
   	unsigned char 		info_win_exists;
   	unsigned char 		edit_pol_win_exists;
	BScrollBar 			*scroll_hori  ;
	BScrollBar 			*scroll_verti ;
	int16 				jump_days;
	unsigned char 		is_flag_load;
	BButton 			*button_Done;
	unsigned char 		weapon_last,weapon_first;
 	BWindow				*mainWin, *editWin, *edit_grpWin, *edit_polWin, *infoWin;
   	uint16 				interligne; //pour text
   	unsigned char 		full_log; //à ON on display aussi les resistance attacks
   	//Ceci n'a rien à voir avec le day mais bon je vais pas chier une classe exprès
   	//et me faire chier à passer les paramètres pour une ou deux valeur globales.
   	unsigned char 		player_group;
   	unsigned char 		active_country;
   	unsigned char 		active_group; //pour edit_mode
   	unsigned char 		active_politic; //pour edit_mode
   	unsigned char 		game_level;
   	unsigned char 		pause, game_started;
   	unsigned char 		edit_mode;
   	unsigned char 		paint_mode; //dans edit mode 
   	color_space 		old_space; //pour conserver ancienne resolution
   	BRect	   			old_frame;
   	float 				zoom_level;
   	BAlert 				*main_alert; //pour init du début
   	//faut beaucoup de place pour si jamais il se passe des trucs partout
   	//et on doit faire des strcat() à donf
   	char 				history_text[65536];
   	unsigned char 		sq_size;//carré de position troops
   

   	Day(int);    //constructeur valeur annee debut
   	
   	void	add_history(char str_received[255]);
   	void	next();  //avance d'un _jour
   	void	time_warp(int days_to_advance); //avance de X _jours
	void	PlaySoundFile(const char *name);
	BRect	find_win_pos(float width, float height);
	
	//fonctions pour loader BBItmap (from BeBook tel quel)   
	BBitmap*	load_bmp(const char *name);
	void 		StoreTranslatorBitmap(BBitmap *bitmap, char *filename, uint32 type) ;
};


#endif
