#include "W6.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "politic.h"
#include "weapon.h"

/**** initialisation arme ****/
void W6Application::InitWeapon()
{
	_jour->weapon_first= 0;
	_weapon[0]         =  new Weapon("Infantry",	0, 	0.01,	1, 		1, 		1500,	ON,		ON,		-1); //-1 tout le monde se bat
	_weapon[1]         =  new Weapon("Tanks",		1,  6,	 	3, 		40, 	10,		ON,		ON,		-1);
	_weapon[2]         =  new Weapon("Marine",		2,   100,	200, 	350, 	1,		ON,		ON,		-1);
	_weapon[3]         =  new Weapon("Airforce",	3,  	15,		5, 		60, 	2,		ON,		ON,		-1);
	_weapon[4]         =  new Weapon("Missile",		4,  	50,		10, 	250, 	2,		ON,		OFF,	16);
	_weapon[5]         =  new Weapon("DCA",			5,  	5,		7, 		150, 	2,		OFF,	ON,		-1);
	_weapon[6]         =  new Weapon("Nukes",		6,  200,	7, 		25000, 	2,		ON,		OFF,	-2);
	_jour->weapon_last = 6;
}

/**** initialiser les groupes ****/
void W6Application::InitGroup()
{
//PAR DEFAUT TOUT LES GROUPES SONT AU COMPUTER
//creation de Groupes et Politiques plus bas

//les numeros des politiques sont définis dans def_col
//PO_ANARCHY =0 ... PO_SOCIALISM=6
 _jour->politic_first = PO_ANARCHY;   //premier groupe
 _jour->politic_last  = PO_SOCIALISM; //dernier groupe
 _politic[PO_ANARCHY]    = new Politic    ("Anarchy"   ,PO_ANARCHY);
 _politic[PO_DEMOCRACY]  = new Politic    ("Democracy" ,PO_DEMOCRACY);
 _politic[PO_FASCISM]    = new Politic    ("Fascism"   ,PO_FASCISM);
 _politic[PO_COMMUNISM]  = new Politic    ("Communism" ,PO_COMMUNISM);
 _politic[PO_KINGDOM]    = new Politic    ("Kingdom"   ,PO_KINGDOM);
 _politic[PO_THEOCRACY]  = new Politic    ("Theocracy" ,PO_THEOCRACY);
 _politic[PO_SOCIALISM]  = new Politic    ("Socialism" ,PO_SOCIALISM);
 
 //pour sea and border fake countries
 _politic[PO_NOTHING]    = new Politic      ("FAKE POLITIC" ,PO_NOTHING);
 //par défaut, elle est amie avec tous donc on modifie rien
 
 //repression (1 à 100);
 _politic[PO_ANARCHY]->repression=0; 
 _politic[PO_DEMOCRACY]->repression=10; 
 _politic[PO_FASCISM]->repression=95; 
 _politic[PO_COMMUNISM]->repression=75; 
 _politic[PO_KINGDOM]->repression=50; 
 _politic[PO_THEOCRACY]->repression=85; 
 _politic[PO_SOCIALISM]->repression=15; 
 _politic[PO_NOTHING]->repression=0; 
 
 //propaganda (1 à 100);
 _politic[PO_ANARCHY]->propaganda=0; 
 _politic[PO_DEMOCRACY]->propaganda=10; 
 _politic[PO_FASCISM]->propaganda=30; 
 _politic[PO_COMMUNISM]->propaganda=35; 
 _politic[PO_KINGDOM]->propaganda=15; 
 _politic[PO_THEOCRACY]->propaganda=20; 
 _politic[PO_SOCIALISM]->propaganda=20; 
 _politic[PO_NOTHING]->propaganda=0; 
 
//-------------------------------------------------------------------------------------------
 
 
 //Relations entre les politiques

 //anarchy
 _politic[PO_ANARCHY]->relation[PO_ANARCHY]=FRIEND; //Anarchy "aime" tout le monde
 _politic[PO_ANARCHY]->relation[PO_DEMOCRACY]=FRIEND; //et attaque personne
 _politic[PO_ANARCHY]->relation[PO_FASCISM]=FRIEND; 
 _politic[PO_ANARCHY]->relation[PO_COMMUNISM]=FRIEND; 
 _politic[PO_ANARCHY]->relation[PO_KINGDOM]=FRIEND;
 _politic[PO_ANARCHY]->relation[PO_THEOCRACY]=FRIEND; 
 _politic[PO_ANARCHY]->relation[PO_SOCIALISM]=FRIEND; 
 _politic[PO_ANARCHY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Democracy
 _politic[PO_DEMOCRACY]->relation[PO_ANARCHY]=NEUTRAL; 
 _politic[PO_DEMOCRACY]->relation[PO_DEMOCRACY]=FRIEND; 
 _politic[PO_DEMOCRACY]->relation[PO_FASCISM]=ENNEMY; 
 _politic[PO_DEMOCRACY]->relation[PO_COMMUNISM]=NEUTRAL; 
 _politic[PO_DEMOCRACY]->relation[PO_KINGDOM]=ENNEMY; 
 _politic[PO_DEMOCRACY]->relation[PO_THEOCRACY]=ENNEMY; 
 _politic[PO_DEMOCRACY]->relation[PO_SOCIALISM]=NEUTRAL; 
 _politic[PO_DEMOCRACY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Fascism
 _politic[PO_FASCISM]->relation[PO_ANARCHY]=ENNEMY; 
 _politic[PO_FASCISM]->relation[PO_DEMOCRACY]=ENNEMY; 
 _politic[PO_FASCISM]->relation[PO_FASCISM]=NEUTRAL; 
 _politic[PO_FASCISM]->relation[PO_COMMUNISM]=ENNEMY;  
 _politic[PO_FASCISM]->relation[PO_KINGDOM]=NEUTRAL;  
 _politic[PO_FASCISM]->relation[PO_THEOCRACY]=NEUTRAL;  
 _politic[PO_FASCISM]->relation[PO_SOCIALISM]=ENNEMY;  
 _politic[PO_FASCISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Communism
 _politic[PO_COMMUNISM]->relation[PO_ANARCHY]=NEUTRAL; //Fascism deteste tous meme fascism
 _politic[PO_COMMUNISM]->relation[PO_DEMOCRACY]=NEUTRAL; 
 _politic[PO_COMMUNISM]->relation[PO_FASCISM]=ENNEMY; 
 _politic[PO_COMMUNISM]->relation[PO_COMMUNISM]=FRIEND;  
 _politic[PO_COMMUNISM]->relation[PO_KINGDOM]=ENNEMY;  
 _politic[PO_COMMUNISM]->relation[PO_THEOCRACY]=ENNEMY;  
 _politic[PO_COMMUNISM]->relation[PO_SOCIALISM]=NEUTRAL;  
 _politic[PO_COMMUNISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Kingdom
 _politic[PO_KINGDOM]->relation[PO_ANARCHY]=ENNEMY; 
 _politic[PO_KINGDOM]->relation[PO_DEMOCRACY]=ENNEMY; 
 _politic[PO_KINGDOM]->relation[PO_FASCISM]=NEUTRAL; 
 _politic[PO_KINGDOM]->relation[PO_COMMUNISM]=ENNEMY;  
 _politic[PO_KINGDOM]->relation[PO_KINGDOM]=NEUTRAL;  
 _politic[PO_KINGDOM]->relation[PO_THEOCRACY]=NEUTRAL;  
 _politic[PO_KINGDOM]->relation[PO_SOCIALISM]=ENNEMY;  
 _politic[PO_KINGDOM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Theocracy
 _politic[PO_THEOCRACY]->relation[PO_ANARCHY]=ENNEMY; 
 _politic[PO_THEOCRACY]->relation[PO_DEMOCRACY]=ENNEMY; 
 _politic[PO_THEOCRACY]->relation[PO_FASCISM]=NEUTRAL; 
 _politic[PO_THEOCRACY]->relation[PO_COMMUNISM]=ENNEMY;  
 _politic[PO_THEOCRACY]->relation[PO_KINGDOM]=NEUTRAL;  
 _politic[PO_THEOCRACY]->relation[PO_THEOCRACY]=ENNEMY;  
 _politic[PO_THEOCRACY]->relation[PO_SOCIALISM]=ENNEMY;  
 _politic[PO_THEOCRACY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Socialism
 _politic[PO_SOCIALISM]->relation[PO_ANARCHY]=NEUTRAL; 
 _politic[PO_SOCIALISM]->relation[PO_DEMOCRACY]=NEUTRAL; 
 _politic[PO_SOCIALISM]->relation[PO_FASCISM]=ENNEMY; 
 _politic[PO_SOCIALISM]->relation[PO_COMMUNISM]=NEUTRAL;  
 _politic[PO_SOCIALISM]->relation[PO_KINGDOM]=ENNEMY;  
 _politic[PO_SOCIALISM]->relation[PO_THEOCRACY]=ENNEMY;  
 _politic[PO_SOCIALISM]->relation[PO_SOCIALISM]=FRIEND;  
 _politic[PO_SOCIALISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 


 //NOTHING
 _politic[PO_NOTHING]->relation[PO_ANARCHY]   = FRIEND; 
 _politic[PO_NOTHING]->relation[PO_DEMOCRACY] = FRIEND; 
 _politic[PO_NOTHING]->relation[PO_FASCISM]   = FRIEND; 
 _politic[PO_NOTHING]->relation[PO_COMMUNISM] = FRIEND;  
 _politic[PO_NOTHING]->relation[PO_KINGDOM]   = FRIEND;  
 _politic[PO_NOTHING]->relation[PO_THEOCRACY] = FRIEND;  
 _politic[PO_NOTHING]->relation[PO_SOCIALISM] = FRIEND;  
 _politic[PO_NOTHING]->relation[PO_NOTHING]   = FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 




//----------------------------------------------------



//----------------------------------------------------
//CREATION GROUPES
  
 rgb_color couleur;

 _jour->group_first=GRP_A; //premier groupe

 couleur= (rgb_color) {230,230,230,0};
 _group[GRP_A]      = new Group  		(COMPUTER,"Pacific Union",GRP_A,couleur,PO_ANARCHY,"pacific.png",_jour);

 couleur= (rgb_color) {190,160,172,0};
 _group[GRP_B]         =  new Group		(COMPUTER,"White Nationalists",GRP_B,couleur,PO_FASCISM,"white.png",_jour);

 couleur= (rgb_color) {230,170,0,0};
 _group[GRP_C]         = new Group        (COMPUTER,"African Union",GRP_C,couleur,PO_DEMOCRACY,"africa.png",_jour);

 couleur= (rgb_color) {240,0,0,0};
 _group[GRP_D]         = new Group    (COMPUTER,"Neo-Communist Union",GRP_D,couleur,PO_COMMUNISM,"soviet.png",_jour);
 
 couleur= (rgb_color) {97,181,90,0};
 _group[GRP_E]         =  new Group           (COMPUTER,"Islamic Revolution",GRP_E,couleur,PO_THEOCRACY,"islam.png",_jour);
 
 couleur= (rgb_color) {255,255,100,0};
 _group[GRP_F]         = new Group        (COMPUTER,"Sun Empire",GRP_F,couleur,PO_KINGDOM,"japan.png",_jour);

 couleur= (rgb_color) {98,156,255,0};
 _group[GRP_G]         = new Group          (COMPUTER,"European Union",GRP_G,couleur,PO_DEMOCRACY,"europe.png",_jour);

 couleur= (rgb_color) {186,200,255,0};
 _group[GRP_H]         = new Group          (COMPUTER,"Christian Nation",GRP_H,couleur,PO_THEOCRACY,"christ.png",_jour);

 couleur= (rgb_color) {255,100,185,0};
 _group[GRP_I]         =new Group         (COMPUTER,"Socialist Group",GRP_I,couleur,PO_SOCIALISM,"social.png",_jour);

 couleur= (rgb_color) {255,210,210,0};
 _group[GRP_J]         = new Group      (COMPUTER,"Roschti Neutral Activists",GRP_J,couleur,PO_DEMOCRACY,"roschti.png",_jour);
 
 _jour->group_last=GRP_J; //dernier groupe
 
 couleur= (rgb_color) {0,255,120,120}; //vert pétant
 _group[GRP_X]         = new Group      (COMPUTER,"Fake for sea and border",GRP_X,couleur,PO_NOTHING,"",_jour);
}

/**** initialisation generale ****/
void W6Application::Init()
{
 //****  creation de pays *****

/*
ATTENTION GRAND CON, oui ça changé entre l'europe et les autres groupes.
des fois on a créée bêtement des pointeurs en trop alors qu'on a pas besoin
ils sont déja dans _country... sauf que comme on utilise ces pointeur dans
DATA.CPP FAUT PAS MODIFIER, sinon faut modifier aussi data.cpp et c'est long
de toute façon ces données finiront dans
un fichier .w6s tôt ou tard. Donc elles auront la même gueule dans l'éditeur
Pigé?
Blaireau va! ;-)
*/
 
 //europ
 _country[PORTUGAL]   = new Country ("Portugal",PORTUGAL,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SPAIN]      = new Country ("Spain",SPAIN,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[FRANCE]     = new Country ("France",FRANCE,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[UK]         = new Country ("United Kingdom",UK,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[ITALY]      = new Country ("Italy",ITALY,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[BELGIUM]    = new Country ("Belgium",BELGIUM,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SLOVAKIA]   = new Country ("Slovakia",SLOVAKIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[GERMANY]    = new Country ("Germany",GERMANY,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[NETHERLANDS]= new Country ("Netherlands",NETHERLANDS,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[DENMARK]    = new Country ("Denmark",DENMARK,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[NORWAY]     = new Country ("Norway",NORWAY,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[AUSTRIA]    = new Country ("Austria",AUSTRIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[CZECHIA]    = new Country ("Czech Republic",CZECHIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[GREECE]     = new Country ("Greece",GREECE,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SERBIA]     = new Country ("Serbia",SERBIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[LITHUANIA]  = new Country ("Lithuania",LITHUANIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SWEDEN]     = new Country ("Sweden",SWEDEN,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[POLAND]     = new Country ("Poland",POLAND,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SWITZERLAND]= new Country ("Switzerland",SWITZERLAND,GRP_J,_jour,_group,_country, _politic, _weapon); //eh, oui
 _country[FINLAND]    = new Country ("Finland",FINLAND,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[ESTONIA]    = new Country ("Estonia",ESTONIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[LETTONIA]   = new Country ("Lettonia",LETTONIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[IRELAND]    = new Country ("Ireland",IRELAND,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[BOSNIA]     = new Country ("Bosnia Herzegovina",BOSNIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[CROATIA]    = new Country ("Croatia",CROATIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SLOVENIA]   = new Country ("Slovenia",SLOVENIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[GUYANA_FR]  = new Country ("Guyana (french)",GUYANA_FR,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[SURINAM]    = new Country ("Surinam",SURINAM,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[ICELAND]    = new Country ("Iceland",ICELAND,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[GROENLAND]  = new Country ("Greenland",GROENLAND,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[HUNGARY]    = new Country ("Hungary",HUNGARY,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[ROMANIA]    = new Country ("Romania",ROMANIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[BULGARIA]   = new Country ("Bulgaria",BULGARIA,GRP_G,_jour,_group,_country, _politic, _weapon);
 _country[ALBANIA]    = new Country ("Albania",ALBANIA,GRP_G,_jour,_group,_country, _politic, _weapon);


//bon là à partir d'ici c'est un peu la version longue du grand bleu mais on s'en fout ça marche

 //soviet
 Country *russia;
 russia = new Country          ("Russia",RUSSIA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[RUSSIA]         = russia              ;


Country *mongolia;
 mongolia= new Country          ("Mongolia",MONGOLIA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[MONGOLIA]         = mongolia            ;

Country *china;
 china = new Country              ("China",CHINA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[CHINA]         = china               ;

Country *belarus;
 belarus= new Country        ("Belarus",BELARUS,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[BELARUS]         = belarus         ;

Country *ukraine;
 ukraine= new Country             ("Ukraine", UKRAINE,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[UKRAINE]         = ukraine            ;

Country *moldavia;
 moldavia= new Country            ("Moldavia",MOLDAVIA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[MOLDAVIA]         = moldavia            ;

Country *georgia;
 georgia= new Country              ("Georgia",GEORGIA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[GEORGIA]         = georgia             ;

Country *armenia;
 armenia = new Country              ("Armenia",ARMENIA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[ARMENIA]         = armenia             ;

Country *kazakhstan;
 kazakhstan = new Country           ("Kazakhstan",KAZAKHSTAN ,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[KAZAKHSTAN ]         = kazakhstan          ;

Country *uzbekistan;
 uzbekistan= new Country           ("Uzbekistan",UZBEKISTAN,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[UZBEKISTAN]         = uzbekistan          ;

Country *tadzikistan;
 tadzikistan= new Country         ("Tadzikistan",TADZIKISTAN,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[TADZIKISTAN]         = tadzikistan         ;

Country *kirgikistan;
 kirgikistan = new Country          ("Kirgikistan",KIRGIKISTAN,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[KIRGIKISTAN]         = kirgikistan         ;

Country *north_korea ;
 north_korea = new Country         ("Northern Korea",NORTH_KOREA,GRP_D,_jour,_group,_country, _politic, _weapon);
 _country[NORTH_KOREA]         = north_korea         ;
//et le zizikistan alors?

 //islam
Country *turkey;
 turkey = new Country               ("Turkey",TURKEY,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[TURKEY]         = turkey              ;

Country *afghanistan;
 afghanistan = new Country          ("Afghanistan",AFGHANISTAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[AFGHANISTAN]         = afghanistan         ;

Country *iran;
 iran = new Country                ("Iran",IRAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[IRAN]         = iran                ;

Country *irak;
 irak = new Country                ("Irak",IRAK,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[IRAK]         = irak                ;

Country *saudi_arabia ;
 saudi_arabia = new Country        ("Saudi Arabia",SAUDI_ARABIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[SAUDI_ARABIA]         = saudi_arabia        ;

Country *koweit;
koweit = new Country              ("Koweit",KOWEIT,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[KOWEIT]         = koweit              ;

Country *egypt;
egypt = new Country               ("Egypt",EGYPT,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[EGYPT]         = egypt               ;

Country *jordania;
 jordania= new Country            ("Jordania",JORDANIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[JORDANIA]         = jordania            ;

Country *syria;
syria = new Country               ("Syria",SYRIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[SYRIA]         = syria               ;

Country *sudan;
 sudan = new Country               ("Sudan",SUDAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[SUDAN]         = sudan               ;

Country *lybia;
lybia = new Country               ("Lybia",LYBIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[LYBIA]         = lybia               ;

Country *tunisia;
tunisia = new Country             ("Tunisia",TUNISIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[TUNISIA]         = tunisia             ;

Country *algeria;
 algeria = new Country             ("Algeria",ALGERIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[ALGERIA]         = algeria             ;

Country *morocco;
morocco = new Country             ("Morocco",MOROCCO,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[MOROCCO]         = morocco             ;

Country *djibouti;
 djibouti= new Country            ("Djibouti",DJIBOUTI,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[DJIBOUTI]         = djibouti            ;

Country *somalia;
 somalia= new Country             ("Somalia",SOMALIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[SOMALIA]         = somalia             ;

Country *qatar;
 qatar= new Country               ("Qatar",QATAR,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[QATAR]         = qatar               ;

Country *azerbaidjan;
 azerbaidjan= new Country          ("Azerbaidjan",AZERBAIDJAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[AZERBAIDJAN]         = azerbaidjan         ;

Country *turkmenistan ;
 turkmenistan  = new Country       ("Turkmenistan",TURKMENISTAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[TURKMENISTAN]         = turkmenistan        ;

Country *pakistan;
 pakistan= new Country             ("Pakistan",PAKISTAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[PAKISTAN]         = pakistan            ;

Country *uae;
 uae= new Country                 ("United Arabic Emirates",UAE,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[UAE]         = uae                 ;

Country *yemen;
 yemen = new Country               ("Yemen",YEMEN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[YEMEN]         = yemen               ;

Country  *south_yemen;
 south_yemen = new Country         ("South Yemen",SOUTH_YEMEN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[SOUTH_YEMEN]         = south_yemen         ;

Country *oman;
oman = new Country                 ("Oman",OMAN,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[OMAN]         = oman                ;

Country *malaysia;
 malaysia = new Country            ("Malaysia",MALAYSIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[MALAYSIA]         = malaysia            ;

Country *indonesia;
 indonesia= new Country            ("Indonesia",INDONESIA,GRP_E,_jour,_group,_country, _politic, _weapon);
 _country[INDONESIA]         = indonesia           ;

 //neutral

Country *israel;
 israel= new Country         ("Israel",ISRAEL,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[ISRAEL]         = israel              ;

Country *india;
 india = new Country             ("India",INDIA,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[INDIA]         = india               ;

Country *nepal;
 nepal = new Country            ("Nepal",NEPAL,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[NEPAL]         = nepal               ;

Country *buthan;
 buthan= new Country            ("Buthan",BUTHAN,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[BUTHAN]         = buthan              ;

Country *bangla_desh;
bangla_desh = new Country          ("Bangla Desh",BANGLA_DESH,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[BANGLA_DESH]         = bangla_desh         ;

Country *sri_lanka;
 sri_lanka= new Country           ("Sri Lanka",SRI_LANKA,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[SRI_LANKA]         = sri_lanka           ;

Country *australia;
 australia= new Country            ("Australia",AUSTRALIA,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[AUSTRALIA]         = australia           ;

Country *new_zealand;
 new_zealand= new Country        ("New Zealand",NEW_ZEALAND,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[NEW_ZEALAND]         = new_zealand         ;

Country *new_guinea  ;
 new_guinea  = new Country         ("New Guinea",NEW_GUINEA,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[NEW_GUINEA]         = new_guinea          ;

Country *lebanon;
 lebanon= new Country              ("Lebanon",LEBANON,GRP_A,_jour,_group,_country, _politic, _weapon);
 _country[LEBANON]         = lebanon             ;



 //west african union

Country *guinea_bissau;
 guinea_bissau= new Country        ("Guinea Bissau",GUINEA_BISSAU,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[GUINEA_BISSAU]         = guinea_bissau       ;

Country *mauritania;
 mauritania= new Country          ("Mauritania",MAURITANIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[MAURITANIA]         = mauritania          ;

Country *mali;
mali = new Country                ("Mali",MALI,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[MALI]         = mali          ;

Country *senegal;
senegal = new Country            ("Senegal",SENEGAL,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[SENEGAL]         = senegal             ;

Country *guinea;
 guinea = new Country              ("Guinea",GUINEA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[GUINEA]         = guinea              ;

Country *sierra_leone ;
 sierra_leone = new Country        ("Sierra Leone",SIERRA_LEONE,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[SIERRA_LEONE]         = sierra_leone        ;

Country *liberia;
 liberia = new Country              ("Liberia",LIBERIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[LIBERIA]         = liberia             ;

Country *ivory_coast;
 ivory_coast= new Country        ("Ivory Coast",IVORY_COAST,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[IVORY_COAST]         = ivory_coast         ;

Country *ghana;
 ghana = new Country               ("Ghana",GHANA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[GHANA]         = ghana               ;

Country *burkina_faso;
 burkina_faso= new Country         ("Burkina Faso",BURKINA_FASO,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[BURKINA_FASO]         = burkina_faso        ;

Country *togo;
 togo= new Country                ("Togo",TOGO,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[TOGO]         = togo                ;

Country *benin;
 benin= new Country               ("Benin",BENIN,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[BENIN]         = benin               ;

Country *niger;
 niger= new Country                ("Niger",NIGER,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[NIGER]         = niger               ;

Country *nigeria;
 nigeria= new Country             ("Nigeria",NIGERIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[NIGERIA]         = nigeria             ;

Country *cameroon;
 cameroon= new Country           ("Cameroun",CAMEROON,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[CAMEROON]         = cameroon            ;

Country *tchad;
 tchad= new Country              ("Tchad",TCHAD,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[TCHAD]         = tchad               ;

Country *centrafrica;
 centrafrica= new Country          ("Central Africa Republic",CENTRAFRICA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[CENTRAFRICA]         = centrafrica         ;

Country *equatorial_guinea;
 equatorial_guinea= new Country    ("Equatorial Guineas",EQUATORIAL_GUINEA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[EQUATORIAL_GUINEA]         = equatorial_guinea   ;

Country *gabon  ;
gabon   = new Country              ("Gabon",GABON,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[GABON]         = gabon               ;

Country *rep_congo;
rep_congo = new Country            ("Democratic Republic of Congo",REP_CONGO,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[REP_CONGO]         = rep_congo           ;

Country *congo;
congo = new Country               ("Congo (ex-Zaire)",CONGO,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[CONGO]         = congo               ;

Country *uganda  ;
 uganda  = new Country             ("Uganda",UGANDA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[UGANDA]         = uganda              ;

Country *ethiopia  ;
 ethiopia  = new Country           ("Ethiopia",ETHIOPIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[ETHIOPIA]         = ethiopia            ;

Country *kenya;
 kenya = new Country                ("Kenya",KENYA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[KENYA]         = kenya               ;

Country *rwanda;
 rwanda= new Country               ("Rwanda",RWANDA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[RWANDA]         = rwanda              ;

Country *burundi;
 burundi= new Country              ("Burundi",BURUNDI,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[BURUNDI]         = burundi             ;

Country *tanzania;
tanzania = new Country             ("Tanzania",TANZANIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[TANZANIA]         = tanzania            ;

Country *mozambique;
 mozambique= new Country           ("Mozambique",MOZAMBIQUE,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[MOZAMBIQUE]         = mozambique          ;

Country *malawi;
malawi = new Country              ("Malawi",MALAWI,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[MALAWI]         = malawi              ;

Country *madagascar;
 madagascar= new Country           ("Madagascar",MADAGASCAR,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[MADAGASCAR]         = madagascar          ;

Country *zambia;
 zambia= new Country               ("Zambia",ZAMBIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[ZAMBIA]         = zambia              ;

Country *zimbabwe;
 zimbabwe= new Country            ("Zimbabwe",ZIMBABWE,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[ZIMBABWE]         = zimbabwe            ;

Country *botswana;
 botswana= new Country             ("Botswana",BOTSWANA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[BOTSWANA]         = botswana            ;

Country *namibia;
 namibia = new Country              ("Namibia",NAMIBIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[NAMIBIA]         = namibia             ;

Country *angola;
 angola = new Country               ("Angola",ANGOLA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[ANGOLA]         = angola              ;

Country *gambia;
 gambia = new Country               ("Gambia",GAMBIA,GRP_C,_jour,_group,_country, _politic, _weapon);
 _country[GAMBIA]         = gambia              ;

 //white national

Country *canada;
 canada= new Country              ("Canada",CANADA,GRP_B,_jour,_group,_country, _politic, _weapon);
 _country[CANADA]         = canada             ;

Country *usa;
 usa= new Country                 ("United States",USA,GRP_B,_jour,_group,_country, _politic, _weapon);
 _country[USA]         = usa                ;

Country *south_africa;
 south_africa = new Country        ("South Africa",SOUTH_AFRICA,GRP_B,_jour,_group,_country, _politic, _weapon);
 _country[SOUTH_AFRICA]         = south_africa       ;

Country *lesotho;
  lesotho= new Country            ("Lesotho",LESOTHO,GRP_B,_jour,_group,_country, _politic, _weapon);
 _country[LESOTHO]         = lesotho            ;

Country  *swaziland;
 swaziland= new Country          ("Swaziland",SWAZILAND,GRP_B,_jour,_group,_country, _politic, _weapon);
 _country[SWAZILAND]         = swaziland          ;

 //christian nation (sudac)
Country *brazil;
 brazil= new Country              ("Brazil",BRAZIL,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[BRAZIL]         = brazil             ;

Country *venezuela;
 venezuela = new Country           ("Venezuela",VENEZUELA,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[VENEZUELA]         = venezuela          ;

Country *colombia;
 colombia = new Country           ("Colombia",COLOMBIA,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[COLOMBIA]         = colombia           ;

Country *ecuador;
 ecuador= new Country             ("Ecuador",ECUADOR,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[ECUADOR]         = ecuador            ;

Country *uruguay;
 uruguay = new Country             ("Uruguay",URUGUAY,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[URUGUAY]         = uruguay            ;

Country *paraguay;
 paraguay= new Country            ("Paraguay",PARAGUAY,GRP_H,_jour,_group,_country, _politic, _weapon);
 _country[PARAGUAY]         = paraguay           ;


 //socialist group (sudac)

Country *mexico;
 mexico = new Country              ("Mexico",MEXICO,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[MEXICO]         = mexico             ;

Country *belize;
 belize= new Country              ("Belize",BELIZE,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[BELIZE]         = belize             ;

Country *guatemala;
 guatemala= new Country           ("Guatemala",GUATEMALA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[GUATEMALA]         = guatemala          ;

Country *honduras;
 honduras= new Country            ("Honduras",HONDURAS,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[HONDURAS]         = honduras           ;

Country *salvador;
salvador = new Country           ("El Salvador",SALVADOR,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[SALVADOR]         = salvador           ;

Country *nicaragua;
 nicaragua= new Country           ("Nicaragua",NICARAGUA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[NICARAGUA]         = nicaragua          ;

Country *costa_rica;
 costa_rica = new Country          ("Costa Rica",COSTA_RICA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[COSTA_RICA]         = costa_rica         ;

Country *panama;
 panama = new Country              ("Panama",PANAMA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[PANAMA]         = panama             ;

Country *cuba;
 cuba = new Country                ("Cuba",CUBA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[CUBA]         = cuba               ;

Country *jamaica;
 jamaica = new Country             ("Jamaica",JAMAICA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[JAMAICA]         = jamaica            ;

Country *haiti;
haiti = new Country               ("Haiti",HAITI,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[HAITI]         = haiti              ;

Country *dominican;
dominican = new Country           ("Dominican Republic",DOMINICAN,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[DOMINICAN]         = dominican          ;

Country *puerto_rico;
 puerto_rico= new Country         ("Puerto Rico",PUERTO_RICO,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[PUERTO_RICO]         = puerto_rico        ;

Country *guyana;
 guyana= new Country              ("Guyana",GUYANA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[GUYANA]         = guyana             ;

Country *peru;
 peru= new Country                ("Peru",PERU,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[PERU]         = peru               ;

Country *bolivia;
 bolivia= new Country             ("Bolivia",BOLIVIA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[BOLIVIA]         = bolivia            ;

Country *chili;
 chili= new Country               ("Chili",CHILI,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[CHILI]         = chili              ;

Country *argentina;
 argentina= new Country           ("Argentina",ARGENTINA,GRP_I,_jour,_group,_country, _politic, _weapon);
 _country[ARGENTINA]         = argentina          ;

 //Sun Empire
Country *japan;
 japan = new Country               ("Japan",JAPAN,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[JAPAN]         = japan              ;

Country *birmania;
 birmania = new Country            ("Birmania",BIRMANIA,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[BIRMANIA]         = birmania           ;

Country *thailand;
 thailand= new Country           ("Thailand",THAILAND,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[THAILAND]         = thailand           ;

Country *laos;
 laos= new Country                ("Laos",LAOS,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[LAOS]         = laos               ;

Country *cambodge;
 cambodge = new Country            ("Cambodge",CAMBODGE,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[CAMBODGE]         = cambodge           ;

Country *vietnam;
 vietnam = new Country             ("Vietnam",VIETNAM,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[VIETNAM]         = vietnam            ;

Country *south_korea;
 south_korea= new Country         ("Southern Korea",SOUTH_KOREA,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[SOUTH_KOREA]         = south_korea        ;

Country *philippines;
philippines = new Country         ("Philippines",PHILIPPINES,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[PHILIPPINES]         = philippines        ;

Country *taiwan;
 taiwan= new Country              ("Taiwan",TAIWAN,GRP_F,_jour,_group,_country, _politic, _weapon);
 _country[TAIWAN]         = taiwan             ;
 

///////////////////////////////////////////////////////////////////////////////////
//pour éviter des plantages ceci est nécessaie deux pays fake pour la couleur eau + frontière

 _country[COL_SEA]         = new Country              ("",COL_SEA,GRP_X,_jour,_group,_country, _politic, _weapon);
 _country[COL_BORDER]      = new Country              ("",COL_BORDER,GRP_X,_jour,_group,_country, _politic, _weapon);
//pour editeur (pays vides)

//CETTE LIGNE FAIT TOUT MERDER POURQUOI???
// _country[COL_EMPTY]       = new Country              ("empty",COL_BORDER,GRP_X,_jour,_group,_country, _politic, _weapon);

//le grp_X est aussi un group fake avec politique fake (ennemi de personne, ami de tous, personne attaque ces pays!)
 
///ATTENTION TOUTES CES DONNEES DE POPULATION DATENT DE 1969-70!!!!
//faut avancer dans le temps avant de commencer ailleurs qu'en 1970

/**********************************************************************/
/**********************************************************************/
//GROUP_G
//DEFINITIONS POUR LE GROUPE EUROPE
/**********************************************************************/
/**********************************************************************/

/*
ATTENTION GRAND CON, oui ça changé entre l'europe et les autres groupes.
des fois on a créée bêtement des pointeurs en trop alors qu'on a pas besoin
ils sont déja dans _country... sauf que comme on utilise ces pointeur dans
DATA.CPP FAUT PAS MODIFIER, de toute façon ces données finiront dans
un fichier .w6s tôt ou tard. Pigé?

*/


//par défaut access_sea=ON, access_nuke=OFF
//Portugal----------------------------------------------
   _country[PORTUGAL]->set_population  (32807000);
   _country[PORTUGAL]->set_birth_rate  (1.6);
   _country[PORTUGAL]->set_tech_level  (65);
   _country[PORTUGAL]->set_pnb         (1000);

//Spain----------------------------------------------
   _country[SPAIN]->set_population  (33290000);
   _country[SPAIN]->set_birth_rate  (1.3);
   _country[SPAIN]->set_tech_level  (70);
   _country[SPAIN]->set_pnb         (1200);
//France----------------------------------------------
   _country[FRANCE]->set_population  (50770000);
   _country[FRANCE]->set_birth_rate  (1.3);
   _country[FRANCE]->set_tech_level  (85);
   _country[FRANCE]->set_pnb         (2400);
   _country[FRANCE]->access_nuke     = ON  ;
//United Kingdom----------------------------------------------
   _country[UK]->set_population  (55711000);
   _country[UK]->set_birth_rate  (1.3);
   _country[UK]->set_tech_level  (85);
   _country[UK]->set_pnb         (1950);
   _country[UK]->access_nuke     = ON  ;  //officiel
//Austria----------------------------------------------
   _country[AUSTRIA]->set_population  (13000000);
   _country[AUSTRIA]->set_birth_rate  (1.3);
   _country[AUSTRIA]->set_tech_level  (80);
   _country[AUSTRIA]->set_pnb         (1950);
   _country[AUSTRIA]->access_nuke     = OFF  ;
//_country[ITALY]----------------------------------------------
   _country[ITALY]->set_population  (53170000);
   _country[ITALY]->set_birth_rate  (1.3);
   _country[ITALY]->set_tech_level  (80);
   _country[ITALY]->set_pnb         (1800);
//_country[BELGIUM]----------------------------------------------
   _country[BELGIUM]->set_population  (9646000);
   _country[BELGIUM]->set_birth_rate  (1.3);
   _country[BELGIUM]->set_tech_level  (80);
   _country[BELGIUM]->set_pnb         (2080);
//Slovaquie----------------------------------------------
   _country[SLOVAKIA]->set_population  (6120000); //environ 40% tchecoslovaquie!
   _country[SLOVAKIA]->set_birth_rate  (1.6);
   _country[SLOVAKIA]->set_tech_level  (70);
   _country[SLOVAKIA]->set_pnb         (1000);
   _country[SLOVAKIA]->access_sea      = OFF  ;
//_country[GERMANY]----------------------------------------------
   _country[GERMANY]->set_population  (75554000);
   _country[GERMANY]->set_birth_rate  (1.3);
   _country[GERMANY]->set_tech_level  (80);
   _country[GERMANY]->set_pnb         (2180);
//_country[NETHERLANDS]----------------------------------------------
   _country[NETHERLANDS]->set_population  (13019000);
   _country[NETHERLANDS]->set_birth_rate  (1.4);
   _country[NETHERLANDS]->set_tech_level  (80);
   _country[NETHERLANDS]->set_pnb         (1970);
//_country[DENMARK]----------------------------------------------
   _country[DENMARK]->set_population  (4891000);
   _country[DENMARK]->set_birth_rate  (1.4);
   _country[DENMARK]->set_tech_level  (80);
   _country[DENMARK]->set_pnb         (2420);
//_country[NORWAY]----------------------------------------------
   _country[NORWAY]->set_population  (3879000);
   _country[NORWAY]->set_birth_rate  (1.3);
   _country[NORWAY]->set_tech_level  (75);
   _country[NORWAY]->set_pnb         (2280);
//_country[CZECHIA]----------------------------------------------
   _country[CZECHIA]->set_population  (8443000);  //env. 65% tchecoslovaquie
   _country[CZECHIA]->set_birth_rate  (1.5);
   _country[CZECHIA]->set_tech_level  (70);
   _country[CZECHIA]->set_pnb         (1200);
   _country[CZECHIA]->access_sea      = OFF  ;
//_country[GREECE]----------------------------------------------
   _country[GREECE]->set_population  (8880000);
   _country[GREECE]->set_birth_rate  (1.5);
   _country[GREECE]->set_tech_level  (70);
   _country[GREECE]->set_pnb         (900);
//_country[SERBIA]----------------------------------------------
   _country[SERBIA]->set_population  (6040000); //deduit d'apres yougo.
   _country[SERBIA]->set_birth_rate  (1.5);
   _country[SERBIA]->set_tech_level  (65);
   _country[SERBIA]->set_pnb         (510);
//_country[LITHUANIA]----------------------------------------------
   _country[LITHUANIA]->set_population  (1300000); //au bol!
   _country[LITHUANIA]->set_birth_rate  (1.5);
   _country[LITHUANIA]->set_tech_level  (65);
   _country[LITHUANIA]->set_pnb         (850);
//_country[SWEDEN]----------------------------------------------
   _country[SWEDEN]->set_population  (8093000);
   _country[SWEDEN]->set_birth_rate  (1.3);
   _country[SWEDEN]->set_tech_level  (75);
   _country[SWEDEN]->set_pnb         (2920);
//_country[POLAND]----------------------------------------------
   _country[POLAND]->set_population  (32807000);
   _country[POLAND]->set_birth_rate  (1.6);
   _country[POLAND]->set_tech_level  (65);
   _country[POLAND]->set_pnb         (940);
//_country[SWITZERLAND]----------------------------------------------
   _country[SWITZERLAND]->set_population  (6270000);
   _country[SWITZERLAND]->set_birth_rate  (1.5);
   _country[SWITZERLAND]->set_tech_level  (75);
   _country[SWITZERLAND]->set_pnb         (2710);
   _country[SWITZERLAND]->access_sea      = OFF  ;
//_country[FINLAND]----------------------------------------------
   _country[FINLAND]->set_population  (4710000);
   _country[FINLAND]->set_birth_rate  (1.3);
   _country[FINLAND]->set_tech_level  (70);
   _country[FINLAND]->set_pnb         (1740);
//_country[ESTONIA]----------------------------------------------
   _country[ESTONIA]->set_population  (900000);   //AU BOL!!!
   _country[ESTONIA]->set_birth_rate  (1.6);
   _country[ESTONIA]->set_tech_level  (65);
   _country[ESTONIA]->set_pnb         (850);
//_country[LETTONIA]----------------------------------------------
   _country[LETTONIA]->set_population  (852000);  //AU BOL!!!
   _country[LETTONIA]->set_birth_rate  (1.6);
   _country[LETTONIA]->set_tech_level  (65);
   _country[LETTONIA]->set_pnb         (850);
//_country[IRELAND]----------------------------------------------
   _country[IRELAND]->set_population  (2944000);
   _country[IRELAND]->set_birth_rate  (1.3);
   _country[IRELAND]->set_tech_level  (70);
   _country[IRELAND]->set_pnb         (1000);
//_country[BOSNIA]----------------------------------------------
   _country[BOSNIA]->set_population  (3950000); //deduction d'apres yougo
   _country[BOSNIA]->set_birth_rate  (1.6);
   _country[BOSNIA]->set_tech_level  (65);
   _country[BOSNIA]->set_pnb         (510);
//_country[CROATIA]----------------------------------------------
   _country[CROATIA]->set_population  (5980000);      //deduction d'apres yougo
   _country[CROATIA]->set_birth_rate  (1.6);
   _country[CROATIA]->set_tech_level  (65);
   _country[CROATIA]->set_pnb         (510);
//_country[SLOVENIA]----------------------------------------------
   _country[SLOVENIA]->set_population  (3450000);    //deduction d'apres yougo
   _country[SLOVENIA]->set_birth_rate  (1.4);
   _country[SLOVENIA]->set_tech_level  (65);
   _country[SLOVENIA]->set_pnb         (600);
//_country[GUYANA_FR]----------------------------------------------
   _country[GUYANA_FR]->set_population  (48000);
   _country[GUYANA_FR]->set_birth_rate  (1.6);
   _country[GUYANA_FR]->set_tech_level  (80);
   _country[GUYANA_FR]->set_pnb         (2000);
//_country[SURINAM]----------------------------------------------
   _country[SURINAM]->set_population  (403000);
   _country[SURINAM]->set_birth_rate  (1.7);
   _country[SURINAM]->set_tech_level  (75);
   _country[SURINAM]->set_pnb         (600);
//_country[ICELAND]----------------------------------------------
   _country[ICELAND]->set_population  (205000);
   _country[ICELAND]->set_birth_rate  (1.3);
   _country[ICELAND]->set_tech_level  (70);
   _country[ICELAND]->set_pnb         (1740);
//_country[groenland]----------------------------------------------
   _country[GROENLAND]->set_population  (47000);
   _country[GROENLAND]->set_birth_rate  (1.3);
   _country[GROENLAND]->set_tech_level  (65);
   _country[GROENLAND]->set_pnb         (2000);

//----------------------------------------------
   _country[HUNGARY]->set_population  (10331000);
   _country[HUNGARY]->set_birth_rate  (1.6);
   _country[HUNGARY]->set_tech_level  (65);
   _country[HUNGARY]->set_pnb         (1100);
   _country[HUNGARY]->access_sea      = OFF ;
//----------------------------------------------
   _country[ROMANIA]->set_population  (20253000);
   _country[ROMANIA]->set_birth_rate  (1.6);
   _country[ROMANIA]->set_tech_level  (70);
   _country[ROMANIA]->set_pnb         (860);
//----------------------------------------------
   _country[BULGARIA]->set_population  (8500000);
   _country[BULGARIA]->set_birth_rate  (1.6);
   _country[BULGARIA]->set_tech_level  (70);
   _country[BULGARIA]->set_pnb         (620);
//----------------------------------------------
   _country[ALBANIA]->set_population  (2075000);
   _country[ALBANIA]->set_birth_rate  (1.7);
   _country[ALBANIA]->set_tech_level  (65);
   _country[ALBANIA]->set_pnb         (440);

/**********************************************************************/
/**********************************************************************/
//GROUP_D
//DEFINITIONS POUR LE GROUPE COMMUNISME
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
   russia->set_population  (180000000);  //deduit d'URSS (250 mio)
   russia->set_birth_rate  (1.6);
   russia->set_tech_level  (84);  //seuil avant division infantry
   russia->set_pnb         (2100); //plus haut que le reste URSS
   russia->access_nuke     = ON ;
//----------------------------------------------
   mongolia->set_population  (1240000);
   mongolia->set_birth_rate  (1.6);
   mongolia->set_tech_level  (65);
   mongolia->set_pnb         (250);
//----------------------------------------------
   china->set_population  (830000000);
   china->set_birth_rate  (1.7);
   china->set_tech_level  (60);
   china->set_pnb         (200);
   china->access_nuke     = ON ;
//----------------------------------------------
   belarus->set_population  (17500000); //deduit d'URSS (250 mio)
   belarus->set_birth_rate  (1.6);
   belarus->set_tech_level  (75);
   belarus->set_pnb         (1000);
   belarus->access_sea      = OFF  ;
//----------------------------------------------
   ukraine->set_population  (20200000); //deduit d'URSS (250 mio)
   ukraine->set_birth_rate  (1.5);
   ukraine->set_tech_level  (83);
   ukraine->set_pnb         (1200);
   ukraine->access_nuke     = ON ;
//----------------------------------------------
   moldavia->set_population  (3000000);  //deduit d'URSS (250 mio)
   moldavia->set_birth_rate  (1.6);
   moldavia->set_tech_level  (75);
   moldavia->set_pnb         (900);
   moldavia->access_sea      = OFF  ;
//----------------------------------------------
   georgia->set_population  (4000000);   //deduit d'URSS (250 mio)
   georgia->set_birth_rate  (1.6);
   georgia->set_tech_level  (75);
   georgia->set_pnb         (900);
//----------------------------------------------
   armenia->set_population  (2600000);    //deduit d'URSS (250 mio)
   armenia->set_birth_rate  (1.6);
   armenia->set_tech_level  (65);
   armenia->set_pnb         (700);
   armenia->access_sea      = OFF  ;
//----------------------------------------------
   kazakhstan->set_population  (6200000);      //deduit d'URSS (250 mio)
   kazakhstan->set_birth_rate  (1.6);
   kazakhstan->set_tech_level  (70);
   kazakhstan->set_pnb         (500);
   kazakhstan->access_sea      = OFF  ;
//----------------------------------------------
   uzbekistan->set_population  (4000000);
   uzbekistan->set_birth_rate  (1.6);
   uzbekistan->set_tech_level  (70);
   uzbekistan->set_pnb         (600);
   uzbekistan->access_sea      = OFF ;
//----------------------------------------------
   tadzikistan->set_population  (2000000);
   tadzikistan->set_birth_rate  (1.6);
   tadzikistan->set_tech_level  (70);
   tadzikistan->set_pnb         (500);
   tadzikistan->access_sea      = OFF  ;
//----------------------------------------------
   kirgikistan->set_population  (2500000);
   kirgikistan->set_birth_rate  (1.6);
   kirgikistan->set_tech_level  (70);
   kirgikistan->set_pnb         (400);
   kirgikistan->access_sea      = OFF  ;
//----------------------------------------------
   north_korea->set_population  (13600000);
   north_korea->set_birth_rate  (1.6);
   north_korea->set_tech_level  (70);
   north_korea->set_pnb         (250);

/**********************************************************************/
/**********************************************************************/
//GROUP_E
//DEFINITIONS POUR LE GROUPE ISLAM
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
   turkey->set_population  (34500000);
   turkey->set_birth_rate  (1.8);
   turkey->set_tech_level  (65);
   turkey->set_pnb         (400);
//----------------------------------------------
   afghanistan->set_population  (17125000);
   afghanistan->set_birth_rate  (2.0);
   afghanistan->set_tech_level  (55);
   afghanistan->set_pnb         (70);
   afghanistan->access_sea      = OFF  ;
//----------------------------------------------
   iran->set_population  (28662000);
   iran->set_birth_rate  (2.0);
   iran->set_tech_level  (55);
   iran->set_pnb         (300);
//----------------------------------------------
   irak->set_population  (9350000);
   irak->set_birth_rate  (1.9);
   irak->set_tech_level  (70);
   irak->set_pnb         (350);
   irak->access_sea      = OFF ;  //ou alors a peine?
//----------------------------------------------
   saudi_arabia->set_population  (6870000);
   saudi_arabia->set_birth_rate  (2.3);
   saudi_arabia->set_tech_level  (65);
   saudi_arabia->set_pnb         (500);
//----------------------------------------------
   koweit->set_population  (600000);
   koweit->set_birth_rate  (2.0);
   koweit->set_tech_level  (70);
   koweit->set_pnb         (4830); //wow!
//----------------------------------------------
   egypt->set_population  (33329000);
   egypt->set_birth_rate  (2.0);
   egypt->set_tech_level  (65);
   egypt->set_pnb         (170);
//----------------------------------------------
   jordania->set_population  (2217000);
   jordania->set_birth_rate  (1.9);
   jordania->set_tech_level  (68);
   jordania->set_pnb         (220);
   jordania->access_sea      = OFF  ;
//----------------------------------------------
   syria->set_population  (6098000);
   syria->set_birth_rate  (2.0);
   syria->set_tech_level  (65);
   syria->set_pnb         (260);
//----------------------------------------------
   sudan->set_population  (15695000);
   sudan->set_birth_rate  (2.4);
   sudan->set_tech_level  (45);
   sudan->set_pnb         (110);
//----------------------------------------------
   lybia->set_population  (6869000);
   lybia->set_birth_rate  (2.0);
   lybia->set_tech_level  (60);
   lybia->set_pnb         (1700);
//----------------------------------------------
   tunisia->set_population  (5137000);
   tunisia->set_birth_rate  (2.0);
   tunisia->set_tech_level  (65);
   tunisia->set_pnb         (300);
//----------------------------------------------
   algeria->set_population  (13349000);
   algeria->set_birth_rate  (2.8);
   algeria->set_tech_level  (65);
   algeria->set_pnb         (280);
//----------------------------------------------
   morocco->set_population  (15525000);
   morocco->set_birth_rate  (2.0);
   morocco->set_tech_level  (65);
   morocco->set_pnb         (190);
//----------------------------------------------
   djibouti->set_population  (500000); //AU BOL!!
   djibouti->set_birth_rate  (2.0);
   djibouti->set_tech_level  (65);
   djibouti->set_pnb         (200);  //AU BOL!!!
//----------------------------------------------
   somalia->set_population  (2730000);
   somalia->set_birth_rate  (2.9);
   somalia->set_tech_level  (50);
   somalia->set_pnb         (70);
//----------------------------------------------
   qatar->set_population  (100000);
   qatar->set_birth_rate  (2.0);
   qatar->set_tech_level  (70);
   qatar->set_pnb         (800);
//----------------------------------------------
   azerbaidjan->set_population  (3540000);  //d'apres URSS Au bol quoi...
   azerbaidjan->set_birth_rate  (2.0);
   azerbaidjan->set_tech_level  (70);
   azerbaidjan->set_pnb         (500);
   azerbaidjan->access_sea      = OFF ;
//----------------------------------------------
   turkmenistan->set_population  (3200000); //d'apres URSS Au bol quoi...
   turkmenistan->set_birth_rate  (2.0);
   turkmenistan->set_tech_level  (70);
   turkmenistan->set_pnb         (500);
   turkmenistan->access_sea      = OFF ;
//----------------------------------------------
   pakistan->set_population  (57000000);
   pakistan->set_birth_rate  (2.9);
   pakistan->set_tech_level  (65);
   pakistan->set_pnb         (105);
   pakistan->access_nuke     = ON ; //non officiel
//----------------------------------------------
   uae->set_population  (945000);  
   uae->set_birth_rate  (2.1);
   uae->set_tech_level  (65);
   uae->set_pnb         (800);
//----------------------------------------------
   yemen->set_population  (1200000);
   yemen->set_birth_rate  (2.0);
   yemen->set_tech_level  (65);
   yemen->set_pnb         (100);
//----------------------------------------------
   south_yemen->set_population  (5100000);
   south_yemen->set_birth_rate  (2.0);
   south_yemen->set_tech_level  (65);
   south_yemen->set_pnb         (110);
//----------------------------------------------
   oman->set_population  (750000);
   oman->set_birth_rate  (2.0);
   oman->set_tech_level  (65);
   oman->set_pnb         (800);
//----------------------------------------------
   malaysia->set_population  (10650000);
   malaysia->set_birth_rate  (2.6);
   malaysia->set_tech_level  (65);
   malaysia->set_pnb         (340);
//----------------------------------------------
   indonesia->set_population  (116918000);
   indonesia->set_birth_rate  (2.8);
   indonesia->set_tech_level  (65);
   indonesia->set_pnb         (90);

/**********************************************************************/
/**********************************************************************/
//GROUP_A
//DEFINITIONS POUR LE GROUPE NEUTRE ET IDEALISTE
/**********************************************************************/
/**********************************************************************/


//----------------------------------------------
  israel->set_population  (2998000);
  israel->set_birth_rate  (2.2);   //beaucoup immigr.
  israel->set_tech_level  (80);
  israel->set_pnb         (1480);
  israel->access_nuke     = ON ;  ///non officiel
//----------------------------------------------
  india->set_population  (546950000);
  india->set_birth_rate  (3.4);
  india->set_tech_level  (70);
  india->set_pnb         (80);
  india->access_nuke     = ON ; //non officiel
//----------------------------------------------
  nepal->set_population  (10465000);
  nepal->set_birth_rate  (1.9);
  nepal->set_tech_level  (65);
  nepal->set_pnb         (70);
  nepal->access_sea      = OFF  ;
//----------------------------------------------
  buthan->set_population  (800000);
  buthan->set_birth_rate  (1.8);
  buthan->set_tech_level  (65);
  buthan->set_pnb         (100);
  buthan->access_sea      = OFF ;
//----------------------------------------------
  bangla_desh->set_population  (70000000);
  bangla_desh->set_birth_rate  (3.2);
  bangla_desh->set_tech_level  (45);
  bangla_desh->set_pnb         (95);
//----------------------------------------------
  sri_lanka->set_population  (12514000);
  sri_lanka->set_birth_rate  (2.0);
  sri_lanka->set_tech_level  (65);
  sri_lanka->set_pnb         (150);
//----------------------------------------------
  australia->set_population  (12552000);
  australia->set_birth_rate  (1.8);
  australia->set_tech_level  (75);
  australia->set_pnb         (2260);
//----------------------------------------------
  new_zealand->set_population  (2816000);
  new_zealand->set_birth_rate  (1.7);
  new_zealand->set_tech_level  (65);
  new_zealand->set_pnb         (1810);
//----------------------------------------------
  new_guinea->set_population  (1701000);
  new_guinea->set_birth_rate  (1.9);
  new_guinea->set_tech_level  (60);
  new_guinea->set_pnb         (1800);
//----------------------------------------------
  lebanon->set_population  (2645000);
  lebanon->set_birth_rate  (1.6);
  lebanon->set_tech_level  (65);
  lebanon->set_pnb         (480);

/**********************************************************************/
/**********************************************************************/
//GROUP_C
//DEFINITIONS POUR LE GROUPE WEST AFRICAN
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  guinea_bissau->set_population  (530000);
  guinea_bissau->set_birth_rate  (2.8);
  guinea_bissau->set_tech_level  (45);
  guinea_bissau->set_pnb         (75);
//----------------------------------------------
  mauritania->set_population  (1150000);
  mauritania->set_birth_rate  (2.3);
  mauritania->set_tech_level  (54);
  mauritania->set_pnb         (140);
//----------------------------------------------
  senegal->set_population  (3870000);
  senegal->set_birth_rate  (2.8);
  senegal->set_tech_level  (45);
  senegal->set_pnb         (200);
//----------------------------------------------
  guinea->set_population  (3890000);
  guinea->set_birth_rate  (2.8);
  guinea->set_tech_level  (46);
  guinea->set_pnb         (100);
//----------------------------------------------
  sierra_leone->set_population  (2512000);
  sierra_leone->set_birth_rate  (2.8);
  sierra_leone->set_tech_level  (45);
  sierra_leone->set_pnb         (170);
//----------------------------------------------
  liberia->set_population  (1150000);
  liberia->set_birth_rate  (2.8);
  liberia->set_tech_level  (44);
  liberia->set_pnb         (290);
//----------------------------------------------
  ivory_coast->set_population  (4195000);
  ivory_coast->set_birth_rate  (2.8);
  ivory_coast->set_tech_level  (50);
  ivory_coast->set_pnb         (230);
//----------------------------------------------
  ghana->set_population  (8600000);
  ghana->set_birth_rate  (2.8);
  ghana->set_tech_level  (45);
  ghana->set_pnb         (220);
//----------------------------------------------
  burkina_faso->set_population  (5384000);
  burkina_faso->set_birth_rate  (2.8);
  burkina_faso->set_tech_level  (41);
  burkina_faso->set_pnb         (50);
  burkina_faso->access_sea      = OFF  ;
//----------------------------------------------
  togo->set_population  (1857000);
  togo->set_birth_rate  (2.8);
  togo->set_tech_level  (45);
  togo->set_pnb         (100);
//----------------------------------------------
  benin->set_population  (2640000);
  benin->set_birth_rate  (2.8);
  benin->set_tech_level  (45);
  benin->set_pnb         (80);
//----------------------------------------------
  mali->set_population  (10000000); //aU BOL!!
  mali->set_birth_rate  (2.8);
  mali->set_tech_level  (45);
  mali->set_pnb         (80);
//----------------------------------------------
  niger->set_population  (4016000);
  niger->set_birth_rate  (2.8);
  niger->set_tech_level  (45);
  niger->set_pnb         (80);
//----------------------------------------------
  nigeria->set_population  (66174000);
  nigeria->set_birth_rate  (2.8);
  nigeria->set_tech_level  (45);
  nigeria->set_pnb         (80);
//----------------------------------------------
  cameroon->set_population  (5836000);
  cameroon->set_birth_rate  (2.8);
  cameroon->set_tech_level  (45);
  cameroon->set_pnb         (150);
//----------------------------------------------
  tchad->set_population  (3510000);
  tchad->set_birth_rate  (2.8);
  tchad->set_tech_level  (45);
  tchad->set_pnb         (70);
  tchad->access_sea      = OFF ;
//----------------------------------------------
  centrafrica->set_population  (1518000);
  centrafrica->set_birth_rate  (2.8);
  centrafrica->set_tech_level  (45);
  centrafrica->set_pnb         (130);
  centrafrica->access_sea      = OFF  ;
//----------------------------------------------
  equatorial_guinea->set_population  (286000);
  equatorial_guinea->set_birth_rate  (2.8);
  equatorial_guinea->set_tech_level  (45);
  equatorial_guinea->set_pnb        (150);
//----------------------------------------------
  gabon->set_population  (500000);
  gabon->set_birth_rate  (2.8);
  gabon->set_tech_level  (48);
  gabon->set_pnb         (410);
//----------------------------------------------
  rep_congo->set_population  (915000);
  rep_congo->set_birth_rate  (2.8);
  rep_congo->set_tech_level  (55);
  rep_congo->set_pnb         (160);
//----------------------------------------------
  congo->set_population  (17100000);
  congo->set_birth_rate  (2.8);
  congo->set_tech_level  (50);
  congo->set_pnb         (70);
//----------------------------------------------
  uganda->set_population  (9764000);
  uganda->set_birth_rate  (2.8);
  uganda->set_tech_level  (45);
  uganda->set_pnb         (110);
  uganda->access_sea      = OFF  ;
//----------------------------------------------
  ethiopia->set_population  (24769000);
  ethiopia->set_birth_rate  (2.9);
  ethiopia->set_tech_level  (43);
  ethiopia->set_pnb         (60);
//----------------------------------------------
  kenya->set_population  (11152000);
  kenya->set_birth_rate  (2.7);
  kenya->set_tech_level  (50);
  kenya->set_pnb         (130);
//----------------------------------------------
  rwanda->set_population  (3500000);
  rwanda->set_birth_rate  (2.8);
  rwanda->set_tech_level  (45);
  rwanda->set_pnb         (80);
  rwanda->access_sea      = OFF ;
//----------------------------------------------
  burundi->set_population  (3475000);
  burundi->set_birth_rate  (2.8);
  burundi->set_tech_level  (45);
  burundi->set_pnb         (90);
  burundi->access_sea      = OFF  ;
//----------------------------------------------
  tanzania->set_population  (13273000);
  tanzania->set_birth_rate  (3.1);
  tanzania->set_tech_level  (45);
  tanzania->set_pnb         (100);
//----------------------------------------------
  mozambique->set_population  (7376000);
  mozambique->set_birth_rate  (2.8);
  mozambique->set_tech_level  (45);
  mozambique->set_pnb         (70);
//----------------------------------------------
  malawi->set_population  (4530000);
  malawi->set_birth_rate  (2.8);
  malawi->set_tech_level  (45);
  malawi->set_pnb         (60);
  malawi->access_sea      = OFF  ;
//----------------------------------------------
  madagascar->set_population  (6750000);
  madagascar->set_birth_rate  (2.8);
  madagascar->set_tech_level  (43);
  madagascar->set_pnb         (110);
//----------------------------------------------
  zambia->set_population  (4208000);
  zambia->set_birth_rate  (2.8);
  zambia->set_tech_level  (45);
  zambia->set_pnb         (280);
  zambia->access_sea      = OFF  ;
//----------------------------------------------
  zimbabwe->set_population  (5270000);
  zimbabwe->set_birth_rate  (2.8);
  zimbabwe->set_tech_level  (45);
  zimbabwe->set_pnb         (240);
  zimbabwe->access_sea      = OFF  ;
//----------------------------------------------
  botswana->set_population  (648000);
  botswana->set_birth_rate  (2.8);
  botswana->set_tech_level  (45);
  botswana->set_pnb         (180);
  botswana->access_sea      = OFF  ;
//----------------------------------------------
  namibia->set_population  (615000);
  namibia->set_birth_rate  (2.8);
  namibia->set_tech_level  (52);
  namibia->set_pnb         (250); //AU BOL!!!
//----------------------------------------------
  angola->set_population  (5430000);
  angola->set_birth_rate  (2.8);
  angola->set_tech_level  (45);
  angola->set_pnb         (210);
//----------------------------------------------
  gambia->set_population  (357000);
  gambia->set_birth_rate  (2.8);
  gambia->set_tech_level  (45);
  gambia->set_pnb         (80); //AU BOL!!!

/**********************************************************************/
/**********************************************************************/
//GROUP_B
//DEFINITIONS POUR LE GROUPE WHITE NATIONAL
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  canada->set_population  (21700000);
  canada->set_birth_rate  (1.7);
  canada->set_tech_level  (82);
  canada->set_pnb         (2620);
//----------------------------------------------
  usa->set_population  (207200000);
  usa->set_birth_rate  (1.6);
  usa->set_tech_level  (90);
  usa->set_pnb         (4240);
  usa->access_nuke     = ON ;
//----------------------------------------------
  south_africa->set_population  (21282000);
  south_africa->set_birth_rate  (1.9);
  south_africa->set_tech_level  (75);
  south_africa->set_pnb         (710);
//----------------------------------------------
  lesotho->set_population  (920000);
  lesotho->set_birth_rate  (2.0);
  lesotho->set_tech_level  (70);
  lesotho->set_pnb         (400);
  lesotho->access_sea      = OFF  ;
//----------------------------------------------
  swaziland->set_population  (408000);
  swaziland->set_birth_rate  (2.1);
  swaziland->set_tech_level  (65);
  swaziland->set_pnb         (500);
  swaziland->access_sea      = OFF ;
//----------------------------------------------

/**********************************************************************/
/**********************************************************************/
//GROUP_H
//DEFINITIONS POUR LE GROUPE CHRISTIAN NATION
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  brazil->set_population  (95305000);
  brazil->set_birth_rate  (2.0);
  brazil->set_tech_level  (66);
  brazil->set_pnb         (280);
//----------------------------------------------
  venezuela->set_population  (10399000);
  venezuela->set_birth_rate  (1.9);
  venezuela->set_tech_level  (65);
  venezuela->set_pnb         (1000);
//----------------------------------------------
  colombia->set_population  (20463000);
  colombia->set_birth_rate  (1.9);
  colombia->set_tech_level  (65);
  colombia->set_pnb         (340);
//----------------------------------------------
  ecuador->set_population  (6093000);
  ecuador->set_birth_rate  (1.9);
  ecuador->set_tech_level  (60);
  ecuador->set_pnb         (230);
//----------------------------------------------
  uruguay->set_population  (2886000);
  uruguay->set_birth_rate  (1.9);
  uruguay->set_tech_level  (65);
  uruguay->set_pnb         (580);
//----------------------------------------------
  paraguay->set_population  (2379000);
  paraguay->set_birth_rate  (1.8);
  paraguay->set_tech_level  (65);
  paraguay->set_pnb         (220);
  paraguay->access_sea      = OFF  ;

/**********************************************************************/
/**********************************************************************/
//GROUP_I
//DEFINITIONS POUR LE GROUPE SOCIALIST GROUP
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  mexico->set_population  (50670000);
  mexico->set_birth_rate  (2.0);
  mexico->set_tech_level  (60);
  mexico->set_pnb         (580);
//----------------------------------------------
  belize->set_population  (120000);  //=honduras britanique???
  belize->set_birth_rate  (2.0);
  belize->set_tech_level  (58);
  belize->set_pnb         (240);
//----------------------------------------------
  guatemala->set_population  (5014000);
  guatemala->set_birth_rate  (2.0);
  guatemala->set_tech_level  (62);
  guatemala->set_pnb         (300);
//----------------------------------------------
  honduras->set_population  (2570000);
  honduras->set_birth_rate  (2.0);
  honduras->set_tech_level  (62);
  honduras->set_pnb         (240);
//----------------------------------------------
  salvador->set_population  (3390000);
  salvador->set_birth_rate  (2.2);
  salvador->set_tech_level  (58);
  salvador->set_pnb         (260);
//----------------------------------------------
  nicaragua->set_population  (1984000);
  nicaragua->set_birth_rate  (2.0);
  nicaragua->set_tech_level  (60);
  nicaragua->set_pnb         (360);
//----------------------------------------------
  costa_rica->set_population  (1700000);
  costa_rica->set_birth_rate  (2.0);
  costa_rica->set_tech_level  (62);
  costa_rica->set_pnb         (450);
//----------------------------------------------
  panama->set_population  (1464000);
  panama->set_birth_rate  (2.0);
  panama->set_tech_level  (62);
  panama->set_pnb         (580);
//----------------------------------------------
  cuba->set_population  (8250000);
  cuba->set_birth_rate  (2.0);
  cuba->set_tech_level  (64);
  cuba->set_pnb         (280);
//----------------------------------------------
  jamaica->set_population  (1955000);
  jamaica->set_birth_rate  (2.4);
  jamaica->set_tech_level  (58);
  jamaica->set_pnb         (490);
//----------------------------------------------
  haiti->set_population  (4867000);
  haiti->set_birth_rate  (2.9);
  haiti->set_tech_level  (40);
  haiti->set_pnb         (90);
//----------------------------------------------
  dominican->set_population  (4325000);
  dominican->set_birth_rate  (2.2);
  dominican->set_tech_level  (56);
  dominican->set_pnb         (260);
//----------------------------------------------
  puerto_rico->set_population  (2775000);
  puerto_rico->set_birth_rate  (2.5);
  puerto_rico->set_tech_level  (58);
  puerto_rico->set_pnb         (1000);  //USA
//----------------------------------------------
  guyana->set_population  (763000);
  guyana->set_birth_rate  (2.0);
  guyana->set_tech_level  (66);
  guyana->set_pnb         (280);
//----------------------------------------------
  peru->set_population  (13586000);
  peru->set_birth_rate  (2.0);
  peru->set_tech_level  (63);
  peru->set_pnb         (270);
//----------------------------------------------
  bolivia->set_population  (4931000);
  bolivia->set_birth_rate  (2.0);
  bolivia->set_tech_level  (62);
  bolivia->set_pnb         (180);
  bolivia->access_sea      = OFF  ;
//----------------------------------------------
  chili->set_population  (9780000);
  chili->set_birth_rate  (2.0);
  chili->set_tech_level  (62);
  chili->set_pnb         (560);
//----------------------------------------------
  argentina->set_population  (24352000);
  argentina->set_birth_rate  (1.9);
  argentina->set_tech_level  (66);
  argentina->set_pnb         (740);


/**********************************************************************/
/**********************************************************************/
//GROUP_F
//DEFINITIONS POUR LE GROUPE SUN EMPIRE
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  japan->set_population  (104513000);
  japan->set_birth_rate  (1.3);
  japan->set_tech_level  (84);
  japan->set_pnb         (2800);
//----------------------------------------------
  birmania->set_population  (27584000);
  birmania->set_birth_rate  (2.5);
  birmania->set_tech_level  (58);
  birmania->set_pnb         (70);
//----------------------------------------------
  thailand->set_population  (35814000);
  thailand->set_birth_rate  (2.5);
  thailand->set_tech_level  (62);
  thailand->set_pnb         (160);
//----------------------------------------------
  laos->set_population  (18322000);
  laos->set_birth_rate  (2.4);
  laos->set_tech_level  (62);
  laos->set_pnb         (70);
  laos->access_sea      = OFF  ;
//----------------------------------------------
  cambodge->set_population  (6701000);
  cambodge->set_birth_rate  (2.5);
  cambodge->set_tech_level  (60);
  cambodge->set_pnb         (80);
//----------------------------------------------
  vietnam->set_population  (21999000);
  vietnam->set_birth_rate  (2.4);
  vietnam->set_tech_level  (62);
  vietnam->set_pnb         (140);
//----------------------------------------------
  south_korea->set_population  (1360000);
  south_korea->set_birth_rate  (2.0);
  south_korea->set_tech_level  (66);
  south_korea->set_pnb         (530);
//----------------------------------------------
  philippines->set_population  (38493000);
  philippines->set_birth_rate  (2.4);
  philippines->set_tech_level  (62);
  philippines->set_pnb         (320);
//----------------------------------------------
  taiwan->set_population  (14910000);
  taiwan->set_birth_rate  (1.9);
  taiwan->set_tech_level  (74);
  taiwan->set_pnb         (350);

//set_army pour tous les pays
unsigned char the_ctry = _jour->country_first; //pour pointer dans list pays
while(the_ctry != _jour->country_last+1) 
{
	_country[the_ctry]->set_army(); //génére valeurs par défaut pour le pays
	_country[the_ctry]->default_army(); //met une fois ces valeurs dans le pays
	//met une fois ces valeurs dans le pays
	the_ctry++;
}


//pays speciaux
russia->add_infantry(800000); //sinon ca fait pas assez
                             //en regard des 4 mio d'origine de l'URSS!!!
}                             