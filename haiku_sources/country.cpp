//*************************************//
//********* Classe Country ************//
//*************************************//
#include "def_col.h" //pour on/off

#include "day.h"
#include "group.h"
#include "country.h"
#include "politic.h"
#include "weapon.h"
#include "attack.h"

#include <Window.h>
#include <Alert.h>

/**** constructeur ****/
Country::Country(const char *name,char palette_color,char grp, Day *compteur,Group *Group_id[MAX_GROUP], Country *Country_id[MAX_COUNTRY],Politic *Politic_id[MAX_POLITIC],Weapon *Weapon_id[MAX_WEAPON]) 
{ 
	_jour=compteur;
	attack_amount=0;
	_group = Group_id;
	_country  = Country_id;
	_politic = Politic_id;
	_weapon = Weapon_id;

	//ces valeurs sont nécessaires pour init dans Mapview	
	limit.top = DEF_PIC_Y_SIZE-1;
	limit.left = DEF_PIC_X_SIZE-1;
	limit.bottom=0;
	limit.right=0;
	attacked_by=grp; //par défaut le pays est son propre agresseur
							//histoire de pas chier dans le vide
	//nb de mois que dure l'euphorie avant de risquer nouvelle revolution
	revolution_euphory=REVOLUTION_EUPHORY;   //pas de révolution dès le début...
	power=0;
	revolution_happened=OFF;
	
	//initialisations standards pour tous les pays avant le debut
	_name = name;
	resist_counter=0;
	civ_killed=0;
	status=FREE;
	agriculture=100; //en pourcents
	industry=100;
	moral=100;
	resistance=0;
	victory=0;
	defeat=0;
	war = OFF;

	infantry= 0;
	tank    = 0;
	marine  = 0;
	airforce= 0;
	missile = 0;
	dca = 0;
	nuke = 0;

	ennemy_infantry= 0;
	ennemy_tank    = 0;
	ennemy_marine  = 0;
	ennemy_airforce= 0;
	ennemy_missile = 0;
	ennemy_nuke = 0;

	victim_01 = NULL;
	victim_02 = NULL;
	victim_03 = NULL;
	victim_04 = NULL;

	agressor_01 = NULL;
	agressor_02 = NULL;
	agressor_03 = NULL;
	agressor_04 = NULL;

	move_01=move_02=move_03=move_04=OFF;
	travel_01=travel_02=travel_03=travel_04=0;
	ennemy_tech_level=0;
	access_sea  = ON;
	access_nuke = OFF;

	center_x=100;  //coord du pixel au centre du pays pour calc distances
	center_y=100;
	nb_in_pal=palette_color;
	base_group=grp;
	group=grp;
	birth_rate=DEFAULT_BIRTH_RATE; //defini dans defines.h (=1.05 normalement)
	money=1;  //pas zero sinon div. by zero dans calcul moral
	tax=DEFAULT_ARMY_TAX;

	real_temperature     = VERY_COLD;
	expected_temperature = MODERATE;
	real_weather         = VERY_DRY;
	expected_weather     = MODERATE;
}

/**** constructeur ****/
Country::Country(BMessage *archive)
{
}

/**** fonction instantiate doit être dans chaque classe à archiver ****/
BArchivable *Country::Instantiate(BMessage *archive)
{
	if(!validate_instantiation(archive, "Country")) 
		return NULL; 

	return new Country(archive); 
}


void Country::AddArmy(uint8 which_type, bool to_ennemy, uint64 amount)
{
	if(to_ennemy)
		the_ennemy_army[which_type] += amount;
	else
		the_army[which_type] += amount;
}

void Country::SubArmy(uint8 which_type, bool to_ennemy, uint64 amount)
{
	if(to_ennemy)
	{
		if(the_ennemy_army[which_type] > amount)
			the_ennemy_army[which_type] -= amount;
		else
			the_ennemy_army[which_type] = 0;
	}
	else
	{
		if(the_army[which_type] > amount)
			the_army[which_type] -= amount;
		else
			the_army[which_type] = 0;
	}
}

void Country::SetArmy(uint8 which_type, bool to_ennemy, uint64 amount)
{
	if(to_ennemy)
		the_ennemy_army[which_type] = amount;
	else
		the_army[which_type] = amount;
}


int16 Country::TravelTime(Country* to_which_country)
{
	int16 delta; 
	delta=FindDistance(this,to_which_country);//trouve distance en KM

	//plus tech est bas plus c'est long
	int16 temp_travel=(int16) (delta/KILOMETER_PER_DAY);
	temp_travel= (int16 )(temp_travel/float(tech_level/100));
	temp_travel+=1; //+1 sinon si on a pas le minimum (1, donc) ça plante

	return temp_travel;
}



/*-----------------------------------------------------------------------*/

void Country::send_troops(Country *victim, long sent_inf, int32 sent_tnk, int32 sent_mar,int32 sent_air, int32 sent_mis, int32 sent_nuke)
{//envoi des troupes

	unsigned int delta; 
	delta=FindDistance(this,victim);//trouve distance en KM

	//plus tech est bas plus c'est long
	unsigned int temp_travel=(unsigned int)(delta/KILOMETER_PER_DAY);
	temp_travel= (unsigned int)(temp_travel/(tech_level/100));

	temp_travel+=2; //+2 sinon si on a pas le minimum (2, donc) ça plante

	long tmp_inf;
	int tmp_tnk,tmp_mar,tmp_air,tmp_mis,tmp_nuke;

	//par defaut egal au valeur donnees mais
	tmp_inf  = sent_inf;
	tmp_tnk  = sent_tnk;
	tmp_mar  = sent_mar;
	tmp_air  = sent_air;
	tmp_mis  = sent_mis;
	tmp_nuke = sent_nuke;

	//on envoie seulement si les troupes existent!
	if(tmp_inf  > infantry)
		tmp_inf=infantry;

	if(tmp_tnk  > tank)
		tmp_tnk=tank;

	if(tmp_mar  > marine)
		tmp_mar=marine;

	if(tmp_air  > airforce)
		tmp_air=airforce;

	if(tmp_mis  > missile)
		tmp_mis=missile;

	if(tmp_nuke > nuke)
		tmp_nuke=nuke;

	//4 attaques simultanees possibles
	/*RENFORTS*/
	//si deja utilise (guerre en cours) -> Renforts
	if(victim_01!=NULL)
	{
 		//si c'est le meme et que le mouvement precedent est termine
 		if((victim==victim_01) && (move_01==OFF))
     	{
     		move_01=ON; travel_01=temp_travel;
      		inf_01=tmp_inf, tnk_01=tmp_tnk, mar_01=tmp_mar,air_01=tmp_air,mis_01=tmp_mis,nuke_01=tmp_nuke;
      		sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
      		sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
		}
	}

	//si deja utilise (guerre en cours) -> Renforts
	if(victim_02!=NULL)
	{
		if((victim==victim_02) && (move_02==OFF)) //si c'est le meme et que le mouvement precedent est termine
		{
			move_02=ON; travel_02=temp_travel;
      		inf_02=tmp_inf, tnk_02=tmp_tnk, mar_02=tmp_mar,air_02=tmp_air,mis_02=tmp_mis,nuke_02=tmp_nuke;
      	}
     	sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
      	sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
	}

	//si deja utilise (guerre en cours) -> Renforts
	if(victim_03!=NULL)
	{
		//si c'est le meme et que le mouvement precedent est termine
		if((victim==victim_03) && (move_03==OFF))
     	{
     		move_03=ON; travel_03=temp_travel;
      		inf_03=tmp_inf, tnk_03=tmp_tnk, mar_03=tmp_mar,air_03=tmp_air,mis_03=tmp_mis,nuke_03=tmp_nuke;
      	}
      	sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
      	sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
	}

	//si deja utilise (guerre en cours) -> Renforts
	if(victim_04!=NULL)
	{
		//si c'est le meme et que le mouvement precedent est termine
		if((victim==victim_04) && (move_04==OFF))
     	{
     		move_04=ON; travel_04=temp_travel;
      		inf_04=tmp_inf, tnk_04=tmp_tnk, mar_04=tmp_mar,air_04=tmp_air,mis_04=tmp_mis,nuke_04=tmp_nuke;
      	}
      	sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
      	sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
	}

	//AJOUTER UNE NOUVELLE VICTIME A ATTAQUER
	int do_add_victim=0;
	
	if(victim==victim_01)
		do_add_victim+=1;
	
	if(victim==victim_02)
		do_add_victim+=1;
	
	if(victim==victim_03)
		do_add_victim+=1;
	
	if(victim==victim_04)
		do_add_victim+=1;

	if (do_add_victim==0)
	{ 
		//si egal a aucun des attaques existantes on le rajoute
		//si pas deja utilise
		if (victim_01==NULL)
        {
        	victim_01=victim; move_01=ON; travel_01=temp_travel;
            inf_01=tmp_inf, tnk_01=tmp_tnk, mar_01=tmp_mar,air_01=tmp_air,mis_01=tmp_mis,nuke_01=tmp_nuke;
            sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
            sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
		}
		else
		{
         	if(victim_02==NULL)
            {
            	victim_02=victim; move_02=ON; travel_02=temp_travel;
            	inf_02=tmp_inf, tnk_02=tmp_tnk, mar_02=tmp_mar,air_02=tmp_air,mis_02=tmp_mis,nuke_02=tmp_nuke;
            	sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
            	sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
            }
    		else
    		{
    			if(victim_03==NULL)
             	{
             		victim_03=victim; move_03=ON; travel_03=temp_travel;
              		inf_03=tmp_inf, tnk_03=tmp_tnk, mar_03=tmp_mar,air_03=tmp_air,mis_03=tmp_mis,nuke_03=tmp_nuke;
              		sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
              		sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
             	}
    			else
    			{
    				if(victim_04==NULL)
             		{
             			victim_04=victim; move_04=ON; travel_04=temp_travel;
              			inf_04=tmp_inf, tnk_04=tmp_tnk, mar_04=tmp_mar,air_04=tmp_air,mis_04=tmp_mis,nuke_04=tmp_nuke;
              			sub_infantry (tmp_inf); sub_tank (tmp_tnk); sub_marine (tmp_mar);
              			sub_airforce (tmp_air); sub_missile (tmp_mis); sub_nuke (tmp_nuke);
              		}
              	}
			}
		}
	}

	char str[255],str2[255];
	
	sprintf(str,_name.String());
	sprintf(str2," sending troops to ");
	strcat(str,str2); //grouper les deux
	sprintf(str2,victim->Name());
	strcat(str,str2); //on joint les deux bouts après car types différents
	_jour->add_history(str); //en pointer ça merde faut envoyer un char xxx[]
}

void Country::Retreat(Country *home_country)
{
	//retrait d'un pays à un autre
	//on met l'armée dans le pays de refuge
	home_country->add_infantry(ennemy_infantry*0.9); //on perd 10% pendant la fuite
	home_country->add_tank(ennemy_tank*0.9);
	home_country->add_marine(ennemy_marine*0.9);
	home_country->add_airforce(ennemy_airforce*0.9);
    home_country->add_missile(ennemy_missile*0.9);
    home_country->add_nuke(ennemy_nuke*0.9);
		
	//puis on l'efface
	set_ennemy_infantry(0);
    set_ennemy_tank(0);
    set_ennemy_marine(0);
    set_ennemy_airforce(0);
    set_ennemy_missile(0);
    set_ennemy_nuke(0);

    //plus d'attaque
	victim_01 = NULL;
    victim_02 = NULL;
    victim_03 = NULL;
    victim_04 = NULL;
		  
	//plus de guerre      
	war = OFF; 

	char str[255];
	sprintf(str,"Agressors retreat from ");
   	strcat(str,_name.String()); //grouper les deux
	strcat(str," to "); //grouper les deux
   	strcat(str,home_country->Name()); //grouper les deux
	strcat(str,"."); //grouper les deux
	_jour->add_history(str); //en pointer ça merde faut envoyer un char 
}

void Country::attacking(Country *victim, long engaged_inf, int32 engaged_tnk, int32 engaged_mar,int32 engaged_air, int32 engaged_mis, int32 engaged_nuke)
{
	//engagemement des troupes
	if (victim->agressor_01!=NULL)
	{
		//a moins qu'on soit un renfort du meme groupe
		//si un a autre attaqué pendant qu'on travelait gaiement
		//il y a retraite au lieu d'attaque
		if(victim->group != group && victim->agressor_01->group!=group) 
		{
			infantry += engaged_inf;
			tank     += engaged_tnk;
			marine	 += engaged_mar;
			airforce += engaged_air;
			missile  += engaged_mis;
			nuke     += engaged_nuke;
	
			char str[255],str2[255];
			sprintf(str,_name.String());
 	   		sprintf(str2," could not attack ");
			strcat(str,str2); //grouper les deux
			sprintf(str2,victim->Name());
 	   		strcat(str,str2); //grouper les deux
			sprintf(str2,". Other troops are present. Back home.");
			strcat(str,str2); //grouper les deux
			_jour->add_history(str); //en pointer ça merde faut envoyer un char 

			return;	
		}
	}


	// si c'est une attaque de la resistance
	if(victim==this)
		victim->attacked(this,engaged_inf,engaged_tnk,engaged_mar,engaged_air,engaged_mis,engaged_nuke, base_group, RESISTANCE_TECH_LEVEL);
	else
		victim->attacked(this,engaged_inf,engaged_tnk,engaged_mar,engaged_air,engaged_mis,engaged_nuke, group, tech_level);
                 
    char str[255],str2[255];
	if(victim==this) 
	{	
		if(_jour->full_log==ON) 
	 	{
	 		sprintf(str,_name.String());
	 		sprintf(str2," attacked by resistance!"); strcat(str,str2);
	 		_jour->add_history(str); //en pointer ça merde faut envoyer un char xxx[]
	 	} 
 	}
 	else
 	{
 		sprintf(str,_name.String());
    	if (victim->group!=group)
    		sprintf(str2," attacking ");
		else
			sprintf(str2," troops reached ");  
			
		strcat(str,str2); //grouper les deux
		sprintf(str2,victim->Name());
		strcat(str,str2); //on joint les deux bouts après car types différents
		_jour->add_history(str); //en pointer ça merde faut envoyer un char xxx[]
	}
}//fin function attacking

void Country::attacked(Country *agressor,long en_infantry, int32 en_tank, int32 en_marine,int32 en_airforce, int32 en_missile, int32 en_nuke,unsigned char attacking_group, double en_tech)
{
	//en bref: si l'attaquant est le meme que celui qui a le pouvoir
	//dans le pays les forces s'additionnent au lieu d'attaquer.
	if(war==OFF)
		attacked_by = attacking_group;

	int do_add_agressor=0;

	//4 attaques simultanees possibles
	//si l'agresseur existe déjà on le rajoute pas
	if(agressor==agressor_01)
		do_add_agressor+=1;

	if(agressor==agressor_02)
		do_add_agressor+=1;

	if(agressor==agressor_03)
		do_add_agressor+=1;

	if(agressor==agressor_04)
		do_add_agressor+=1;

	//mais si resistance, alors il y a un auto-agresseur
  	if(agressor==this)
		do_add_agressor=0;

	//si egal a aucun des attaques existantes on le rajoute
	if(do_add_agressor==0)
	{
		//si pas deja utilise
		if(agressor_01==NULL)
			agressor_01=agressor;
  		else
  		{
  			if(agressor_02==NULL)
  				agressor_02=agressor;
    		else
    		{
    			if(agressor_03==NULL)
    				agressor_03=agressor;
    			else
    			{
    				if(agressor_04==NULL)
    					agressor_04=agressor;
    			}
    		}
    	}
    }

	//si c'est un renfort de celui qui a le pouvoir
	if(attacking_group==group)
    {
    	add_infantry(en_infantry);
        add_tank(en_tank);
        add_marine(en_marine);
        add_airforce(en_airforce);
        add_missile(en_missile);
        add_nuke(en_nuke);

        //faut aussi que l'agresseur sache que c'est pas une attaque
        if(agressor->victim_01==this)
        	agressor->victim_01=NULL;
        
        if(agressor->victim_02==this)
        	agressor->victim_02=NULL;
        
        if(agressor->victim_03==this)
        	agressor->victim_03=NULL;
        
        if(agressor->victim_04==this)
        	agressor->victim_04=NULL;
	}
	else //si c'est une vraie attaque
	{
		war=ON;
		                  
		add_ennemy_infantry(en_infantry);
		add_ennemy_tank(en_tank);
		add_ennemy_marine(en_marine);
		add_ennemy_airforce(en_airforce);
		add_ennemy_missile(en_missile);
		add_ennemy_nuke(en_nuke);
             
		if(ennemy_tech_level == 0)
			ennemy_tech_level =en_tech;
		else
			ennemy_tech_level = (ennemy_tech_level +en_tech)/2;
             
		battle_turn=0;
	}
	

}//fin function attacked

void Country::day_passed_fake() //seulement pour l'avance du debut
{
	//pour le chgt de mois (recolte de tax+agriculture+moral)
	if(month_changed!=_jour->month_id)
    {
    	month_changed=_jour->month_id;
    	month_passed_fake();
    }

}//fin day_passed_fake

void Country::month_passed_fake() //seulement pour l'avance du debut
{
	//POPULATION BIRTH
  	double b_rate;
	uint32 pop;
	b_rate=(birth_rate *(moral/100)); //reproduction max requiert moral 100%
	pop=(uint32)(b_rate*population); //convertit en int
	pop/=100; //div par 100 parce-que pour-cent
	pop/=18;  //div par 12 parce-que taux par annee et addition par mois
            //ATTENTION!!!
            //18 au lieu de 12 histoire de diminuer le taux naissanc mondial!!!
  	add_population(pop); //ajout de la difference
}//fin month_passed_fake

void Country::AddAttack(uint8 victim_id)
{
	attack_amount++;	
	current_attacks[attack_amount]= new Attack(victim_id, TravelTime(_country[victim_id]));
} 

void Country::AddAgressor(Attack* attack)
{
	agression_amount++;	
	current_agressions[agression_amount]=attack;
} 

void Country::day_passed() //a faire chaque _jour
{
	//pour le chgt de mois (recolte de tax+agriculture+moral)
	if(month_changed!=_jour->month_id)
    {
    	month_changed=_jour->month_id;
    	month_passed();
    }

	//TRAVEL TIME / ARMY MOVEMENT
	if(move_01==ON && travel_01-- <= 0)
		travel_01=0; //soustraction de 1
	
	if(move_02==ON && travel_02-- <= 0)
		travel_02=0;
	
	if(move_03==ON && travel_03-- <= 0)
		travel_03=0;
	
	if(move_04==ON && travel_04-- <= 0)
		travel_04=0;

	if(travel_01==1 && victim_01!=NULL)
  	{	
   		attacking(victim_01, inf_01, tnk_01, mar_01,air_01,mis_01,nuke_01);
   		travel_01=0;
   		move_01=OFF;
  	}

	if(travel_02==1 && victim_02!=NULL)
    {
    	attacking(victim_02, inf_02, tnk_02, mar_02,air_02,mis_02,nuke_02);
     	travel_02=0;
     	move_02=OFF;
	}

	if (travel_03==1 && victim_03!=NULL)
    {
    	attacking(victim_03, inf_03, tnk_03, mar_03,air_03,mis_03,nuke_03);
     	travel_03=0;
     	move_03=OFF;
    }

	if(travel_04==1 && victim_04!=NULL)
    {
    	attacking(victim_04, inf_04, tnk_04, mar_04,air_04,mis_04,nuke_04);
     	travel_04=0;
     	move_04=OFF;
	}

	//AGRICULTURE + INDUSTRY RECOVERY
  	add_agriculture (RECOVERY_AGRICULTURE);
  	add_industry    (RECOVERY_INDUSTRY);

	if (war==ON)
    {
    	char str[255],str2[255];
     
		 //resultat de la bataille via return
     	switch(battle())
     	{//bataille _journaliere
		case LOST:
      		{
      			war=OFF;
      			ennemy_tech_level=0;
      			group=attacked_by;

  				//update le pays
				BMessage msg(MULTIPLY_RECT);
				msg.AddRect("zone",limit);				
				_jour->mainWin->PostMessage(&msg);
      
      			//pour eviter que si la bataille a trop tué le moral la révolution ait lieu de suite
      			revolution_euphory=REVOLUTION_EUPHORY*2;
      
       			//si changement pays changement couleur donc...
       			//puisque le pays change de gvt, l'armee s'integre (occupation)
		       	//si pas d'agresseur externe c'est la resistance
       			//if (agressor_01==NULL) agressor_01=this;
		       	sprintf(str,_name.String());
		       	
		       	 //si pas attaque de la resistance toute seule (donc numero 1
   		    	if(agressor_01!=this)
       			{
       				add_defeat(1);
					sprintf(str2," conquered by ");
					//grouper les deux
					strcat(str,str2);
					sprintf(str2,agressor_01->Name());
					//on joint les deux bouts après car types différents
					strcat(str,str2);
				}
				else
				{
					strcat(str," liberated by local resistance!");
			  		add_victory(1);
			  	}
		
				_jour->add_history(str);
		
       			add_infantry(ennemy_infantry);
       			sub_ennemy_infantry(ennemy_infantry);
       			add_tank(ennemy_tank);
       			sub_ennemy_tank(ennemy_tank);
       			add_marine(ennemy_marine);
       			sub_ennemy_marine(ennemy_marine);
       			add_airforce(ennemy_airforce);
       			sub_ennemy_airforce(ennemy_airforce);
       			add_missile(ennemy_missile);
       			sub_ennemy_missile(ennemy_missile);
   
   				//si le pays est le premier agresseur d'un autre ses troupes reviennet et
   				//sont engrangées par l'occupant
       			if (victim_01!=NULL && victim_01->agressor_01 == this)
       				victim_01->Retreat(this);
       				
       			if (victim_02!=NULL && victim_02->agressor_01 == this)
       				victim_02->Retreat(this);
       				
       			if (victim_03!=NULL && victim_03->agressor_01 == this)
       				victim_03->Retreat(this);
       				
       			if (victim_04!=NULL && victim_04->agressor_01 == this)
       				victim_04->Retreat(this);
       
              	if(agressor_01!=NULL)
         		{
         			agressor_01->add_victory(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_01->victim_01==this) agressor_01->victim_01=NULL;
         			if(agressor_01->victim_02==this) agressor_01->victim_02=NULL;
        			if(agressor_01->victim_03==this) agressor_01->victim_03=NULL;
         			if(agressor_01->victim_04==this) agressor_01->victim_04=NULL;
         		}

         		if(agressor_02!=NULL)
         		{
         			agressor_02->add_victory(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_02->victim_01==this) agressor_02->victim_01=NULL;
         			if(agressor_02->victim_02==this) agressor_02->victim_02=NULL;
         			if(agressor_02->victim_03==this) agressor_02->victim_03=NULL;
         			if(agressor_02->victim_04==this) agressor_02->victim_04=NULL;
         		}

		        if(agressor_03!=NULL)
         		{
         			agressor_03->add_victory(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_03->victim_01==this) agressor_03->victim_01=NULL;
         			if(agressor_03->victim_02==this) agressor_03->victim_02=NULL;
         			if(agressor_03->victim_03==this) agressor_03->victim_03=NULL;
         			if(agressor_03->victim_04==this) agressor_03->victim_04=NULL;
         		}

         		if(agressor_04!=NULL)
         		{
         			agressor_04->add_victory(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_04->victim_01==this) agressor_04->victim_01=NULL;
         			if(agressor_04->victim_02==this) agressor_04->victim_02=NULL;
         			if(agressor_04->victim_03==this) agressor_04->victim_03=NULL;
         			if(agressor_04->victim_04==this) agressor_04->victim_04=NULL;
         		}

		       	agressor_01=NULL; //plus d'agresseurs
       			agressor_02=NULL;
      			agressor_03=NULL;
      			agressor_04=NULL;

		       	victim_01=NULL; //plus d'agresseurs
	   			victim_02=NULL;
       			victim_03=NULL;
       			victim_04=NULL;

	   			CheckUp();
	   			break;
	   		}
		case WON:
			{
				add_victory(1);
				war=OFF;
				ennemy_tech_level=0;
 
 		        if(agressor_01!=NULL)
        		{
			         agressor_01->add_defeat(1);
			         //suppression de l'engaged chez l'agresseur
			         if(agressor_01->victim_01==this) agressor_01->victim_01=NULL;
			         if(agressor_01->victim_02==this) agressor_01->victim_02=NULL;
			         if(agressor_01->victim_03==this) agressor_01->victim_03=NULL;
			         if(agressor_01->victim_04==this) agressor_01->victim_04=NULL;
		        }

		        if(agressor_02!=NULL)
         		{
         			agressor_02->add_defeat(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_02->victim_01==this) agressor_02->victim_01=NULL;
        			if(agressor_02->victim_02==this) agressor_02->victim_02=NULL;
         			if(agressor_02->victim_03==this) agressor_02->victim_03=NULL;
         			if(agressor_02->victim_04==this) agressor_02->victim_04=NULL;
         		}

		        if(agressor_03!=NULL)
         		{
         			agressor_03->add_defeat(1);
         			//suppression de l'engaged chez l'agresseur
         			if(agressor_03->victim_01==this) agressor_03->victim_01=NULL;
         			if(agressor_03->victim_02==this) agressor_03->victim_02=NULL;
         			if(agressor_03->victim_03==this) agressor_03->victim_03=NULL;
         			if(agressor_03->victim_04==this) agressor_03->victim_04=NULL;
         		}

         		if(agressor_04!=NULL)
         		{
         			agressor_04->add_defeat(1);
			        //suppression de l'engaged chez l'agresseur
         			if(agressor_04->victim_01==this) agressor_04->victim_01=NULL;
         			if(agressor_04->victim_02==this) agressor_04->victim_02=NULL;
         			if(agressor_04->victim_03==this) agressor_04->victim_03=NULL;
         			if(agressor_04->victim_04==this) agressor_04->victim_04=NULL;
         		}

				//plus d'agresseurs
		       	agressor_01=NULL;
       			agressor_02=NULL;
       			agressor_03=NULL;
       			agressor_04=NULL;
      
      			//si l'ennemi était trop faible ses troupes sont capturées 
      			//idem que si il avait gagné, sauf que le pays reste dans les mêmes mains ;-)
			    add_infantry(ennemy_infantry);
			    sub_ennemy_infantry(ennemy_infantry);
				add_tank(ennemy_tank);
				sub_ennemy_tank(ennemy_tank);
				add_marine(ennemy_marine);
				sub_ennemy_marine(ennemy_marine);
				add_airforce(ennemy_airforce);
				sub_ennemy_airforce(ennemy_airforce);
			    add_missile(ennemy_missile);
			    sub_ennemy_missile(ennemy_missile);   
				
				break;
			}
		case NOTHING:
			;
		}//fin switch battle result

		//status
		status=FREE; //par defaut
		if(group!=base_group)
			status=OCCUPIED;
		
		if(status==FREE)
			resistance=0;
	}//fin if war==on
	else //don si war ==OFF ou autre chose d'ailleurs
	{
		//si c'est la paix on peut plus avoir d'agresseur donc s'il y en a c'est par erreur
		agressor_01=NULL;
		agressor_02=NULL;
		agressor_03=NULL;
		agressor_04=NULL;
	} 

	//si il y a eu un probleme de synchro et que le pays est déjà conquis...
	//par le meme group, le moving to reste coincé donc.m
 	if(victim_01!=NULL && move_01==OFF && victim_01->war==OFF)		victim_01=NULL;
 	if(victim_02!=NULL && move_02==OFF && victim_02->war==OFF)		victim_02=NULL; 
	if(victim_03!=NULL && move_03==OFF && victim_03->war==OFF)		victim_03=NULL; 
 	if(victim_04!=NULL && move_04==OFF && victim_04->war==OFF) 		victim_04=NULL;

  	//Resistance en % en cas d'occupation
  	if(status==OCCUPIED)
    {
    	if(resistance < 3 )				resistance+=0.1; //progression rapide au debut
      	if(resistance < 7 )				resistance+=0.05; //moins apres et max a 25 %
      	if(agriculture < STARVE_LEVEL)	resistance+=0.05;

		//si famine la resistance augmente encore
		if(resistance > MAX_RESISTANCE) resistance= MAX_RESISTANCE; //limite
	 
		//plus le groupe de base a fait de propagande, plus la resistance est grande
		resistance *= 1+(_politic[_group[base_group]->politic]->propaganda/100);
      
		//si plus de famine
		if(agriculture > STARVE_LEVEL && resistance > MAX_RESISTANCE/2)
			resistance-= 0.01;

		//une attaque tous les 50 _jours
		//a moins qu'on soit en guerre
      	if(resist_counter++==50 && war==OFF)
        {
        	//faut plus d'homme pour un pays peuplé
        	double res_inf=((population/10000)*resistance);
          	
          	//la resistance n'a que de l'infanterie
          	sub_population((long)(res_inf));
       		attacking(this, long(res_inf),0,0,0,0,0);
          	resist_counter=0;
		}
	}//fin resistance


	///POPULATION STARVING, si agriculture trop bas...
	//faire la division en double
	double starve_tmp=(population*STARVE_AMOUNT);

	//histoire que les petits pays souffrent aussi   
	if(starve_tmp < 2 )
		starve_tmp=2;

	if(agriculture <= STARVE_LEVEL)
    {
    	sub_population((int)(starve_tmp));
      	add_civ_killed((int)(starve_tmp));
    }

	//calcul de la puissance militaire du pays
 	//calc puissance du groupe 
 	PowerCalc();
	if(nb_in_pal==_jour->country_first)
		GroupPower();

	//une fois pour tous les pays,donc avec le premier
	if(_group[this->group]->player==COMPUTER)
		ComputerPlay();
}//fin day_passed

void Country::month_passed() //a faire chaque mois
{
	CheckUp();

	//LE TEMPS Qu'IL FAIT... chiffre random entre 1 et 5
	real_weather     = int(rand()/((RAND_MAX)/5)); //div par 5 --> max == 4
	real_temperature = int(rand()/((RAND_MAX)/5));
	real_weather+=1;  //pour jamais etre a zero
	real_temperature+=1;

	///POPULATION BIRTH
	double b_rate;
	unsigned long pop;
	b_rate=(birth_rate *(moral/100)); //reproduction max requiert moral 100%
	pop=long(b_rate*population); //convertit en int
	pop/=100;  //parce-que pour-cent
	pop/=12;  //parce-que taux par annee et addition par mois
	add_population(pop); //ajout de la difference

	//INDUSTRY PRODUCTS ==MONEY ==> PNB
	double monthly_cash=0;   //revenu mensuel
	int xxx= (population/1000); //faut diviser une fois pas mille plus idem en bas
	monthly_cash=(xxx)*(pnb/12);  //parce-que par 1 million ca fait merder les pays pauvres
	monthly_cash*=(industry/100);;  //si l'industrie baisse le pnb aussi
	monthly_cash*=(tax/100); //tax prelevee sur le total
	monthly_cash/=1000;  //deuxieme div. par mill pour faire le mio.
	money+=(long long int)monthly_cash;

	//agriculture en fonction du climat
	//plus on s'est goure sur les previsions (random) plus on est taxe..
	float difference_weather=0;
	float difference_temperature=0;
	float total_difference=0;
	
	if(expected_temperature < real_temperature)   difference_temperature=(real_temperature-expected_temperature);
	if(expected_temperature >= real_temperature)  difference_temperature=(expected_temperature-real_temperature);
	if(expected_weather < real_weather)           difference_weather=(real_weather-expected_weather);
	if(expected_weather >= real_weather)          difference_weather=(expected_weather-real_weather);

 	total_difference=(difference_weather+difference_temperature)/2; //moyenne
 	total_difference*=WEATHER_INFLUENCE;
 	sub_agriculture(total_difference);

   	//MORAL
  	moral=(((industry+agriculture)/2)-(defeat*3)+(victory*3)); //agriculture+industry 100% - 0 defeats = perfect
  	
  	//en gros si pas assez bouffe et trop defaites, moral down
  	if(status==OCCUPIED)
  		moral-=10;
  
  	if((population/money) > 1)
  		add_moral(10);

	//s'il y a 1 $ par habitant de stock, add_moral;
	//pour chaque pourcent de taxe, 2 points de moral en moins
  	sub_moral(2*tax);

	//sinon division par zero et crash!!!
	if(civ_killed!=0)    
    {
    	double percent_dead;
    	
    	//nb morts pa population
        percent_dead = (population/civ_killed); 

        //div par. 2 parce-que et pis voila!
        percent_dead = (100/percent_dead)/2; 
        sub_moral(percent_dead);
    }

	if(status==OCCUPIED)
		sub_moral(10);

	//après une bataille ou une révolution Revolution_euphory augmente pour donner un délai
	//plus la répression est grande plus la révolution arrive facilement
 	if(war==OFF && moral < (30* (1+((_politic[_group[group]->politic]->repression)/4))) && revolution_euphory ==0)
 		Revolution();
}//fin month_passed()

/*--------------------------------------------------------------------------*/

void Country::set_army()
{
	//cette routine genere une armee par defaut
	//faut ensuite appliquer les valeurs par défauts à infantry, tank etc.
	double xx_whealth;
	xx_whealth=(pnb/500);
	xx_whealth/=4;
	xx_whealth+=0.45; //pour avoir un minimum

	//l'infanterie coute pas cher
	inf_def= long((population/250)*xx_whealth);
	
	//les pays tiers-monde ont plus d'infanterie
	if(tech_level<=55)
		inf_def=long(inf_def*1.25); 
	
	//les pays riches en ont moins
	if(tech_level>=77)
		inf_def=long(inf_def/1.35);
	
	//les tres riches encore moins  (USA)
	if(tech_level>=85)
		inf_def=long(inf_def/1.5);

	tnk_def = int((population/(1000*300)*xx_whealth));
	mar_def = int((population/(1000*4500)*(xx_whealth*2)));
	air_def = int((population/(1000*1500)*(xx_whealth*2)));
	mis_def = int((population/(1000*900)*(xx_whealth*2))) ;
	dca_def = int(population/(1000*800*(xx_whealth*2))) ;
	nuke_def=0; 

}//fin Country::set_army

void Country::default_army()
{
	infantry=inf_def;
	tank=tnk_def;
	marine=mar_def;
	airforce=air_def;
	missile=mis_def;
	dca=dca_def;
	nuke=nuke_def;
}

//Nouvelles fonctions pouir nouvelle méthode...
void Country::SendTroops(Country *victim, uint8 attack_id) 
{}

void Country::IsAttacking(Country *victim,uint8 attack_id)
{}

void Country::IsAttacked(Country *agressor,uint8 attack_id)
{}

void Country::AskRetreat(Country *home_country)
{}
   
bool Country::BuyArmy(uint8 which_type, uint64 amount)
{ 
	double price = amount * _weapon[which_type]->cost;
	
	if(price > money)
		return false;
	else
	{
		sub_money(price);
		AddArmy(which_type, false, amount);
		
		//false = pas pour ennemy mais pour soi
        sub_population(amount *  _weapon[which_type]->men_required);  
		return true;
	}
}

bool Country::buy(long inf_xx,int32 tank_xx,int32 mar_xx,int32 air_xx,int32 mis_xx,int32 nuke_xx,int32 dca_xx)
{
	double price;

	price = (inf_xx*COST_INFANTRY + tank_xx*COST_TANK +	mar_xx*COST_MARINE + air_xx*COST_AIRFORCE +	mis_xx*COST_MISSILE + nuke_xx*COST_NUKE + dca_xx*COST_DCA);

	if(price>money)
		return false;
	else
	{
    	sub_money(price);          
        add_infantry(inf_xx);
        sub_population(inf_xx*MEN_PER_INFANTRY);          
        add_tank(tank_xx);
        sub_population(tank_xx*MEN_PER_TANK);          
        add_marine(mar_xx);
        sub_population(mar_xx*MEN_PER_MARINE);          
        add_airforce(air_xx);
        sub_population(air_xx*MEN_PER_AIRFORCE);  
        add_missile(mis_xx);
        sub_population(mis_xx*MEN_PER_MISSILE);          
        add_nuke(nuke_xx);
        sub_population(nuke_xx*MEN_PER_NUKE);
		add_dca(dca_xx);
        sub_population(dca_xx*MEN_PER_DCA);          
	}           
           
	return true;
}//fin buy


unsigned char Country::battle()
{
  	fight_infantry 			= NOTHING;
  	fight_marine   			= NOTHING;
  	fight_airforce 			= NOTHING;
  	fight_missile  			= NOTHING;
  	fight_dca      			= NOTHING;
  	fight_ennemy_infantry 	= NOTHING;
  	fight_ennemy_marine   	= NOTHING;
  	fight_ennemy_airforce 	= NOTHING;
  	fight_ennemy_missile  	= NOTHING;
  	fight_ennemy_nuke     	= NOTHING;
	fight_tank   			= NOTHING;
	fight_ennemy_tank     	= NOTHING;
 
	/*****************************************************************/
	/*       RESULT OF BATTLE  (LOCAL ARMY /ENNEMY ARMY ELEMENTS     */
	/*****************************************************************/

	// DEFAITE Elements de l'armee locale
	//les nukes ne s'utilisent pas pour la defense
  	if(infantry<=1)	 	{fight_infantry = LOST;}
  	if(tank<=1)		 	{fight_tank     = LOST;}
  	if(marine<=1) 		{fight_marine   = LOST;}
  	if(airforce<=1)	 	{fight_airforce = LOST;}
  	if(missile<=1) 		{fight_missile  = LOST;}
  	if(dca<=1) 			{fight_dca      = LOST;}

	// DEFAITE ENNEMIE
  	if(ennemy_infantry<=1) 	{fight_ennemy_infantry = LOST;}
  	if(ennemy_tank<=1) 		{fight_ennemy_tank   = LOST;}
  	if(ennemy_marine<=1) 	{fight_ennemy_marine   = LOST;}
  	if(ennemy_airforce<=1) 	{fight_ennemy_airforce = LOST;}
  	if(ennemy_missile<=1) 	{fight_ennemy_missile  = LOST;}
  	if(ennemy_nuke<=1) 		{fight_ennemy_nuke     = LOST;}

	/**************************************************************/
	/*                    FINAL RESULT          */
	/**************************************************************/

	//SI PERDU PARTOUT add_defeat
    if((fight_infantry == LOST) && (fight_marine == LOST) && (fight_tank == LOST) && (fight_airforce == LOST) && (fight_missile == LOST) && (fight_dca == LOST))
    	return LOST;

	//SI ennemy a PERDU PARTOUT add_victory
    if((fight_ennemy_infantry == LOST) && (fight_ennemy_tank == LOST) && (fight_ennemy_marine == LOST) && (fight_ennemy_airforce == LOST) && (fight_ennemy_nuke == LOST) && (fight_ennemy_missile == LOST))
		return WON;

	//Si c'est pas fini la on fait la battle
	//no dca
	//par defaut battle turn commence a zero,
 	//12 tours au total pour que tous les multiples (de 2,3 et 4) se rejoignent
	if(battle_turn++==12)
		battle_turn=1;

	//NIVEAU TECHNOLOGIQUE entre 1.00 et 2
	double tech=1+(tech_level/200);                 //200% aulieu de 100 pour limiter un peu
	double ennemy_tech=1+(ennemy_tech_level/200);   //l'effet du tech_level

	//PUISSANCE DES ARMEES
	double ratio,e_ratio;
	long long strength   = ((long)((infantry*STRENGTH_INFANTRY)+(tank*STRENGTH_TANK)+(marine*STRENGTH_MARINE)+(airforce*STRENGTH_AIRFORCE)+((missile*STRENGTH_MISSILE)+(dca*STRENGTH_DCA))/1.5)); //pas divise par deux  
	long long e_strength = ((long)((ennemy_infantry*STRENGTH_INFANTRY) +(ennemy_tank*STRENGTH_TANK)+ (ennemy_marine*STRENGTH_MARINE)+(ennemy_airforce*STRENGTH_AIRFORCE)+ (ennemy_missile*STRENGTH_MISSILE)));


	if(e_strength>(strength*5)) 
	{
		char str[255],str2[255];
		sprintf(str,_name.String());
		sprintf(str2," surrenders!");
		strcat(str,str2);
		_jour->add_history(str); 
	
		return LOST;
	}

	//seule la resistance peut se battre en large inferiorite et mourir jusqu'au dernier
	//si l'autre s'est fait couilloné
	if(agressor_01!=this && strength>(e_strength*5))
	{
		char str[255],str2[255];
		sprintf(str,agressor_01->Name());
		sprintf(str2," too weak to fight ");
		strcat(str,str2);
		sprintf(str2,_name.String());
		strcat(str,str2);
		sprintf(str2,". Troops captured");
		strcat(str,str2);
		_jour->add_history(str); 

		return WON;
	}

	//pas de nuke la dedans...
	//Plus ton ratio est haut plus tu te fais buter       
	//       2000          1000
	//pour eviter division by zero
  	strength+=1; 
  	ratio=e_strength/strength;
	e_ratio = 1/ratio;

	//plus ce chiffre est haut, plus une supériorité large rend la bataille rapide
	if(e_ratio>3)	e_ratio=3; 
	if(ratio>3)		ratio=3;
	if(ratio<0)		ratio=0.5;//avoid div zero

	//si le pays appartient à un player humain le level entre en jeu
	//plus le level est haut plus on se fait killer
	//l'ennnemy en prend plus sur la tronche
	if (_group[this->group]->player!=COMPUTER) 
		e_ratio+=_jour->game_level;

  	e_ratio = e_ratio * (ennemy_tech); //tech div par deux donc
  	ratio = ratio * (tech);            //si tech=100%, kill_ratio x1.5 par 2
  	ratio+=0.2; //pour eviter division by zero
  	e_ratio+=0.2; //pour eviter division by zero

   	double k_inf,k_tnk, k_mar, k_air, k_mis, k_dca, k_nuke;
  	double k_e_inf, k_e_tnk, k_e_mar, k_e_air, k_e_mis, k_e_nuke;

   	k_inf= (KILL_INFANTRY*ratio);
   	k_tnk= (KILL_TANK*ratio);
   	k_mar= (KILL_MARINE*ratio);
  	k_air= (KILL_AIRFORCE*ratio);
   	k_mis= (KILL_MISSILE*ratio);
   	k_dca= (KILL_DCA*ratio);
   	k_nuke= k_mis/2; //au sol on en touche plus

   	k_e_inf= (KILL_INFANTRY*e_ratio);
   	k_e_tnk= (KILL_TANK*e_ratio);
   	k_e_mar= (KILL_MARINE*e_ratio);
   	k_e_air= (KILL_AIRFORCE*e_ratio);
   	k_e_mis= (KILL_MISSILE*e_ratio);
   	//pas de k_e_dca
   	k_e_nuke= k_e_mis/4;            //en air on en atteint moins


	//ATTAQUE INTERLACEE, une fois ennemy, une fois defenseurs
	//TOUT ce qui attaque les missiles attaque pour moitie aussi les nukes!
	//ENNEMY no attack by dca for ennemy
	//DEFENSE dca to airforce, missile
	if(fight_dca!=LOST)
    {
    	//turn 1,3,5,7,9,11
    	if((battle_turn==1) || (battle_turn==3) || (battle_turn==5) || (battle_turn==7) || (battle_turn==9) || (battle_turn==11) )
			sub_ennemy_airforce(int(k_e_air));
		
		//turn 2,4,6,8,10,12
       	if((battle_turn==2) || (battle_turn==4) || (battle_turn==6) || (battle_turn==8) || (battle_turn==10) || (battle_turn==12) )
       	{
       		sub_ennemy_missile(int(k_e_mis));
       		sub_ennemy_nuke (int(k_e_nuke));
       	}
     }

	// ENNEMY airforce to air/ !dca! /marine/infantry
	if(fight_ennemy_airforce!=LOST)
	{
		if((battle_turn==1) || (battle_turn==7))  	sub_airforce(int(k_air));
       	if((battle_turn==2) || (battle_turn==8))  	sub_dca(int(k_dca));
       	if((battle_turn==3) || (battle_turn==9))  { sub_missile(int(k_mis)); sub_nuke(int(k_nuke));}
       	if((battle_turn==4) || (battle_turn==10)) 	sub_infantry(int(k_inf)); //oui 2x l'airforce!
       	if((battle_turn==5) || (battle_turn==11)) 	sub_marine(int(k_mar));
       	if((battle_turn==6) || (battle_turn==12)) 	sub_tank(int(k_tnk));
    }

  	//DEFENSE airforce to air/(dca)/marine /infantry
  	if(fight_airforce!=LOST)
	{
		if((battle_turn==1) || (battle_turn==7))  	sub_ennemy_airforce(int(k_e_air));
       	if((battle_turn==2) || (battle_turn==8))  { sub_ennemy_missile(int(k_e_mis));sub_ennemy_nuke(int(k_e_nuke));}
       	if((battle_turn==3) || (battle_turn==9))  	sub_ennemy_infantry(int(k_e_inf));
       	if((battle_turn==4) || (battle_turn==10)) 	sub_ennemy_airforce(int(k_e_air)); //oui 2x l'airforce!
       	if((battle_turn==5) || (battle_turn==11)) 	sub_ennemy_marine(int(k_e_mar)); //b-coz no dca
       	if((battle_turn==6) || (battle_turn==12)) 	sub_ennemy_tank(int(k_e_tnk));
	} //attack to dca only for ennemy

  	//ENNEMY infantry to infantry / !dca!
  	if(fight_ennemy_infantry!=LOST)
  	{
  		if((battle_turn== 1) || (battle_turn==4) || (battle_turn==7) || (battle_turn==10) ) sub_dca(int(k_dca));
      	if((battle_turn== 3) || (battle_turn==6) || (battle_turn==9) || (battle_turn==12) ) sub_infantry(int(k_inf));
      	if((battle_turn== 2) || (battle_turn==5) || (battle_turn==8) || (battle_turn==11) ) sub_tank(int(k_tnk));
    }
       
	//DEFENSE infantry to infantry / (dca)
  	if(fight_infantry!=LOST) //pas la peine de massacrer si bat. perdue!
    {
		//turn 1,3,5,7,9,11
       	if((battle_turn==1) || (battle_turn==3) || (battle_turn==5) || (battle_turn==7) || (battle_turn==9) || (battle_turn==11) )
       		sub_ennemy_infantry(int(k_e_inf));
       	
       	//turn 2,4,6,8,10,12
       	if((battle_turn==2) || (battle_turn==4) || (battle_turn==6) || (battle_turn==8) || (battle_turn==10) || (battle_turn==12) )
       		sub_ennemy_tank(int(k_e_tnk));
    }
  	//attack to dca only for ennemy

  	//ENNEMY marine to marine/air
  	if (fight_ennemy_marine!=LOST)
    {
    	//turn 1,3,5,7,9,11
       	if((battle_turn==1) || (battle_turn==3) || (battle_turn==5) || (battle_turn==7) || (battle_turn==9) || (battle_turn==11) )
       		sub_marine(int(k_mar));
       	
       	//turn 2,4,6,8,10,12
       	if((battle_turn==2) || (battle_turn==4) || (battle_turn==6) || (battle_turn==8) || (battle_turn==10) || (battle_turn==12) )
       		sub_airforce(int(k_air));
    }
       
  	//DEFENSE marine to marine/air
	if(fight_marine!=LOST)
	{
       	//turn 1,3,5,7,9,11
       	if((battle_turn==1) || (battle_turn==3) || (battle_turn==5) || (battle_turn==7) || (battle_turn==9) || (battle_turn==11) )
       		sub_ennemy_marine(int(k_e_mar)) ;
       	
       	//turn 2,4,6,8,10,12
       	if((battle_turn==2) || (battle_turn==4) || (battle_turn==6) || (battle_turn==8) || (battle_turn==10) || (battle_turn==12) )
       		sub_ennemy_airforce(int(k_e_air));
    }

  	//ENNEMY  missile to marine, infantry , !dca!
  	if(fight_ennemy_missile!=LOST)
    {
    	if((battle_turn==2) || (battle_turn==5) || (battle_turn==8) || (battle_turn==11)) 	sub_tank(int(k_tnk*MISSILE_POWER));
       	if((battle_turn==1) || (battle_turn==4) || (battle_turn==7) || (battle_turn==10)) 	sub_marine(int(k_mar*MISSILE_POWER));
       	if((battle_turn==3) || (battle_turn==6) || (battle_turn==9) || (battle_turn==12)) 	sub_dca(int(k_dca*MISSILE_POWER));
	   	
	   	sub_ennemy_missile(MISSILE_PER_DAY);
    }

  	//DEFENSE missile to marine, infantry (dca)
  	if (fight_missile!=LOST)
  	{
    	//turn 1,3,5,7,9,11
       	if((battle_turn==1) || (battle_turn==3) || (battle_turn==5) || (battle_turn==7) || (battle_turn==9) || (battle_turn==11) )
       		sub_ennemy_tank(int(k_e_tnk*MISSILE_POWER));
       	
       	//turn 2,4,6,8,10,12
       	if((battle_turn==2) || (battle_turn==4) || (battle_turn==6) || (battle_turn==8) || (battle_turn==10) || (battle_turn==12) )
       		sub_ennemy_marine(int(k_e_mar*MISSILE_POWER));
    	
    	sub_missile(MISSILE_PER_DAY);         //les missiles ca s'utilise qu'une fois
     } //attack to dca only for ennemy


	  //DEFENSE tank to tank, airforce, infantry
  	if(fight_tank!=LOST)
    {
    	if((battle_turn==2) || (battle_turn==5) || (battle_turn==8) || (battle_turn==11)) 	sub_ennemy_tank(int(k_e_tnk));
       	if((battle_turn==1) || (battle_turn==4) || (battle_turn==7) || (battle_turn==10)) 	sub_ennemy_airforce(int(k_e_air));
       	if((battle_turn==3) || (battle_turn==6) || (battle_turn==9) || (battle_turn==12)) 	sub_ennemy_infantry(int(k_e_inf));
    }


	//Ennemy tank to tank, airforce, infantry
	if(fight_ennemy_tank!=LOST)
    {
    	if((battle_turn==2) || (battle_turn==5) || (battle_turn==8) || (battle_turn==11)) 	sub_tank(int(k_tnk));
       	if((battle_turn==1) || (battle_turn==4) || (battle_turn==7) || (battle_turn==10)) 	sub_airforce(int(k_air));
       	if((battle_turn==3) || (battle_turn==6) || (battle_turn==9) || (battle_turn==12)) 	sub_infantry(int(k_inf));
	}

  	// ATTAQUE DE CIVILS par missiles +airforce
  	sub_industry(double(KILL_INDUSTRY * ennemy_tech * ratio ));
  	sub_agriculture(double(KILL_AGRICULTURE * ennemy_tech * ratio ));
  	sub_population(int(KILL_POPULATION * ennemy_tech * ratio ));
  	add_civ_killed(int(KILL_POPULATION * ennemy_tech * ratio ));

  	//S'il reste des nukes apres le travail de la dca... AIE AIE AIE!
  	if(ennemy_nuke!=0)
    {
    	int temp_nuke;
  	  	
  	  	if(ennemy_nuke > NUKE_PER_DAY)
  	  		temp_nuke=NUKE_PER_DAY;
  	  	else
  	  		temp_nuke=ennemy_nuke;

     	sub_population(int(KILL_POPULATION_NUKE * temp_nuke));
     	add_civ_killed(int(KILL_POPULATION_NUKE * temp_nuke));
     	sub_industry(int(KILL_INDUSTRY_NUKE * temp_nuke));
     	sub_ennemy_nuke(temp_nuke);     //les bombes A s'utilisent qu'une fois
	}

    return NOTHING; //rien... ni gagne ni perdu

}//fin battle

void Country::Revolution()
{
	revolution_happened=OFF;
	defeat=0; //pour que le moral remonte
	victory=0;	//parce-que bon... faut pas trop qu'il monte aussi ;-)
	civ_killed=0; //on oublie tout
	unsigned long new_group;
 
   	//LE TEMPS Qu'IL FAIT... chiffre random entre 1 et 5
   	new_group = (unsigned long)(rand()/((RAND_MAX)/_jour->group_last+1)); //div par nb group --> max == LASTGROUP
   
   	if(new_group<_jour->group_first)
   		new_group=_jour->group_first;
   	if(new_group>_jour->group_last)
   		new_group=_jour->group_last;
   
	base_group=new_group; //sinon le pays serait occupé
	group=new_group; 
	
	//un peu de répit avant de risquer nouvelle émeute populaire
	revolution_euphory=REVOLUTION_EUPHORY;

	//on reactive le groupe si il ressuscite du vide..
	_group[this->group]->active=ON;
	_politic[_group[this->group]->politic]->active=ON;//on reactive l'idéologie aussi
	
	char str[255],str2[255];
	sprintf(str2,_name.String());
	sprintf(str,"Revolution in ");
	strcat(str,str2); //grouper les deux
	sprintf(str2,"! New government installed!");
	strcat(str,str2); //grouper les deux

	_jour->add_history(str); //en pointer ça merde faut envoyer un char xxx[]
	tax=DEFAULT_ARMY_TAX; //des fois que ça ait causé une révolution...

	//la guerre s'arrete et tout le monde rentre à la maison
	//si war==on et revolution
	if(war==ON)
	{
		war=OFF;	
	 	unsigned char how_many_agressors=0; //si guerre c'est le minimum
	 	
	 	if(agressor_01!=NULL) 	how_many_agressors++;
	 	if(agressor_02!=NULL) 	how_many_agressors++;
	 	if(agressor_03!=NULL) 	how_many_agressors++;
	 	if(agressor_04!=NULL) 	how_many_agressors++;
	 	
	  	//les troupes divisées retournent chez l'agresseur
	    if (agressor_01!=NULL) 
	  	{	
	  		agressor_01->infantry+=(ennemy_infantry/how_many_agressors); 
	 		agressor_01->tank+=(ennemy_tank/how_many_agressors); 
	 		agressor_01->marine+=(ennemy_marine/how_many_agressors);
	 		agressor_01->airforce+=(ennemy_airforce/how_many_agressors); 
	  		agressor_01->missile+=(ennemy_missile/how_many_agressors);
	  		agressor_01->nuke+=(ennemy_nuke/how_many_agressors);
	  	}
	  
	  	if(agressor_02!=NULL) 
	  	{
	  		agressor_02->infantry+=(ennemy_infantry/how_many_agressors); 
	 		agressor_02->tank+=(ennemy_tank/how_many_agressors); 
	 		agressor_02->marine+=(ennemy_marine/how_many_agressors);
	 		agressor_02->airforce+=(ennemy_airforce/how_many_agressors); 
	  		agressor_02->missile+=(ennemy_missile/how_many_agressors);
	  		agressor_02->nuke+=(ennemy_nuke/how_many_agressors);
	  	}
	  
	  	if(agressor_03!=NULL) 
	  	{	
	  		agressor_03->infantry+=(ennemy_infantry/how_many_agressors); 
	 		agressor_03->tank+=(ennemy_tank/how_many_agressors); 
	 		agressor_03->marine+=(ennemy_marine/how_many_agressors);
	 		agressor_03->airforce+=(ennemy_airforce/how_many_agressors); 
	  		agressor_03->missile+=(ennemy_missile/how_many_agressors);
	  		agressor_03->nuke+=(ennemy_nuke/how_many_agressors);
	 	}
	 
	  	if(agressor_04!=NULL) 
	  	{	
	  		agressor_04->infantry+=(ennemy_infantry/how_many_agressors); 
	 		agressor_04->tank+=(ennemy_tank/how_many_agressors); 
	 		agressor_04->marine+=(ennemy_marine/how_many_agressors);
	 		agressor_04->airforce+=(ennemy_airforce/how_many_agressors); 
	  		agressor_04->missile+=(ennemy_missile/how_many_agressors);
	  		agressor_04->nuke+=(ennemy_nuke/how_many_agressors);
	  	}
	  
	  	ennemy_infantry=0;
	  	ennemy_tank=0;
	  	ennemy_marine=0;
	  	ennemy_airforce=0;
	  	ennemy_missile=0;
	  	ennemy_nuke=0;
	}//fin revolution&& war==ON

	//update le pays
	BMessage msg(MULTIPLY_RECT);
	msg.AddRect("zone",limit);				
	_jour->mainWin->PostMessage(&msg);
}

void Country::ComputerPlay()
{
	Country *my_ennemy=NULL;
	Country *tmp_ennemy=NULL;
	long inf_xx;
	int tank_xx,mar_xx,air_xx,mis_xx,nuke_xx; //ARMEE ATTAQUE
	unsigned char do_attack;
	unsigned char defense_purchased;
	defense_purchased=ON;
	do_attack=ON;
	unsigned int dist,temp_dist;
	dist=temp_dist=1000000;//on cherche la plus courte donc de base c'est à fond

	/*************************************/
	/*0. générer armée défense au besoin */
	/*************************************/
	if(infantry < inf_def*0.75)
		defense_purchased=OFF;

	/***********************/
	/* Si attaque possible */
	/***********************/
	if( victim_01==NULL || victim_02==NULL || victim_03==NULL || victim_04==NULL) //si une attaque libre
	{
		//1. Trouver l'ennemi
		unsigned char temp_ctry = _jour->country_first;
        
        while (temp_ctry != _jour->country_last+1)
        {
        	//si déjà en guerre pas d'attaque normalement 
          	if(_country[temp_ctry]->war==ON)
          	{
          		do_attack=OFF;
          		
          		//sauf si déjà en guerre avec nous (MEME groupe)
         		if(_country[temp_ctry]->agressor_01->group==this->group)
         			do_attack=ON;
          	}//fin if war==on
          
         	unsigned char xxx;
         	unsigned char not_dead;
          	
         	if(do_attack==ON)
         	{
         		unsigned char pol_ennemy = _group[_country[temp_ctry]->group]->politic;
		 		unsigned char pol = _group[group]->politic;
         
         		//si la politique du groupe du pays est hostile 
         		//à la politique du groupe de l'assaillant on l'assigne
 		 		switch (_politic[pol]->relation[pol_ennemy])
 		 		{
 		 		case ENNEMY:
 		 			tmp_ennemy=_country[temp_ctry];
 		 			break;
	 		 	case NEUTRAL:
    		       	{
    		       		xxx=_jour->politic_first;
            			not_dead=0;
           				while(xxx!=_jour->politic_last+1)
           				{
						    //test chaque ennemi réel, viscéral
           					if(_politic[pol]->relation[xxx]==ENNEMY && _politic[xxx]->active==ON)
           		   					not_dead++;
           		   			xxx++;
  				 		}
						//si ils sont tous morts on attaque les neutres
						if(not_dead==0)
							tmp_ennemy=_country[temp_ctry];
 		 			}
 		 			break;
				}//fin switch
    			     
       	  		if(tmp_ennemy!=NULL)
         		{
           			//si c'est le premier tour on l'assigne de toute façons
           	  		if(my_ennemy==NULL)
           	  			my_ennemy=tmp_ennemy;
           	 	 	
           	 		//ou sinon on cherche le plus faible... et plus près
	           	 	if((tmp_ennemy->infantry < my_ennemy->infantry) && FindDistance(this,tmp_ennemy)< FindDistance(this,my_ennemy))
						my_ennemy=tmp_ennemy;				           	 	    	          		
				}//fin tmp_ennemy!=NULL     	
			}//fin if pas déjà en guere
        	temp_ctry++;
		}//fin while recherche ennemy

		if(my_ennemy!=NULL) //si on a trouvé un ennemi (c'est probable vu l'état du monde ;-)
		{
			//2. Préparer l'attaque (achats en fonction)		
			//faudrait avoir le double de l'ennemi pour une victoire facile et rapide
			inf_xx  = (my_ennemy->infantry*2)+10000; //+10000 car si le pays a rien 2xzero == zero!!! 
			tank_xx = (my_ennemy->tank*2)+50; 
			mar_xx  = (my_ennemy->marine*2)+2; 
			air_xx  = (my_ennemy->airforce*2)+10; 
			mis_xx  = (my_ennemy->missile*2)+0;
			nuke_xx = (my_ennemy->nuke*2)+0; 
	   	
	   		if(defense_purchased==OFF)
			{
				if(buy(inf_xx+inf_def,tank_xx+tnk_def,mar_xx+mar_def,air_xx+air_def,mis_xx+mis_def,nuke_xx+nuke_def,0+dca_def)==true)
					send_troops(my_ennemy,inf_xx,tank_xx,mar_xx,air_xx,mis_xx,nuke_xx);		
				else //si on peut pas attaquer +acheter defense, on achete juste defense et on envoie la moitié au pays le plus fort du groupe
				{
					if(buy(inf_def,tnk_def,mar_def,air_def,mis_def,nuke_def,dca_def)==true)
					{
					//trouver le plus faible
						uint32 power_temp=0;
						unsigned char the_strongest = _jour->country_first;
						unsigned char ct =_jour->country_first;
					
						while (ct!=_jour->country_last+1)
						{
							//a ceux du même groupe
							if (_country[ct]->group==group && _country[ct]->power > power_temp)
							{
								power_temp = _country[ct]->power;
								the_strongest = ct;	
							}
							ct++;
						}	
						send_troops(_country[the_strongest],inf_def/2, tnk_def/2, mar_def/2, air_def/2,mis_def/2, nuke_def/2);
					}
	 			} 
			}
			else //si pas besoin acheter plus défense (defense_purchased==ON)
			{
				//si pas trop armée en stock on achète
				if(infantry/2 < inf_xx+inf_def)
				{
					if (buy(inf_xx,tank_xx,mar_xx,air_xx,mis_xx,nuke_xx,0)==true)
						send_troops(my_ennemy,inf_xx,tank_xx,mar_xx,air_xx,mis_xx,nuke_xx);
				}
				else
					send_troops(my_ennemy,inf_xx,tank_xx,mar_xx,air_xx,mis_xx,nuke_xx);
			}
		}//fin ennemy pas null
	} //fin ComputerPlay
}

int32 Country::FindDistance(Country *ct1,Country *ct2)
{
	if(ct1!=NULL && ct2!=NULL)
	{
   		int16 delta,delta_x,delta_y;
   		delta = delta_x = delta_y = 0;
   		float pos_1_x=ct1->center_x;
   		float pos_2_x=ct2->center_x;
   		float pos_1_y=ct1->center_y;
   		float pos_2_y=ct2->center_y;
    
   		//delta X
  		if(pos_1_x == pos_2_x)  delta_x = 0;
   		if(pos_1_x > pos_2_x)  	delta_x = (int16)(pos_1_x-pos_2_x);
   		if(pos_1_x < pos_2_x)  	delta_x = (int16)(pos_2_x-pos_1_x);

   		//delta Y
   		if(pos_1_y == pos_2_y)  delta_y = 0;
   		if(pos_1_y > pos_2_y)  	delta_y = (int16)(pos_1_y-pos_2_y);
   		if(pos_1_y < pos_2_y)  	delta_y = (int16)(pos_2_y-pos_1_y);

   		//on trouve l'hypothenuse, ah pythagore, toute ma jeunesse
   		delta=(int16)(float(delta_x*delta_x)+(delta_y*delta_y)); //au carre
   		delta=(int16)(float(sqrt(delta))); //racine

   		delta*=KM_PER_PIXEL;  //Pour convertir les pixels de la pic en km

		return delta;
	}
	else
		return 100;
}


void Country::PowerCalc() //calcul de la puissance militaire du pays (power)
{
	//power du pays
	#define MOINS 1000
	power=(infantry*STRENGTH_INFANTRY)/MOINS + (tank*STRENGTH_TANK)/MOINS + (marine*STRENGTH_MARINE)/MOINS + (airforce*STRENGTH_AIRFORCE)/MOINS + (missile*STRENGTH_MISSILE)/MOINS + (dca*STRENGTH_DCA)/MOINS;
	power++; //evite divide by zero
}

void Country::GroupPower()
{
	//d'abord on met le power du groupe à zero pour tous
	unsigned char temp_grp = _jour->group_first;
    
    while (temp_grp != _jour->group_last+1)
    {
 		_group[temp_grp]->grp_power=0;
		temp_grp++;    
    }

	//on ajoute aux groupe_power le pouvoir de tous les pays lui appartenant
	unsigned char temp_ctry = _jour->country_first;
    
    while (temp_ctry != _jour->country_last+1)
    {
    	_group[_country[temp_ctry]->group]->grp_power += _country[temp_ctry]->power;
		temp_ctry++;    
    }

	//total de tous les groupes
	uint64 total=0;
    temp_grp = _jour->group_first;
    
    while (temp_grp != _jour->group_last+1)
    {
 		total+=_group[temp_grp]->grp_power;
		temp_grp++;    
    }

	//pourcentage du total pour chaque groupe
    temp_grp = _jour->group_first;
	
	while (temp_grp != _jour->group_last+1)
    {
    	double ttt = double(total)/double(_group[temp_grp]->grp_power);
        float x= float(100)/float(ttt);
	    _group[temp_grp]->power_percent=x;
        temp_grp++;    
    }
}

void Country::CheckUp() ///effectué après chaque victoire dans une bataille (conquête)
{
	unsigned char exists=0;	
	unsigned char the_ctry = _jour->country_first; //pour pointer dans list pays
    
    while (the_ctry != _jour->country_last+1) 
	{
    	//check group exists
	    if(_country[the_ctry]->group==base_group)
	    	exists++; 

		the_ctry++;
	}

	if(exists==0) //si groupe anihilated
    {
    	_group[base_group]->active=OFF; //le groupe est MORT A PARTIR D'ICI

		char str[255];
		sprintf(str,_group[base_group]->Name());
		strcat(str," ANIHILATED!!! Members joining their occupants.");
		_jour->add_history(str); 
	
	 	unsigned char pol=_group[base_group]->politic;
	 	unsigned char pol_exists=0;	
 	 	unsigned char temp_grp = _jour->group_first;
        
        while(temp_grp != _jour->group_last+1)
        {
	        //dans chaque groupe vivant
			//si politique existe ici, l'idéologie subsiste
			if(_group[temp_grp]->active==ON && _group[temp_grp]->politic==pol) 
				pol_exists++; 
 			temp_grp++;    
		}
			
	 	if(pol_exists==0) //si politique anihilated
     	{
	 		char str[255],str2[255];
			sprintf(str,_politic[_group[base_group]->politic]->Name());
			sprintf(str2,"'s ideology destroyed with its last supporter.");
			strcat(str,str2);
			_jour->add_history(str); 
			_politic[_group[base_group]->politic]->active=OFF;
		}
	
		//tous les membres du group destroyé rejoignent leur occupant actuel
		unsigned char old_group=base_group;
 		the_ctry = _jour->country_first; 
     	
     	while(the_ctry != _jour->country_last+1) 
     	{
       		if(_country[the_ctry]->base_group==old_group) 
       		{
       			_country[the_ctry]->base_group=_country[the_ctry]->group; 
	   			_country[the_ctry]->status=FREE; 
	   			_country[the_ctry]->resistance=0; 
	   
			}
	   		the_ctry++;
		 }
		_group[old_group]->active=OFF;
	
		//------------------------------------------
	 	//tou_jours si un groupe vient d'etre anihilé		
	 	//on verifie aussi si le monde est conquis par un seul parti
	 	unsigned char free=0;	
	 	the_ctry = _jour->country_first; //pour pointer dans list pays
     	
     	while(the_ctry != _jour->country_last+1) 
     	{
    		if(_country[the_ctry]->group!=this->group) free++; 
	         	the_ctry++;
	 	}
	
	 	if(free==0)
	 	{
			char str[255],str2[255];
			sprintf(str,_group[this->group]->Name());
			sprintf(str2," CONQUERED THE WHOLE WORLD! GAME OVER...");
			strcat(str,str2);
			_jour->add_history(str);  
	 
	 		BAlert *alert = new BAlert("",str,"Rule!"); alert->Go();
	 		_jour->pause=ON;
	 		return; //pour pas qu'il fasse la verif ennemi pour personne en dessous
	 	}
	}//fin if exists

	//VERIFIE s'il y a plus d'ennemi pour personne (par exemple s'il reste plus que des démocracies ou que des anarchies)
	uint16 i=_jour->politic_first;
	uint16 yyy=_jour->politic_first;
	unsigned char only_friends=0;	  

	//relations de chaque politique
	while(i!=_jour->politic_last+1) 
    {
		if(_politic[i]->active == ON)
		{
			//relations de chaque politique
			while(yyy!=_jour->politic_last+1) 
           	{
           		//par rapport à chaque autre politique
				if(_politic[yyy]->active==ON)
           		{
           			if(_politic[yyy]->relation[i] == ENNEMY)
           				only_friends++;
           			
           			if(_politic[yyy]->relation[i] == NEUTRAL)
           				only_friends++;
           		}  
       		 	yyy++;
           	}	
		}
		i++;		
  		yyy=_jour->politic_first;
 	}
 				 
	if(_jour->game_started ==ON && only_friends==0)
	{
		char str[255];
		sprintf(str,"One or several flavors of ");
		strcat(str,_politic[_group[this->group]->politic]->Name());
		strcat(str," have managed to convert the world to their ideology.\n\nGAME OVER");		
		_jour->add_history(str);  
	 
	 	BAlert *alert = new BAlert("",str,"Wow!"); alert->Go();
	 	_jour->pause=ON;
	 	_jour->game_started=OFF;
	}
}//FIN COUNTRY