#include "attack.h"

/**** constructeur ****/
Attack::Attack(uint8 which_to_attack, uint16 days_before)
{
	victim_id = which_to_attack;
	days_before_attack = days_before;
	fighting = false;
}

/**** set army ****/ 
void Attack::SetArmy(uint8 which_type, uint64 amount)
{
	attack_army[which_type] = amount;
}