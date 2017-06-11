#ifndef ATTACK_H
#define ATTACK_H
//************************************//
//********* Classe Attack ************//
//************************************//

#include "def_col.h"
#include <Archivable.h>

class Day;
class Group;
class weapon;

class Attack: public BArchivable 
{
public:
   uint64	attack_army[MAX_WEAPON];
   uint8	victim_id;
   uint16	days_before_attack;
   bool		fighting;

   Attack(uint8 which_to_attack, uint16 days_before);
   Attack(BMessage *archive);
   
   //on fait le setarmy après la création dans une boucle
   void SetArmy(uint8 which_type, uint64 amount);
};
#endif
