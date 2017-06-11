#ifndef DEF_COL_H
#define DEF_COL_H

#define WIN_X_SIZE  400  //TAILLE de la fenêtre
#define WIN_Y_SIZE  300 

#define INFO_X_SIZE  192
#define INFO_Y_SIZE  350 //max 600 utilisé 

#define EDIT_X_SIZE 352
#define EDIT_Y_SIZE 500

#define FLAG_X_SIZE 80
#define FLAG_Y_SIZE 48

#define EDIT_GRP_X_SIZE 280
#define EDIT_GRP_Y_SIZE 340

#define EDIT_POL_X_SIZE 280
#define EDIT_POL_Y_SIZE 470

#define HISTORY_Y_SIZE 90

#define DEF_PIC_X_SIZE  1160 //taille de la carte complete
#define DEF_PIC_Y_SIZE  740


#define UPDATE_POWER_BAR 'uppb'



#define	MENU_GAME_RESTART		'gmrs'
#define	MENU_GAME_PAUSE			'paus'
#define MENU_GAME_SET_DAY_RATE	'drat'
#define MENU_GAME_EDIT			'gedt'
#define	MENU_GAME_QUIT			'quit'

#define	MENU_LOAD		'load'
#define	MENU_SAVE		'save'


#define	MENU_LEVEL_EASY		'lvea'
#define	MENU_LEVEL_NORMAL	'lvnm'
#define	MENU_LEVEL_HARD		'lvhd'
#define	MENU_LEVEL_TOO_HARD		'lvth'

#define	MENU_SCENARIO		'mnsc'
#define	MENU_PAINT_MODE		'mnpt'
#define MENU_EDIT_REFRESH   'refr'
#define MENU_POLITIC   'polt'


#define LOG_IMPORTANT_MESSAGES 'lgim'

#define	MENU_ABOUT	'abou'
#define	MENU_DOC	'mdoc'

//FAUDRAIT PAS SETTER CES VALEURS EN DESSUS DE 255 vu que c'est des char
#define MAX_COUNTRY 255 //on es limité par un char...
#define MAX_GROUP   64 //pas trop quand meme!
#define MAX_POLITIC 64 //pas plus que de groupes!
#define MAX_WEAPON 24 
#define MAX_ATTACK 255 



#define PO_ANARCHY		0 //par d�faut, eh oui!
#define PO_DEMOCRACY	1
#define PO_FASCISM		2 
#define PO_COMMUNISM	3 
#define PO_KINGDOM		4 
#define PO_THEOCRACY	5
#define PO_SOCIALISM	6   //le communisme parfait
#define PO_NOTHING		64 //pour border and sea fake group

#define COMPUTER        0
#define PLAYER_01		1
#define PLAYER_02		2
#define PLAYER_03		3
#define PLAYER_04		4
#define PLAYER_05		5
#define PLAYER_06		6
#define PLAYER_07		7
#define PLAYER_08		8



#define EASY 2
#define NORMAL 1
#define HARD 0

//MESSAGES
#define DRAW_ACTIVE_COUNTRY 'dwct'
#define DRAW_INFO 	'dwif'
#define REDRAW_ME	'rdme'

#define SET_EDIT 	  'sded'
#define SET_GRP_EDIT  'sged'
#define UPDATE_GRP_EDIT  'udgd'

#define EDIT_UPDATE  'edup'
#define EDIT_GRP_UPDATE  'grup'

#define EDIT_CT_SELECT  'ctsl'
#define UPDATE_RELATIONS 'uprl'


#define UPDATE_TITLE 'uptt'

#define SET_POL_EDIT  	 'spet'
#define UPDATE_POL_EDIT  'upet'


#define GRP_COLOR_CHANGED 'gcch'


#define CT_NEXT 'ctnx'
#define CT_PREV 'ctpv'

#define MULTIPLY_RECT 'mprc'
#define MULTIPLY_ALL 'mpal'

#define SHOW_SELECT 'shsl'
#define DEFAULT_PULSE_RATE 		(1*1000000) //chaque seconde
#define DEFAULT_DAY_STEP 		4	//= 4 secondes
#define DEFAULT_SCENARIO_FOLDER "/w6s/"


//------------------------------------------------------------


#define OFF 0
#define ON  1
#define SELECT  255 //pour utiliser l'edit sans l'editmode
				   // pour choisir le pays
#define NOTHING  255 //pour utiliser l'edit sans l'editmode

#define FRIEND 0
#define ENNEMY 1 
#define NEUTRAL 2


#define BECOMES_FRIEND 	 'bcfr'
#define BECOMES_ENNEMY 	 'bcen'
#define BECOMES_NEUTRAL 'bcnt'

//DEFINITIONS numéros groupe 
#define GRP_A 0
#define GRP_B 1
#define GRP_C 2
#define GRP_D 3
#define GRP_E 4
#define GRP_F 5
#define GRP_G 6
#define GRP_H 7
#define GRP_I 8
#define GRP_J 9
#define GRP_X 255

//DEFINITIONS POUR LES POLITIQUES PO_XX
	
//DEFINITIONS COULEURS CORRESPONDANT A UN PAYS DANS LA PALETTE
//SUR LA PIC 8 bits des frontieres
//NECESSAIRE MEME AVEC L'editeur!!!
#define COL_BORDER 0  	      //couleur des frontieres
#define COL_SEA    1	         //couleur de l'eau
#define COL_EMPTY 255		//pays vide pour editeur

//ATTENTION IL NE FAUT ABSOLUMENT PAS qu'il y ait de chiffre vide,
//sinon ca fait un pointeur non initialise et qui va tout faire merder
#define PORTUGAL      2
#define SPAIN         3
#define FRANCE        4
#define UK            5
#define ITALY         6
#define BELGIUM       7
#define SLOVAKIA      8
#define GERMANY       9
#define NETHERLANDS   10
#define DENMARK       11
#define NORWAY        12
#define AUSTRIA       13
#define CZECHIA       14
#define HUNGARY       15
#define ROMANIA       16
#define BULGARIA      17
#define ALBANIA       18
#define GREECE        19
#define TURKEY        20
#define RUSSIA        21
#define MONGOLIA      22
#define CHINA         23
#define AFGHANISTAN   24
#define IRAN          25
#define IRAK          26
#define SAUDI_ARABIA  27
#define KOWEIT        28
#define EGYPT         29
#define ISRAEL        30
#define JORDANIA      31
#define SYRIA         32
#define SUDAN         33
#define LYBIA         34
#define TUNISIA       35
#define ALGERIA       36
#define MOROCCO       37
#define GUINEA_BISSAU 38
#define MAURITANIA    39
#define MALI       	 40
#define SENEGAL	    41
#define DJIBOUTI	    42
#define GUINEA        43
#define SIERRA_LEONE  44
#define LIBERIA	    45
#define IVORY_COAST	 46
#define GHANA	       47
#define BURKINA_FASO  48
#define TOGO	       49
#define BENIN         50
#define NIGER         51
#define NIGERIA	    52
#define CAMEROON	    53
#define TCHAD	       54
#define CENTRAFRICA	 55
#define EQUATORIAL_GUINEA  56
#define GABON	       57
#define REP_CONGO	    58
#define CONGO	       59  //ex Zaire
#define UGANDA	       60
#define ETHIOPIA      61
#define SOMALIA       62
#define KENYA	       63
#define RWANDA	       64
#define BURUNDI	    65
#define TANZANIA	    66
#define MOZAMBIQUE    67
#define MALAWI 	    68
#define MADAGASCAR    69
#define ZAMBIA	       70
#define ZIMBABWE	    71
#define SOUTH_AFRICA  72
#define BOTSWANA	    73
#define NAMIBIA	    74
#define ANGOLA	       75
#define LESOTHO	    76
#define SWAZILAND	    77
#define INDIA	       78
#define NEPAL	       79
#define BUTHAN	       80
#define BANGLA_DESH   81
#define SRI_LANKA	    82
#define BIRMANIA      83
#define THAILAND      84
#define LAOS	       85
#define CAMBODGE	    86
#define VIETNAM 	    87
#define NORTH_KOREA   88
#define SOUTH_KOREA   89
#define JAPAN	       90
#define MALAYSIA 	    91
#define INDONESIA	    92
#define PHILIPPINES   93
#define AUSTRALIA     94
#define NEW_ZEALAND   95
#define NEW_GUINEA    96
#define ICELAND       97
#define GROENLAND     98
#define CANADA        99
#define USA           100
#define MEXICO        101
#define BELIZE        102
#define GUATEMALA     103
#define HONDURAS      104
#define SALVADOR      105
#define NICARAGUA     106
#define COSTA_RICA    107
#define PANAMA        108
#define SLOVENIA	    109
#define COLOMBIA      110
#define CUBA	       111
#define JAMAICA	    112
#define HAITI	       113
#define DOMINICAN	    114
#define PUERTO_RICO	 115
#define VENEZUELA     116
#define GUYANA	       117 //Guyana UK
#define GUYANA_FR     118 
#define SURINAM	    119 //Guyana NL
#define BRAZIL        120
#define PERU          121
#define ECUADOR	    122
#define BOLIVIA       123
#define PARAGUAY      124
#define ARGENTINA     125
#define URUGUAY       126
#define CHILI         127
#define GAMBIA	       128
#define YEMEN         129
#define SOUTH_YEMEN   130
#define OMAN          131
#define TAIWAN	       132
#define SERBIA        133
#define LITHUANIA     134
#define SWEDEN        135
#define POLAND        136
#define QATAR         137
#define SWITZERLAND   138
#define FINLAND       139
#define ESTONIA       140
#define LETTONIA      141
#define IRELAND       142
#define PAKISTAN      143
#define LEBANON       144
#define BELARUS		  145
#define UKRAINE       146
#define MOLDAVIA      147
#define GEORGIA       148
#define ARMENIA       149
#define AZERBAIDJAN   150
#define KAZAKHSTAN    151
#define TURKMENISTAN  152
#define UZBEKISTAN    153
#define TADZIKISTAN   154
#define KIRGIKISTAN   155
#define UAE           156 //united arabic emirates pas un emulateur amiga!
#define BOSNIA		  157
#define CROATIA		  158

#define DEF_FIRST_POLITIC   0 //tou_jours egal au premier
#define DEF_LAST_POLITIC    6 //tou_jours egal au plus haut de la liste

#define DEF_FIRST_GROUP   0 //tou_jours egal au premier
#define DEF_LAST_GROUP   9 //tou_jours egal au plus haut de la liste

#define DEF_FIRST_COUNTRY   2 //tou_jours egal au premier
#define DEF_LAST_COUNTRY  158 //tou_jours egal au plus haut de la liste

#endif