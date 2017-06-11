#ifndef POLITIC_H
#define POLITIC_H
//*************************************//
//******* Classe Group.h (alliance) *****//
//*************************************//

#include <String.h>

class Politic
{
public:
	unsigned char nb_pol;		//numero politique
	unsigned char relation[255]; //relation avec autres politiques
	unsigned char active; 		//si plus de guerre on check qui est actif, et ils gagnent ensemble
	float repression;
	float propaganda;

	Politic(const char *name, unsigned char num);	// constructeur nom + numero	

	inline	const char *Name()						{ return _name.String(); }
	inline	void		SetName(const char *name)	{ _name = name; }

protected:
	BString		_name;
}; 
#endif
