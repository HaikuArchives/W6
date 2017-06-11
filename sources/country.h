#ifndef COUNTRY_H
#define COUNTRY_H
//*************************************//
//********* Classe Country.H ************//
//*************************************//

#include "def_col.h"
#include <Archivable.h>
#include <String.h>

class Day;
class Group;
class Politic;
class Weapon;
class Attack;

#define FREE      0
#define OCCUPIED  1
#define RESISTANCE_TECH_LEVEL  25  //en pourcents
#define MAX_RESISTANCE         15  //en pourcents de l'infanterie ennemie

#define REVOLUTION_EUPHORY 150  //nb _jours avant risque nouvelle révolution si agric augmente pas assez

#define COST_INFANTRY 0.01             //en millions!!!
#define COST_TANK     6
#define COST_MARINE   100
#define COST_AIRFORCE 15
#define COST_MISSILE  50      //le missile est pas cher car il s'utilise qu'une fois
#define COST_DCA      5
#define COST_NUKE     50

#define MEN_PER_INFANTRY 1     //nb hommes par unite militaire (inf=1 of course)
#define MEN_PER_TANK     3    //faut du monde pour faire marcher ca...
#define MEN_PER_MARINE   200   //pour soustraire la populace
#define MEN_PER_AIRFORCE 5     //un pilote et 4 logistique...
#define MEN_PER_MISSILE  10    //faut du monde pour faire marcher ca...
#define MEN_PER_DCA      7     //faut du monde pour faire marcher ca...
#define MEN_PER_NUKE     25     //faut du monde pour faire marcher ca...

#define STRENGTH_INFANTRY 1    //FORCE par rapport a une unit d'infanterie (infanterie =tou_jours 1 of course...)
#define STRENGTH_TANK     40
#define STRENGTH_MARINE   350
#define STRENGTH_AIRFORCE 120
#define STRENGTH_MISSILE  250
#define STRENGTH_DCA      250

#define MISSILE_POWER     10    //nb de fois qu'on multiplie le kill de l'autre
                                //le missile est hyperpuissants mais disparait au bout d'un _jour
#define MISSILE_PER_DAY   10    //nb de missiles lances par _jour
#define NUKE_PER_DAY      10    //nb max de bombes A par _jour
//pas de strength nuke...

#define KM_PER_PIXEL   35 //pour image.cc
                          //voir pour etre plus precis
#define LOST    0
#define WON     1

#define DEFAULT_ARMY_TAX     10     //en pourcents du PNB qui va pour l'armee
#define DEFAULT_BIRTH_RATE   1.5
#define DEFAULT_YEAR         1970  //c'est l'age de mes statistiques
#define KILOMETER_PER_DAY    1000

#define INFANTRY 0   //UTILISE par fonction buy
#define TANK     1
#define MARINE   2
#define AIRFORCE 3
#define MISSILE  4
#define DCA      5
#define NUKE     6

#define KILL_INFANTRY 1500     //morts par _jour pour bataille ratio 1 contre 1
#define KILL_TANK     10
#define KILL_MARINE   0.5
#define KILL_AIRFORCE 2
#define KILL_MISSILE  2
#define KILL_DCA      8

#define KILL_INDUSTRY    0.05    //pourcentage de l'industrie perdue par attaque
#define KILL_AGRICULTURE 0.03    //a multiplier par le tech_level de l'autre
#define KILL_POPULATION  500
#define KILL_POPULATION_NUKE     50000   //par bombe pas abbatue par la dca voire plus
#define KILL_INDUSTRY_NUKE       1.5       //en pourcents par bombe

#define MIN_AGRICULTURE 25         //minimum possible
#define MIN_INDUSTRY    25
#define MIN_MORAL       25
#define MIN_TECH_LEVEL  5

#define STARVE_LEVEL  35                  //si agriculture trop bas en pourcents... morts de faim
#define STARVE_AMOUNT 0.00001                 // pourcents de population morts de faim par _jour
#define RECOVERY_AGRICULTURE 0.021         //recuperation en pourcent par _jour
#define RECOVERY_INDUSTRY    0.02         //ca devrait etre pas moins que
                                          //kILL_INDUSTRY et KILL_AGRI


//pour agriculture-temps
#define VERY_DRY        1
#define DRY             2
#define MODERATE        3
#define RAINY           4
#define VERY_RAINY      5

#define VERY_COLD       1
#define COLD            2
// #define MODERATE     3 //meme moderate pour secheresse et temperature
#define WARM            4
#define HOT             5

#define WEATHER_INFLUENCE 0.6  // nb de fois qu'on multiplie la difference
                                // pour obtenir les pourcents a soustraire de l'agriculture
                                // par mois
                                


class Country: public BArchivable //faut dériver de BArchivable pour pouvoir etre archivé (sauvé sur HD)
{
public:
	Group	**_group;
	Country	**_country;
	Politic	**_politic;
	Weapon	**_weapon;
	Day		*_jour;   
	int16	attack_amount;
	int16	agression_amount;
	Attack	*current_attacks[MAX_ATTACK];  
	Attack	*current_agressions[MAX_ATTACK];  
	uint64	the_army[MAX_WEAPON]; //max 24 armes sinon le tab multiplié par le nb de pays devient trop gros déjà comme ça pour 200 pays on en a pour 384 k
	uint64	the_ennemy_army[MAX_WEAPON];
	BRect	limit;
	int		status;
   	int32	inf_def; 
   	int32	tnk_def, mar_def, air_def, mis_def,dca_def,nuke_def;
   	unsigned char attacked_by;
   	float	center_x,center_y;
   	int16	travel_01,travel_02,travel_03,travel_04;
   	unsigned char move_01,move_02,move_03,move_04;
   	unsigned char month_changed,access_sea,access_nuke;
   	unsigned char real_temperature,expected_temperature;  //cold or hot
   	unsigned char real_weather,expected_weather;          //dry ou rainy
	uint32 money;
	uint32 power;
	Country *victim_01,*victim_02,*victim_03,*victim_04; //pays_attackes
	Country *agressor_01,*agressor_02,*agressor_03,*agressor_04; //agresseurs presents
	uint64 population;
	int16 defeat,victory,war,civ_killed,pnb;
	double moral,birth_rate,tech_level,ennemy_tech_level,tax; // moral,birth ou tech en % donc avec virgule
	double agriculture, industry, resistance,resist_counter;
	int32 marine, airforce, missile,dca,tank,nuke;
	int32 inf_01, tnk_01, mar_01, air_01, mis_01, nuke_01; //troupes engagees
	int32 inf_02, tnk_02, mar_02, air_02, mis_02, nuke_02; //ou en route
	int32 inf_03, tnk_03, mar_03, air_03, mis_03, nuke_03;
	int32 inf_04, tnk_04, mar_04, air_04, mis_04, nuke_04;
	int32 infantry, ennemy_infantry;
	int32 ennemy_marine, ennemy_airforce,ennemy_missile,ennemy_tank,ennemy_nuke;
	unsigned char fight_marine,fight_infantry, fight_airforce, fight_missile, fight_dca,fight_tank;
	unsigned char fight_ennemy_marine, fight_ennemy_tank, fight_ennemy_infantry, fight_ennemy_airforce, fight_ennemy_missile,fight_ennemy_nuke;
  	unsigned char nb_in_pal,battle_turn;
    unsigned char group,base_group; //numero du groupe politique
	unsigned char battle(); //action de bataille
	unsigned char revolution_happened;
	int32 revolution_euphory; //nb de _jour que dure l'euphorie avant de risquer nouvelle revolution

	Country(const char *name,char couleur_num,char group, Day *compteur,Group *Group_id[MAX_GROUP], Country *Country_id[MAX_COUNTRY],Politic *Politic_id[MAX_POLITIC],Weapon *Weapon_id[MAX_WEAPON]); 	// col_dans pal + groupe
	Country(BMessage *archive);
	
	BArchivable *Country::Instantiate(BMessage *archive); 

	int16 TravelTime(Country* to_which_country);
	void AddAttack(uint8 victim_id);
	void AddAgressor(Attack* attack);
	void PowerCalc();
	void GroupPower();
	void CheckUp();

	inline void		set_group(unsigned char grp)	{ group=grp; }

	//Ca c'est les nouvelles fonctions pour l'armée...
	void AddArmy(uint8 which_type, bool to_ennemy, uint64 amount);
	void SubArmy(uint8 which_type, bool to_ennemy, uint64 amount);
	void SetArmy(uint8 which_type, bool to_ennemy, uint64 amount);
	bool BuyArmy(uint8 which_type, uint64 amount);
	void SendTroops(Country *victim, uint8 attack_id);
	void IsAttacking(Country *victim,uint8 attack_id);
	void IsAttacked(Country *agressor,uint8 attack_id);
	void AskRetreat(Country *home_country);
	
	// population
	inline	void	add_moral(double to_add)				{ moral+=to_add; if(moral< MIN_MORAL) moral= MIN_MORAL; if(moral>100) moral=100; }	//industry functions
	inline	void	sub_moral(double to_sub)				{ moral-=to_sub; if(moral< MIN_MORAL) moral= MIN_MORAL; if(moral>100) moral=100; }
	inline	void	set_moral(double set)					{ moral=set; if(moral< MIN_MORAL) moral= MIN_MORAL; if(moral>100) moral=100; }
	inline	void	add_population(unsigned long to_add)	{ population+=to_add; if(population<1) population=0; }
	inline	void	sub_population(unsigned long to_sub)	{ population-=to_sub; if(population<1) population=0; }
	inline	void	set_population(unsigned long set)		{ population=set; if(population<1) population=0; }
	inline	void	add_pnb(int32 to_add)					{ pnb+=to_add; if(pnb<1) pnb=0; }
	inline	void	sub_pnb(int32 to_sub)					{ pnb-=to_sub; if(pnb<1) pnb=0; }
	inline	void	set_pnb(int32 set)						{ pnb=set; if(pnb<1) pnb=0; }
	inline	void	add_civ_killed(int32 to_add)			{ civ_killed+=to_add; if(civ_killed<1) civ_killed=0; }
	inline	void	sub_civ_killed(int32 to_sub)			{ civ_killed-=to_sub; if(civ_killed<1) civ_killed=0; }
	inline	void	set_civ_killed(int32 set)				{ civ_killed=set; if(civ_killed<1) civ_killed=0; }
	inline	void	add_birth_rate(double to_add)			{ birth_rate+=to_add; if(birth_rate<1) birth_rate=1; }
	inline	void	sub_birth_rate(double to_sub)			{ birth_rate-=to_sub; if(birth_rate<1) birth_rate=1; }
	inline	void	set_birth_rate(double set)				{ birth_rate=set; if(birth_rate<1) birth_rate=1; }
 	
 	// argent
	inline	void	add_tax(double to_add)			{ tax+=to_add; if(tax<1) tax=1; if(tax>=100) tax=100;}
	inline	void	sub_tax(double to_sub)			{ tax-=to_sub; if(tax<1) tax=1; if(tax>=100) tax=100;}
	inline	void	set_tax(double set)				{ tax=set; if(tax<1) tax=1; if(tax>=100) tax=100;}
	inline	void	add_tech_level(double to_add)	{ tech_level+=to_add; if(tech_level< MIN_TECH_LEVEL) tech_level=MIN_TECH_LEVEL; if(tech_level>100) tech_level=100;}
	inline	void	sub_tech_level(double to_sub)	{ tech_level-=to_sub; if(tech_level<MIN_TECH_LEVEL) tech_level=MIN_TECH_LEVEL; if(tech_level>100) tech_level=100;}
	inline	void	set_tech_level(double set)		{ tech_level=set; if (tech_level<MIN_TECH_LEVEL) tech_level=MIN_TECH_LEVEL; if(tech_level>100) tech_level=100;}
	inline	void	add_money(float to_add)			{ money+=(long long int)to_add; if(money<1) money=1;} //sinon div par 0
	inline	void	sub_money(float to_sub)			{ money-=(long long int)to_sub; if(money<1) money=1;}
	inline	void	set_money(float set)			{ money=(long long int)set; if(money<1) money=1;}
	inline	void	add_agriculture(double to_add)	{ agriculture+=to_add; if(agriculture< MIN_AGRICULTURE) agriculture=MIN_AGRICULTURE; if(agriculture>100) agriculture=100;}
	inline	void	sub_agriculture(double to_sub)	{ agriculture-=to_sub; if(agriculture< MIN_AGRICULTURE) agriculture=MIN_AGRICULTURE; if(agriculture>100) agriculture=100;}
	inline	void	set_agriculture(double set)		{ agriculture=set; if(agriculture<MIN_AGRICULTURE) agriculture=MIN_AGRICULTURE; if(agriculture>100) agriculture=100;}
	inline	void	add_industry(double to_add)		{ industry+=to_add; if(industry< MIN_INDUSTRY) industry=MIN_INDUSTRY; if(industry>100) industry=100;}
	inline	void	sub_industry(double to_sub)		{ industry-=to_sub; if(industry< MIN_INDUSTRY) industry=MIN_INDUSTRY; if(industry>100) industry=100;}
	inline	void	set_industry(double set)		{ industry=set; if(industry< MIN_INDUSTRY) industry=MIN_INDUSTRY; if(industry>100) industry=100;}

	// armes
	inline	void	add_infantry(long to_add)	{ infantry+=to_add; if(infantry<=0) infantry=0; }
	inline	void	sub_infantry(long to_sub)	{ infantry-=to_sub; if(infantry<=0) infantry=0; }
	inline	void	set_infantry(long set)		{ infantry=set; if(infantry<=0) infantry=0; }
	inline	void	add_tank(int32 to_add)		{ tank+=to_add; if(tank<=0) tank=0; }
	inline	void	sub_tank(int32 to_sub)		{ tank-=to_sub; if(tank<=0) tank=0; }
	inline	void	set_tank(int32 set)			{ tank=set; if(tank<=0) tank=0; }
	inline	void	add_marine(int32 to_add)	{ marine+=to_add; if(marine<=0) marine=0; }
	inline	void	sub_marine(int32 to_sub)	{ marine-=to_sub; if(marine<=0) marine=0; }
	inline	void	set_marine(int32 set)		{ marine=set; if(marine<=0) marine=0; }
	inline	void	add_airforce(int32 to_add)	{ airforce+=to_add; if(airforce<=0) airforce=0; } //industry functions
	inline	void	sub_airforce(int32 to_sub)	{ airforce-=to_sub; if(airforce<=0) airforce=0; }
	inline	void	set_airforce(int32 set)		{ airforce=set; if(airforce<=0) airforce=0; }
	inline	void	add_missile(int32 to_add)	{ missile+=to_add; if(missile<=0) missile=0; }
	inline	void	sub_missile(int32 to_sub)	{ missile-=to_sub; if(missile<=0) missile=0; }
	inline	void	set_missile(int32 set)		{ missile=set; if(missile<=0) missile=0; }
	inline	void	add_dca(int32 to_add)		{ dca+=to_add; if(dca<=0) dca=0; }
	inline	void	sub_dca(int32 to_sub)		{ dca-=to_sub; if(dca<=0) dca=0; }
	inline	void	set_dca(int32 set)			{ dca=set; if(dca<=0) dca=0; }
	inline	void	add_nuke(int32 to_add)		{ nuke+=to_add; if(nuke<=0) nuke=0; }
	inline	void	sub_nuke(int32 to_sub)		{ nuke-=to_sub; if(nuke<=0) nuke=0; }
	inline	void	set_nuke(int32 set)			{ nuke=set; if(nuke<=0) nuke=0; }

	// ennemies
	inline	void	add_ennemy_marine(int32 to_add)		{ ennemy_marine+=to_add; if(ennemy_marine<1) ennemy_marine=0; }
	inline	void	sub_ennemy_marine(int32 to_sub)		{ ennemy_marine-=to_sub; if(ennemy_marine<1 )ennemy_marine=0; }
	inline	void	set_ennemy_marine(int32 set)		{ ennemy_marine=set; if(ennemy_marine<1) ennemy_marine=0; }
	inline	void	add_ennemy_infantry(long to_add)	{ ennemy_infantry+=to_add; if(ennemy_infantry<1) ennemy_infantry=0; }
	inline	void	sub_ennemy_infantry(long to_sub)	{ ennemy_infantry-=to_sub; if(ennemy_infantry<1) ennemy_infantry=0; }
	inline	void	set_ennemy_infantry(long set)		{ ennemy_infantry=set; if(ennemy_infantry<1) ennemy_infantry=0; }
	inline	void	add_ennemy_tank(int32 to_add)		{ ennemy_tank+=to_add; if(ennemy_tank<1) ennemy_tank=0; }
	inline	void	sub_ennemy_tank(int32 to_sub)		{ ennemy_tank-=to_sub; if(ennemy_tank<1) ennemy_tank=0; }
	inline	void	set_ennemy_tank(int32 set)    		{ ennemy_tank=set; if(ennemy_tank<1) ennemy_tank=0; }
	inline	void	add_ennemy_airforce(int32 to_add)	{ ennemy_airforce+=to_add; if(ennemy_airforce<1) ennemy_airforce=0; } //industry functions
	inline	void	sub_ennemy_airforce(int32 to_sub)	{ ennemy_airforce-=to_sub; if(ennemy_airforce<1) ennemy_airforce=0; }
	inline	void	set_ennemy_airforce(int32 set)		{ ennemy_airforce=set; if(ennemy_airforce<1) ennemy_airforce=0; }
	inline	void	add_ennemy_missile(int32 to_add)	{ ennemy_missile+=to_add; if(ennemy_missile<1) ennemy_missile=0; }
	inline	void	sub_ennemy_missile(int32 to_sub)	{ ennemy_missile-=to_sub; if(ennemy_missile<1) ennemy_missile=0; }
	inline	void	set_ennemy_missile(int32 set)		{ ennemy_missile=set; if(ennemy_missile<1) ennemy_missile=0; }
	inline	void	add_ennemy_nuke(int32 to_add)		{ ennemy_nuke+=to_add; if(ennemy_nuke<1) ennemy_nuke=0; }
	inline	void	sub_ennemy_nuke(int32 to_sub)		{ ennemy_nuke-=to_sub; if(ennemy_nuke<1) ennemy_nuke=0; }
	inline	void	set_ennemy_nuke(int32 set)			{ ennemy_nuke=set; if(ennemy_nuke<1) ennemy_nuke=0; }


	// victoire defaite
	inline	void	add_defeat(int32 to_add)		{ defeat+=to_add; if(defeat<1) defeat=0; }
	inline	void	sub_defeat(int32 to_sub)		{ defeat-=to_sub; if(defeat<1) defeat=0; }
	inline	void	set_defeat(int32 set)			{ defeat=set; if(defeat<1) defeat=0; }
	inline	void	add_victory(int32 to_add)		{ victory+=to_add; if(victory<1) victory=0; } //industry functions
	inline	void	sub_victory(int32 to_sub)		{ victory-=to_sub; if(victory<1) victory=0; }
	inline	void	set_victory(int32 set)			{ victory=set; if(victory<1) victory=0; }

	void set_army();		//génére les valeurs par défaut
	void default_army();	//applique les valeurs par défaut

	bool buy(long inf_xx,int32 tank_xx,int32 mar_xx,int32 air_xx,int32 mis_xx,int32 nuke_xx,int32 dca_xx);
	void day_passed();			//chaque fois qu'un _jour passe, industry etc...
	void month_passed();		//chaque fois qu'un _jour passe, industry etc...
	void day_passed_fake();     //juste pour l'avance du debut...
	void month_passed_fake();   //ces deux n'agissent que sur la population
	void send_troops(Country *victim, long sent_inf, int32 sent_tnk, int32 sent_mar,int32 sent_air, int32 sent_mis, int32 sent_nuke); //envoi des troupes
	void attacking(Country *victim, long engaged_inf, int32 engaged_tnk, int32 engaged_mar,int32 engaged_air, int32 engaged_mis, int32 engaged_nuke); //engagement des troupes
	void attacked(Country *agressor,long en_infantry, int32 en_tank, int32 en_marine,int32 en_airforce, int32 en_missile, int32 en_nuke,unsigned char attacking_group, double en_tech); //attaque par ennemi
	void Retreat(Country *home_country);
	void Revolution();  
	void ComputerPlay();
	int32 FindDistance(Country *ct1,Country *ct2);//distance en km

	inline	const char *Name()						{ return _name.String(); }
	inline	void		SetName(const char *name)	{ _name = name; }
	
protected:
	BString		_name;
}; //fin de declaration classe Country
#endif
